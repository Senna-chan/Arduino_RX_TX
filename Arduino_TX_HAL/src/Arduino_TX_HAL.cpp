#include "Arduino_TX_HAL.h"

#include "Config.h"

#include "AUX_Serial_reader.h"
#include "ArduMath.hpp"
#include "ChannelFunctions.hpp"
#include "Encoder.h"
#include "I2CHelpers.h"
#include "MCPExpanders.h"
#include "MiscHelpers.hpp"
#include "SharedNRF.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "settingsHelper.h"
#include "usart.h"
#include <PlotterLib.h>
#include <SerialControlLibrary.h>
#include <SerialUtils.h>
#include <cstring>
#include <queue>
#include <stdarg.h>
#include <stdio.h>

void UART1Error(UART_HandleTypeDef* huart) {
#ifdef DEBUG
    __BKPT(0);
#endif
    // Error in main serial so what now?
}

SerialControlLibrary scl;

uint16_t lastCalButtons = 0;
uint16_t rawChannels[RC_MAX_CHANNELS];
uint16_t AUXRXChannels[RC_MAX_CHANNELS]; // AUX Serial channels temp capture
uint32_t IOExpanderBits = 0;
uint16_t prevRawChannels[RC_MAX_CHANNELS];
uint16_t parsedChannels[RC_MAX_CHANNELS];
uint16_t mappedChannels[RC_MAX_CHANNELS];
uint16_t detectingRawChannels[RC_MAX_CHANNELS];   /// DMA'd ADC Channels                   // TODO: Rename this eventualy
uint16_t detectedAUXRXChannels[RC_MAX_CHANNELS];  // AUX Serial channels refresing capture // TODO: Rename this eventualy
uint16_t detectingAUXRXChannels[RC_MAX_CHANNELS]; // AUX Serial channels refresing capture // TODO: Rename this eventualy

bool tx, fail, rx;

struct
{
    uint32_t send;
    uint32_t txack;
    uint32_t rx;
    uint32_t fail;
} radioStats;

bool allowInterrupts = false;          // In the beginning we are not allowed to process interrupts because of FreeRTOS
uint16_t interruptsToProcess = 0x0000; // Capture the interrupt pins that we didn't process yet
// Two counters because why TF doesn't the Tasks just run
uint16_t CALIRQNotProcessedLoops = 0;
uint16_t IOIRQNotProcessedLoops = 0;

void readIOExpanders() {
    // xSemaphoreTake(i2c_mutex, portMAX_DELAY);
    vPortEnterCritical();
    uint32_t lowBytes = IOExpander2.readGPIOAB();
    uint32_t highBytes = IOExpander1.readGPIOAB();
    IOExpanderBits = (highBytes << 16) | lowBytes;
    vPortExitCritical();
    // xSemaphoreGive(i2c_mutex);
}

void processIOInterrupt(void* parameter) {
    while (1) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        IOIRQNotProcessedLoops = 0;
        SerialPrint("IOTask: ");
        readIOExpanders();
        printBits(IOExpanderBits, true);
        ulTaskNotifyValueClear(NULL, UINT32_MAX);
    }
}

void readCALExpander() {
    // xSemaphoreTake(i2c_mutex, portMAX_DELAY);
    vPortEnterCritical();
    uint16_t buttons = calButtonExpender.readGPIOAB();
    vPortExitCritical();
    // xSemaphoreGive(i2c_mutex);
    printBits(buttons, true);
    for (int i = 0; i < 6; i++) {
        uint8_t btn = i * 2;
        int ch = i;
        if (bitRead(buttons, btn) && bitRead(buttons, btn + 1)) {
            SerialPrintf("CH%02d offset reset\n", ch + 1);
            settings.model[settings.activeModel].channel_settings[ch].trim = 0;
        } else if (bitRead(buttons, btn) && !bitRead(lastCalButtons, btn)) {
            settings.model[settings.activeModel].channel_settings[ch].trim++;
            SerialPrintf("CH%02d offset ++ to %d\n", ch + 1, settings.model[settings.activeModel].channel_settings[i].trim);
        } else if (bitRead(buttons, btn + 1) && !bitRead(lastCalButtons, btn + 1)) {
            settings.model[settings.activeModel].channel_settings[ch].trim--;
            SerialPrintf("CH%02d offset -- to %d\n", ch + 1, settings.model[settings.activeModel].channel_settings[i].trim);
        }
    }
    lastCalButtons = buttons;
}

