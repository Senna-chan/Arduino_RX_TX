// ChannelFunctions.h

#ifndef _CHANNELFUNCTIONS_h
#define _CHANNELFUNCTIONS_h

#include "Arduino.h"
#include <MyHelpers.h>
#include "SharedVars.h"

enum mixTypes{
	ADDSUBTRACT
};

void mixChannels(uint16_t ch1In, uint16_t ch2In, uint16_t* ch1Out, uint16_t* ch2Out, mixTypes mixType);

#endif

