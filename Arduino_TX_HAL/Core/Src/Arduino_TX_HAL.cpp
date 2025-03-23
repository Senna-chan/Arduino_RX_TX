#include "Arduino_TX_HAL.hpp"

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler_CPP(char *file, int line) {
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    HAL_Delay(1000);
    printf("Error in file %s on line %d\r\n", file, line);
    uint8_t printCount = 0;
    while (1) {
        HAL_Delay(100);
        printCount++;
        if (printCount % 5 == 0) {
            printf("Task %s failed. Error in file %s on line %d\r\n", file, line);
        }
        if (printCount == 20) {
            NVIC_SystemReset();
        }
    }
    /* USER CODE END Error_Handler_Debug */
}
