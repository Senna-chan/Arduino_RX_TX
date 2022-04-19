// Logger.h

#ifndef _LOGGER_h
#define _LOGGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include <Arduino.h>
#else
#if defined(STM32F1)
	#include "stm32f103.h"
#elif defined(STM32F4)
	#include "stm32f403.h"
#endif
#endif


class Logger {
private:

public:
	void init(UART_HandleTypeDef* uart);
	void loop();
};

#endif