void processCALInterrupt(void* parameter) {
    while (true) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        CALIRQNotProcessedLoops = 0;
        SerialPrint("CALTask: ");
        readCALExpander();
    }
}

void MainLoop(void* arg) {
    while (true) {
#if ENABLE_MCPIO
        if (HAL_GPIO_ReadPin(CAL_IRQ_GPIO_Port, CAL_IRQ_Pin) == GPIO_PIN_RESET) {
            TaskStatus_t taskStatus;
            vTaskGetInfo(cal_taskHandle, &taskStatus, pdTRUE, eInvalid);
            CALIRQNotProcessedLoops++;
            SerialPrintf("CAL IRQ is set for %3d loops. Taskstate = %d\n", CALIRQNotProcessedLoops, taskStatus.eCurrentState);
        }
        if (HAL_GPIO_ReadPin(MCP_IRQ_GPIO_Port, MCP_IRQ_Pin) == GPIO_PIN_RESET) {
            TaskStatus_t taskStatus;
            vTaskGetInfo(io_taskHandle, &taskStatus, pdTRUE, eInvalid);
            IOIRQNotProcessedLoops++;
            SerialPrintf("IO IRQ is set for %3d loops. Taskstate = %d.\n", IOIRQNotProcessedLoops, taskStatus.eCurrentState);
        }
#endif
#if DEBUG_ADC
        char buf[255] = { 0 };
        char* bufPtr = buf;
        for (int i = 0; i < DMABUFFERSIZE; i++) {
            bufPtr += sprintf(bufPtr, "ADC%02d: %04d  ", i, ADCDMABuffer[i]);
        }
        *bufPtr = '\n';
        SerialPrint(buf);
#endif

#if DEBUG_RADIO
        SerialPrintf("NRFStats: TX %7u ACK %7u RX %7u FAIL %7u\n", radioStats.send, radioStats.txack, radioStats.rx, radioStats.fail);
#endif
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Nothing so just sleep
    }
}

/**
 * Parses all the things to make the RC values.
 *
 * \param activeSettings        [in] Current active settings
 * \param channel_data          [out] Parsed and packed data
 * \param raw_channels          [in] Raw channels from ADC DMA buffer
 * \param parsed_channels       [out] Intermidiary buffer for parsed but not yet mapped data
 * \param mapped_channels       [out] Mapped data
 * \param IO_bits               [in] IOExpender bits from IOExpender 1 and 2
 * \param AUX_Serial_channels   [in] Aux serial channels
 */
