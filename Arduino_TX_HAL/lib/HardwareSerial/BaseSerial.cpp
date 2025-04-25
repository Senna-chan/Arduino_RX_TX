//
// Created by senyaa on 4/22/25.
//

#include "BaseSerial.h"


size_t BaseSerial::write(const uint8_t* buffer, size_t size) {
    if (availableForWrite() < size) {
        Error_Handler();
    }

    uint32_t irq_num = taskENTER_CRITICAL_FROM_ISR();
    tx_queue.insert(buffer, size);
    taskEXIT_CRITICAL_FROM_ISR(irq_num);
    checkForTXPossible();
    return size;
}

size_t BaseSerial::write(uint8_t b) {
    if (!availableForWrite()) {
        Error_Handler();
    }

    uint32_t irq_num = taskENTER_CRITICAL_FROM_ISR();
    tx_queue.insert(b);
    taskEXIT_CRITICAL_FROM_ISR(irq_num);
    checkForTXPossible();
    return 1;
}

__weak void BaseSerial::checkForTXPossible() {

}

size_t BaseSerial::availableForRead() {
    return rx_queue.space_used();
}

int BaseSerial::read() {
    if (rx_queue.space_used() == 0) {
        return -1;
    }

    return rx_queue.read();
}

int BaseSerial::peek() {
    if (rx_queue.space_used() == 0) {
        return -1;
    }
    return rx_queue.peek();
}

void BaseSerial::readBuffer(uint8_t* buffer, size_t size) {
    rx_queue.retrieve(buffer, size);
}

int BaseSerial::availableForWrite() {
    volatile size_t free_space = tx_queue.space_free();
    return static_cast<int>(free_space);
}
