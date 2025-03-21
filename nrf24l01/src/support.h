//
// Created by ilia.motornyi on 13-Dec-18.
//

#ifndef __SUPPORT_H
#define __SUPPORT_H

#ifdef ARDUINO
#include <Arduino.h>
#endif
#ifdef USE_HAL_DRIVER
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


static inline uint8_t nRF24_LL_RW(uint8_t data) {
    // Wait until TX buffer is empty
    uint8_t result;
    auto hal_result = HAL_SPI_TransmitReceive(&nRF_hspi, &data, &result, 1, 2000);
    int count = 0;
    while(hal_result != HAL_OK && ++count < 30) {
        Serial.printf("%2d: HAL_RESULT: %s, SPI_STATE %s\n",count, HAL_StatusTypeDef_string_table[hal_result], HAL_SPI_StateTypeDef_string_table[nRF_hspi.State]);
        delayMicroseconds(50);
        hal_result = HAL_SPI_TransmitReceive(&nRF_hspi, &data, &result, 1, 2000);
    };
    return result;
}

static inline void USART_printf(USART_TypeDef *usart, const char* fmt, ...){
    va_list args;
    va_start(args, fmt);
    char buf[255];
    vsnprintf(buf, 255, fmt, args);
    Serial.print(buf);
    va_end(args);
    delay(100);
}

static inline void Delay_ms(uint32_t ms) { HAL_Delay(ms); }

#elif USE_FULL_LL_DRIVER
#define NRF_SPI SPI2

static inline void nRF24_CE_L() {
    LL_GPIO_ResetOutputPin(NRF_CE_GPIO_Port, NRF_CE_Pin);
}

static inline void nRF24_CE_H() {
    LL_GPIO_SetOutputPin(NRF_CE_GPIO_Port, NRF_CE_Pin);
}

static inline void nRF24_CSN_L() {
    LL_GPIO_ResetOutputPin(NRF_CSN_GPIO_Port, NRF_CSN_Pin);
}

static inline void nRF24_CSN_H() {
    LL_GPIO_SetOutputPin(NRF_CSN_GPIO_Port, NRF_CSN_Pin);
}


static inline uint8_t nRF24_LL_RW(uint8_t data) {
    LL_SPI_SetRxFIFOThreshold(NRF_SPI,LL_SPI_RX_FIFO_TH_QUARTER);
    LL_SPI_Enable(NRF_SPI);
    // Wait until TX buffer is empty
    while (LL_SPI_IsActiveFlag_BSY(NRF_SPI));
    while (!LL_SPI_IsActiveFlag_TXE(NRF_SPI));
    LL_SPI_TransmitData8(NRF_SPI, data);
    while (!LL_SPI_IsActiveFlag_RXNE(NRF_SPI));
    return LL_SPI_ReceiveData8(NRF_SPI);
}


static inline void Delay_ms(uint32_t ms) { LL_mDelay(ms); }

#else // nor USE_FULL_LL_DRIVER, nor USE_HAL_DRIVER

#error LL or HAL support must be enabled

#endif // USE_FULL_LL_DRIVER

#endif //__SUPPORT_H
