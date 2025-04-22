//
//
//

#include "MCPExpanders.h"

#include "Config.h"

#include <stdio.h>

#include "I2CHelpers.h"
#include "i2c.h"
#include "main.h"

MCP23017 IOExpander1, IOExpander2, calButtonExpender;

void enableExpender(MCP23017* expender, uint8_t address)
{
    uint8_t fullAddress = 0x20 + address;
    while (!I2CDeviceConnected(&hi2c2, fullAddress)) {
        SerialPrintf("EXPANDER(0x%02X) not found\r\n", fullAddress);
        HAL_Delay(500);
        // digitalWrite(LED_BUILTIN, LOW);
        // delay(500);
        // digitalWrite(LED_BUILTIN, HIGH);
        // delay(500);
    }

    expender->begin(&hi2c2, address);
    expender->bulkPinMode(0xFFFF, MODE_INPUT, GPIO_PULLUP, true, true, address == CALEXPENDER_ADDR ? GPIO_MODE_IT_RISING : GPIO_MODE_IT_RISING_FALLING);
    expender->setupInterrupts(true, true, GPIO_PIN_RESET);
    expender->readGPIOAB(); // Clearing any interrupts that may be active
    expender->readRegister16(MCP23017::MCP23017_INTCAPA);
}

void setupMCPChips()
{
    bool io1Found =  I2CDeviceConnected(&hi2c2, 0x20 + IOEXPANDER1_ADDR);
    bool io2Found =  I2CDeviceConnected(&hi2c2, 0x20 + IOEXPANDER2_ADDR);
    bool calFound =  I2CDeviceConnected(&hi2c2, 0x20 + CALEXPENDER_ADDR);
    SerialPrintf("Expander1 %s Expander2 %s Calc %s\n", io1Found ? "found" : "not found", io2Found ? "found" : "not found", calFound ? "found" : "not found");
    enableExpender(&IOExpander1, IOEXPANDER1_ADDR);
    enableExpender(&IOExpander2, IOEXPANDER2_ADDR);
    enableExpender(&calButtonExpender, CALEXPENDER_ADDR);
}