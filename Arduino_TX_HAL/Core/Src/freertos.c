/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for check_radio */
osThreadId_t check_radioHandle;
const osThreadAttr_t check_radio_attributes = {
  .name = "check_radio",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for handleCALIRQ */
osThreadId_t handleCALIRQHandle;
const osThreadAttr_t handleCALIRQ_attributes = {
  .name = "handleCALIRQ",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for handleIOIRQ */
osThreadId_t handleIOIRQHandle;
const osThreadAttr_t handleIOIRQ_attributes = {
  .name = "handleIOIRQ",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for handleEncoder */
osThreadId_t handleEncoderHandle;
const osThreadAttr_t handleEncoder_attributes = {
  .name = "handleEncoder",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for handleHMI */
osThreadId_t handleHMIHandle;
const osThreadAttr_t handleHMI_attributes = {
  .name = "handleHMI",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for handleSerialCom */
osThreadId_t handleSerialComHandle;
const osThreadAttr_t handleSerialCom_attributes = {
  .name = "handleSerialCom",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for parseSendChanne */
osThreadId_t parseSendChanneHandle;
const osThreadAttr_t parseSendChanne_attributes = {
  .name = "parseSendChanne",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for I2CMutex */
osMutexId_t I2CMutexHandle;
const osMutexAttr_t I2CMutex_attributes = {
  .name = "I2CMutex"
};
/* Definitions for SPI1Mutex */
osMutexId_t SPI1MutexHandle;
const osMutexAttr_t SPI1Mutex_attributes = {
  .name = "SPI1Mutex"
};
/* Definitions for SPI2Mutex */
osMutexId_t SPI2MutexHandle;
const osMutexAttr_t SPI2Mutex_attributes = {
  .name = "SPI2Mutex"
};
/* Definitions for HMIMutex */
osMutexId_t HMIMutexHandle;
const osMutexAttr_t HMIMutex_attributes = {
  .name = "HMIMutex"
};
/* Definitions for myBinarySem01 */
osSemaphoreId_t myBinarySem01Handle;
const osSemaphoreAttr_t myBinarySem01_attributes = {
  .name = "myBinarySem01"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void checkRadio(void *argument);
void processCALInterrupt(void *argument);
void processIOInterrupt(void *argument);
void processEncoder(void *argument);
void updateHMI(void *argument);
void handleSerialCommunication(void *argument);
void parseAndTransmitChannels(void *argument);

extern void MX_USB_HOST_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* creation of I2CMutex */
  I2CMutexHandle = osMutexNew(&I2CMutex_attributes);

  /* creation of SPI1Mutex */
  SPI1MutexHandle = osMutexNew(&SPI1Mutex_attributes);

  /* creation of SPI2Mutex */
  SPI2MutexHandle = osMutexNew(&SPI2Mutex_attributes);

  /* creation of HMIMutex */
  HMIMutexHandle = osMutexNew(&HMIMutex_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of myBinarySem01 */
  myBinarySem01Handle = osSemaphoreNew(1, 1, &myBinarySem01_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of check_radio */
  check_radioHandle = osThreadNew(checkRadio, NULL, &check_radio_attributes);

  /* creation of handleCALIRQ */
  handleCALIRQHandle = osThreadNew(processCALInterrupt, NULL, &handleCALIRQ_attributes);

  /* creation of handleIOIRQ */
  handleIOIRQHandle = osThreadNew(processIOInterrupt, NULL, &handleIOIRQ_attributes);

  /* creation of handleEncoder */
  handleEncoderHandle = osThreadNew(processEncoder, NULL, &handleEncoder_attributes);

  /* creation of handleHMI */
  handleHMIHandle = osThreadNew(updateHMI, NULL, &handleHMI_attributes);

  /* creation of handleSerialCom */
  handleSerialComHandle = osThreadNew(handleSerialCommunication, NULL, &handleSerialCom_attributes);

  /* creation of parseSendChanne */
  parseSendChanneHandle = osThreadNew(parseAndTransmitChannels, NULL, &parseSendChanne_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* init code for USB_HOST */
  MX_USB_HOST_Init();
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_checkRadio */
/**
* @brief Function implementing the check_radio thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_checkRadio */
__weak void checkRadio(void *argument)
{
  /* USER CODE BEGIN checkRadio */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END checkRadio */
}

/* USER CODE BEGIN Header_processCALInterrupt */
/**
* @brief Function implementing the handleCALIRQ thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_processCALInterrupt */
__weak void processCALInterrupt(void *argument)
{
  /* USER CODE BEGIN processCALInterrupt */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END processCALInterrupt */
}

/* USER CODE BEGIN Header_processIOInterrupt */
/**
* @brief Function implementing the handleIOIRQ thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_processIOInterrupt */
__weak void processIOInterrupt(void *argument)
{
  /* USER CODE BEGIN processIOInterrupt */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END processIOInterrupt */
}

/* USER CODE BEGIN Header_processEncoder */
/**
* @brief Function implementing the handleEncoder thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_processEncoder */
__weak void processEncoder(void *argument)
{
  /* USER CODE BEGIN processEncoder */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END processEncoder */
}

/* USER CODE BEGIN Header_updateHMI */
/**
* @brief Function implementing the handleHMI thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_updateHMI */
__weak void updateHMI(void *argument)
{
  /* USER CODE BEGIN updateHMI */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END updateHMI */
}

/* USER CODE BEGIN Header_handleSerialCommunication */
/**
* @brief Function implementing the handleSerialCom thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_handleSerialCommunication */
__weak void handleSerialCommunication(void *argument)
{
  /* USER CODE BEGIN handleSerialCommunication */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END handleSerialCommunication */
}

/* USER CODE BEGIN Header_parseAndTransmitChannels */
/**
* @brief Function implementing the parseSendChanne thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_parseAndTransmitChannels */
__weak void parseAndTransmitChannels(void *argument)
{
  /* USER CODE BEGIN parseAndTransmitChannels */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END parseAndTransmitChannels */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

