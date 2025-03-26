#ifndef _ATX_FREERTOS_H
#define _ATX_FREERTOS_H

#ifdef  __cplusplus
extern "C"
{
#endif

#include <FreeRTOS.h>
#include <task.h>
#include "main.h"
#include <cmsis_os.h>
#include <semphr.h>

#ifdef  __cplusplus
}
#endif

TaskHandle_t nRFData_taskHandle;         // nRF Receive task
TaskHandle_t plotter_taskHandle;         // Task for plotter stuff
TaskHandle_t hmi_taskHandle;             // Task for HMI Data transmission things
TaskHandle_t serialControl_taskHandle;   // Task for serial control library
TaskHandle_t companionSerial_taskHandle; // Task for serial communication with the companion app. Custom protocol that bypasses SerialControl for easy use
TaskHandle_t nrfTransmitTest_taskHandle; // Task for nrf transmission testing
TaskHandle_t nrfTransit_taskHandle;      // Task for nrf transmission
TaskHandle_t printNrfStats_taskHandle;   // Task for printing nrf communication stats

SemaphoreHandle_t hmi_mutex;    // Lock for HMI
SemaphoreHandle_t nrf_mutex;    // Lock for nRF
SemaphoreHandle_t main_serial_mutex; // Lock for everything Serial

#endif