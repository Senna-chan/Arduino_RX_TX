#pragma once
#include <RF24.h>

#include "Structs.h"


#define RC_OUTPUT_DAC 4
#define RC_OUTPUT_PWM 2
#define RC_OUTPUT_HTL 1
#define RC_OUTPUT_LTH 0

#define DEBUG 1

extern uint32_t IOExpanderBits;
extern uint32_t prevIOExpanderBits;
extern uint16_t rawChannels[24];
