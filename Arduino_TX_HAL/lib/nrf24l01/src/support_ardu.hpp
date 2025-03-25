#ifndef _NRF_SUPPORT_H
#define _NRF_SUPPORT_H

#include <Arduino.h>

extern SPI_HandleTypeDef nRF_hspi;

extern GPIO_TypeDef *nRF_cePort;
extern GPIO_TypeDef *nRF_csnPort;
extern uint16_t      nRF_cePin;
extern uint16_t      nRF_csnPin;

static inline void nRF24_CE_L() {
    HAL_GPIO_WritePin(nRF_cePort, nRF_cePin, GPIO_PIN_RESET);
}

static inline void nRF24_CE_H() {
    HAL_GPIO_WritePin(nRF_cePort, nRF_cePin, GPIO_PIN_SET);
}

static inline void nRF24_CSN_L() {
    HAL_GPIO_WritePin(nRF_csnPort, nRF_csnPin, GPIO_PIN_RESET);
}

static inline void nRF24_CSN_H() {
    HAL_GPIO_WritePin(nRF_csnPort, nRF_csnPin, GPIO_PIN_SET);
}

static const char* HAL_SPI_StateTypeDef_string_table[8] = {
    "HAL_SPI_STATE_RESET",
    "HAL_SPI_STATE_READY",
    "HAL_SPI_STATE_BUSY",
    "HAL_SPI_STATE_BUSY_TX",
    "HAL_SPI_STATE_BUSY_RX",
    "HAL_SPI_STATE_BUSY_TX_RX",
    "HAL_SPI_STATE_ERROR",
    "HAL_SPI_STATE_ABORT",
};

static const char* HAL_StatusTypeDef_string_table[4] = {
    "HAL_OK",
    "HAL_ERROR",
    "HAL_BUSY",
    "HAL_TIMEOUT",
};

inline void nRF24_printf(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    char buf[255];
    vsnprintf(buf, 255, fmt, args);
    Serial.print(buf);
    va_end(args);
    delay(100);
}

static inline uint8_t nRF24_LL_RW(uint8_t data) {
    // Wait until TX buffer is empty
    uint8_t result;
    auto hal_result = HAL_SPI_TransmitReceive(&nRF_hspi, &data, &result, 1, 2000);
    int count = 0;
    while(hal_result != HAL_OK && ++count < 30) {
        nRF24_printf("%2d: HAL_RESULT: %s, SPI_STATE %s\n",count, HAL_StatusTypeDef_string_table[hal_result], HAL_SPI_StateTypeDef_string_table[nRF_hspi.State]);
        delayMicroseconds(50);
        hal_result = HAL_SPI_TransmitReceive(&nRF_hspi, &data, &result, 1, 2000);
    };
    return result;
}

static inline void Delay_ms(uint32_t ms) { HAL_Delay(ms); }

inline void nRF24_SetCEPin(uint16_t pin)
{
    nRF_cePort = digitalPinToPort(pin);
    nRF_cePin = digitalPinToBitMask(pin);
}

inline void nRF24_SetCSNPin(uint16_t pin)
{
    nRF_csnPort = digitalPinToPort(pin);
    nRF_csnPin = digitalPinToBitMask(pin);
}

#endif //__SUPPORT_H
