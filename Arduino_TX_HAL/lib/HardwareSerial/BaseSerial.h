//
// Created by senyaa on 4/22/25.
//

#ifndef BASESERIAL_H
#define BASESERIAL_H

#include "freertos.h"
#include "main.h"
#include "usart.h"

#include "Print.h"

#include "RingBuffer.hpp"
#include <functional>
#include <utility>

#ifndef SERIAL_DMA_BUFFER_SIZE
#define SERIAL_DMA_BUFFER_SIZE 256
#endif
#define SERIAL_BUFFER_QUEUE_SIZE (SERIAL_DMA_BUFFER_SIZE * 8) // Max size of serial queue

class BaseSerial : public Print {
public:
    enum EventType {
        RX_EVENT,
        TX_EVENT,
        ERROR_EVENT
    };

    // Overloads from Print
    int availableForWrite() override;
    size_t write(const uint8_t* buffer, size_t size) override;
    size_t write(uint8_t) override;

    size_t availableForRead();
    int read();
    int peek();
    void readBuffer(uint8_t* buffer, size_t size);

    void attachRXCallback(std::function<void(BaseSerial*)> callback) {
        onRX = std::move(callback);
    }
    void attachTXCallback(std::function<void(BaseSerial*)> callback) {
        onTX = std::move(callback);
    }

protected:
    virtual void checkForTXPossible();
    bool initialized = false;
    RingBuffer<uint8_t, SERIAL_BUFFER_QUEUE_SIZE> tx_queue = RingBuffer<uint8_t, SERIAL_BUFFER_QUEUE_SIZE> {};
    RingBuffer<uint8_t, SERIAL_BUFFER_QUEUE_SIZE> rx_queue = RingBuffer<uint8_t, SERIAL_BUFFER_QUEUE_SIZE> {};
    std::function<void(BaseSerial*)> onTX = nullptr;
    std::function<void(BaseSerial*)> onRX = nullptr;
};

#endif // BASESERIAL_H
