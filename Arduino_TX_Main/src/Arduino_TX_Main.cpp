// System includes
#include <Arduino.h>
#include <stm32f4xx_hal_crc.h>

// Config
#include "config.h"

// Library includes
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_MCP23X17.h>
#include <ArduinoTimerV2.h>
#include <MyHelpers.h>
#include <TimedAction.h>
#include <PlotterLib.h>
#include <SerialControlLibrary.h>
#include <BetterHardwareTimer.h>
#include <GUISlice_HMI_Lib.h>
#include <i2cEncoderLibV2.h>
#include <nrf24.hpp>

// My includes
#include <SharedFunctions.h>
#include <sharedSetup.h>
#include <Structs.h>
#include <SharedVars.h>
#include <ADCDMAFunctions.h>
#include "MCPExpanders.h"
#include "settingsHelper.h"
#include "STMRTOSIncludes.h"
#include "CompanionControl.h"
#include "Encoder.h"
#include "ChannelFunctions.h"
#include "Arduino_TX_Display_hmi.h"
#include <sharedNRF.h>
#include "AUX_Serial_reader.h"

#include "Arduino_TX_Main.h"

// extern "C"
// {
//     void* malloc(size_t size) {
//         if (size != 0)
//         {
//             return (pvPortMalloc(size));
//         }
//         return NULL;
//     }

//     void free(void* ptr)
//     {
//         if (ptr != NULL)
//         {
//             vPortFree(ptr);
//         }
//     }

//     //void* realloc(void* ptr, size_t size) {
//     //    free(ptr);
//     //    return malloc(size);
//     //}
// }

TaskHandle_t nRFData_taskHandle;            // nRF Receive task
TaskHandle_t plotter_taskHandle;            // Task for plotter stuff
TaskHandle_t hmi_taskHandle;                // Task for HMI Data transmission things
TaskHandle_t serialControl_taskHandle;        // Task for serial control library
TaskHandle_t companionSerial_taskHandle;    // Task for serial communication with the companion app. Custom protocol that bypasses SerialControl for easy use
TaskHandle_t nrfTransmitTest_taskHandle;    // Task for nrf transmission testing
TaskHandle_t nrfTransit_taskHandle;            // Task for nrf transmission
TaskHandle_t printNrfStats_taskHandle;        // Task for printing nrf communication stats
TaskHandle_t loop_taskHandle;

SemaphoreHandle_t hmi_mutex;        // Lock for HMI
SemaphoreHandle_t nrf_mutex;        // Lock for nRF
SemaphoreHandle_t serial_mutex;        // Lock for everything Serial

CRC_HandleTypeDef crc_t;
SerialControlLibrary scl;

bool debugging = true;

uint16_t lastCalButtons = 0;
uint16_t rawChannels[RC_MAX_CHANNELS];
uint16_t AUXRXChannels[RC_MAX_CHANNELS];   // AUX Serial channels temp capture
uint32_t IOExpanderBits = 0;
uint16_t detectingRawChannels[RC_MAX_CHANNELS];    /// DMA'd ADC Channels
uint16_t detectedAUXRXChannels[RC_MAX_CHANNELS];    // AUX Serial channels refresing capture // TODO: Rename this eventualy
uint16_t detectingAUXRXChannels[RC_MAX_CHANNELS];    // AUX Serial channels refresing capture // TODO: Rename this eventualy

HardwareSerial HMISerial = HardwareSerial(HMI_RX, HMI_TX);
HardwareSerial auxSerial = HardwareSerial(AUX_RX, AUX_TX);
TwoWire Wire2 = TwoWire(PB10, PB11);
bool eepromFound = false;

uint32_t prevSendTime;
bool printChannelValues = false;
bool printDMAValues = false;
bool printADCChannels = false;

bool allowSettingsSend = true;
uint16_t settingsAckValue = 0;

uint16_t buttonValues, oldButtonValues;

byte sendChannel = 0;

bool detectingChannelsSet = false;

uint16_t prevRawChannels[RC_MAX_CHANNELS];
uint16_t parsedChannels[RC_MAX_CHANNELS];
uint16_t mappedChannels[RC_MAX_CHANNELS];
uint16_t fixedChannelValue = 0;
uint32_t prevIOExpanderBits = 0;
uint16_t twoWay = 0;
uint8_t oneWay = 0;
bool transmitTest = false;
uint32_t lastMessageSend = 0;

bool tx, fail, rx;

struct {
    uint32_t send;
    uint32_t txack;
    uint32_t rx;
    uint32_t fail;
} radioStats;

#define BTN_K0 PE4
#define BTN_K1 PE3

HMI_Text* DispayRCObjs[RC_MAX_CHANNELS]{
    &e_n0, &e_n1, &e_n2, &e_n3, &e_n4, &e_n5, &e_n6, &e_n7, &e_n8, &e_n9,
    &e_n10, &e_n11, &e_n12, &e_n13, &e_n14, &e_n15, &e_n16, &e_n17, &e_n18, &e_n19,
    &e_n20, &e_n21, &e_n22, &e_n23
};

