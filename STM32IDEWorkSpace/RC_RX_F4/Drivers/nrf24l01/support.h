//
// Created by ilia.motornyi on 13-Dec-18.
//

#ifndef __SUPPORT_H
#define __SUPPORT_H

#include "main.h"


#ifdef USE_HAL_DRIVER

static inline void nRF24_CE_L() {
    HAL_GPIO_WritePin(nRF_CE_GPIO_Port, nRF_CE_Pin, GPIO_PIN_RESET);
}

static inline void nRF24_CE_H() {
    HAL_GPIO_WritePin(nRF_CE_GPIO_Port, nRF_CE_Pin, GPIO_PIN_SET);
}

static inline void nRF24_CSN_L() {
    HAL_GPIO_WritePin(nRF_CSN_GPIO_Port, nRF_CSN_Pin, GPIO_PIN_RESET);
}

static inline void nRF24_CSN_H() {
    HAL_GPIO_WritePin(nRF_CSN_GPIO_Port, nRF_CSN_Pin, GPIO_PIN_SET);
}

static const char* HAL_SPI_StateTypeDef_string_table[8] = {
    "SS_RESET",
    "SS_READY",
    "SS_BUSY",
    "SS_BUSY_TX",
    "SS_BUSY_RX",
    "SS_BUSY_TX_RX",
    "SS_ERROR",
    "SS_ABORT",
};

static const char* HAL_StatusTypeDef_string_table[4] = {
    "H_OK",
    "H_ERROR",
    "H_BUSY",
    "H_TIMEOUT",
};

static inline uint8_t nRF24_LL_RW(uint8_t data) {
    // Wait until TX buffer is empty
    uint8_t result;
    HAL_StatusTypeDef hal_result =HAL_SPI_TransmitReceive(&hspi3,&data,&result,1,2000);
    if(hal_result!=HAL_OK) {
    	printf("H: %s, S %s\n", HAL_StatusTypeDef_string_table[hal_result], HAL_SPI_StateTypeDef_string_table[nRF_hspi.State]);
//        Error_Handler();
    };
    return result;
}

static inline void USART_printf(USART_TypeDef * usart, const char* fmt, ...){
    va_list args;
    va_start(args, fmt);
    char buf[255];
    int bufSize = vsnprintf(buf, 255, fmt, args);
    HAL_UART_Transmit(&huart1, (uint8_t*)buf, bufSize, 100);
    va_end(args);
    HAL_Delay(100);
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
