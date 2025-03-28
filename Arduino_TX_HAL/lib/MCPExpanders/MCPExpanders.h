// MCP23X17.h

#ifndef _MCP23X17_h
#define _MCP23X17_h

#include <FreeRTOS.h>
#include <task.h>
#include <cmsis_os.h>

#include <MCP23017.h>

extern MCP23017 IOExpander1, IOExpander2, calButtonExpender;

void enableExpender(MCP23017* expender, uint8_t address);
void setupMCPChips();

#endif