HMI_Text* rawDispObjs[12]{
    &e_nr0,
    &e_nr1,
    &e_nr2,
    &e_nr3,
    &e_nr4,
    &e_nr5,
    &e_nr6,
    &e_nr7,
    &e_nr8,
    &e_nr9,
    &e_dprevio,
    &e_dcurio
};

HMI_Text* calDispObjs[10][2]{
    {&e_d1, &e_c1},
    {&e_d2, &e_c2},
    {&e_d3, &e_c3},
    {&e_d4, &e_c4},
    {&e_d5, &e_c5},
    {&e_d6, &e_c6},
    {&e_d7, &e_c7},
    {&e_d8, &e_c8},
    {&e_d9, &e_c9},
    {&e_d10, &e_c10},
};

extern "C" void _Error_Handler(const char *file, int line)
{
    vTaskSuspendAll(); // Stop! Error time
    int count = 0;
    TaskHandle_t currentTask = xTaskGetCurrentTaskHandle();
    TaskStatus_t taskStatus;
    vTaskGetInfo(currentTask, &taskStatus, pdTRUE, eInvalid);
    while (1) {
        if (++count % 10 == 0) {
            Serial.printf("Error in file '%s' Line %d, Task %s\n", file, line, taskStatus.pcTaskName);
        }
        if (count == 100) HAL_NVIC_SystemReset();
        digitalToggle(LED_BUILTIN);
        delay(250);
    }
}

void notifyThread(TaskHandle_t taskHandle) {

}

// TODO: Move this to someplace else so we can maybe unit test the whole project
#pragma region SPIStuff
#ifdef ARDUINO_ARCH_STM32
SPI_HandleTypeDef nRF_hspi;
void HAL_SPI_MspInit(SPI_HandleTypeDef* hspi)
{
    GPIO_InitTypeDef GPIO_InitStruct = { 0 };
    if (hspi->Instance == SPI3)
    {
        /* USER CODE BEGIN SPI3_MspInit 0 */

        /* USER CODE END SPI3_MspInit 0 */
          /* Peripheral clock enable */
        __HAL_RCC_SPI3_CLK_ENABLE();

        __HAL_RCC_GPIOB_CLK_ENABLE();
        /**SPI3 GPIO Configuration
        PB3     ------> SPI3_SCK
        PB4     ------> SPI3_MISO
        PB5     ------> SPI3_MOSI
        */
        GPIO_InitStruct.Pin = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        /* USER CODE BEGIN SPI3_MspInit 1 */

        /* USER CODE END SPI3_MspInit 1 */
    }
}

