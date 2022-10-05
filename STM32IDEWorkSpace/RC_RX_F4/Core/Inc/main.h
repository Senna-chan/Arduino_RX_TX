/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include "Structs.h"
#include "RXStructs.h"
#include "RC_RX.hpp"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
extern UART_HandleTypeDef huart1;
extern SPI_HandleTypeDef hspi2;
extern SPI_HandleTypeDef hspi3;
extern uint8_t uart1TXBusy;
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
void _Error_Handler(char *, int);

#define GET_MACRO( _0, _1, NAME, ... ) NAME

#define Error_Handler(...) GET_MACRO( _0, ##__VA_ARGS__, Error_Handler1, Error_Handler0 )()

#define Error_Handler0() _Error_Handler( __FILE__, __LINE__ )

#define Error_Handler1(unused) _Error_Handler( char * file, int line )
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SLEDB_Pin GPIO_PIN_2
#define SLEDB_GPIO_Port GPIOE
#define SLEDG_Pin GPIO_PIN_3
#define SLEDG_GPIO_Port GPIOE
#define SLEDR_Pin GPIO_PIN_4
#define SLEDR_GPIO_Port GPIOE
#define FF2_1_Pin GPIO_PIN_5
#define FF2_1_GPIO_Port GPIOE
#define FF2_2_Pin GPIO_PIN_6
#define FF2_2_GPIO_Port GPIOE
#define nRF_CSN_Pin GPIO_PIN_0
#define nRF_CSN_GPIO_Port GPIOC
#define nRF_CE_Pin GPIO_PIN_1
#define nRF_CE_GPIO_Port GPIOC
#define CH1_Pin GPIO_PIN_0
#define CH1_GPIO_Port GPIOA
#define CH2_Pin GPIO_PIN_1
#define CH2_GPIO_Port GPIOA
#define CH3_Pin GPIO_PIN_2
#define CH3_GPIO_Port GPIOA
#define CH4_Pin GPIO_PIN_3
#define CH4_GPIO_Port GPIOA
#define STEP3_FF5_Pin GPIO_PIN_6
#define STEP3_FF5_GPIO_Port GPIOA
#define STEP4_FF6_Pin GPIO_PIN_7
#define STEP4_FF6_GPIO_Port GPIOA
#define SPIFLASH_CS_Pin GPIO_PIN_0
#define SPIFLASH_CS_GPIO_Port GPIOB
#define CH5_Pin GPIO_PIN_1
#define CH5_GPIO_Port GPIOB
#define CHSEL_DAC1_CH5_Pin GPIO_PIN_7
#define CHSEL_DAC1_CH5_GPIO_Port GPIOE
#define CHSEL_DAC2_CH6_Pin GPIO_PIN_8
#define CHSEL_DAC2_CH6_GPIO_Port GPIOE
#define CH6_Pin GPIO_PIN_9
#define CH6_GPIO_Port GPIOE
#define CH7_Pin GPIO_PIN_11
#define CH7_GPIO_Port GPIOE
#define CHSEL_STEP3_FF5_CH8_Pin GPIO_PIN_12
#define CHSEL_STEP3_FF5_CH8_GPIO_Port GPIOE
#define CH8_Pin GPIO_PIN_13
#define CH8_GPIO_Port GPIOE
#define CH9_Pin GPIO_PIN_14
#define CH9_GPIO_Port GPIOE
#define CHSEL_STEP4_FF6_CH9_Pin GPIO_PIN_15
#define CHSEL_STEP4_FF6_CH9_GPIO_Port GPIOE
#define CHSEL_FF2_1_CH1_Pin GPIO_PIN_10
#define CHSEL_FF2_1_CH1_GPIO_Port GPIOB
#define CHSEL_FF2_2_CH2_Pin GPIO_PIN_11
#define CHSEL_FF2_2_CH2_GPIO_Port GPIOB
#define nRF_IRQ_Pin GPIO_PIN_12
#define nRF_IRQ_GPIO_Port GPIOB
#define nRF_IRQ_EXTI_IRQn EXTI15_10_IRQn
#define FF1_1_Pin GPIO_PIN_14
#define FF1_1_GPIO_Port GPIOB
#define FF1_2_Pin GPIO_PIN_15
#define FF1_2_GPIO_Port GPIOB
#define CHSEL_FF1_1_CH10_Pin GPIO_PIN_8
#define CHSEL_FF1_1_CH10_GPIO_Port GPIOD
#define CHSEL_FF1_2_CH11_Pin GPIO_PIN_9
#define CHSEL_FF1_2_CH11_GPIO_Port GPIOD
#define CH10_Pin GPIO_PIN_12
#define CH10_GPIO_Port GPIOD
#define CH11_Pin GPIO_PIN_13
#define CH11_GPIO_Port GPIOD
#define CH12_Pin GPIO_PIN_14
#define CH12_GPIO_Port GPIOD
#define CH13_Pin GPIO_PIN_15
#define CH13_GPIO_Port GPIOD
#define CH14_Pin GPIO_PIN_6
#define CH14_GPIO_Port GPIOC
#define CH15_Pin GPIO_PIN_7
#define CH15_GPIO_Port GPIOC
#define CH16_Pin GPIO_PIN_8
#define CH16_GPIO_Port GPIOC
#define CH17_Pin GPIO_PIN_9
#define CH17_GPIO_Port GPIOC
#define SBUS_TX_Pin GPIO_PIN_10
#define SBUS_TX_GPIO_Port GPIOC
#define SBUS_RX_Pin GPIO_PIN_11
#define SBUS_RX_GPIO_Port GPIOC
#define CUSTOM_TX_Pin GPIO_PIN_12
#define CUSTOM_TX_GPIO_Port GPIOC
#define CUSTOM_RX_Pin GPIO_PIN_2
#define CUSTOM_RX_GPIO_Port GPIOD
#define IO_DBG_1_Pin GPIO_PIN_6
#define IO_DBG_1_GPIO_Port GPIOD
#define IO_DBG_2_Pin GPIO_PIN_7
#define IO_DBG_2_GPIO_Port GPIOD
#define STEP1_FF3_Pin GPIO_PIN_8
#define STEP1_FF3_GPIO_Port GPIOB
#define STEP2_FF4_Pin GPIO_PIN_9
#define STEP2_FF4_GPIO_Port GPIOB
#define CHSEL_STEP1_FF3_CH16_Pin GPIO_PIN_0
#define CHSEL_STEP1_FF3_CH16_GPIO_Port GPIOE
#define CHSEL_STEP2_FF4_CH17_Pin GPIO_PIN_1
#define CHSEL_STEP2_FF4_CH17_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */
#define customUart huart5
#define SBUSUart huart3
#define nRF_hspi hspi2
#define isTransmitter 0
#define delay(time) HAL_Delay(time)
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
