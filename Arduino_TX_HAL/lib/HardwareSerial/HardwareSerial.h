////
//// Created by senyaa on 4/14/25.
////

#ifndef SERIAL_H
#define SERIAL_H

#include "freertos.h"
#include "main.h"
#include "usart.h"

#include "../ArduinoBackport/Print.h"
#include "../RingBuffer/RingBuffer.hpp"

#include <functional>
#include <queue>
#include <utility>

#ifndef SERIAL_DMA_BUFFER_SIZE
#define SERIAL_DMA_BUFFER_SIZE 256
#endif
#define SERIAL_BUFFER_QUEUE_SIZE (SERIAL_DMA_BUFFER_SIZE * 8) // Max size of serial queue

class HardwareSerial : public Print {
public:
    enum EventType {
        RX_EVENT,
        TX_EVENT,
        ERROR_EVENT
    };

    void create(UART_HandleTypeDef* huart);
    void init();
    // Overloads from Print
    int availableForWrite() override;
    size_t write(const uint8_t* buffer, size_t size) override;
    size_t write(uint8_t) override;

    size_t availableForRead();
    int read();
    int peek();
    void readBuffer(uint8_t* buffer, size_t size);

    void waitForNewData();
    static HardwareSerial* getInstance(UART_HandleTypeDef* huart);
    // These functions are not for user use
    void handleISR(EventType eventType, uint16_t pos);
    void attachRXCallback(std::function<void(HardwareSerial*)> callback) {
        onRX = std::move(callback);
    }
    void attachTXCallback(std::function<void(HardwareSerial*)> callback) {
        onTX = std::move(callback);
    }

private:
    void checkForTXPossible();
    SemaphoreHandle_t queue_mutex; // Lock for everything Serial
    bool initialized = false;
    UART_HandleTypeDef* _huart = nullptr;
    RingBuffer<uint8_t, SERIAL_BUFFER_QUEUE_SIZE> tx_queue = RingBuffer<uint8_t, SERIAL_BUFFER_QUEUE_SIZE> {};
    int lastTransmitTXPoint = 0;
    int nextTransmitTXPoint = 0;
    std::deque<uint8_t> rx_queue;
    uint16_t currentRXPos = 0;
    uint16_t lastRXPos = 0;
    bool DMA_RX_Triggered = false; // Holds the flag if DMA has been triggered since the last read
    bool DMA_TX_Done = true;       // When this is true we can send more data to DMA
    std::function<void(HardwareSerial*)> onTX = nullptr;
    std::function<void(HardwareSerial*)> onRX = nullptr;
    uint8_t tx_dma_buf[SERIAL_DMA_BUFFER_SIZE] = { 0 };
    uint8_t rx_dma_buf[SERIAL_DMA_BUFFER_SIZE] = { 0 };
};

#if defined(USART1)
extern HardwareSerial Serial1;
#endif
#if defined(USART2)
extern HardwareSerial Serial2;
#endif
#if defined(USART3)
extern HardwareSerial Serial3;
#endif
#if defined(UART4) || defined(USART4)
extern HardwareSerial Serial4;
#endif
#if defined(UART5) || defined(USART5)
extern HardwareSerial Serial5;
#endif
#if defined(USART6)
extern HardwareSerial Serial6;
#endif
#if defined(UART7) || defined(USART7)
extern HardwareSerial Serial7;
#endif
#if defined(UART8) || defined(USART8)
extern HardwareSerial Serial8;
#endif
#if defined(UART9)
extern HardwareSerial Serial9;
#endif
#if defined(UART10) || defined(USART10)
extern HardwareSerial Serial10;
#endif
#if defined(LPUART1)
extern HardwareSerial SerialLP1;
#endif
#if defined(LPUART2)
extern HardwareSerial SerialLP2;
#endif
#if defined(LPUART3)
extern HardwareSerial SerialLP3;
#endif

#endif // SERIAL_H
