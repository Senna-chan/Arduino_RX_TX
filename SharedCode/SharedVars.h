#pragma once
#include <RF24.h>

#include "Structs.h"

byte address[][5] = { 0xCC,0xCE,0xCC,0xCE,0xCC , 0xCE,0xCC,0xCE,0xCC,0xCE };
#define RF24PA RF24_PA_HIGH
#define RF24BR RF24_1MBPS

#define RC_OUTPUT_DAC 4
#define RC_OUTPUT_PWM 2
#define RC_OUTPUT_HTL 1
#define RC_OUTPUT_LTH 0

#define DEBUG 1


extern Settings settings;
extern Model activeSettings;

#define SETTINGSVERSION 12
#define EEPROMFULLWIPE false