#pragma once

#ifdef ARDUINO
	#include <Arduino.h>
#endif

#define CTYPE_NONE	0
#define CTYPE_ADC	-1
#define CTYPE_IO	1

typedef union {
	uint8_t u8[32];
	uint16_t u16[16];
	uint32_t u32[8];
	uint64_t u64[4];
}byteDataUnion;

typedef struct {
	int8_t type; //!< If 0 then not set. If -1 then ADC. If 1 then Digital
	uint8_t index;
} s_channelMapping;

typedef struct {
	uint32_t frequency;
	uint32_t resolution;
} s_pwmConfig;

typedef struct {
	uint32_t minFrequency;
	uint32_t maxFrequency;
} s_stepperConfig;

typedef struct
{
	uint16_t chMin;						// Only needed for analog channels
	uint16_t chMax;						// Only needed for analog channels
	uint16_t chMid;						// Only needed for analog channels
	int16_t  chOffset;					// Only needed for analog channels
	uint16_t chDefaults;				// Needed for all channels
	uint8_t  outputMode;				// Output modes for channels
	s_pwmConfig pwmConfig;				// PWM Config
	s_stepperConfig stepperConfig;		// Stepper Config
	s_channelMapping channelMapping[2];	// Channel mapping for min/mid/max or min/max or any other combo. First index is adc(-1) or digital(1). Second index is adc/io index
} channelConfigs;

typedef struct
{
	uint8_t source1;
	uint8_t source2;
	uint8_t dest1;
	uint8_t dest2;
	uint8_t type;
} channelMixStruct;

typedef struct
{
	int32_t minValue;
	int32_t maxValue;
	int32_t steps;
	int32_t curValue;
	int32_t division; // 1 or multiple of 10
} encoderStruct;

typedef struct
{
	char* name;
	uint8_t nameSize;
	channelConfigs channel_settings[24];
	uint16_t deadzone; // Deadzone is +/- from either center or from minPostion and maxPosition
	uint32_t channelReversed; // Bitmap of all the channels in 4 bytes to save room in the EEPROM
	channelMixStruct channelMixing[8];
	encoderStruct encoderSettings[2];
} Model;

typedef struct
{
	uint16_t version;
	uint8_t activeModel;
	Model model[8];
} Settings;


typedef struct
{
	uint8_t identifier;
	uint8_t batteryVoltage;
	double lat;
	double lon;
	uint16_t speedms;
} rxData;

#define CHANNELDATAID 			0b0001
#define SETTINGSDATAID			0b0010
#define SETTINGSDATASETUPID		0b0011
typedef struct
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
} channelBitSettings;

typedef union
{
	byteDataUnion bytesUnion;
	channelBitSettings ch_data;
} transmitTypes;
typedef union
{
	byteDataUnion bytesUnion;
	rxData rx_data;
} receiveTypes;


#define OUTPUTMODE_RC 	0	///< Default 1000 to 2000 ms
#define OUTPUTMODE_DAC 	1	///< Use CH7/CH8 for DAC1/DAC2 output
#define OUTPUTMODE_IO 	2	///< Simple HIGH/LOW
#define OUTPUTMODE_PWM 	3	///< PWM using one of of the six timer outputs
#define OUTPUTMODE_STEP	4	///< PWM steppermode with changing frequency

typedef struct
{
	uint8_t outputMode;
	uint8_t outputSet;
	__IO uint32_t* timOutput;
	uint32_t* miscOutput1;
	uint32_t* miscOutput2;
} channelOutputConfig;

extern transmitTypes transmitData;
extern receiveTypes receiveData;


extern Settings settings;
extern Model activeSettings;

void initStructs();
void saveSettings();
