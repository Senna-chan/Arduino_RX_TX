// MCP23X17.h

#ifndef _MCP23X17_h
#define _MCP23X17_h

#if defined(ARDUINO)
	#include <Arduino.h>
	#include "STMRTOSIncludes.h"
#endif

#include <Adafruit_MCP23X17.h>

extern TaskHandle_t cal_taskHandle;				// Task for handling calibration buttons(Super high prio but only run when needed, Gets data via queue)
extern TaskHandle_t io_taskHandle;					// Task for handling IO expanders

extern Adafruit_MCP23X17 IOExpander1, IOExpander2, calButtonExpender;

void enableExpender(Adafruit_MCP23X17* expender, uint8_t address);
void setupMCPChips();

#endif