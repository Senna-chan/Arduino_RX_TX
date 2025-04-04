#include "Arduino_TX_HAL.h"

#include <cstring>

#include "Encoder.h"
#include "SharedNRF.h"
#include "MCPExpanders.h"
#include "i2c.h"
#include "dma.h"
#include "adc.h"
#include "I2CHelpers.h"
#include "ArduMath.hpp"
#include "MiscHelpers.hpp"
#include "settingsHelper.h"
#include "Config.h"
#include "ChannelFunctions.hpp"


uint16_t lastCalButtons = 0;
uint16_t rawChannels[RC_MAX_CHANNELS];
uint16_t AUXRXChannels[RC_MAX_CHANNELS]; // AUX Serial channels temp capture
uint32_t IOExpanderBits = 0;
uint16_t prevRawChannels[RC_MAX_CHANNELS];
uint16_t parsedChannels[RC_MAX_CHANNELS];
uint16_t mappedChannels[RC_MAX_CHANNELS];
uint16_t detectingRawChannels[RC_MAX_CHANNELS];   /// DMA'd ADC Channels
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

bool allowInterrupts = false; // In the beginning we are not allowed to process interrupts because of FreeRTOS
uint16_t interruptsToProcess = 0x0000; // Capture the interrupt pins that we didn't process yet
// Two counters because why TF doesn't the Tasks just run
uint16_t CALIRQNotProcessedLoops = 0;
uint16_t IOIRQNotProcessedLoops = 0;

void readIOExpanders(){
    xSemaphoreTake(i2c_mutex, portMAX_DELAY);
    vPortEnterCritical();
    IOExpanderBits = (IOExpander1.readGPIOAB() << 16) | IOExpander2.readGPIOAB();
    vPortExitCritical();
    xSemaphoreGive(i2c_mutex);
}

void processIOInterrupt(void *parameter)
{
    while (1)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        IOIRQNotProcessedLoops = 0;
        printf("IOTask");
        readIOExpanders();
        printBits(IOExpanderBits, true);
    }
}

void readCALExpander(){
    xSemaphoreTake(i2c_mutex, portMAX_DELAY);
    vPortEnterCritical();
    uint16_t buttons = calButtonExpender.readGPIOAB();
    vPortExitCritical();
    xSemaphoreGive(i2c_mutex);
    printBits(buttons, true);
    for (int i = 0; i < 6; i++)
    {
        uint8_t btn = i * 2;
        int ch = i;
        if (bitRead(buttons, btn) && bitRead(buttons, btn + 1))
        {
            printf("CH%02d offset reset\n", ch + 1);
            settings.model[settings.activeModel].channel_settings[ch].trim = 0;
        }
        else if (bitRead(buttons, btn) && !bitRead(lastCalButtons, btn))
        {
            settings.model[settings.activeModel].channel_settings[ch].trim++;
            printf("CH%02d offset ++ to %d\n", ch + 1, settings.model[settings.activeModel].channel_settings[i].trim);
        }
        else if (bitRead(buttons, btn + 1) && !bitRead(lastCalButtons, btn + 1))
        {
            settings.model[settings.activeModel].channel_settings[ch].trim--;
            printf("CH%02d offset -- to %d\n", ch + 1, settings.model[settings.activeModel].channel_settings[i].trim);
        }
    }
    lastCalButtons = buttons;
}

