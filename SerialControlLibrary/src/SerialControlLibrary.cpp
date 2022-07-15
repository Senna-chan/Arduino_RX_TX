/*
 Name:		SerialControlLibrary.cpp
 Created:	4/21/2022 4:30:34 PM
 Author:	Senna
 Editor:	http://www.visualmicro.com
*/

#include "SerialControlLibrary.h"

#ifdef ARDUINO
	void SerialControlLibrary::init(HardwareSerial* serial, char endLine, uint16_t bufSize) {
	this->serial = serial;
#else
	void SerialControlLibrary::init(UART_HandleTypeDef* uart, char endLine, uint16_t bufSize) {
	this->uart = uart; 
#endif
	this->endLine = endLine;
	buf = (char*)malloc(bufSize);
	memset(buf, 0, bufSize);
	bufPtr = buf;
	this->bufSize = bufSize;
}

void SerialControlLibrary::loop()
{
#ifdef ARDUINO
	if(serial->peek() != -1){
		*bufPtr = (char)serial->read();
		//Serial.printf("Got char H(0x%02X)'%c'\r\n", *bufPtr, *bufPtr);
#else
	HAL_StatusTypeDef status = HAL_UART_Receive(uart, (uint8_t*)bufPtr, 1, 0);
	if (status == HAL_OK) {
#endif
			if (*bufPtr == endLine) {
				*bufPtr = 0;
				//Serial.printf("Got newline '%c'. Bufferdata '%s'\r\n", endLine, buf);
				char* ptr = buf;
				serialCallbackMap* currentMap = &serialCallbacks;
				for (ptr;ptr < bufPtr; ptr++) {
					char c = *ptr;
					if (currentMap->find(c) == currentMap->end()) {
						break;
					}
					else {
						s_serialCallbacks* scb = currentMap->at(c);
						if (scb->serialCallbacks.size() == 0) {
							if (scb->callback.datacb != nullptr) {
								uint32_t copyAmount = ptr - buf;
								char* data = nullptr;
								data = (char*)malloc(copyAmount);
								memset(data, 0, copyAmount);
								memcpy(data, ptr+1, copyAmount);
								scb->callback.datacb(data);
								free(data);
							}
							else if (scb->callback.voidcb != nullptr) {
								scb->callback.voidcb();
							}
							else {
								Serial.printf("NO CALLBACK: End of command '%c', buf '%s'\r\n", c, buf);
							}
							break;
						}
						currentMap = &scb->serialCallbacks;
					}
				}
				memset(buf, 0, bufSize);
				bufPtr = buf;
			}
			else {
				bufPtr++;
			}

	}
}

void SerialControlLibrary::addDataCallback(const char* serialData, serialCallbackFunction cb)
{
	auto sdLen = strlen(serialData);
	serialCallbackMap* currentMap = &serialCallbacks;
	s_serialCallbacks* scb;
	for (const char* ptr = serialData; ptr < serialData + sdLen; ptr++) {
		char c = *ptr;
		if (currentMap->find(c) == currentMap->end()) {
			currentMap->insert(std::pair<char, s_serialCallbacks*>(c, new s_serialCallbacks));
		}
		scb = currentMap->at(c);
		currentMap = &scb->serialCallbacks;
	}
	scb->callback.datacb = cb;
}

void SerialControlLibrary::addVoidCallback(const char* serialData, serialCallbackFunctionVoid cb)
{
	auto sdLen = strlen(serialData);
	serialCallbackMap* currentMap = &serialCallbacks;
	s_serialCallbacks* scb;
	for (const char* ptr = serialData; ptr < serialData + sdLen; ptr++) {
		char c = *ptr;
		if (currentMap->find(c) == currentMap->end()) {
			currentMap->insert(std::pair<char, s_serialCallbacks*>(c, new s_serialCallbacks));
		}
		scb = currentMap->at(c);
		currentMap = &scb->serialCallbacks;
	}
	scb->callback.voidcb = cb;
}
