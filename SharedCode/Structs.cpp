#include "Structs.h"

transmitTypes transmitData;
receiveTypes receiveData;
Settings settings;

void initStructs()
{
	transmitData.ch_data.identifier = channelBitID;
	transmitData.tx_misc_data.identifier = txmiscdataID;
	receiveData.rx_data.identifier = rxdataID;
}

void saveSettings() {
	eeWrite(0, settings);
}