void initSPI() {
    nRF_hspi.Instance = SPI3;
    nRF_hspi.Init.Mode = SPI_MODE_MASTER;
    nRF_hspi.Init.Direction = SPI_DIRECTION_2LINES;
    nRF_hspi.Init.DataSize = SPI_DATASIZE_8BIT;
    nRF_hspi.Init.CLKPolarity = SPI_POLARITY_LOW;
    nRF_hspi.Init.CLKPhase = SPI_PHASE_1EDGE;
    nRF_hspi.Init.NSS = SPI_NSS_SOFT;
    nRF_hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
    nRF_hspi.Init.FirstBit = SPI_FIRSTBIT_MSB;
    nRF_hspi.Init.TIMode = SPI_TIMODE_DISABLE;
    nRF_hspi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    nRF_hspi.Init.CRCPolynomial = 10;
    if (HAL_SPI_Init(&nRF_hspi) != HAL_OK)
    {
        Error_Handler();
    }
    __HAL_SPI_ENABLE(&nRF_hspi);

}
#else
void initSPI() {}
#endif
#pragma endregion

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
void updateValues(Model* activeSettings, channelBitData* channel_data, uint16_t* raw_channels, uint16_t* parsed_channels, uint16_t* mapped_channels, uint32_t IO_bits, uint16_t* AUX_Serial_Channels) {
    for (int i = 0; i < ADCCHANNELNUMBERS; i++)
    {
        auto chSettings = activeSettings->channel_settings[i];
        parsed_channels[i] = parseADCChannel(raw_channels[i], chSettings.chMin, chSettings.chMid, chSettings.chMax, activeSettings->deadzone, chSettings.chOffset);
    }

    for (int i = 0; i < RC_MAX_CHANNELS; i++) {
        auto chSettings = activeSettings->channel_settings[i];
        auto io1t = chSettings.channelMapping[0].type;
        auto io2t = chSettings.channelMapping[1].type;
        auto io1 = chSettings.channelMapping[0].index;
        auto io2 = chSettings.channelMapping[1].index;
        //auto outputMode = chSettings.outputMode;
        if (io1t == CTYPE_NONE && io2t == CTYPE_NONE) { // Not mapped
            mapped_channels[i] = 2023; // Make sure that RX will not parse this
            continue;
        }
        if (io1t != CTYPE_NONE && io2t == CTYPE_NONE) { // Single channel mapped
            switch(io1t)
            {
                case CTYPE_ADC:
                    mapped_channels[i] = parsed_channels[io1];
                break;

                case CTYPE_IO:
                    mapped_channels[i] = bitRead(IO_bits, io1) ? 2000 : 1000;
                break;

                case CTYPE_AUX_IO:

                break;

                case CTYPE_AUX_SERIAL:
                    mapped_channels[i] = AUX_Serial_reader.getChannel(io1);
                break;

                default:
                    Error_Handler();
                break;
            }
        }
        else if (io1t == CTYPE_IO && io2t == CTYPE_IO) // Multi IO mapped
        {
            bool b1 = bitRead(IO_bits, io1);
            bool b2 = bitRead(IO_bits, io2);
            if (!b1 && !b2) {
                mapped_channels[i] = 1500;
            }
            else if (b1 && !b2) {
                mapped_channels[i] = 2000;
            }
            else if (!b1 && b2) {
                mapped_channels[i] = 1000;
            }
            else {
                Serial.printf("CH%d invalid config. IO1 and IO2 both high", i);
            }
        }
        else { // Can't map ADC with IO or multiple ADC
            Serial.printf("CH Mapping for %d invalid. IOType1 %d Type2 %d\n", i, io1t, io2t); // Yes this is spammy
        }
        if (bitRead(activeSettings->channelReversed, i)) {
            int16_t tempVal = (mapped_channels[i] - 3000) * -1;
            mappedChannels[i] = tempVal;
        }
    }

    //for (channelMixStruct channel_mixing : settings.model[settings.activeModel].channelMixing)
    //{
    //    if(channel_mixing.dest1 != 0 && channel_mixing.dest2 != 0 && channel_mixing.source1 != 0 && channel_mixing.source2 != 0)
    //    {
    //        mixChannels(mappedChannels[channel_mixing.source1], mappedChannels[channel_mixing.source2], &mappedChannels[channel_mixing.dest1], &mappedChannels[channel_mixing.dest2], MixTypes::AddSubtract);
    //    }
    //}

     // Testing
    if (between(fixedChannelValue, 1000, 2000))
    {
        for (int i = 0; i < RC_MAX_CHANNELS; i++)
        {
            mapped_channels[i] = fixedChannelValue;
        }
    }

    // We can only send the 24 channels if it are 10 bit values so we need to subtract 1000 to get a range from 0 to 1000
    channel_data->channel1 =  mapped_channels[0]  - 1000;
    channel_data->channel2 =  mapped_channels[1]  - 1000;
    channel_data->channel3 =  mapped_channels[2]  - 1000;
    channel_data->channel4 =  mapped_channels[3]  - 1000;
    channel_data->channel5 =  mapped_channels[4]  - 1000;
    channel_data->channel6 =  mapped_channels[5]  - 1000;
    channel_data->channel7 =  mapped_channels[6]  - 1000;
    channel_data->channel8 =  mapped_channels[7]  - 1000;
    channel_data->channel9 =  mapped_channels[8]  - 1000;
    channel_data->channel10 = mapped_channels[9]  - 1000;
    channel_data->channel11 = mapped_channels[10] - 1000;
    channel_data->channel12 = mapped_channels[11] - 1000;
    channel_data->channel13 = mapped_channels[12] - 1000;
    channel_data->channel14 = mapped_channels[13] - 1000;
    channel_data->channel15 = mapped_channels[14] - 1000;
    channel_data->channel16 = mapped_channels[15] - 1000;
    channel_data->channel17 = mapped_channels[16] - 1000;
    channel_data->channel18 = mapped_channels[17] - 1000;
    channel_data->channel19 = mapped_channels[18] - 1000;
    channel_data->channel20 = mapped_channels[19] - 1000;
    channel_data->channel21 = mapped_channels[20] - 1000;
    channel_data->channel22 = mapped_channels[21] - 1000;
    channel_data->channel23 = mapped_channels[22] - 1000;
    channel_data->channel24 = mapped_channels[23] - 1000;
}

#pragma region IRQ functions

void setNrfIRQFlag() {
    vTaskNotifyGiveFromISR(nRFData_taskHandle, NULL);
}

#pragma endregion
void SendDataToRX(uint8_t* data, uint8_t dataSize) {
#if ENABLE_RADIO
    radioStats.send++;
    if (xSemaphoreTake(nrf_mutex, 7 / portTICK_RATE_MS) == pdFALSE) {
        Serial.println("SendData FATAL: Failed to take mutex");
    }
    else
    {
        uint32_t counter = 0;
        do {
            uint8_t fifoStatus = nRF24_GetStatus_TXFIFO();
            if (fifoStatus != nRF24_STATUS_TXFIFO_EMPTY) {
                nRF24_CE_H(); // Buffer not empty yet trigger retransmit
                delayMicroseconds(15);
                nRF24_CE_L();
            }
            else if(fifoStatus == nRF24_STATUS_TXFIFO_FULL) {
                Serial.println("TXFULL. NOT GOOD");
                Error_Handler();
            }
            else {
                break;
            }
        } while (++counter < 5);
        //Serial.print("Sending");

        nRF24_CE_L();

        // Transfer a data from the specified buffer to the TX FIFO
        nRF24_WritePayload(data, dataSize);

        // Start a transmission by asserting CE pin (must be held at least 10us)
        nRF24_CE_H();

        delayMicroseconds(15);

        nRF24_CE_L(); // Pull it low

        prevSendTime = micros();
        xSemaphoreGive(nrf_mutex);
    }
#endif
}

