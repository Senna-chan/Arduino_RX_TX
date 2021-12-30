// 
// 
// 

#include "ChannelFunctions.h"

void mixChannels(uint16_t ch1In, uint16_t ch2In, uint16_t* ch1Out, uint16_t* ch2Out, mixTypes mixType)
{
	if (mixType == ADDSUBTRACT) {
		if (outside(ch2In, 1480, 1520) && outside(ch1In, 1480, 1520))
		{
			int16_t diff = ch1In - 1500;
			if (ch1In > 1500) {
				*ch1Out = ch2In + diff;
				*ch2Out = ch2In - diff;
			}
			else
			{
				*ch1Out = ch2In - diff;
				*ch2Out = ch2In + diff;
			}
		}
		else if (outside(ch2In, 1480, 1520))
		{
			*ch1Out = *ch2Out = ch2In;
		}
		else if (outside(ch1In, 1480, 1520))
		{
			int16_t diff = ch1In - 1500;
			if (ch1In > 1500) {
				*ch1Out = 1500 + diff;
				*ch2Out = 1500 - diff;
			}
			else
			{
				*ch1Out = 1500 - diff;
				*ch2Out = 1500 + diff;
			}
		}
		else
		{
			*ch1Out = *ch2Out = 1500;
		}
	}
	*ch1Out = constrain(*ch1Out, 1000, 2000);
	*ch2Out = constrain(*ch2Out, 1000, 2000);
}
