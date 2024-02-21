// CustomRC.h

#ifndef _CUSTOMRC_h
#define _CUSTOMRC_h

#include "Arduino.h"
#include <functional>

typedef std::function<void(uint16_t*, uint16_t*)> channelDataCallback;

class CustomRC {
private:
	uint8_t headerFound = 0;
	uint8_t headerByte = 0xFA;
	uint8_t headerSize = 3;
	uint8_t footerByte = 0xFB;
	uint8_t footerSize = 2;
	uint8_t dataSize = 0;
	uint8_t serialDataToRead = headerSize; ///< Serial data amount to read

	enum commands {
		CHANNELS,
		STREAM_CHANNELS
	};
	uint8_t currentBufferIndex = 0;
	uint8_t uartBuffer[255];


	uint16_t prevChannels[25]; ///<Used to keep track of previous values

	HardwareSerial* _serial;
	channelDataCallback channelCallback;
	uint8_t calculateCRC(uint8_t* data, uint8_t length);
	void writePacket(uint8_t command, uint8_t* data, uint8_t dataSize);
	void parsePacket();
public:
	void loop();
	void init(HardwareSerial* serial);
	void configureChannelStreaming(uint16_t millis);
	void getChannels();
	void attachChannelCallback(channelDataCallback cb);
};

#endif