// TODO: Rewrite this to accept a data input and to provide a output pointer
void parseReceivednRFPacket() {
    while (true){
        uint8_t buf[32];
        uint8_t length = 0;
        nRF24_RXResult pipeLine = nRF24_ReadPayloadDpl(buf, &length);
        if (pipeLine == nRF24_RX_EMPTY)
            return; // Nothing left in buffer.
        if (length == 6) {
            //Serial.printf("%s Message size '%d'. Data: ", isTransmitter ? "ACK" : "Message", length);
            //for (int i = 0; i < length; i++) {
            //    Serial.printf(" %02d ", buf[i]);
            //}
            //Serial.println();
        }
        else
        {
            //Serial.printf("nRF_SIZE %d\r\n", length);
            //if (length == 32) {
            memmove(receiverData.bytesUnion.u8, buf, length);
            uint8_t packetId = receiverData.packetId.id;
            switch (packetId) {
            case SETTINGSDATAID:
                //Serial.printf("SETTINGSACK");
                allowSettingsSend = true;
                settingsAckValue = receiverData.settingsDataAck.settingsPacket;
                break;
            }
        }
    }
}


#pragma region SerialControl Functions
// TODO: mMake this function less complex
void transmitSettingsToRX() {
#ifdef DISABLE_NRF
    return;
#endif

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

    //Serial.print("Header packet: ");
    //for (int b = 0; b < 32; b++) {
    //    Serial.printf("0x%02X ", transmitterData.bytesUnion.u8[b]);
    //}
    //Serial.println();
    do {
        SendDataToRX(transmitterData.bytesUnion.u8, 32);
        vTaskDelay(10);
    } while (!allowSettingsSend && ++counter < maxCounterVal);
    if (counter >= maxCounterVal) {
        Serial.println("Failed to transmit settingsheader");
        Error_Handler();
    }
    if (counter >= warningCounterVal) Serial.printf("SettingsTX To long. c %d\r\n", counter);
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
        //Serial.printf("packet_%d: ", i);
        //for (int b = 0; b < 32; b++) {
        //    Serial.printf("0x%02X ", transmitterData.bytesUnion.u8[b]);
        //}
        //Serial.println();
        do {
            SendDataToRX(transmitterData.bytesUnion.u8, 32);
            vTaskDelay(10);
            if (allowSettingsSend) {
                if (settingsAckValue != i) {
                    //Serial.printf("Wrong settings ack. Got %d want %d\r\n", settingsAckValue, i);
                }
                else if (settingsAckValue == i) {
                    break;
                }
            }
        } while (++counter < maxCounterVal);
        if (counter >= maxCounterVal) {
            Serial.printf("Failed to transmit settings packet %d. %d packets remaining\r\n", i, settingsSizeAmount - i);
            Error_Handler();
        }
        if (counter >= warningCounterVal) Serial.printf("SettingsTX To long. c %d\r\n", counter);
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

    //Serial.print("modulo packet: ");
    //for (int b = 0; b < 32; b++) {
    //    Serial.printf("0x%02X ", transmitterData.bytesUnion.u8[b]);
    //}
    //Serial.println();
    do {
        SendDataToRX(transmitterData.bytesUnion.u8, 32);
        if (allowSettingsSend) {
            if (settingsAckValue != transmitterData.settingsData.packetNumber) {
                //Serial.printf("Wrong settings ack. Got %d want %d\r\n", settingsAckValue, transmitterData.bytesUnion.u8[1]);
            }
            else if (settingsAckValue == transmitterData.settingsData.packetNumber) {
                break;
            }
        }
        vTaskDelay(10);
    } while (++counter < maxCounterVal);
    if (counter >= maxCounterVal) Error_Handler();
    if (counter >= warningCounterVal) Serial.printf("SettingsTX To long. c %d\r\n", counter);
    counter = 0;
    // End modulo packet

    // Start finish packet
    memset(&transmitterData.bytesUnion.u8, 0, 32);
    transmitterData.settingsData.id = SETTINGSDATAID;
    transmitterData.settingsData.packetNumber = settingsSizeAmount + 1;
    transmitterData.bytesUnion.u32[1] = settingscrc;
    crc = gencrc(transmitterData.bytesUnion.u8, RFPACKETLENGTH - 2);
    transmitterData.settingsData.crc = crc;
    //Serial.printf("SettingsCRC %u\r\n", crc);
    allowSettingsSend = false;

    //Serial.print("Final packet: ");
    //for (int b = 0; b < 32; b++) {
    //    Serial.printf("0x%02X ", transmitterData.bytesUnion.u8[b]);
    //}
    //Serial.println();
    do {
        SendDataToRX(transmitterData.bytesUnion.u8, 32);
        if (allowSettingsSend) {
            if (settingsAckValue != transmitterData.settingsData.packetNumber) {
                //Serial.printf("Wrong settings ack. Got %d want %d\r\n", settingsAckValue, transmitterData.bytesUnion.u8[1]);
            }
            else if (settingsAckValue == transmitterData.settingsData.packetNumber) {
                break;
            }
        }
        vTaskDelay(10);
    } while (++counter < maxCounterVal);
    if (counter >= maxCounterVal) Error_Handler();
    if (counter >= warningCounterVal) Serial.printf("SettingsTX To long. c %d\r\n", counter);
    // End finish packet

    Serial.println("Finished transmitting settings");
    p_transmittingSettings.close();
    vTaskResume(nrfTransit_taskHandle);
}