void updateValues(Model* activeSettings, channelBitData* channel_data, const uint16_t* raw_channels, uint16_t* parsed_channels, uint16_t* mapped_channels, uint32_t IO_bits, uint16_t* AUX_Serial_Channels) {
    // Parse ADC channels
    for (int i = 0; i < ADCCHANNELNUMBERS; i++) {
        auto chSettings = activeSettings->channel_settings[i];
        parsed_channels[i] = parseADCChannel(raw_channels[i], chSettings.adcConfig.min, chSettings.adcConfig.mid, chSettings.adcConfig.max, activeSettings->deadzone, chSettings.trim);
    }

    for (int i = 0; i < RC_MAX_CHANNELS; i++) {
        auto chSettings = activeSettings->channel_settings[i];
        mapped_channels[i] = parseRCChannel(i, &chSettings, &activeSettings->rateLimitConfig, &activeSettings->outputEnable, bitRead(activeSettings->channelReversed, i), parsed_channels, IO_bits, AUX_Serial_Channels);
        if (mapped_channels[i] != 2023) {
            continue;
        }
        // Failsafe detection
        if (chSettings.startupVal != 0) {
            mapped_channels[i] = chSettings.startupVal;
        }
        if (chSettings.failsafe != 0) {
            mapped_channels[i] = chSettings.failsafe;
        }
    }

    // for (channelMixStruct channel_mixing : settings.model[settings.activeModel].channelMixing)
    //{
    //     if(channel_mixing.dest1 != 0 && channel_mixing.dest2 != 0 && channel_mixing.source1 != 0 && channel_mixing.source2 != 0)
    //     {
    //         mixChannels(mappedChannels[channel_mixing.source1], mappedChannels[channel_mixing.source2], &mappedChannels[channel_mixing.dest1], &mappedChannels[channel_mixing.dest2], MixTypes::AddSubtract);
    //     }
    // }

    channel_data->channel1 = mapped_channels[0] - 500;
    channel_data->channel2 = mapped_channels[1] - 500;
    channel_data->channel3 = mapped_channels[2] - 500;
    channel_data->channel4 = mapped_channels[3] - 500;
    channel_data->channel5 = mapped_channels[4] - 500;
    channel_data->channel6 = mapped_channels[5] - 500;
    channel_data->channel7 = mapped_channels[6] - 500;
    channel_data->channel8 = mapped_channels[7] - 500;
    channel_data->channel9 = mapped_channels[8] - 500;
    channel_data->channel10 = mapped_channels[9] - 500;
    channel_data->channel11 = mapped_channels[10] - 500;
    channel_data->channel12 = mapped_channels[11] - 500;
    channel_data->channel13 = mapped_channels[12] - 500;
    channel_data->channel14 = mapped_channels[13] - 500;
    channel_data->channel15 = mapped_channels[14] - 500;
    channel_data->channel16 = mapped_channels[15] - 500;
    channel_data->channel17 = mapped_channels[16] - 500;
    channel_data->channel18 = mapped_channels[17] - 500;
    channel_data->channel19 = mapped_channels[18] - 500;
    channel_data->channel20 = mapped_channels[19] - 500;
}

void nrfTransmitChannels(void* parameter) {
    while (true) {
        transmitTypes txData;
        memcpy(rawChannels, ADCDMABuffer, ADCCHANNELNUMBERS * 2);
#if ENABLE_AUX_SERIAL
        AUX_Serial_reader.getChannels(AUXRXChannels);
#endif
        updateValues(activeModel, &txData.ch_data, rawChannels, parsedChannels, mappedChannels, IOExpanderBits, AUXRXChannels);
        txData.ch_data.identifier = CHANNELDATAID;
        // SendDataToRX(txData.bytesUnion.u8, sizeof(transmitTypes));
        vTaskDelay(7 / portTICK_PERIOD_MS);
    }
}

