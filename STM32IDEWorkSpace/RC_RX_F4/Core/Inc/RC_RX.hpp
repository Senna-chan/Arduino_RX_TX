/*
 * RX_RX.h
 *
 *  Created on: Apr 19, 2022
 *      Author: Senna
 */

#ifndef INC_RC_RX_HPP_
#define INC_RC_RX_HPP_

#include "TimerHelpers.hpp"

#ifdef __cplusplus
extern "C"
{
#endif

	#include "SharedFunctions.h"
	#include "SharedVars.h"
	#include "math.h"
	#include "dac.h"
	#include "spi.h"
	#include "tim.h"
	#include "usart.h"
	#include "gpio.h"
	#include "crc.h"
	#include "nrf24.h"
	#include <stdio.h>
	#include "w25qxx.h"
	#include <stdlib.h>

	void setup(void);
	void loop(void);
	void Error_Handler_CPP(char * file, int line);
	void SerialPrint(char* string, int length);
	void UART1TXDone(UART_HandleTypeDef *huart);
	void UART1Error(UART_HandleTypeDef *huart);
#ifdef __cplusplus
}
#endif

void setStatusLed(uint8_t R, uint8_t G, uint8_t B);

void common_nRFInit();

void UART_SendChar(char b);
void UART_SendStr(char *string);

void configureChannels();

void setupChannelOutputConfign(uint8_t channelNumber);
void setupChannelOutputConfigt(uint8_t channelNumber, TIM_HandleTypeDef* mainTimer, uint8_t mainTimerChannel);
void setupChannelOutputConfigtm(uint8_t channelNumber, TIM_HandleTypeDef* mainTimer, uint8_t mainTimerChannel, __IO uint32_t* miscOutput, GPIO_TypeDef* muxGPIO, uint32_t muxPin);
void setupChannelOutputConfigtt(uint8_t channelNumber, TIM_HandleTypeDef* mainTimer, uint8_t mainTimerChannel, __IO uint32_t* miscOutput, TIM_HandleTypeDef* miscTimConf, uint8_t miscTIMCH, GPIO_TypeDef* muxGPIO, uint32_t muxPin);


// CustomUartFunctions
void sendChannelData();

#endif /* INC_RC_RX_HPP_ */
