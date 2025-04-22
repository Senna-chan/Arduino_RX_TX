//
// Created by senyaa on 4/14/25.
//

#include "HardwareSerial.h"

#include <../ArduinoBackport/ArduMath.hpp>

void UART_TX_Done(UART_HandleTypeDef* huart) {
    HardwareSerial::getInstance(huart)->handleISR(HardwareSerial::TX_EVENT, 0);
}

void UART_RX_Done(UART_HandleTypeDef* huart) {
    HardwareSerial::getInstance(huart)->handleISR(HardwareSerial::RX_EVENT, SERIAL_DMA_BUFFER_SIZE);
}

void UART_RXIDLE_Done(UART_HandleTypeDef* huart, uint16_t pos) {
    HardwareSerial::getInstance(huart)->handleISR(HardwareSerial::RX_EVENT, pos);
}

void UART_Error(UART_HandleTypeDef* huart) {
    HardwareSerial::getInstance(huart)->handleISR(HardwareSerial::ERROR_EVENT, 0);
}

void HardwareSerial::handleISR(EventType eventType, uint16_t pos) {
    if (_huart == nullptr) { // Uh...
        return;
    }
    if (eventType == RX_EVENT) {
        currentRXPos = pos;

        if (currentRXPos == lastRXPos) {
            return;
        }

        if (currentRXPos > lastRXPos) { // No overflow has been reached. Just copy data from the last to current position into rx_queue
            rx_queue.insert(rx_queue.end(), &rx_dma_buf[lastRXPos], &rx_dma_buf[currentRXPos]);
        } else {
            rx_queue.insert(rx_queue.end(), &rx_dma_buf[lastRXPos], &rx_dma_buf[SERIAL_DMA_BUFFER_SIZE]);
            if (currentRXPos > 0) {
                rx_queue.insert(rx_queue.end(), &rx_dma_buf[lastRXPos], &rx_dma_buf[currentRXPos]);
            }
        }
        lastRXPos = currentRXPos;
        // HAL_UARTEx_ReceiveToIdle_DMA(_huart, rx_dma_buf, SERIAL_BUFFER_SIZE); // Directly restart reading
        DMA_RX_Triggered = true;
        if (onRX != nullptr) {
            onRX(this);
        }
    } else if (eventType == TX_EVENT) {
        DMA_TX_Done = true;
        checkForTXPossible();
        if (onTX != nullptr) {
            onTX(this);
        }
    } else if (eventType == ERROR_EVENT) {
        Error_Handler();
    }
}

HardwareSerial* HardwareSerial::getInstance(UART_HandleTypeDef* huart) {
    if (huart->Instance == USART1) {
        return &Serial1;
    } else if (huart->Instance == USART2) {
        return &Serial2;
    } else if (huart->Instance == USART3) {
        return &Serial3;
    } else if (huart->Instance == UART4) {
        return &Serial4;
    } else if (huart->Instance == UART5) {
        return &Serial5;
    }
    Error_Handler();
    return nullptr;
}

void HardwareSerial::create(UART_HandleTypeDef* huart) {
    _huart = huart;
}

void HardwareSerial::init() {
    HAL_UART_UnRegisterCallback(_huart, HAL_UART_ERROR_CB_ID);
    HAL_UART_UnRegisterCallback(_huart, HAL_UART_TX_COMPLETE_CB_ID);

    HAL_UART_RegisterCallback(_huart, HAL_UART_ERROR_CB_ID, UART_Error);
    HAL_UART_RegisterCallback(_huart, HAL_UART_TX_COMPLETE_CB_ID, UART_TX_Done);
    HAL_UART_RegisterCallback(_huart, HAL_UART_RX_COMPLETE_CB_ID, UART_RX_Done);
    queue_mutex = xSemaphoreCreateBinary();
    if (_huart->Init.Mode == UART_MODE_RX || _huart->Init.Mode == UART_MODE_TX_RX) {
        HAL_UART_UnRegisterRxEventCallback(_huart);
        HAL_UART_AbortReceive(_huart);
        HAL_UART_RegisterRxEventCallback(_huart, UART_RXIDLE_Done);
        __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
        HAL_UARTEx_ReceiveToIdle_DMA(_huart, rx_dma_buf, SERIAL_DMA_BUFFER_SIZE);
    }

    initialized = true;
}

