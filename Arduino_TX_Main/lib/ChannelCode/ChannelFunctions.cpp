// 
// 
// 

#include <MyHelpers.h>

#include "ChannelFunctions.h"


uint16_t parseADCChannel(const uint16_t raw_channel, const uint16_t minValue, const uint16_t midValue, const uint16_t maxValue, const uint16_t deadZone, const uint16_t offset)
{
	uint16_t result = 0;
	if (midValue != 0) {
		if (between(raw_channel, midValue - deadZone, midValue + deadZone))
		{
			result = 1500;
		}
		else {
			if (raw_channel < midValue)
			{
				result = map(raw_channel, minValue, midValue - deadZone, 1000, 1500);
			}
			else
			{
				result = map(raw_channel, midValue + deadZone, maxValue, 1500, 2000);
			}
		}
	}
	else {
		if (raw_channel > minValue + deadZone) {
			result = map(raw_channel, minValue, maxValue - deadZone, 1000, 2000);
		}
	}
	result += offset;
	result = constrain(result, 1000, 2000);
	return result;
}
