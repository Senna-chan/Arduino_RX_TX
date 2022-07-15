/*
 Name:		SerialControlLibrary.h
 Created:	4/21/2022 4:30:34 PM
 Author:	Senna
 Editor:	http://www.visualmicro.com
*/

#ifndef _SerialControlLibrary_h
#define _SerialControlLibrary_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include <Arduino.h>
#else

#endif

#include <map>

class SerialControlLibrary {

public:
	typedef std::function<void(const char*)> serialCallbackFunction;
	typedef std::function<void()> serialCallbackFunctionVoid;
private:

	typedef struct s_serialCallbacks;
	typedef std::map<char, s_serialCallbacks*> serialCallbackMap;
	struct s_serialCallbackFunc {
		serialCallbackFunction datacb;
		serialCallbackFunctionVoid voidcb;
	};
	struct s_serialCallbacks {
		s_serialCallbackFunc callback;
		serialCallbackMap serialCallbacks;
	};  // This is recurs
	serialCallbackMap serialCallbacks;
#ifdef ARDUINO
	HardwareSerial* serial;
#endif
	UART_HandleTypeDef* uart;
	char endLine;
	char* buf;
	char* bufPtr;
	uint16_t bufSize;
public:
#ifdef ARDUINO
	/**
	 * Used for arduino because Arduino is holding RX busy.
	 * 
	 * \param uart
	 * \param endLine
	 * \param bufSize
	 */
	void init(HardwareSerial* serial, char endLine = '\n', uint16_t bufferSize = 255);
#else 
	void init(UART_HandleTypeDef * uart, char endLine = '\n', uint16_t bufferSize = 255);
#endif
	void loop();
	void addDataCallback(const char* serialData, serialCallbackFunction cb);
	void addVoidCallback(const char* serialData, serialCallbackFunctionVoid cb);
};

#endif

