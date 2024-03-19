/*
 * sbus.h
 *
 *  Created on: Mar 29, 2022
 *      Author: Senna
 */

#ifndef SBUS_SBUS_H_
#define SBUS_SBUS_H_

#include "stm32f4xx_hal.h"

void begin(USART_TypeDef* uart);
void setChannel(uint8_t channel, uint16_t value);
uint16_t getChannel(uint8_t channel)

#endif /* SBUS_SBUS_H_ */