void HardwareSerial::waitForNewData() {
    while (!DMA_RX_Triggered) {
        HAL_Delay(10);
    }
    DMA_RX_Triggered = false;
}

size_t HardwareSerial::availableForRead() {
    return SERIAL_BUFFER_QUEUE_SIZE - rx_queue.size();
}

int HardwareSerial::read() {
    if (rx_queue.empty() == 0) {
        return -1;
    }

    uint8_t c = rx_queue.front();
    rx_queue.pop_front();
    return c;
}

int HardwareSerial::peek() {
    if (rx_queue.empty() == 0) {
        return -1;
    }
    return rx_queue.front();
}

void HardwareSerial::readBuffer(uint8_t* buffer, size_t size) {
    std::copy(rx_queue.begin(), rx_queue.begin() + size, buffer);
    rx_queue.erase(rx_queue.begin(), rx_queue.begin() + size);
}

int HardwareSerial::availableForWrite() {
    volatile size_t free_space = tx_queue.space_free();
    volatile size_t used_space = tx_queue.space_used();
    return free_space;
}

size_t HardwareSerial::write(const uint8_t* buffer, size_t size) {
    if (availableForWrite() < size) {
        Error_Handler();
    }

    uint32_t irq_num = taskENTER_CRITICAL_FROM_ISR();
    nextTransmitTXPoint = tx_queue.insert(buffer, size);
    taskEXIT_CRITICAL_FROM_ISR(irq_num);
    checkForTXPossible();
    return size;
}

size_t HardwareSerial::write(uint8_t b) {
    if (!availableForWrite()) {
        Error_Handler();
    }

    uint32_t irq_num = taskENTER_CRITICAL_FROM_ISR();
    tx_queue.at(nextTransmitTXPoint++) = b;
    taskEXIT_CRITICAL_FROM_ISR(irq_num);
    checkForTXPossible();
    return 1;
}

void HardwareSerial::checkForTXPossible() {
    if (nextTransmitTXPoint > tx_queue.size()) {
        Error_Handler();
    }
    if (DMA_TX_Done) {
        volatile size_t space_used = tx_queue.space_used();
        volatile size_t space_free = tx_queue.space_free();
        size_t amountToTransmit = min(static_cast<size_t>(SERIAL_DMA_BUFFER_SIZE), tx_queue.space_used());

        if (!amountToTransmit) {
            return;
        }
        tx_queue.retrieve(tx_dma_buf, amountToTransmit);
        DMA_TX_Done = false;
        if (HAL_UART_Transmit_DMA(_huart, tx_dma_buf, amountToTransmit) != HAL_OK) {
            Error_Handler();
        }
    }
}

#if defined(USART1)
HardwareSerial Serial1;
#endif
#if defined(USART2)
HardwareSerial Serial2;
#endif
#if defined(USART3)
HardwareSerial Serial3;
#endif
#if defined(UART4) || defined(USART4)
HardwareSerial Serial4;
#endif
#if defined(UART5) || defined(USART5)
HardwareSerial Serial5;
#endif
#if defined(USART6)
HardwareSerial Serial6;
#endif
#if defined(UART7) || defined(USART7)
HardwareSerial Serial7;
#endif
#if defined(UART8) || defined(USART8)
HardwareSerial Serial8;
#endif
#if defined(UART9)
HardwareSerial Serial9;
#endif
#if defined(UART10) || defined(USART10)
HardwareSerial Serial10;
#endif
#if defined(LPUART1)
HardwareSerial SerialLP1;
#endif
#if defined(LPUART2)
HardwareSerial SerialLP2;
#endif
#if defined(LPUART3)
HardwareSerial SerialLP3;
#endif
