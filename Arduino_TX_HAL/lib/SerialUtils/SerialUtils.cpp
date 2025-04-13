//
// Created by senyaa on 4/13/25.
//
#include "SerialUtils.h"

#include <queue>
#include <string>
#include <cstdint>
#include <cstring>
#include "freertos.h"
#include "usart.h"
#include <stdarg.h>
#include <stdio.h>

std::queue<char*> serialTXBuffer;
size_t maxQueueSize = 20;
char* stringToPrint;
bool uartIRQWorking = false;

void UART1TXDone(UART_HandleTypeDef* huart) {
    uartIRQWorking = true;
    if (stringToPrint != nullptr) {
        free(stringToPrint);
        stringToPrint = nullptr;
    }
    if (!serialTXBuffer.empty()) {
        stringToPrint = serialTXBuffer.front();
        serialTXBuffer.pop();
        HAL_UART_Transmit_IT(&huart1, (uint8_t*)stringToPrint, strlen(stringToPrint));
    } else {
        xSemaphoreGiveFromISR(main_serial_mutex, NULL);
    }
}

void SerialPrint(const char* string) {
    SerialPrintLen(string, strlen(string));
}

void SerialPrintLen(const char* string, size_t length) {
    bool queueMessage = true;
    BaseType_t inISR = xPortIsInsideInterrupt();

    if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED && !inISR) {
        if (xSemaphoreTake(main_serial_mutex, 0)) {
            queueMessage = false;
        }
    }

    if (huart1.gState == HAL_UART_STATE_READY) {
        queueMessage = false;
    }

    size_t strLength = length == 0 ? strlen(string) : length;
    if (queueMessage) {
        char* strPtr = (char*)malloc(strLength);
        strcpy(strPtr, string);
        serialTXBuffer.push(strPtr); // Please let this be safe to do
    } else {
        stringToPrint = (char*)malloc(strLength);
        strcpy(stringToPrint, string);
        HAL_UART_Transmit_IT(&huart1, (uint8_t*)stringToPrint, strLength);
    }
}

void SerialPrintf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    const size_t maxBufferSize = 256;
    char buffer[maxBufferSize] = { 0 };
    size_t stringLen = vsnprintf(buffer, maxBufferSize, format, args);
    va_end(args);
    SerialPrintLen(buffer, stringLen);
}

int SerialRead() {
    uint8_t buf[1];
    HAL_StatusTypeDef status = HAL_UART_Receive(&huart1, (uint8_t*)buf, 1, 0);
    if(status == HAL_TIMEOUT) {
        return -1;
    }
    return buf[0];
}

int SerialRead(char* buffer, size_t length) {
    HAL_StatusTypeDef status = HAL_UART_Receive(&huart1, (uint8_t*)buffer, length, 0xFF);
    if(status == HAL_TIMEOUT) {
        return -1;
    }
    return length;
}

namespace std {
#ifdef __cplusplus
extern "C" {
#endif

// void* realloc(void* ptr, size_t size) {
//     free(ptr);
//     return malloc(size);
// }

int _read(int file, char* ptr, int len) {
    HAL_StatusTypeDef hstatus;
    hstatus = HAL_UART_Receive(&huart1, (uint8_t*)ptr, 1, HAL_MAX_DELAY);
    return hstatus == HAL_OK ? 0 : -1;
}

size_t _write(int fd, char* ptr, size_t len) {
    SerialPrintLen(ptr, len);
    return len;
}

#ifdef __cplusplus
}
#endif
}

void __io_putchar(uint8_t ch) {
    HAL_UART_Transmit(&huart1, &ch, 1, 1);
}

#include "SerialUtils.h"
