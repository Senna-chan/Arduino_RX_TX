// //
// // Created by senyaa on 4/14/25.
// //
//
// #include "HardwareSerial.h"
//
// void UART_TX_Done(UART_HandleTypeDef* huart) {
//     HardwareSerial::getInstance(huart)->handleISR(false, 0);
// }
//
// void UART_RX_Done(UART_HandleTypeDef* huart, uint16_t pos) {
//     HardwareSerial::getInstance(huart)->handleISR(true, pos);
// }
//
// void HardwareSerial::handleISR(bool rxEvent, uint16_t pos) {
//     if (_huart == nullptr) {
//         return;
//     }
//     if (rxEvent) {
//         if (pos) {
//             rx_queue.insert(rx_queue.end(), &rx_dma_buf[0], &rx_dma_buf[pos]);
//         }
//         HAL_UARTEx_ReceiveToIdle_DMA(_huart, rx_dma_buf, SERIAL_BUFFER_SIZE); // Directly restart reading
//     }
// }
//
// HardwareSerial* HardwareSerial::getInstance(UART_HandleTypeDef* huart) {
//     if (huart->Instance == USART1) {
//         return &Serial1;
//     } else if (huart->Instance == USART2) {
//         return &Serial2;
//     } else if (huart->Instance == USART3) {
//         return &Serial3;
//     } else if (huart->Instance == UART4) {
//         return &Serial4;
//     } else if (huart->Instance == UART5) {
//         return &Serial5;
//     } else {
//         Error_Handler();
//     }
//     return nullptr;
// }
//
// void HardwareSerial::create(UART_HandleTypeDef* huart) {
//     _huart = huart;
// }
//
// void HardwareSerial::init() {
//     tx_queue.resize(SERIAL_BUFFER_QUEUE_SIZE);
//     rx_queue.resize(SERIAL_BUFFER_QUEUE_SIZE);
//     // HAL_UART_UnRegisterCallback(_huart, HAL_UART_ERROR_CB_ID);
//     HAL_UART_UnRegisterCallback(_huart, HAL_UART_TX_COMPLETE_CB_ID);
//     HAL_UART_UnRegisterRxEventCallback(_huart);
//
//     // HAL_UART_RegisterCallback(_huart, HAL_UART_ERROR_CB_ID, );
//     HAL_UART_RegisterCallback(_huart, HAL_UART_TX_COMPLETE_CB_ID, UART_TX_Done);
//     HAL_UART_RegisterRxEventCallback(_huart, UART_RX_Done);
//     HAL_UARTEx_ReceiveToIdle_DMA(_huart, rx_dma_buf, SERIAL_BUFFER_SIZE);
//     initialized = true;
// }
//
// size_t HardwareSerial::availableForRead() {
//     return rx_queue.size();
// }
//
// int HardwareSerial::availableForWrite() {
//     return SERIAL_BUFFER_QUEUE_SIZE - tx_queue.size();
// }
// size_t HardwareSerial::write(const uint8_t* buffer, size_t size) {
//     rx_queue.insert(rx_queue.end(), buffer[0], buffer[size]);
//     return size;
// }
// size_t HardwareSerial::write(uint8_t) {
//     return 1;
// }
