#include "Structs.h"

transmitTypes transmitData;
receiveTypes receiveData;
void initStructs()
{
	transmitData.ch_data.identifier = channelBitID;
	transmitData.tx_misc_data.identifier = txmiscdataID;
	receiveData.rx_data.identifier = rxdataID;
}