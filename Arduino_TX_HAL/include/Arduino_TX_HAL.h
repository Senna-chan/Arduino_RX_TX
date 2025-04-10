
#ifndef _ATXH_MAIN_H
#define _ATXH_MAIN_H

#include "Config.h" // Config is the most important, include it first

#ifdef __cplusplus
extern "C" {
#endif
#include "freertos.h"
#include "gpio.h"
#include "main.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include <stdio.h>
#include <stdlib.h>

void setupCPP();
void startFreeRTOS();
void SerialPrint(const char* string);
void SerialPrintLen(const char* string, size_t length);
void SerialPrintf(const char* format, ...);
#ifdef __cplusplus
}
#endif

#endif