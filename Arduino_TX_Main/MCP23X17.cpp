// 
// 
// 

#include "MCP23X17.h"
#include "Structs.h"

#include "config.h"
#include <MyHelpers.h>
#include <Wire.h>

TaskHandle_t cal_taskHandle;				// Task for handling calibration buttons(Super high prio but only run when needed, Gets data via queue)
TaskHandle_t io_taskHandle;					// Task for handling IO expanders

Adafruit_MCP23017 IOExpander1, IOExpander2, calButtonExpender;

static void setCalibrateIRQFlag()
{
	vTaskNotifyGiveFromISR(cal_taskHandle, NULL);
}

static void setIOExpanderIRQFlas() {
	vTaskNotifyGiveFromISR(io_taskHandle, NULL);
}

void enableExpender(Adafruit_MCP23017* expender, uint8_t address) 
{
	while (!I2CDeviceConnected(&Wire, 0x20 + address)) {
		Serial.printf("EXPANDER(0x%02X) not found\r\n", 0x20 + address);
		digitalWrite(LED_BUILTIN, LOW);
		delay(500);
		digitalWrite(LED_BUILTIN, HIGH);
		delay(500);
	}

	expender->begin(address, &Wire);
	expender->writeRegister(MCP23017_IODIRA, 0xFF);   // IO TO INPUT.writeRegister(MCP23017_IODIRA, 0xFF);   // IO TO INPUT
	expender->writeRegister(MCP23017_IODIRB, 0xFF);
	expender->writeRegister(MCP23017_GPPUA, 0xFF);	// ENABLE PULLUP.writeRegister(MCP23017_GPPUA, 0xFF);	// ENABLE PULLUP
	expender->writeRegister(MCP23017_GPPUB, 0xFF);
	expender->writeRegister(MCP23017_IPOLA, 0xFF);  // ENABLE REVERSING OF IO. DOES THIS FIX A BUG?
	expender->writeRegister(MCP23017_IPOLB, 0xFF);
	expender->setupInterrupts(true, true, LOW);
	expender->writeRegister(MCP23017_GPINTENA, 0xFF);  // Enable IRQ
	expender->writeRegister(MCP23017_GPINTENB, 0xFF);
}

void setupMCPChips() 
{
	pinMode(CALEXPENDER_INT_PIN, INPUT_PULLUP);				// Expender Interupt pin
	pinMode(IOEXPENDER_INT_PIN, INPUT_PULLUP);				// IO twoway/oneway IRQ pin

	Serial.printf("Twoway %s OneWay %s Calc %s\n", I2CDeviceConnected(&Wire, 0x20 + IOEXPANDER1_ADDR) ? "found" : "not found", I2CDeviceConnected(&Wire, 0x20 + IOEXPANDER2_ADDR) ? "found" : "not found", I2CDeviceConnected(&Wire, 0x20 + CALEXPENDER_ADDR) ? "found" : "not found");
	enableExpender(&IOExpander1, IOEXPANDER1_ADDR);
	//enableExpender(&IOExpander2, IOEXPANDER2_ADDR);
	IOExpander2.begin(IOEXPANDER2_ADDR, &Wire);
	enableExpender(&calButtonExpender, CALEXPENDER_ADDR);

	calButtonExpender.readGPIOAB(); // Clearing any interrupts that may be active

	attachInterrupt(CALEXPENDER_INT_PIN, setCalibrateIRQFlag, FALLING);
	attachInterrupt(IOEXPENDER_INT_PIN, setIOExpanderIRQFlas, FALLING);
}