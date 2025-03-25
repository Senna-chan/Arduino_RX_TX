#include "Arduino_TX_HAL.hpp"

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler_CPP(char *file, int line) {
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    HAL_Delay(1000);
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
