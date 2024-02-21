#ifndef __ARDUINO_TX_MAIN_H
#define __ARDUINO_TX_MAIN_H

#include <Arduino.h>

// Config
#include "config.h"

#include "SharedVars.h"

extern uint16_t rawChannels[RC_MAX_CHANNELS];
extern uint16_t AUXRXChannels[RC_MAX_CHANNELS];   // AUX Serial channels temp capture
extern uint16_t mappedChannels[RC_MAX_CHANNELS];    // Final RC values
extern uint32_t IOExpanderBits;

#endif