void wipeEeprom() {
    Serial.println("Wiping EEPROM");
    memset(&settings, 0, sizeof(Settings));
    generateDefaultSettings();
    activeModel = &settings.model[settings.activeModel];
    saveSettings();
    PrintCalValues();
    Serial.println("Wipe done");
}

void resetMCU() {
    NVIC_SystemReset();
}

void setTransmitTest() {
#ifdef DISABLE_NRF
    return;
#endif
    transmitTest = !transmitTest;
    if (transmitTest) {
        vTaskResume(nrfTransmitTest_taskHandle);
        vTaskSuspend(nrfTransit_taskHandle);
    }
    else {
        vTaskSuspend(nrfTransmitTest_taskHandle);
        vTaskResume(nrfTransit_taskHandle);
    }
}

void setHMITracing(const char* data) {
    Serial.print("Setting HMI Tracing ");
    Serial.println(data[0] == '1' ? "on" : "off");
    HMI.setTracing(data[0] == '1');
}
void setHMIDebugging(const char* data) {
    Serial.print("Setting HMI Debugging ");
    Serial.println(data[0] == '1' ? "on" : "off");
    HMI.setDebugging(data[0] == '1');
}

void getAuxChannels(){
    Serial.println("Aux channel data");
    for (int i = 0; i < 14; i++)
    {
        Serial.printf("AUX%i:%d\t", i, AUX_Serial_reader.getChannel(i));
    }
    Serial.println();
}

#pragma endregion

#pragma region FreeRTOS tasks

void nrfTransmitChannels(void* parameter)
{
    while (true) {
        transmitTypes txData;
        memcpy(rawChannels, ADCDMABuffer, ADCCHANNELNUMBERS * 2);
        AUX_Serial_reader.getChannels(AUXRXChannels);
        updateValues(activeModel, &txData.ch_data, rawChannels, parsedChannels, mappedChannels, IOExpanderBits, AUXRXChannels);
        txData.ch_data.identifier = CHANNELDATAID;
        SendDataToRX(txData.bytesUnion.u8, sizeof(transmitTypes));
        vTaskDelay(7 / portTICK_RATE_MS);
    }
}

void nrfTransmitTest(void* parameter) {
    while (true) {
        uint32_t now = millis();
        lastMessageSend = now;
        uint8_t txBuf[32];
        txBuf[0] = 1;
        txBuf[1] = 0;
        txBuf[2] = now >> 24 & 0xFF;
        txBuf[3] = now >> 16 & 0xFF;
        txBuf[4] = now >> 8 & 0xFF;
        txBuf[5] = now >> 0 & 0xFF;
        Serial.printf("Sending message with time %d\n", now);

        nRF24_CE_L();

        // Transfer a data from the specified buffer to the TX FIFO
        nRF24_WritePayload(txBuf, 6);

        // Start a transmission by asserting CE pin (must be held at least 10us)
        nRF24_CE_H();

        delayMicroseconds(10);
        nRF24_CE_L();
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}

// TODO: Check what this function does fully
void check_radio(void* parameters)
{
    while (true) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        if (xSemaphoreTake(nrf_mutex, 7 / portTICK_RATE_MS) == pdFALSE) {
            Serial.println("CHECKRADIO: nRF_BUSY");
        }
        else {
            uint8_t status = nRF24_GetIRQFlags();
            tx = (status & nRF24_FLAG_TX_DS) != 0;
            fail = (status & nRF24_FLAG_MAX_RT) != 0;
            rx = (status & nRF24_FLAG_RX_DR) != 0;
            uint8_t fifoStatus = nRF24_GetStatus_TXFIFO();
            if (fifoStatus == nRF24_STATUS_TXFIFO_EMPTY) {
                nRF24_CE_L(); // All packets transmitted
            }

            if (tx) {
                radioStats.txack++;
                //if(debugging) Serial.println("TXOK");
            }
            if (fail) { // TXFail
                radioStats.fail++;
                //if (debugging) Serial.println("TXFERR");
            }

            if (rx) {                      // Did we receive a message?
                radioStats.rx++;
                parseReceivednRFPacket();
            }
            nRF24_ClearIRQFlags();
            xSemaphoreGive(nrf_mutex);
        }
    }
}

