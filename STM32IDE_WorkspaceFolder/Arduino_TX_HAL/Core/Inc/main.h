/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define C41_NRF_CS_Pin GPIO_PIN_2
#define C41_NRF_CS_GPIO_Port GPIOE
#define C41_CC23_CS_Pin GPIO_PIN_3
#define C41_CC23_CS_GPIO_Port GPIOE
#define C41_A7105_CS_Pin GPIO_PIN_4
#define C41_A7105_CS_GPIO_Port GPIOE
#define C41_CYRF_CS_Pin GPIO_PIN_5
#define C41_CYRF_CS_GPIO_Port GPIOE
#define C41_CYRF_RST_Pin GPIO_PIN_6
#define C41_CYRF_RST_GPIO_Port GPIOE
#define TOUCH_PEN_Pin GPIO_PIN_5
#define TOUCH_PEN_GPIO_Port GPIOC
#define SPI_FS_CS_Pin GPIO_PIN_0
#define SPI_FS_CS_GPIO_Port GPIOB
#define BACK_LIGHT_Pin GPIO_PIN_1
#define BACK_LIGHT_GPIO_Port GPIOB
#define AUX_MUX_S1_Pin GPIO_PIN_6
#define AUX_MUX_S1_GPIO_Port GPIOC
#define AUX_MUX_S2_Pin GPIO_PIN_7
#define AUX_MUX_S2_GPIO_Port GPIOC
#define AUX_TX_Pin GPIO_PIN_10
#define AUX_TX_GPIO_Port GPIOC
#define AUX_RX_Pin GPIO_PIN_11
#define AUX_RX_GPIO_Port GPIOC
#define HMI_TX_Pin GPIO_PIN_12
#define HMI_TX_GPIO_Port GPIOC
#define HMI_RX_Pin GPIO_PIN_2
#define HMI_RX_GPIO_Port GPIOD
#define NRF_CE_Pin GPIO_PIN_6
#define NRF_CE_GPIO_Port GPIOB
#define NRF_CSN_Pin GPIO_PIN_7
#define NRF_CSN_GPIO_Port GPIOB
#define NRF_IRQ_Pin GPIO_PIN_8
#define NRF_IRQ_GPIO_Port GPIOB
#define ENC_IRQ_Pin GPIO_PIN_9
#define ENC_IRQ_GPIO_Port GPIOB
#define CAL_IRQ_Pin GPIO_PIN_0
#define CAL_IRQ_GPIO_Port GPIOE
#define MCP_IRQ_Pin GPIO_PIN_1
#define MCP_IRQ_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
