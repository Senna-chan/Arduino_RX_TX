#pragma once

#ifdef ARDUINO
    #include <Arduino.h>
#else
#include <stdint.h>
#endif

#include "SharedVars.h"

// #define CTYPE_NONE   0
// #define CTYPE_ADC    -1
// #define CTYPE_IO 1

typedef union
{
    uint8_t u8[32];
    uint16_t u16[16];
    uint32_t u32[8];
    uint64_t u64[4];
} byteDataUnion;


#define CTYPE_NONE          0
#define CTYPE_ADC           1
#define CTYPE_IO            2
#define CTYPE_AUX_IO        3
#define CTYPE_AUX_SERIAL    4

const char* const channel_types_str[] =
{
    "NONE",
    "ADC",
    "IO",
    "AUX_IO",
    "AUX_RX"
};

#pragma pack(push, 1)
typedef struct
{
    uint8_t type;
    uint8_t index;
} s_channelMapping;


typedef struct
{
    uint32_t frequency;
} s_pwmConfig;

typedef struct
{
    uint32_t minFrequency;
    uint32_t maxFrequency;
} s_stepperConfig;

typedef struct
{
    uint16_t chMin;                     // ADC Calibration      // TODO: Move to ADC_Config struct
    uint16_t chMid;                     // ADC Calibration      // TODO: Move to ADC_Config struct
    uint16_t chMax;                     // ADC Calibration      // TODO: Move to ADC_Coofig struct
    int16_t  chOffset;                  // TODO: Rename to trim
    uint16_t chDefaults;                // Needed for all channels
    uint8_t  outputMode;                // Output modes for channels
    uint8_t  centeredStick;             // Used with combi input for mapping. If true then we will map Mid to ends as both
    s_pwmConfig pwmConfig;              // PWM Config
    s_stepperConfig stepperConfig;      // Stepper Config
    s_channelMapping channelMapping[2]; // Channel mapping for min/mid/max or min/max or any other combo. First index is adc(-1) or digital(1). Second index is adc/io index
} channelConfigs; // TODO: Add MinEndpoint and MaxEndPoint

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
    uint8_t nameSize;
    char name[20]; // Alocate in this to prevent it being a pointer and messing with bytepointer transfers
    channelConfigs channel_settings[RC_MAX_CHANNELS];
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


// Channel data
#define CHANNELDATAID           0b0001
// Settings data packet
#define SETTINGSDATAID          0b0010
// Settings data setup packet
#define SETTINGSDATASETUPID     0b0011

#pragma region RX/TX data structs
// RX/TX
typedef struct {
    uint8_t id : 4;
    uint8_t RES : 4;
    // Rest is not needed
} packetTypeId;


// RX

typedef struct
{
    uint8_t id;
    uint8_t batteryVoltage;
    double lat;
    double lon;
    uint16_t speedms;
} rxData;

typedef struct
{
    uint8_t id : 4;
    uint8_t RES : 4;
    uint16_t settingsPacket;
} rxSettingsDataAck;
// TX


typedef struct
{
    uint8_t id : 4;
    uint8_t RES : 4;
    uint16_t packetNumber;
    uint8_t data[SETTINGSDATASIZE];
    uint16_t crc;
} txSettingsData_s;

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
} channelBitData;

typedef union
{
    byteDataUnion bytesUnion;
    packetTypeId packetId;
    txSettingsData_s settingsData;
    channelBitData ch_data;
} transmitTypes;

typedef union
{
    byteDataUnion bytesUnion;
    packetTypeId packetId;
    rxSettingsDataAck settingsDataAck;
    rxData rx_data;
} receiveTypes;
#pragma endregion

#pragma pack(pop)

#define OUTPUTMODE_NONE 0   /*<! No physical output */
#define OUTPUTMODE_RC   1   /*<! RC PWM 1000 to 2000 ms */
#define OUTPUTMODE_DAC  5   /*<! Use CH7/CH8 for DAC1/DAC2 output */
#define OUTPUTMODE_IO   2   /*<! Simple HIGH/LOW with the RC timer pin */
#define OUTPUTMODE_PWM  3   /*<! PWM using one of the other timers */
#define OUTPUTMODE_STEP 4   /*<! PWM steppermode with changing frequency */

extern const char* OUTPUTMODE_STR_TABLE[];

extern transmitTypes transmitterData;
extern receiveTypes receiverData;


extern Settings settings;
extern Model* activeModel;

void initStructs();
