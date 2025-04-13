//
// Created by senyaa on 4/13/25.
//

#ifndef SERIALUTILS_H
#define SERIALUTILS_H

#include "main.h"

void UART1TXDone(UART_HandleTypeDef* huart);

void SerialPrint(const char* string);
void SerialPrintf(const char* format, ...);
void SerialPrintLen(const char* string, size_t length);
int SerialRead();
int SerialRead(char* buffer, size_t length);

#endif //SERIALUTILS_H
