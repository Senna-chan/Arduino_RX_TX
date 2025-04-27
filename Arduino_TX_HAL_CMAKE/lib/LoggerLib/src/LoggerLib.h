/*
 Name:		LoggerLib.h
 Created:	4/19/2022 9:55:29 PM
 Author:	Senna
 Editor:	http://www.visualmicro.com
*/

#ifndef _LoggerLib_h
#define _LoggerLib_h

#include "main.h"
#include "freertos.h"

class Logger{
public:
	void init();
	void printf(const char* format, ...);
	void printfln(const char* format, ...);
private:
	void writeToQueue(const char* value);
	TaskHandle_t printTask;
	UART_HandleTypeDef* uart;
	SemaphoreHandle_t* serialSemaphore;
};

#endif
