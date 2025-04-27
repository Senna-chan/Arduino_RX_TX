
#ifndef _ATXH_MAIN_H
#define _ATXH_MAIN_H

#include "Config.h"

#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>

void setupCPP();
void startFreeRTOS();
void SerialPrint(const char* string);
void SerialPrintLen(const char* string, size_t length);
void SerialPrintf(const char* format, ...);

#ifdef __cplusplus
}
#endif

#endif