// 
// 
// 

#include <Adafruit_MCP23X17.h>
#include <MyHelpers.h>
#include <Wire.h>

#include "config.h"

#include "Structs.h"
#include "STMRTOSIncludes.h"

TaskHandle_t cal_taskHandle;				// Task for handling calibration buttons(Super high prio but only run when needed, Gets data via queue)
TaskHandle_t io_taskHandle;					// Task for handling IO expanders

Adafruit_MCP23X17 IOExpander1, IOExpander2, calButtonExpender;

static void setCalibrateIRQFlag()
{
	vTaskNotifyGiveFromISR(cal_taskHandle, NULL);
}

static void setIOExpanderIRQFlas() {
	vTaskNotifyGiveFromISR(io_taskHandle, NULL);
}

void enableExpender(Adafruit_MCP23X17* expender, uint8_t address)
{
	while (!I2CDeviceConnected(&Wire, 0x20 + address)) {
		Serial.printf("EXPANDER(0x%02X) not found\r\n", 0x20 + address);
		digitalWrite(LED_BUILTIN, LOW);
		delay(500);
		digitalWrite(LED_BUILTIN, HIGH);
		delay(500);
	}

	expender->begin_I2C(address, &Wire);
	expender->writeRegister16(MCP23XXX_GPIO, 0xFFFF);
	expender->writeRegister16(MCP23XXX_GPPU, 0xFFFF); 
	expender->writeRegister16(MCP23XXX_IPOL, 0xFFFF);
	expender->setupInterrupts(true, true, LOW);
	expender->writeRegister16(MCP23XXX_GPINTEN, 0xFFFF);  // Enable IRQ
}

void setupMCPChips() 
{
	pinMode(CALEXPENDER_INT_PIN, INPUT_PULLUP);				// Expender Interupt pin
	pinMode(IOEXPENDER_INT_PIN, INPUT_PULLUP);				// IO twoway/oneway IRQ pin

	Serial.printf("Twoway %s OneWay %s Calc %s\n", I2CDeviceConnected(&Wire, 0x20 + IOEXPANDER1_ADDR) ? "found" : "not found", I2CDeviceConnected(&Wire, 0x20 + IOEXPANDER2_ADDR) ? "found" : "not found", I2CDeviceConnected(&Wire, 0x20 + CALEXPENDER_ADDR) ? "found" : "not found");
	enableExpender(&IOExpander1, IOEXPANDER1_ADDR);
	enableExpender(&IOExpander2, IOEXPANDER2_ADDR);
	enableExpender(&calButtonExpender, CALEXPENDER_ADDR);

	calButtonExpender.readGPIOAB(); // Clearing any interrupts that may be active

	attachInterrupt(CALEXPENDER_INT_PIN, setCalibrateIRQFlag, FALLING);
	attachInterrupt(IOEXPENDER_INT_PIN, setIOExpanderIRQFlas, FALLING);
}