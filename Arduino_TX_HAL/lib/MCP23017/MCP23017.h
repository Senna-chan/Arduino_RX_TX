#ifndef _MCP23017_H
#define _MCP23017_H

#include "main.h"

class MCP23017{
public:
    enum registers{
        MCP_IODIRA		= 0x00,
        MCP_IODIRB		= 0x01,
        MCP_IPOLA		= 0x02,
        MCP_IPOLB		= 0x03,
        MCP_GPINTENA	= 0x04,
        MCP_GPINTENB	= 0x05,
        MCP_DEFVALA	    = 0x06,
        MCP_DEFVALB	    = 0x07,
        MCP_INTCONA	    = 0x08,
        MCP_INTCONB	    = 0x09,
        MCP_IOCONA	    = 0x0A,
        MCP_IOCONB	    = 0x0B,
        MCP_GPPUA		= 0x0C,
        MCP_GPPUB		= 0x0D,
        MCP_INTFA		= 0x0E,
        MCP_INTFB		= 0x0F,
        MCP_INTCAPA	    = 0x10,
        MCP_INTCAPB	    = 0x11,
        MCP_GPIOA		= 0x12,
        MCP_GPIOB		= 0x13,
        MCP_OLATA		= 0x14,
        MCP_OLATB		= 0x15,
    };
    void begin(I2C_HandleTypeDef *hi2c, uint16_t address);
    void pinMode(uint8_t p, uint8_t d);
    void digitalWrite(uint8_t p, uint8_t d);
    void pullUp(uint8_t p, uint8_t d);
    uint8_t digitalRead(uint8_t p);

    void writeGPIOAB(uint16_t);
    uint16_t readGPIOAB();
    uint8_t readGPIO(uint8_t b);

    void setupInterrupts(uint8_t mirroring, uint8_t open, uint8_t polarity);
    void setupInterruptPin(uint8_t pin, uint8_t mode);
    void disableInterruptPin(uint8_t pin);
    uint8_t getLastInterruptPin();
    uint8_t getLastInterruptPinValue();
private:
    uint8_t bitForPin(uint8_t pin);
    uint8_t regForPin(uint8_t pin, uint8_t portAaddr, uint8_t portBaddr);

    uint8_t readRegister(uint8_t addr);
    void writeRegister(uint8_t addr, uint8_t value);
    /**
     * Utility private method to update a register associated with a pin (whether
     * port A/B) reads its value, updates the particular bit, and writes its
     * value.
     */
    void updateRegisterBit(uint8_t p, uint8_t pValue, uint8_t portAaddr,
    uint8_t portBaddr);
    I2C_HandleTypeDef _hi2c;
    uint8_t address;

};

#endif