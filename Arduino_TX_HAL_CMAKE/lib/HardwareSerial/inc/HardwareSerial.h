////
//// Created by senyaa on 4/14/25.
////

#ifndef SERIAL_H
#define SERIAL_H

#include <Print.h>
#include "BaseSerial.h"

class HardwareSerial : public BaseSerial {
public:
    void create(UART_HandleTypeDef* huart);
    void init();

    void waitForNewData();
    static HardwareSerial* getInstance(UART_HandleTypeDef* huart);
    // These functions are not for user use
    void handleISR(EventType eventType, uint16_t pos);

protected:
    void checkForTXPossible() override;

private:
    UART_HandleTypeDef* _huart;
    bool initialized = false;
    uint16_t currentRXDMAPos = 0;
    uint16_t lastRXDMAPos = 0;
    bool DMA_RX_Triggered = false; // Holds the flag if DMA has been triggered since the last read
    bool DMA_TX_Done = true;       // When this is true we can send more data to DMA
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