void processCALInterrupt(void *parameter)
{
    while (1)
    {
        if(ulTaskNotifyTakeIndexed( 1, pdTRUE, 100 );


        // ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        CALIRQNotProcessedLoops = 0;
        printf("CALTask");
        readCALExpander();
    }
}

void MainLoop(void* arg){
    allowInterrupts = true;
    for(int i = 0; i < 16; i++)
    {
        if(bitRead(interruptsToProcess, i)){
            HAL_GPIO_EXTI_Callback(1 << i);
        }
    }
    while(true)
    {
        #if ENABLE_MCPIO
        if(HAL_GPIO_ReadPin(CAL_IRQ_GPIO_Port, CAL_IRQ_Pin) == GPIO_PIN_RESET)
        {
            TaskStatus_t taskStatus;
            vTaskGetInfo(cal_taskHandle, &taskStatus, pdTRUE, eInvalid);
            
            CALIRQNotProcessedLoops++;
            printf("CAL IRQ is set for %3d loops. Taskstate = %d\n", CALIRQNotProcessedLoops, taskStatus.eCurrentState);
            // ulTaskNotifyValueClear(cal_taskHandle, UINT32_MAX);
            // xTaskGenericNotify( ( cal_taskHandle ), ( 0 ), eNoAction, __null );
            vTaskResume(cal_taskHandle);
            readCALExpander();
        }
        if(HAL_GPIO_ReadPin(MCP_IRQ_GPIO_Port, MCP_IRQ_Pin) == GPIO_PIN_RESET)
        {
            IOIRQNotProcessedLoops++;
            printf("IO IRQ is set for %3d loops\n", IOIRQNotProcessedLoops);
            vTaskResume(io_taskHandle);
            // ulTaskNotifyValueClear(io_taskHandle, UINT32_MAX);
            // xTaskGenericNotify( ( io_taskHandle ), ( 0 ), eNoAction, __null );
            readIOExpanders();
        }
        #endif
        #if DEBUG_ADC
            for(int i = 0; i < DMABUFFERSIZE; i++){
                printf("ADC%02d: %04d  ", i, ADCDMABuffer[i]);
            }
            printf("\n");
        #endif

        #if DEBUG_RADIO
            printf("NRFStats: TX %7u ACK %7u RX %7u FAIL %7u\n", radioStats.send, radioStats.txack, radioStats.rx, radioStats.fail);
        #endif
        vTaskDelay(1000 / portTICK_RATE_MS); // Nothing so just sleep
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
void updateValues(Model *activeSettings, channelBitData *channel_data, const uint16_t *raw_channels, uint16_t *parsed_channels, uint16_t *mapped_channels, uint32_t IO_bits, uint16_t *AUX_Serial_Channels)
{
    // Parse ADC channels
    for (int i = 0; i < ADCCHANNELNUMBERS; i++)
    {
        auto chSettings = activeSettings->channel_settings[i];
        parsed_channels[i] = parseADCChannel(raw_channels[i], chSettings.adcConfig.min, chSettings.adcConfig.mid, chSettings.adcConfig.max, activeSettings->deadzone, chSettings.trim);
    }

    for (int i = 0; i < RC_MAX_CHANNELS; i++)
    {
        auto chSettings = activeSettings->channel_settings[i];
        mapped_channels[i] = parseRCChannel(i, &chSettings, &activeSettings->rateLimitConfig, &activeSettings->outputEnable, bitRead(activeSettings->channelReversed, i), parsed_channels, IO_bits, AUX_Serial_Channels);
        if(mapped_channels[i] != 2023)
        {
            continue;
        }
        // Failsafe detection
        if(chSettings.startupVal != 0)
        {
            mapped_channels[i] = chSettings.startupVal;
        }
        if(chSettings.failsafe != 0)
        {
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

    channel_data->channel1 =  mapped_channels[0]  - 500;
    channel_data->channel2 =  mapped_channels[1]  - 500;
    channel_data->channel3 =  mapped_channels[2]  - 500;
    channel_data->channel4 =  mapped_channels[3]  - 500;
    channel_data->channel5 =  mapped_channels[4]  - 500;
    channel_data->channel6 =  mapped_channels[5]  - 500;
    channel_data->channel7 =  mapped_channels[6]  - 500;
    channel_data->channel8 =  mapped_channels[7]  - 500;
    channel_data->channel9 =  mapped_channels[8]  - 500;
    channel_data->channel10 = mapped_channels[9]  - 500;
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

void nrfTransmitChannels(void *parameter)
{
    while (true)
    {
        transmitTypes txData;
        memcpy(rawChannels, ADCDMABuffer, ADCCHANNELNUMBERS * 2);
        // AUX_Serial_reader.getChannels(AUXRXChannels);
        updateValues(activeModel, &txData.ch_data, rawChannels, parsedChannels, mappedChannels, IOExpanderBits, AUXRXChannels);
        txData.ch_data.identifier = CHANNELDATAID;
        // SendDataToRX(txData.bytesUnion.u8, sizeof(transmitTypes));
        vTaskDelay(7 / portTICK_RATE_MS);
    }
}

void nrfTransmitTest(void *parameter)
{
    while (true)
    {
        uint32_t now = HAL_GetTick();
        uint8_t txBuf[32];
        txBuf[0] = 1;
        txBuf[1] = 0;
        txBuf[2] = now >> 24 & 0xFF;
        txBuf[3] = now >> 16 & 0xFF;
        txBuf[4] = now >> 8 & 0xFF;
        txBuf[5] = now >> 0 & 0xFF;
        printf("Sending message with time %u\n", now);

        Main_nRF.CE_L();

        // Transfer a data from the specified buffer to the TX FIFO
        Main_nRF.WritePayload(txBuf, 6);

        // Start a transmission by asserting CE pin (must be held at least 10us)
        Main_nRF.CE_H();

        delay_us(10);
        Main_nRF.CE_L();
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}

// TODO: Check what this function does fully
void check_radio(void *parameters)
{
    while (true)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        if (xSemaphoreTake(nrf_mutex, 7 / portTICK_RATE_MS) == pdFALSE)
        {
            printf("CHECKRADIO: nRF_BUSY\n");
        }
        else
        {
            uint8_t status = Main_nRF.GetIRQFlags();
            tx = (status & nRF24::FLAG_TX_DS) != 0;
            fail = (status & nRF24::FLAG_MAX_RT) != 0;
            rx = (status & nRF24::FLAG_RX_DR) != 0;
            uint8_t fifoStatus = Main_nRF.GetStatus_TXFIFO();
            if (fifoStatus == nRF24::FIFO_EMPTY)
            {
                Main_nRF.CE_L(); // All packets transmitted
            }

            if (tx)
            {
                radioStats.txack++;
                // if(debugging) Serial.println("TXOK");
            }
            if (fail)
            { // TXFail
                radioStats.fail++;
                // if (debugging) Serial.println("TXFERR");
            }

            if (rx)
            { // Did we receive a message?
                radioStats.rx++;
                // parseReceivednRFPacket();
            }
            Main_nRF.ClearIRQFlags();
            xSemaphoreGive(nrf_mutex);
        }
    }
}

// void handlePlotter(void *parameter)
// {
//     while (true)
//     {
//         Plotter.loop();
//         vTaskDelay((Plotter.getTransmitInterval() + 2) / portTICK_RATE_MS);
//     }
// }

// void handleSerialControl(void *parameter)
// {
//     while (true)
//     {
//         scl.loop();
//         vTaskDelay(10 / portTICK_RATE_MS);
//     }
// }

void setupCPP(){
    printf("setupCPP()\n");
    #if DEBUG_I2C
        scanI2C(&hi2c2);
    #endif

    loadSettings();

    #if ENABLE_ENCODER
        configureEncoder();
    #endif

    #if ENABLE_MCPIO
        setupMCPChips();
        xTaskCreate(processCALInterrupt, "CALExpander", 20, NULL, osPriorityRealtime2, &cal_taskHandle);
        xTaskCreate(processIOInterrupt, "IOExpander", 20, NULL, osPriorityRealtime, &io_taskHandle);
    #endif

    #if ENABLE_RADIO
        Main_nRF.SetCEPin(NRF_CE_GPIO_Port, NRF_CE_Pin);
        Main_nRF.SetCSNPin(NRF_CSN_GPIO_Port, NRF_CSN_Pin);
        Main_nRF.SetSPI(&hspi3);
        Main_nRF.CSN_H();
        common_nRFInit(true);
        xTaskCreate(check_radio, "checkRadio", 50, NULL, osPriorityRealtime, &nRFData_taskHandle);
        xTaskCreate(nrfTransmitTest, "nrfTest", 10, NULL, osPriorityBelowNormal, &nrfTransmitTest_taskHandle);
        vTaskSuspend(nrfTransmitTest_taskHandle);
        xTaskCreate(nrfTransmitChannels, "nrfChannels", 100, NULL, osPriorityRealtime1, &nrfTransit_taskHandle);
        printf("WARNING: NRF TRANSMISSION IS DISABLED\n");
    #endif

    #if ENABLE_ADC
        memset(&ADCDMABuffer, 0, DMABUFFERSIZE * 2);
        HAL_ADC_Start_DMA(&hadc1, (uint32_t*)ADCDMABuffer, DMABUFFERSIZE);
    #endif

    xTaskCreate(MainLoop, "Main loop", 128, NULL, osPriorityLow, &main_taskHandle);
    
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
    if(!allowInterrupts) {
        bitSet(interruptsToProcess, GPIO_Pin);
        return;
    }
    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
    if(GPIO_Pin == ENC_IRQ_Pin){
        printf("ENC IRQ\n");
        vTaskNotifyGiveIndexedFromISR(encoder_taskHandle, 1, )
	    // vTaskNotifyGiveFromISR(encoder_taskHandle, &xHigherPriorityTaskWoken);
    } else if(GPIO_Pin == NRF_IRQ_Pin){
        //printf("NRF IRQ\n");
    } else if(GPIO_Pin == CAL_IRQ_Pin){
        printf("CAL IRQ\n");
        vTaskNotifyGiveFromISR(cal_taskHandle, &xHigherPriorityTaskWoken);
    } else if(GPIO_Pin == MCP_IRQ_Pin){
        printf("IO IRQ\n");
        vTaskNotifyGiveFromISR(io_taskHandle, &xHigherPriorityTaskWoken);
    } else if(GPIO_Pin == TOUCH_IRQ_Pin){
        //printf("TOUCH IRQ\n");
    }
    portYIELD();
    // portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler_CPP(const char *file, int line) {
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    vTaskSuspendAll();
    TaskHandle_t currentTask = xTaskGetCurrentTaskHandle();
    TaskStatus_t taskStatus;
    vTaskGetInfo(currentTask, &taskStatus, pdTRUE, eInvalid);
    uint8_t printCount = 0;
    while (1) {
        HAL_Delay(100);
        if (++printCount % 10 == 0)
        {
            printf("Error in file '%s' Line %d, Task %s\n", file, line, taskStatus.pcTaskName);
        }
        if (printCount == 100){
            HAL_NVIC_SystemReset();
        }
    }
    /* USER CODE END Error_Handler_Debug */
}