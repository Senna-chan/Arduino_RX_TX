// 
// 
// 

#include "MCPExpanders.h"

#include "Config.h"

#include <stdio.h>

#include "main.h"
#include "i2c.h"
#include "I2CHelpers.h"


MCP23017 IOExpander1, IOExpander2, calButtonExpender;

// static void setCalibrateIRQFlag()
// {
// 	vTaskNotifyGiveFromISR(cal_taskHandle, NULL);
// }

// static void setIOExpanderIRQFlas() {
// 	vTaskNotifyGiveFromISR(io_taskHandle, NULL);
// }

void enableExpender(MCP23017* expender, uint8_t address)
{
	uint8_t fullAddress = 0x20 + address;
	while (!I2CDeviceConnected(&hi2c2, fullAddress)) {
		printf("EXPANDER(0x%02X) not found\r\n", fullAddress);
		HAL_Delay(500);
		// digitalWrite(LED_BUILTIN, LOW);
		// delay(500);
		// digitalWrite(LED_BUILTIN, HIGH);
		// delay(500);
	}

	expender->begin(&hi2c2, address);
	expender->writeRegister16(MCP23017::MCP23017_IODIRA, 0xFFFF); // Set all as input
	expender->writeRegister16(MCP23017::MCP23017_GPPUA, 0xFFFF);  // Enable pullup registers
	expender->writeRegister16(MCP23017::MCP23017_IPOLA, 0xFFFF);  // Reverse the logic level(LOW is read as HIGH)
	expender->writeRegister16(MCP23017::MCP23017_GPINTENA, 0xFFFF);  // Enable IRQ
	expender->writeRegister16(MCP23017::MCP23017_INTCONA, 0x0000);  // Enable IRQ
	expender->setupInterrupts(true, true, GPIO_PIN_SET);

}

void setupMCPChips() 
{
	printf("Expander1 %s Expander2 %s Calc %s\n", I2CDeviceConnected(&hi2c2, 0x20 + IOEXPANDER1_ADDR) ? "found" : "not found", I2CDeviceConnected(&hi2c2, 0x20 + IOEXPANDER2_ADDR) ? "found" : "not found", I2CDeviceConnected(&hi2c2, 0x20 + CALEXPENDER_ADDR) ? "found" : "not found");
	enableExpender(&IOExpander1, IOEXPANDER1_ADDR);
	enableExpender(&IOExpander2, IOEXPANDER2_ADDR);
	enableExpender(&calButtonExpender, CALEXPENDER_ADDR);

	calButtonExpender.readGPIOAB(); // Clearing any interrupts that may be active
}