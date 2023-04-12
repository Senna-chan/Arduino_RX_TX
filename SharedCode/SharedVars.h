#pragma once


#define RC_OUTPUT_DAC 4
#define RC_OUTPUT_PWM 2
#define RC_OUTPUT_HTL 1
#define RC_OUTPUT_LTH 0

#define DEBUG 1

#define SETTINGSDATASIZE 27
#define RFPACKETLENGTH 32

#define RC_MAX_CHANNELS 24

extern uint32_t IOExpanderBits;
extern uint32_t prevIOExpanderBits;
extern uint16_t rawChannels[RC_MAX_CHANNELS];