void printNrfStats(void* parameter) {
    while (true) {
        Serial.printf("NRFStats: TX %7d ACK %7d RX %7d FAIL %7d\r\n", radioStats.send, radioStats.txack, radioStats.rx, radioStats.fail);
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}

uint32_t sendRCChannelTime;
void HMIdoSetupChannel()
{
    if (detectingIO != 0 && !detectingChannelsSet)
    {
        detectingChannelsSet = true;
        memcpy(detectingRawChannels, rawChannels, ADCCHANNELNUMBERS * 2);
        memcpy(detectedAUXRXChannels, AUXRXChannels, RC_MAX_CHANNELS * 2);
        sendRCChannelTime = millis();
    }
    if (detectingIO != 0)
    {
        for (uint8_t i = 0; i < RC_MAX_CHANNELS; i++)
        {
            if (i < 12) // ADC Checking
            {
                if (abs((int16_t)detectingRawChannels[i] - (int16_t)rawChannels[i]) > 200)
                {
                    char str[25];
                    snprintf(str, sizeof(str), "Detected ADC %u", i);
                    Serial.printf("ADCDETECT: %s\n", str);
                    if (detectingIO == 1)
                    {
                        detectedIO1.type = CTYPE_ADC;
                        detectedIO1.index = i;
                        e_detectIO1.setValue(str);
                    }
                    else if (detectingIO == 2)
                    {
                        Serial.printf("INVALID");
                        e_detectIO2.setValue("INVALID");
                    }
                    detectingChannelsSet = false;
                    detectingIO = 0;
                }
            }
            if (abs((int16_t)detectingAUXRXChannels[i] - (int16_t)detectedAUXRXChannels[i]) > 200)
            {
                char str[25];
                snprintf(str, sizeof(str), "Detected AUX_RX %u", i);
                Serial.printf("AUXDETECT: %s\n", str);
                if (detectingIO == 1)
                {
                    detectedIO1.type = CTYPE_AUX_SERIAL;
                    detectedIO1.index = i;
                    e_detectIO1.setValue(str);
                }
                else if (detectingIO == 2)
                {
                    Serial.printf("INVALID");
                    e_detectIO2.setValue("INVALID");
                }
                detectingChannelsSet = false;
                detectingIO = 0;
            }
        }
    }

    auto io1t = activeModel->channel_settings[channelToEditIdx].channelMapping[0].type;
    auto io2t = activeModel->channel_settings[channelToEditIdx].channelMapping[1].type;
    // if (io1t != CTYPE_NONE || io2t != CTYPE_NONE)
    // {
    //     if (millis() - sendRCChannelTime > 100)
    //     {
    //         sendRCChannelTime = millis();
    //         e_channelval.setValue(mappedChannels[channelToEditIdx]);
    //     }
    // }
}
// TODO: Rewrite this to be more simple and to have the bussiness code in a seperate function
uint32_t lastHMIRefresh = 0;
void updateHMITask(void* parameter) {
    while (true) {
        if (xSemaphoreTake(hmi_mutex, 10 / portTICK_RATE_MS) == pdFALSE) {
            Serial.println("updateHMITask failed to get mutex");
        }
        else
        {
            // TODO: Seperate function with params for channel buffers
            HMI.loop(hmiObjects);
            uint8_t currentPageId = HMI.getCurrentPageId();
            switch (currentPageId)
            {
                case HMIPageElems::calibrations:
                    calDispObjs[sendChannel][0]->setValue(rawChannels[sendChannel]);
                    calDispObjs[sendChannel][1]->setValue(parsedChannels[sendChannel]);
                    sendChannel++;
                    if (sendChannel == ADCCHANNELNUMBERS) {
                        sendChannel = 0;
                    }
                break;

                case HMIPageElems::setupChannel:
                    HMIdoSetupChannel();
                break;
            }

            if (HMI.getCurrentPageId() == HMIPageElems::DisplayRcValues) {
                DispayRCObjs[sendChannel]->setValue(mappedChannels[sendChannel]);
                sendChannel++;
                if (sendChannel == 24) {
                    sendChannel = 0;
                }
            }
            if (HMI.getCurrentPageId() == HMIPageElems::DisplayRawValues) {
                if (sendChannel < 10) {
                    rawDispObjs[sendChannel]->setValue(rawChannels[sendChannel]);
                }
                else if (sendChannel == 10)
                {
                    char buffer[33];
                    for (uint i = 0; i < 32; i++)
                    {
                        buffer[31 - i] = '0' + ((prevIOExpanderBits & (1u << i)) > 0);
                    }
                    buffer[32] = '\0';
                    rawDispObjs[sendChannel]->setValue(buffer);
                }
                else if (sendChannel == 11)
                {
                    char buffer[33];
                    for (uint i = 0; i < 32; i++)
                    {
                        buffer[31 - i] = '0' + ((IOExpanderBits & (1u << i)) > 0);
                    }
                    buffer[32] = '\0';
                    rawDispObjs[sendChannel]->setValue(buffer);
                }
                sendChannel++;
                if (sendChannel == 12)
                {
                    sendChannel = 0;
                }
            }
            if (millis() - lastHMIRefresh > 5000) {

                switch (HMI.getCurrentPageId()) {
                case HMIPageElems::calibrations:
                case HMIPageElems::DisplayRawValues:
                case HMIPageElems::DisplayRcValues:
                    HMI.refreshDisplay();
                    break;
                }
                lastHMIRefresh = millis();
            }
            xSemaphoreGive(hmi_mutex);
        }
        vTaskDelay(10 / portTICK_PERIOD_MS); // Delay 10 ms
    }
}

void processIOInterrupt(void* parameter) {
    while (true) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        IOExpanderBits = (IOExpander1.readGPIOAB() << 16) | IOExpander2.readGPIOAB();
    }
}

