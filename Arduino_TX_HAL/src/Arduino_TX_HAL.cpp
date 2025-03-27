#include "Arduino_TX_HAL.h"
#include "Encoder.h"
#include "SharedNRF.h"

void setupCPP(){
    printf("setupCPP()\n");
    hmi_mutex = xSemaphoreCreateMutex();
    nrf_mutex = xSemaphoreCreateMutex();
    i2c_mutex = xSemaphoreCreateMutex();
    main_serial_mutex = xSemaphoreCreateMutex();
    configureEncoder();
    Main_nRF.SetCEPin(NRF_CE_GPIO_Port, NRF_CE_Pin);
    Main_nRF.SetCSNPin(NRF_CSN_GPIO_Port, NRF_CSN_Pin);
    Main_nRF.SetSPI(&hspi3);
    HAL_GPIO_WritePin(NRF_CSN_GPIO_Port, NRF_CSN_Pin, GPIO_PIN_SET);
    common_nRFInit(true);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
    if(GPIO_Pin == ENC_IRQ_Pin){
	    vTaskNotifyGiveFromISR(encoder_taskHandle, NULL);
    } else if(GPIO_Pin == NRF_IRQ_Pin){
        printf("NRF IRQ");
    } else if(GPIO_Pin == CAL_IRQ_Pin){
        printf("CAL IRQ");
    } else if(GPIO_Pin == MCP_IRQ_Pin){
        printf("MCP IRQ");
    } else if(GPIO_Pin == MCP_IRQ_Pin){
        printf("TOUCH IRQ");
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