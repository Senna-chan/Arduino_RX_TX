#pragma once

#include <STM32FreeRTOS.h>

extern SemaphoreHandle_t i2c_mutex;		// Lock for everything I2C