void processCALInterrupt(void* parameter) {
    while (1) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        xSemaphoreTake(i2c_mutex, portMAX_DELAY);
        uint16_t buttons = calButtonExpender.readGPIOAB();
        //Serial.print("CAL Interrupt ");
        //printBits(&Serial, buttons, true);
        for (int i = 0; i < 6; i++)
        {
            uint8_t btn = i * 2;
            int ch = i;
            if (bitRead(buttons, btn) && bitRead(buttons, btn + 1))
            {
                Serial.printf("CH%02d offset reset\n", ch + 1);
                settings.model[settings.activeModel].channel_settings[ch].chOffset = 0;
            }
            else if (bitRead(buttons, btn) && !bitRead(lastCalButtons, btn))
            {
                settings.model[settings.activeModel].channel_settings[ch].chOffset++;
                Serial.printf("CH%02d offset ++ to %d\n", ch + 1, settings.model[settings.activeModel].channel_settings[i].chOffset);
            }
            else if (bitRead(buttons, btn + 1) && !bitRead(lastCalButtons, btn + 1))
            {
                settings.model[settings.activeModel].channel_settings[ch].chOffset--;
                Serial.printf("CH%02d offset -- to %d\n", ch + 1, settings.model[settings.activeModel].channel_settings[i].chOffset);
            }
        }
        lastCalButtons = buttons;

        xSemaphoreGive(i2c_mutex);
    }
}

void handlePlotter(void* parameter) {
    while (true) {
        Plotter.loop();
        vTaskDelay((Plotter.getTransmitInterval() + 2) / portTICK_RATE_MS);
    }
}

void handleSerialControl(void* parameter) {
    while (true) {
        scl.loop();
        vTaskDelay(10 / portTICK_RATE_MS);
    }
}

void miscTask(void* param)
{
    while (true)
    {
        if (IOExpanderBits != prevIOExpanderBits)
        {
            Serial.print("IOExpander IRQ. ");
            printBits(&Serial, IOExpanderBits, false);
            Serial.print(" Changed bits: ");
            for (int b = 0; b < 32; b++) {
                if (bitRead(prevIOExpanderBits, b) != bitRead(IOExpanderBits, b))
                {
                    if (bitRead(IOExpanderBits, b) && detectingIO != 0)
                    {
                        auto str = String("Detected IO ");
                        str.concat(b);
                        Serial.printf("IODETECT: %s\n", str.c_str());
                        if (detectingIO == 1)
                        {
                            detectedIO1.type = CTYPE_IO;
                            detectedIO1.index = b;
                            e_detectIO1.setValue(str.c_str());
                        }
                        else if (detectingIO == 2)
                        {
                            detectedIO2.type = CTYPE_IO;
                            detectedIO2.index = b;
                            e_detectIO2.setValue(str.c_str());
                        }
                        detectingIO = 0;
                    }
                    Serial.printf("%d now %s, ", b, bitRead(IOExpanderBits, b) ? "HIGH" : "LOW");
                }
            }
            Serial.println();
        }
        vTaskDelay(100 / portTICK_RATE_MS);
    }
}

void initFreeRTOS() {
    hmi_mutex = xSemaphoreCreateMutex();
    nrf_mutex = xSemaphoreCreateMutex();
    i2c_mutex = xSemaphoreCreateMutex();
    serial_mutex = xSemaphoreCreateMutex();

    xTaskCreate(check_radio, "checkRadio", 50, NULL, 20, &nRFData_taskHandle);
    xTaskCreate(processCALInterrupt, "calibrate_task", 50, NULL, 10, &cal_taskHandle);
    xTaskCreate(processIOInterrupt, "IOExpander", 10, NULL, 10, &io_taskHandle);
    xTaskCreate(processEncoder, "encoder", 50, NULL, 10, &encoder_taskHandle);
    //xTaskCreate(handlePlotter, "plotter", 256, NULL,1, &plotter_taskHandle);
#if ENABLE_HMI
    xTaskCreate(updateHMITask,"HMI", 256, NULL,6, &hmi_taskHandle);
#endif
    xTaskCreate(handleSerialControl,"SerialControl", 256, NULL,5, &serialControl_taskHandle);
#if ENABLE_CONTROLLER_COMPANION
    xTaskCreate(handleCompanionControl,"CompanionControl",1024, &SerialUSB,1, &companionSerial_taskHandle);
#endif
    xTaskCreate(nrfTransmitTest,"nrfTest", 10, NULL,20, &nrfTransmitTest_taskHandle);
    vTaskSuspend(nrfTransmitTest_taskHandle);
    xTaskCreate(nrfTransmitChannels,"nrfChannels", 100, NULL,20, &nrfTransit_taskHandle);
#ifdef DISABLE_NRF
    Serial.println("WARNING: NRF TRANSMISSION IS DISABLED");
#endif
    xTaskCreate(miscTask, "MiscTask", 20, NULL, 1, &loop_taskHandle);
    delay(1000);
    //xTaskCreate(printNrfStats,"nrfChannels",1024, NULL,1, &printNrfStats_taskHandle);
}
#pragma endregion


