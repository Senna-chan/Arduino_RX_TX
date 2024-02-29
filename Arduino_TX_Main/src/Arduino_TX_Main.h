#ifndef __ARDUINO_TX_MAIN_H
#define __ARDUINO_TX_MAIN_H

#include <Arduino.h>

// Config
#include "config.h"

#include "SharedVars.h"

extern uint16_t rawChannels[RC_MAX_CHANNELS];       // Raw ADC Channels
extern uint16_t parsedChannels[RC_MAX_CHANNELS];    // Parsed ADC Channels
extern uint16_t AUXRXChannels[RC_MAX_CHANNELS];     // AUX Serial channels
extern uint16_t mappedChannels[RC_MAX_CHANNELS];    // Final RC values
extern uint32_t IOExpanderBits;

#endif
