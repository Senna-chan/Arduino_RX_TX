// 
// 
// 

#include "ChannelFunctions.h"

void mixChannels(uint16_t sch1, uint16_t sch2, uint16_t* dch1, uint16_t* dch2)
{
	if (outside(sch2, 1480, 1520) && outside(sch1, 1480, 1520))
	{
		int16_t diff = sch1 - 1500;
		if (sch1 > 1500) {
			*dch1 = sch2 + diff;
			*dch2 = sch2 - diff;
		}
		else
		{
			*dch1 = sch2 - diff;
			*dch2 = sch2 + diff;
		}
	}
	else if (outside(sch2, 1480, 1520))
	{
		*dch1 = *dch2 = sch2;
	}
	else if (outside(sch1, 1480, 1520))
	{
		int16_t diff = sch1 - 1500;
		if (sch1 > 1500) {
			*dch1 = 1500 + diff;
			*dch2 = 1500 - diff;
		}
		else
		{
			*dch1 = 1500 - diff;
			*dch2 = 1500 + diff;
		}
	}
	else
	{
		*dch1 = *dch2 = 1500;
	}

	*dch1 = constrain(*dch1, 1000, 2000);
	*dch2 = constrain(*dch2, 1000, 2000);
}