#pragma region Setup Hardware/Software

void initAuxSerial(){
    AUX_Serial_reader.init(&auxSerial);
    AUX_Serial_reader.setProtocol(Aux_Serial_Reader::IBUS);
    AUX_Serial_reader.begin();
}

void initSerialControl() {
    scl.init(&Serial1);
    scl.addVoidCallback("*", resetMCU);
    scl.addVoidCallback("t", setTransmitTest);
    scl.addVoidCallback("w", wipeEeprom);
    scl.addVoidCallback("s", transmitSettingsToRX);
    scl.addDataCallback("HMIt", setHMITracing);
    scl.addDataCallback("HMId", setHMIDebugging);
    scl.addVoidCallback("AUXc", getAuxChannels);
}

void initPlotter()
{

    Plotter.init(&Serial1, "Raw channels", &scl);
    for (int i = 0; i < ADCCHANNELNUMBERS; i++) {
        char adcNum[10];
        sprintf(adcNum, "ADC%02d", i);
        Plotter.addPlotData(&ADCDMABuffer[i], adcNum);
    }
    PlotterLib* chPlotter = Plotter.addNewPlotter("ChannelData");

    for (int i = 1; i <= 24; i++) {
        char chNum[10];
        sprintf(chNum, "CH%02d", i);
        chPlotter->addPlotData(&mappedChannels[i], chNum);
    }
    Plotter.setPlotState(false);
    chPlotter->setPlotState(false);
}


#pragma endregion

void setup()
{
    CoreDebug->DHCSR |= CoreDebug_DHCSR_C_DEBUGEN_Msk;
    uint32_t startSetup = millis();
    Serial.begin(115200);
    // SerialUSB.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(PE3, INPUT_PULLDOWN);
    pinMode(BTN_K0, INPUT_PULLDOWN);
    pinMode(BTN_K1, INPUT_PULLDOWN);
    delay(50);

    if (digitalRead(PE3)) {
        transmitTest = true;
        Serial.println("TransmitTest");
    }
    digitalWrite(LED_BUILTIN, HIGH);

#if DEBUG_HMI
    HMI.setDebugging(true);
#endif
#if TRACE_HMI
    HMI.setTracing(true);
#endif

    Serial.println("Starting TX");

#if ENABLE_HMI
    initHMI();
#endif
    initStructs();
#if DEBUG
    Serial.printf("Size of settings is %d bytes\n", sizeof(settings));
#endif

    setupWire1();

#if 1
    scanI2C(&Wire, &Serial);
#endif

#if ENABLE_EEPROM
    int count = 20;
    do
    {
        if (I2CDeviceConnected(&Wire, 0x50))
        {
            eepromFound = true;
            break;
        }
        Serial.println("I2C Failure. EEPROM on 0x50 not found, EEPROM is most recommended");
        delay(1000);
        count--;
    } while (count > 0);
#endif

#if ENABLE_MCPIO
    setupMCPChips();
#endif
    loadSettings();

    ADCInit();

    ADCStart();

    memset(&transmitterData.bytesUnion.u8, 0, 32);
    PrintCalValues();

#if ENABLE_ENCODER
    configureEncoder();
#endif

    pinMode(cePin, OUTPUT);
    pinMode(csnPin, OUTPUT);
    digitalWrite(csnPin, HIGH);
    pinMode(irqPin, INPUT);
    attachInterrupt(irqPin, setNrfIRQFlag, FALLING);
    nRF24_SetCEPin(cePin);
    nRF24_SetCSNPin(csnPin);
    initSPI();

#if ENABLE_RADIO
    common_nRFInit();
    // Set TX power
    nRF24_SetTXPower(nRF24_TXPWR_18dBm);
#endif

#if ENABLE_MCPIO
    IOExpanderBits = (IOExpander1.readGPIOAB() << 16) | IOExpander2.readGPIOAB();
#else
    IOExpanderBits = 0;
#endif
    initPlotter();

#if ENABLE_AUX_SERIAL
    initAuxSerial();
#endif

    initSerialControl();

    initFreeRTOS();
    crc_t.Instance = CRC;
    if (HAL_CRC_Init(&crc_t) != HAL_OK)
    {
        Error_Handler();
    }
    __HAL_RCC_CRC_CLK_ENABLE();
    Serial.printf("Started in %d millis\n", millis() - startSetup);
    uint32_t max_head_size = configTOTAL_HEAP_SIZE;
    Serial.printf("Max stack/head size %u, Free now %u\n", max_head_size, xPortGetFreeHeapSize());
    vTaskStartScheduler();
    Serial.println("FATAL ERROR OCCURED");
}

void loop()
{
    // Not used because of FreeRTOS
}