void nrfTransmitTest(void* parameter) {
    while (true) {
        uint32_t now = HAL_GetTick();
        uint8_t txBuf[32];
        txBuf[0] = 1;
        txBuf[1] = 0;
        txBuf[2] = now >> 24 & 0xFF;
        txBuf[3] = now >> 16 & 0xFF;
        txBuf[4] = now >> 8 & 0xFF;
        txBuf[5] = now >> 0 & 0xFF;
        SerialPrintf("Sending message with time %u\n", now);

        Main_nRF.CE_L();

        // Transfer a data from the specified buffer to the TX FIFO
        Main_nRF.WritePayload(txBuf, 6);

        // Start a transmission by asserting CE pin (must be held at least 10us)
        Main_nRF.CE_H();

        delay_us(10);
        Main_nRF.CE_L();
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

// TODO: Check what this function does fully
void check_radio(void* parameters) {
    while (true) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        if (xSemaphoreTake(nrf_mutex, 7 / portTICK_PERIOD_MS) == pdFALSE) {
            SerialPrint("CHECKRADIO: nRF_BUSY\n");
        } else {
            uint8_t status = Main_nRF.GetIRQFlags();
            tx = (status & nRF24::FLAG_TX_DS) != 0;
            fail = (status & nRF24::FLAG_MAX_RT) != 0;
            rx = (status & nRF24::FLAG_RX_DR) != 0;
            uint8_t fifoStatus = Main_nRF.GetStatus_TXFIFO();
            if (fifoStatus == nRF24::FIFO_EMPTY) {
                Main_nRF.CE_L(); // All packets transmitted
            }

            if (tx) {
                radioStats.txack++;
#if DEBUG_RADIO
                SerialPrint("TXOK\n");
#endif
            }
            if (fail) { // TXFail
                radioStats.fail++;
#if DEBUG_RADIO
                SerialPrint("TXFERR\n");
#endif
            }

            if (rx) { // Did we receive a message?
                radioStats.rx++;
                // parseReceivednRFPacket();
            }
            Main_nRF.ClearIRQFlags();
            xSemaphoreGive(nrf_mutex);
        }
    }
}

void handlePlotter(void* parameter) {
    Plotter.init(&huart1, "Raw channels", &scl);
    for (int i = 0; i < ADCCHANNELNUMBERS; i++) {
        char adcNum[10];
        snprintf(adcNum, sizeof(adcNum), "ADC%02d", i);
        Plotter.addPlotData(&ADCDMABuffer[i], adcNum);
    }
    PlotterLib* chPlotter = Plotter.addNewPlotter("ChannelData");

    for (int i = 1; i <= RC_MAX_CHANNELS; i++) {
        char chNum[10];
        snprintf(chNum, sizeof(chNum), "CH%02d", i);
        chPlotter->addPlotData(&mappedChannels[i], chNum);
    }
    Plotter.setPlotState(false);
    chPlotter->setPlotState(false);

    while (true) {
        if (xSemaphoreTake(main_serial_mutex, 0xFF) == pdTRUE) {
            Plotter.loop();
            xSemaphoreGive(main_serial_mutex);
            vTaskDelay((Plotter.getTransmitInterval() + 2) / portTICK_PERIOD_MS);
        } else {
            SerialPrint("PLOT, SemaphoreLocked");
        }
    }
}

#pragma region SerialControl Functions
// TODO: mMake this function less complex
void transmitSettingsToRX() {
#if 0
    vTaskSuspend(nrfTransit_taskHandle);
    saveSettings(); // Be sure that we have saved the settings to EEPROM. This will do an update(read and write if needed)
    p_transmittingSettings.navigateTo();
    double settingsSizeAmountD = sizeof(Settings) / (double)SETTINGSDATASIZE;
    uint16_t settingsSizeAmount = (uint16_t)settingsSizeAmountD;
    uint8_t settingsModulo = sizeof(Settings) % SETTINGSDATASIZE;
    uint8_t* settingsPtr = (uint8_t*)&settings;

    Serial.printf("Transmitting settings to RX. Settings size %d. Settings packets %d(%5.2f) rest %d. Settings / 4 %f\n", sizeof(Settings), settingsSizeAmount, settingsSizeAmountD, settingsModulo, sizeof(Settings) / 4.0);
    int counter = 0;
    // Main CRC
    uint32_t settingscrc = HAL_CRC_Calculate(&crc_t, (uint32_t*)settingsPtr, sizeof(Settings) / 4);

    // start header packet
    memset(transmitterData.bytesUnion.u8, 0, 32);
    transmitterData.bytesUnion.u8[0] = SETTINGSDATASETUPID;
    transmitterData.bytesUnion.u8[1] = settingsSizeAmount >> 8;
    transmitterData.bytesUnion.u8[2] = settingsSizeAmount & 0xFF;
    transmitterData.bytesUnion.u8[3] = settingsModulo;
    uint16_t crc = gencrc(transmitterData.bytesUnion.u8, RFPACKETLENGTH - 2);
    transmitterData.settingsData.crc = crc;
    allowSettingsSend = false;
    counter = 0;
    int maxCounterVal = 200;
    int warningCounterVal = 10;

    // Serial.print("Header packet: ");
    // for (int b = 0; b < 32; b++) {
    //     Serial.printf("0x%02X ", transmitterData.bytesUnion.u8[b]);
    // }
    // Serial.println();
    do {
        SendDataToRX(transmitterData.bytesUnion.u8, 32);
        vTaskDelay(10);
    } while (!allowSettingsSend && ++counter < maxCounterVal);
    if (counter >= maxCounterVal) {
        Serial.println("Failed to transmit settingsheader");
        Error_Handler();
    }
    if (counter >= warningCounterVal) {
        Serial.printf("SettingsTX To long. c %d\r\n", counter);
    }
    // End header packet

    // Start data packets
    for (int i = 0; i < settingsSizeAmount; i++) {
        memset(transmitterData.bytesUnion.u8, 0, 32); // Clear mem
        transmitterData.settingsData.id = SETTINGSDATAID;
        transmitterData.settingsData.packetNumber = i;
        uint8_t* txsdPtr = (uint8_t*)&transmitterData.settingsData.data;
        memcpy(txsdPtr, settingsPtr, SETTINGSDATASIZE);
        crc = gencrc(transmitterData.bytesUnion.u8, RFPACKETLENGTH - 2);
        transmitterData.settingsData.crc = crc;
        settingsPtr += SETTINGSDATASIZE;
        allowSettingsSend = false;
        counter = 0;
        if (i % 40 == 0) {
            Serial.println("HMI Settings Update");
            char buf[52];
            sprintf(buf, "Currently at packet %d of %d", i, settingsSizeAmount);
            e_settingstxtorxprogress.setValue(buf);
        }
        // Serial.printf("packet_%d: ", i);
        // for (int b = 0; b < 32; b++) {
        //     Serial.printf("0x%02X ", transmitterData.bytesUnion.u8[b]);
        // }
        // Serial.println();
        do {
            SendDataToRX(transmitterData.bytesUnion.u8, 32);
            vTaskDelay(10);
            if (allowSettingsSend) {
                if (settingsAckValue != i) {
                    // Serial.printf("Wrong settings ack. Got %d want %d\r\n", settingsAckValue, i);
                } else if (settingsAckValue == i) {
                    break;
                }
            }
        } while (++counter < maxCounterVal);
        if (counter >= maxCounterVal) {
            Serial.printf("Failed to transmit settings packet %d. %d packets remaining\r\n", i, settingsSizeAmount - i);
            Error_Handler();
        }
        if (counter >= warningCounterVal) {
            Serial.printf("SettingsTX To long. c %d\r\n", counter);
        }
    }
    // End data packets

    // Start modulo packet
    transmitterData.settingsData.id = SETTINGSDATAID;
    transmitterData.settingsData.packetNumber = settingsSizeAmount;

    uint8_t* txsdPtr = (uint8_t*)&transmitterData.settingsData.data;
    memset(txsdPtr, 0, SETTINGSDATASIZE);
    counter = 0;
    if (settingsModulo != 0) { // Transmit last packet
        memcpy(txsdPtr, settingsPtr, settingsModulo);
    }
    crc = gencrc(transmitterData.bytesUnion.u8, RFPACKETLENGTH - 2);
    transmitterData.settingsData.crc = crc;

    allowSettingsSend = false;

    // Serial.print("modulo packet: ");
    // for (int b = 0; b < 32; b++) {
    //     Serial.printf("0x%02X ", transmitterData.bytesUnion.u8[b]);
    // }
    // Serial.println();
    do {
        SendDataToRX(transmitterData.bytesUnion.u8, 32);
        if (allowSettingsSend) {
            if (settingsAckValue != transmitterData.settingsData.packetNumber) {
                // Serial.printf("Wrong settings ack. Got %d want %d\r\n", settingsAckValue, transmitterData.bytesUnion.u8[1]);
            } else if (settingsAckValue == transmitterData.settingsData.packetNumber) {
                break;
            }
        }
        vTaskDelay(10);
    } while (++counter < maxCounterVal);
    if (counter >= maxCounterVal) {
        Error_Handler();
    }
    if (counter >= warningCounterVal) {
        Serial.printf("SettingsTX To long. c %d\r\n", counter);
    }
    counter = 0;
    // End modulo packet

    // Start finish packet
    memset(&transmitterData.bytesUnion.u8, 0, 32);
    transmitterData.settingsData.id = SETTINGSDATAID;
    transmitterData.settingsData.packetNumber = settingsSizeAmount + 1;
    transmitterData.bytesUnion.u32[1] = settingscrc;
    crc = gencrc(transmitterData.bytesUnion.u8, RFPACKETLENGTH - 2);
    transmitterData.settingsData.crc = crc;
    // Serial.printf("SettingsCRC %u\r\n", crc);
    allowSettingsSend = false;

    // Serial.print("Final packet: ");
    // for (int b = 0; b < 32; b++) {
    //     Serial.printf("0x%02X ", transmitterData.bytesUnion.u8[b]);
    // }
    // Serial.println();
    do {
        SendDataToRX(transmitterData.bytesUnion.u8, 32);
        if (allowSettingsSend) {
            if (settingsAckValue != transmitterData.settingsData.packetNumber) {
                // Serial.printf("Wrong settings ack. Got %d want %d\r\n", settingsAckValue, transmitterData.bytesUnion.u8[1]);
            } else if (settingsAckValue == transmitterData.settingsData.packetNumber) {
                break;
            }
        }
        vTaskDelay(10);
    } while (++counter < maxCounterVal);
    if (counter >= maxCounterVal) {
        Error_Handler();
    }
    if (counter >= warningCounterVal) {
        Serial.printf("SettingsTX To long. c %d\r\n", counter);
    }
    // End finish packet

    Serial.println("Finished transmitting settings");
    p_transmittingSettings.close();
    vTaskResume(nrfTransit_taskHandle);
#endif
}

void wipeEeprom() {
    SerialPrint("Wiping EEPROM\n");
    memset(&settings, 0, sizeof(Settings));
    generateDefaultSettings();
    activeModel = &settings.model[settings.activeModel];
    saveSettings();
    PrintCalValues();
    SerialPrint("Wipe done\n");
}

void resetMCU() {
    NVIC_SystemReset();
}
void setTransmitTest() {
#if ENABLE_RADIO

    TaskStatus_t taskStatus;
    vTaskGetInfo(nrfTransit_taskHandle, &taskStatus, pdTRUE, eInvalid);
    if (taskStatus.eCurrentState == eSuspended) {
        vTaskSuspend(nrfTransit_taskHandle);
        vTaskResume(nrfTransmitTest_taskHandle);
    } else {
        vTaskSuspend(nrfTransmitTest_taskHandle);
        vTaskResume(nrfTransit_taskHandle);
    }
#endif
}

void getAuxChannels() {
#if ENABLE_AUX_SERIAL
    SerialPrint("Aux channel data\n");
    char buf[255] = { 0 };
    char* bufPtr = buf;
    for (int i = 0; i < 14; i++) {
        bufPtr += sprintf(bufPtr, "AUX%i:%d\t", i, AUX_Serial_reader.getChannel(i));
    }
    *bufPtr = '\n';
    SerialPrint(buf);
#endif
}

#pragma endregion

void handleSerialControl(void* parameter) {
    scl.init(&huart1);
    scl.addVoidCallback("*", resetMCU);
    scl.addVoidCallback("t", setTransmitTest);
    scl.addVoidCallback("w", wipeEeprom);
    scl.addVoidCallback("s", transmitSettingsToRX);
    scl.addVoidCallback("AUXc", getAuxChannels);
    while (true) {
        if (xSemaphoreTake(main_serial_mutex, 0xFF) == pdTRUE) {
            scl.loop();
            xSemaphoreGive(main_serial_mutex);
            vTaskDelay(10 / portTICK_PERIOD_MS);
        } else {
            SerialPrint("SC, SemaphoreLocked");
        }
    }
}

extern "C" void vApplicationGetRandomHeapCanary(portPOINTER_SIZE_TYPE* pxHeapCanary) {
    if (pxHeapCanary != NULL) {
        *pxHeapCanary = 0x6E796161;
    }
}

void startFreeRTOS() {
    MX_FREERTOS_Init();

    vTaskStartScheduler();
}

void setupCPP() {
    // HAL_UART_RegisterCallback(&huart1, HAL_UART_TX_COMPLETE_CB_ID, UART1TXDone);
    // HAL_UART_RegisterCallback(&huart1, HAL_UART_ERROR_CB_ID, UART1Error);
    Serial1.create(&huart1);
    Serial1.init();
    SerialPrint("setupCPP()\n");
#if DEBUG_I2C
    scanI2C(&hi2c2);
#endif

    loadSettings();

#if ENABLE_ENCODER
    configureEncoder();
#endif

#if ENABLE_MCPIO
    setupMCPChips();
    xTaskCreate(processCALInterrupt, "CALExpander", 100, NULL, 21, &cal_taskHandle);
    xTaskCreate(processIOInterrupt, "IOExpander", 100, NULL, 20, &io_taskHandle);
#endif

#if ENABLE_SERIAL_CONTROL
    xTaskCreate(handleSerialControl, "SerialControl", 100, NULL, 3, &serialControl_taskHandle);
#endif

#if ENABLE_PLOTTER
    xTaskCreate(handlePlotter, "Plotter", 256, NULL, 4, &plotter_taskHandle);
#endif

#if ENABLE_RADIO
    Main_nRF.SetCEPin(NRF_CE_GPIO_Port, NRF_CE_Pin);
    Main_nRF.SetCSNPin(NRF_CSN_GPIO_Port, NRF_CSN_Pin);
    Main_nRF.SetSPI(&hspi3);
    Main_nRF.CSN_H();
    common_nRFInit(true);
    xTaskCreate(check_radio, "checkRadio", 50, NULL, 20, &nRFData_taskHandle);
    xTaskCreate(nrfTransmitTest, "nrfTest", 10, NULL, 1, &nrfTransmitTest_taskHandle);
    vTaskSuspend(nrfTransmitTest_taskHandle);
    xTaskCreate(nrfTransmitChannels, "nrfChannels", 100, NULL, 19, &nrfTransit_taskHandle);
    SerialPrint("WARNING: NRF TRANSMISSION IS DISABLED\n");
#endif

#if ENABLE_ADC
    memset(&ADCDMABuffer, 0, DMABUFFERSIZE * 2);
    HAL_ADC_Start_DMA(&hadc1, reinterpret_cast<uint32_t*>(ADCDMABuffer), DMABUFFERSIZE);
#endif

    xTaskCreate(MainLoop, "Main loop", 1280, NULL, 1, &main_taskHandle);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
    TaskStatus_t taskStatus;
    vTaskGetInfo(NULL, &taskStatus, pdTRUE, eInvalid);
    TaskHandle_t* taskToWake = nullptr;
    if (GPIO_Pin == ENC_IRQ_Pin) {
        SerialPrint("ENC IRQ ");
        taskToWake = &encoder_taskHandle;
    } else if (GPIO_Pin == NRF_IRQ_Pin) {
        // printf("NRF IRQ\n");
    } else if (GPIO_Pin == CAL_IRQ_Pin) {
        SerialPrint("CAL IRQ ");
        taskToWake = &cal_taskHandle;
        // xTaskNotifyFromISR(cal_taskHandle, 1, eSetValueWithOverwrite, &xHigherPriorityTaskWoken);
        // vTaskNotifyGiveFromISR(cal_taskHandle, &xHigherPriorityTaskWoken);
        // xTaskResumeFromISR(cal_taskHandle);
    } else if (GPIO_Pin == MCP_IRQ_Pin) {
        SerialPrint("IO IRQ ");
        taskToWake = &io_taskHandle;
        // xTaskNotifyFromISR(io_taskHandle, 1, eSetValueWithOverwrite, &xHigherPriorityTaskWoken);
        // vTaskNotifyGiveFromISR(io_taskHandle, &xHigherPriorityTaskWoken);
        // xTaskResumeFromISR(io_taskHandle);
    } else if (GPIO_Pin == TOUCH_IRQ_Pin) {
        // printf("TOUCH IRQ\n");
    }
    if (taskToWake != nullptr) {
        vTaskNotifyGiveFromISR(*taskToWake, &xHigherPriorityTaskWoken);
        SerialPrintf("H%ld\n", xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

void Error_Handler_CPP(const char* file, int line) {
    vTaskSuspendAll();
    TaskHandle_t currentTask = xTaskGetCurrentTaskHandle();
    TaskStatus_t taskStatus;
    vTaskGetInfo(currentTask, &taskStatus, pdTRUE, eInvalid);
    uint8_t printCount = 0;
    while (1) {
        HAL_Delay(100);
        if (++printCount % 10 == 0) {
            printf("Error in file '%s' Line %d, Task %s\n", file, line, taskStatus.pcTaskName);
        }
        if (printCount == 100) {
            HAL_NVIC_SystemReset();
        }
    }
}
