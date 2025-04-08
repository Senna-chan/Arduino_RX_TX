
#ifndef _ATXH_MAIN_H
#define _ATXH_MAIN_H

#include "Config.h" // Config is the most important, include it first

#ifdef __cplusplus
extern "C" {
#endif
    #include "spi.h"
    #include "tim.h"
    #include "usart.h"
    #include "gpio.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include "main.h"
    #include "freertos.h"

void setupCPP();
void startFreeRTOS();
void SerialPrint(const char* string);
void SerialPrintf(const char *format, ...);
#ifdef __cplusplus
}
#endif

#endif