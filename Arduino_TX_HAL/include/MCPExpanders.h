// MCP23X17.h

#ifndef _MCP23X17_h
#define _MCP23X17_h

#if defined(ARDUINO)
	#include <Arduino.h>
	#include "STMRTOSIncludes.h"
#else
#include <FreeRTOS.h>
#include <task.h>
#include <cmsis_os.h>
#endif

#include <MCP23017.h>

extern MCP23017 IOExpander1, IOExpander2, calButtonExpender;

void enableExpender(MCP23017* expender, uint8_t address);
void setupMCPChips();

#endif