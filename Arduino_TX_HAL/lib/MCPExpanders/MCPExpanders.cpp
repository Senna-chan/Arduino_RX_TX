// 
// 
// 

#include "MCPExpanders.h"

#include "main.h"
#include "i2c.h"

TaskHandle_t cal_taskHandle;				// Task for handling calibration buttons(Super high prio but only run when needed, Gets data via queue)
TaskHandle_t io_taskHandle;					// Task for handling IO expanders

MCP23017 IOExpander1, IOExpander2, calButtonExpender;

static void setCalibrateIRQFlag()
{
	vTaskNotifyGiveFromISR(cal_taskHandle, NULL);
}

static void setIOExpanderIRQFlas() {
	vTaskNotifyGiveFromISR(io_taskHandle, NULL);
}

void enableExpender(MCP23017* expender, uint8_t address)
{
	while (!I2CDeviceConnected(&Wire, 0x20 + address)) {
		Serial.printf("EXPANDER(0x%02X) not found\r\n", 0x20 + address);
		digitalWrite(LED_BUILTIN, LOW);
		delay(500);
		digitalWrite(LED_BUILTIN, HIGH);
		delay(500);
	}

	expender->begin(&hi2c2, address);
	expender->writeRegister16(MCP23017::MCP23017_GPIOA, 0xFFFF);
	expender->writeRegister16(MCP23017::MCP23017_GPPUA, 0xFFFF); 
	expender->writeRegister16(MCP23017::MCP23017_IPOLA, 0xFFFF);
	expender->setupInterrupts(true, true, GPIO_PIN_RESET);
	expender->writeRegister16(MCP23017::MCP23017_GPINTENA, 0xFFFF);  // Enable IRQ
}

void setupMCPChips() 
{

	Serial.printf("Twoway %s OneWay %s Calc %s\n", I2CDeviceConnected(&Wire, 0x20 + IOEXPANDER1_ADDR) ? "found" : "not found", I2CDeviceConnected(&Wire, 0x20 + IOEXPANDER2_ADDR) ? "found" : "not found", I2CDeviceConnected(&Wire, 0x20 + CALEXPENDER_ADDR) ? "found" : "not found");
	enableExpender(&IOExpander1, IOEXPANDER1_ADDR);
	enableExpender(&IOExpander2, IOEXPANDER2_ADDR);
	enableExpender(&calButtonExpender, CALEXPENDER_ADDR);

	calButtonExpender.readRegister16(MCP23017::MCP23017_GPIOA); // Clearing any interrupts that may be active
}