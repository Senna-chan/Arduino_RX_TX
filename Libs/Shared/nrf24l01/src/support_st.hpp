#ifndef _NRF_SUPPORT_H
#define _NRF_SUPPORT_H

#include "main.h"

extern SPI_HandleTypeDef *nRF_hspi;
extern UART_HandleTypeDef *nRF_uart;

extern GPIO_TypeDef *nRF_cePort;
extern GPIO_TypeDef *nRF_csnPort;
extern uint16_t      nRF_cePin;
extern uint16_t      nRF_csnPin;

inline void Delay_ms(uint32_t ms) 
{ 
    HAL_Delay(ms); 
}

inline void nRF24_CE_L() {
    HAL_GPIO_WritePin(nRF_cePort, nRF_cePin, GPIO_PIN_RESET);
}

inline void nRF24_CE_H() {
    HAL_GPIO_WritePin(nRF_cePort, nRF_cePin, GPIO_PIN_SET);
}

inline void nRF24_CSN_L() {
    HAL_GPIO_WritePin(nRF_csnPort, nRF_csnPin, GPIO_PIN_RESET);
}

inline void nRF24_CSN_H() {
    HAL_GPIO_WritePin(nRF_csnPort, nRF_csnPin, GPIO_PIN_SET);
}

inline uint8_t nRF24_LL_RW(uint8_t data) {
    // Wait until TX buffer is empty
    uint8_t result;
    HAL_StatusTypeDef hal_result = HAL_SPI_TransmitReceive(nRF_hspi, &data, &result, 1, 2000);
    int count = 0;
    while(hal_result != HAL_OK && ++count < 30) {
        Delay_ms(50);
        hal_result = HAL_SPI_TransmitReceive(nRF_hspi, &data, &result, 1, 2000);
    };
    return result;
}

inline void nRF24_printf(const char* fmt, ...){
    va_list args;
    va_start(args, fmt);
    char buf[255];
    vsnprintf(buf, 255, fmt, args);
    HAL_UART_Transmit(nRF_uart, (uint8_t *)buf, 255, 50);
    va_end(args);
    Delay_ms(100);
}

inline void nRF24_SetCEPin(GPIO_TypeDef *gpio, uint16_t pin)
{
    nRF_cePort = gpio;
    nRF_cePin = pin;
}

inline void nRF24_SetCSNPin(GPIO_TypeDef *gpio, uint16_t pin)
{
    nRF_csnPort = gpio;
    nRF_csnPin = pin;
}

#endif //__SUPPORT_H
