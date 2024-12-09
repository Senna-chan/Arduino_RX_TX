// SBUS.h

#ifndef _SBUS_h
#define _SBUS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define RC_CHANNEL_MIN 990
#define RC_CHANNEL_MAX 2010

#define SBUS_MIN_OFFSET 173
#define SBUS_MID_OFFSET 992
#define SBUS_MAX_OFFSET 1811
#define SBUS_CHANNEL_NUMBER 16
#define SBUS_PACKET_LENGTH 25
#define SBUS_FRAME_HEADER 0x0f
#define SBUS_FRAME_FOOTER 0x00
#define SBUS_FRAME_MASK 0x0F
#define SBUS_FRAME_FOOTER_V2 0x04
#define SBUS_STATE_FAILSAFE 0x08
#define SBUS_STATE_SIGNALLOSS 0x04
#define SBUS_UPDATE_RATE 15 //ms

class SBUS
{
 public:
	void init(HardwareSerial* serial);
	void sbusPreparePacket(uint16_t channels[], bool isSignalLoss, bool isFailsafe);
	bool loop();
	bool read(uint16_t* channels, bool* failsafe, bool* lostFrame);
	bool parse();
private:
	HardwareSerial *serial;
	uint8_t sbusOutPacket[SBUS_PACKET_LENGTH];
	uint8_t sbusInPacket[SBUS_PACKET_LENGTH];
	uint32_t sbusTime = 0;
	int feedState;
};

#endif

