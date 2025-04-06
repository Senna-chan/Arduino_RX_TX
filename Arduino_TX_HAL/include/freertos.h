#ifndef _ATX_FREERTOS_H
#define _ATX_FREERTOS_H

#ifdef  __cplusplus
extern "C"
{
#endif

#include <FreeRTOS.h>
#include <task.h>
#include "main.h"
#include <semphr.h>

#ifdef  __cplusplus
}
#endif

extern TaskHandle_t nRFData_taskHandle;         // nRF Receive task
extern TaskHandle_t plotter_taskHandle;         // Task for plotter stuff
extern TaskHandle_t hmi_taskHandle;             // Task for HMI Data transmission things
extern TaskHandle_t serialControl_taskHandle;   // Task for serial control library
extern TaskHandle_t companionSerial_taskHandle; // Task for serial communication with the companion app. Custom protocol that bypasses SerialControl for easy use
extern TaskHandle_t nrfTransmitTest_taskHandle; // Task for nrf transmission testing
extern TaskHandle_t nrfTransit_taskHandle;      // Task for nrf transmission
extern TaskHandle_t printNrfStats_taskHandle;   // Task for printing nrf communication stats
extern TaskHandle_t encoder_taskHandle;         // Task for encoder processing

extern TaskHandle_t cal_taskHandle;				// Task for handling calibration buttons(Super high prio but only run when needed, Gets data via queue)
extern TaskHandle_t io_taskHandle;				// Task for handling IO expanders
extern TaskHandle_t main_taskHandle;

extern SemaphoreHandle_t hmi_mutex;             // Lock for HMI
extern SemaphoreHandle_t nrf_mutex;             // Lock for nRF
extern SemaphoreHandle_t i2c_mutex;             // Lock for I2C
extern SemaphoreHandle_t main_serial_mutex;     // Lock for everything Serial

void MX_FREERTOS_Init(void);

#endif