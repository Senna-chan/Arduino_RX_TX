#pragma once

#include "Arduino.h"


extern uint16_t chPins[8];

struct channelConfigs
{
	uint16_t chMin[8];		 // Only needed for analog channels
	uint16_t chMax[8];		 // Only needed for analog channels
	uint16_t chMid[8];		 // Only needed for analog channels
	int16_t  chOffset[8];	 // Only needed for analog channels
	uint16_t chDefaults[24]; // Needed for all channels
	uint8_t  outputMode[24]; // Output modes for channels
};

struct channelMixStruct
{
	uint8_t source1;
	uint8_t source2;
	uint8_t dest1;
	uint8_t dest2;
	uint8_t type;
};
struct encoderStruct
{
	int32_t minValue;
	int32_t maxValue;
	int32_t steps;
	int32_t curValue;
	int32_t division; // 1 or multiple of 10
};

struct Model
{
	char* name;
	channelConfigs channel_settings;
	byte channelMapping[24];
	uint32_t channelReversed; // Using only one bit to save room in the EEPROM
	channelMixStruct channelMixing[8];
	encoderStruct encoderSettings[2];
};

struct Settings
{
	byte version;
	uint16_t deadzone; // Deadzone is +/- from either center or from minPostion and maxPosition
	uint8_t activeModel;
	Model model[8];
};

struct bigStruct // Used if we have fancier gear and for RX to controller via Serial(not SBUS)
{
	uint8_t identifier;
	uint16_t channel[24];
	uint16_t twoBooloptions;
	uint8_t oneBooloptions;
	int16_t  encoder1;
	int16_t  encoder2;
};

union bigUnion
{
	byte bytes[64];
	bigStruct big_struct;
};

const uint8_t txmiscdataID = 't';
struct txmiscdata
{
	uint8_t identifier;
	int16_t  encoder1;
	int16_t  encoder2;
};

const uint8_t rxdataID = 'r';
struct rxData
{
	uint8_t identifier;
	uint8_t batteryVoltage;
	float lat;
	float lon;
	uint16_t speedms;
};

const uint8_t channelSettings1ID = 'c';
const uint8_t channelSettings2ID = 'C';
struct channelSettings
{
	uint8_t identifier;
	uint16_t defaultValues[13];
	int16_t encoder1;
	int16_t encoder2;
};

const uint8_t channelBitID = 0b1111;
struct channelBitSettings
{
	// No bits free
	uint64_t identifier : 4;
	uint64_t channel1 : 10;
	uint64_t channel2 : 10;
	uint64_t channel3 : 10;
	uint64_t channel4 : 10;
	uint64_t channel5 : 10;
	uint64_t channel6 : 10;

	// 4 bits free
	uint64_t channel7 : 10;
	uint64_t channel8 : 10;
	uint64_t channel9 : 10;
	uint64_t channel10 : 10;
	uint64_t channel11 : 10;
	uint64_t channel12 : 10;

	// 4 bits free
	uint64_t channel13 : 10;
	uint64_t channel14 : 10;
	uint64_t channel15 : 10;
	uint64_t channel16 : 10;
	uint64_t channel17 : 10;
	uint64_t channel18 : 10;

	// 4 bits free
	uint64_t channel19 : 10;
	uint64_t channel20 : 10;
	uint64_t channel21 : 10;
	uint64_t channel22 : 10;
	uint64_t channel23 : 10;
	uint64_t channel24 : 10;

};

union transmitTypes
{
	uint8_t bytes[32];
	txmiscdata tx_misc_data;
	channelBitSettings ch_data;
};
union receiveTypes
{
	uint8_t bytes[32];
	rxData rx_data;
};

extern transmitTypes transmitData;
extern receiveTypes receiveData;

void initStructs();