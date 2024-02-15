/*
 Name:		CommunicationsLib.h
 Created:	9/5/2023 10:18:15 PM
 Author:	Senna
 Editor:	http://www.visualmicro.com
*/

#ifndef _CommunicationsLib_h
#define _CommunicationsLib_h

#ifdef ARDUINO
#include <Arduino.h>
#else
#include <function>
#include <stdint.h>
#endif

typedef std::function<void(uint8_t*)> serialCallbackFunction;
typedef std::function<uint8_t(void)> readerFunc;
typedef std::function<bool(void)> dataAvailableFunc;
class Comms {
private:
	std::map<uint16_t, std::map<uint16_t, serialCallbackFunction>> serialCallbackMap;
	readerFunc reader;
	dataAvailableFunc dataAvailable;
	uint16_t bufSize;
public:
	void init(readerFunc reader, dataAvailableFunc dataAvailable, uint16_t bufferSize = 255);
	void process();
	void addCallback(uint16_t module, uint16_t command, serialCallbackFunction callback);
};



#endif

