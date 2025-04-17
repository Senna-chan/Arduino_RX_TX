////
//// Created by senyaa on 4/14/25.
////
//
//#ifndef SERIAL_H
//#define SERIAL_H
//
//#include "main.h"
//#include "usart.h"
//
//#include "Print.h"
//#include <queue>
//
//#ifndef SERIAL_BUFFER_SIZE
//#define SERIAL_BUFFER_SIZE 256
//#endif
//#define SERIAL_BUFFER_QUEUE_SIZE (SERIAL_BUFFER_SIZE * 8) // Max size of serial queue
//
//void UART_TX_Done(UART_HandleTypeDef* huart);
//void UART_RX_Done(UART_HandleTypeDef* huart);
//class HardwareSerial : public Print {
//public:
//    void create(UART_HandleTypeDef* huart);
//    void init();
//    // Overloads from Print
//    int availableForWrite() override;
//    size_t write(const uint8_t* buffer, size_t size) override;
//    size_t write(uint8_t) override;
//    size_t availableForRead();
//    static HardwareSerial* getInstance(UART_HandleTypeDef* huart);
//    // These functions are not for user use
//    void handleISR(bool rxEvent, uint16_t pos);
//
//private:
//    bool initialized = false;
//    UART_HandleTypeDef* _huart;
//    std::deque<uint8_t> tx_queue;
//    std::deque<uint8_t> rx_queue;
//    uint8_t tx_dma_buf[SERIAL_BUFFER_SIZE];
//    uint8_t rx_dma_buf[SERIAL_BUFFER_SIZE];
//};
//
//#if defined(USART1)
//extern HardwareSerial Serial1;
//#endif
//#if defined(USART2)
//extern HardwareSerial Serial2;
//#endif
//#if defined(USART3)
//extern HardwareSerial Serial3;
//#endif
//#if defined(UART4) || defined(USART4)
//extern HardwareSerial Serial4;
//#endif
//#if defined(UART5) || defined(USART5)
//extern HardwareSerial Serial5;
//#endif
//#if defined(USART6)
//extern HardwareSerial Serial6;
//#endif
//#if defined(UART7) || defined(USART7)
//extern HardwareSerial Serial7;
//#endif
//#if defined(UART8) || defined(USART8)
//extern HardwareSerial Serial8;
//#endif
//#if defined(UART9)
//extern HardwareSerial Serial9;
//#endif
//#if defined(UART10) || defined(USART10)
//extern HardwareSerial Serial10;
//#endif
//#if defined(LPUART1)
//extern HardwareSerial SerialLP1;
//#endif
//#if defined(LPUART2)
//extern HardwareSerial SerialLP2;
//#endif
//#if defined(LPUART3)
//extern HardwareSerial SerialLP3;
//#endif
//
//#endif // SERIAL_H
