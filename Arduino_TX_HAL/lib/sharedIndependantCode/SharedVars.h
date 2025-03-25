#ifndef _SHARED_VARS_H
#define _SHARED_VARS_H

#include <stdbool.h>

#define RC_OUTPUT_DAC 4
#define RC_OUTPUT_PWM 2
#define RC_OUTPUT_HTL 1
#define RC_OUTPUT_LTH 0

#define DEBUG 1

#define SETTINGSDATASIZE 27
#define RFPACKETLENGTH 32

#define RC_MAX_CHANNELS     20

extern uint32_t IOExpanderBits;
extern uint32_t prevIOExpanderBits;
extern uint16_t rawChannels[RC_MAX_CHANNELS];

extern bool eepromFound;

#endif
