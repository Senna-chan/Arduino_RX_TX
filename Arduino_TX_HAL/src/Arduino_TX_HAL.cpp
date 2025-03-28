#include "Arduino_TX_HAL.h"
#include "Encoder.h"
#include "SharedNRF.h"
#include "MCPExpanders.h"
#include "i2c.h"
#include "I2CHelpers.h"
#include "ArduMath.h"
#include "MiscHelpers.hpp"
#include "settingsHelper.h"

uint32_t IOExpanderBits = 0;
uint16_t lastCalButtons = 0;


void processIOInterrupt(void *parameter)
{
    while (true)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        xSemaphoreTake(i2c_mutex, portMAX_DELAY);
        IOExpanderBits = (IOExpander1.readGPIOAB() << 16) | IOExpander2.readGPIOAB();
        printBits(IOExpanderBits, true);
        xSemaphoreGive(i2c_mutex);
    }
}

void processCALInterrupt(void *parameter)
{
    while (true)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        printf("CAL Interrupt ");
        xSemaphoreTake(i2c_mutex, portMAX_DELAY);
        uint16_t buttons = calButtonExpender.readGPIOAB();
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
        xSemaphoreGive(i2c_mutex);
    }
}

void setupCPP(){
    printf("setupCPP()\n");
    scanI2C(&hi2c2);

    xTaskCreate(processCALInterrupt, "calibrate_task", 50, NULL, 10, &cal_taskHandle);
    xTaskCreate(processIOInterrupt, "IOExpander", 10, NULL, 10, &io_taskHandle);
    
    loadSettings();
    configureEncoder();
    setupMCPChips();
    Main_nRF.SetCEPin(NRF_CE_GPIO_Port, NRF_CE_Pin);
    Main_nRF.SetCSNPin(NRF_CSN_GPIO_Port, NRF_CSN_Pin);
    Main_nRF.SetSPI(&hspi3);
    Main_nRF.CSN_H();
    common_nRFInit(true);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
    if(GPIO_Pin == ENC_IRQ_Pin){
        printf("ENC IRQ\n");
	    vTaskNotifyGiveFromISR(encoder_taskHandle, NULL);
    } else if(GPIO_Pin == NRF_IRQ_Pin){
        //printf("NRF IRQ\n");
    } else if(GPIO_Pin == CAL_IRQ_Pin){
        printf("CAL IRQ\n");
        vTaskNotifyGiveFromISR(cal_taskHandle, NULL);
    } else if(GPIO_Pin == MCP_IRQ_Pin){
        printf("IO IRQ\n");
        vTaskNotifyGiveFromISR(io_taskHandle, NULL);
    } else if(GPIO_Pin == TOUCH_IRQ_Pin){
        //printf("TOUCH IRQ\n");
    }
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