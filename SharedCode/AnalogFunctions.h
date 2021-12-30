#ifndef ANALOGFUNCTIONS_H
#define ANALOGFUNCTIONS_H

#include <Arduino.h>
#include "config.h" 


class AnalogFunctions
{
public:
	uint16_t channelData[CHANNELNUMBERS];
	uint16_t oldChannelData[CHANNELNUMBERS];
	void init();
	void initADC();
	void readChannels();
	void readChannelsADC();
	void printChangedChannels();
};

#endif