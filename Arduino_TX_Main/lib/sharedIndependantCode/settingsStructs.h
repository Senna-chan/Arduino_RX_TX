#ifndef _SETTINGS_STRUCTS_H
#define _SETTINGS_STRUCTS_H

#include <stdint.h>

#include "sharedVars.h"

#define CTYPE_NONE          0
#define CTYPE_ADC           1
#define CTYPE_IO            2
#define CTYPE_AUX_IO        3
#define CTYPE_AUX_SERIAL    4

#define LIMIT_UPONLY        1
#define LIMIT_DOWNONLY     -1
#define LIMIT_UPANDDOWN     0

const char *const channel_types_str[] =
    {
        "NONE",
        "ADC",
        "IO",
        "AUX_IO",
        "AUX_RX"};

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
    uint16_t min;
    uint16_t mid;
    uint16_t max;
} s_calibrationConfig;

typedef struct
{
    s_calibrationConfig adcConfig;      // ADC Config/ Min/mid/max config
    int16_t trim;                       // Offset off the channel
    uint16_t failsafe;                  // Value when controller fails to connect
    uint16_t startupVal;                // Value when all are this transmission is allowed
    uint8_t outputMode;                 // Output modes for channels
    uint8_t centeredStick;              // Used with combi input for mapping. If true then we will map Mid to ends as both
    s_calibrationConfig endPoints;      // Endpoint config, AKA changing mapping from 1000-2000 to anything in between
    s_pwmConfig pwmConfig;              // PWM output Config
    s_stepperConfig stepperConfig;      // Stepper output Config
    s_channelMapping channelMapping[2]; // Channel mapping for min/mid/max or min/max or any other combo
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
    s_channelMapping inputIO;
    uint32_t outputsToEnable;
} outputEnableStruct;

typedef struct
{
    s_channelMapping input[2]; // Two needed since we can have two IO ports for low, mid and high
    union
    {
        uint16_t b[3];// 3, for low speed, mid speed and high speed
        s_calibrationConfig s;
        /* data */
    } outputValuesMax;
    uint8_t outputToRateLimit;
    int8_t limitSide;   // If 0 then both, if -1 then only min to mid, if 1 then only mid to max.
} rateLimitConfigStruct;

typedef struct
{
    uint8_t nameSize;
    char name[20]; // Alocate in this to prevent it being a pointer and messing with bytepointer transfers
    channelConfigs channel_settings[RC_MAX_CHANNELS];
    uint16_t deadzone;        // Deadzone is +/- from either center or from minPostion and maxPosition
    uint32_t channelReversed; // Bitmap of all the channels in 4 bytes to save room in the EEPROM
    channelMixStruct channelMixing[8];
    encoderStruct encoderSettings[2];
    outputEnableStruct outputEnable;
    rateLimitConfigStruct rateLimitConfig;
} Model;

typedef struct
{
    uint16_t version;
    uint8_t activeModel;
    Model model[8];
} Settings;

extern Settings settings;
extern Model* activeModel;

#endif
