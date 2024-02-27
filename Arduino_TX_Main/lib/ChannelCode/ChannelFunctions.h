// ChannelFunctions.h

#ifndef _CHANNELFUNCTIONS_h
#define _CHANNELFUNCTIONS_h

#include <Arduino.h>

uint16_t parseADCChannel(const uint16_t raw_channel, const uint16_t minValue, const uint16_t midValue, const uint16_t maxValue, const uint16_t deadZone, const uint16_t offset);
#endif



