#ifndef _MCP23017_H
#define _MCP23017_H

#include "main.h"

class MCP23017{
public:
    enum registers{
        MCP23017_IODIRA		= 0x00,
        MCP23017_IODIRB		= 0x01,
        MCP23017_IPOLA		= 0x02,
        MCP23017_IPOLB		= 0x03,
        MCP23017_GPINTENA	= 0x04,
        MCP23017_GPINTENB	= 0x05,
        MCP23017_DEFVALA    = 0x06,
        MCP23017_DEFVALB    = 0x07,
        MCP23017_INTCONA    = 0x08,
        MCP23017_INTCONB    = 0x09,
        MCP23017_IOCONA	    = 0x0A,
        MCP23017_IOCONB	    = 0x0B,
        MCP23017_GPPUA		= 0x0C,
        MCP23017_GPPUB		= 0x0D,
        MCP23017_INTFA		= 0x0E,
        MCP23017_INTFB		= 0x0F,
        MCP23017_INTCAPA    = 0x10,
        MCP23017_INTCAPB    = 0x11,
        MCP23017_GPIOA		= 0x12,
        MCP23017_GPIOB		= 0x13,
        MCP23017_OLATA		= 0x14,
        MCP23017_OLATB		= 0x15,
    };
    const static int MCP23017_INT_ERR = 0xFF;

    /**
    * Initializes the MCP23017 given its HW selected address, see datasheet for
    * Address selection.
    * @param hi2c Pointer to the I2C_Handle
    * @param address Selected address bits
    */
    void begin(I2C_HandleTypeDef *hi2c, uint16_t address);

    /**
     * @brief Configure pins with all options directly
     * 
     * @param pins Pins to configure. Can be any GPIO_PIN_X combined
     * @param mode Mode, Either MODE_INPUT or MODE_OUTPUT
     * @param pullup Pullup status, either GPIO_NOPULL or GPIO_PULLUP
     * @param invertSignal Inverting of the signal, true for inverting, false for not
     * @param interrupt Interrupt enabled?
     * @param interruptMode Interrupt mode, Any of the GPIO_MODE_IT_X
     */
    void bulkPinMode(uint32_t pins, uint32_t mode, uint32_t pullup, bool invertSignal, bool interrupt, uint32_t interruptMode);
    /**
     * Sets the pin mode to either GPIO_MODE_INPUT or GPIO_MODE_OUTPUT
     * @param p Pin to set
     * @param d Mode to set the pin, Either MODE_INPUT or MODE_OUTPUT
     */
    void pinMode(uint8_t p, uint8_t d); // Arduino style
    void digitalWrite(uint8_t p, uint8_t d); // Arduino style
    void pullUp(uint8_t p, uint8_t d); 
    uint8_t digitalRead(uint8_t p); // Arduino style

    void setupInterrupts(uint8_t mirroring, uint8_t open, uint8_t polarity);
    void setupInterruptPin(uint8_t pin, uint8_t mode);
    void disableInterruptPin(uint8_t pin);
    uint8_t getLastInterruptPin();
    uint8_t getLastInterruptPinValue();

    /**
     * @brief Read a single register
     * 
     * @param addr Adress of the register
     * @return uint8_t Value of register
     */
    uint8_t readRegister(uint8_t addr);
    /**
     * @brief Write to a single adress
     * 
     * @param addr Address of register
     * @param value Value to write
     */
    void writeRegister(uint8_t addr, uint8_t value);
    /**
     * @brief Update a single adress
     * 
     * @param addr Address of register
     * @param value Value to update register with
     */
    void updateRegister(uint8_t addr, uint8_t value);
    /**
     * @brief Same as @see readRegister but with 2 bytes
     * 
     * @param addr Address of register
     * @return uint16_t value of registers
     */
    uint16_t readRegister16(uint8_t addr);
    /**
     * @brief Same as @see writeRegister but with 2 bytes
     * 
     * @param addr Address of register
     * @param value Values to write
     */
    void writeRegister16(uint8_t addr, uint16_t value);
    /**
     * @brief Same as @see updateRegister but with 2 bytes
     * 
     * @param addr Address of register
     * @param value Value to update register with
     */
    void updateRegister16(uint8_t addr, uint16_t value);

    /**
     * @brief Read all the pins at once
     * 
     * @return uint16_t Binary representation of pin state
     */
    uint16_t readGPIOAB(){return readRegister16(MCP23017_GPIOA);}

    /**
     * @brief Read only GPIOA
     * 
     * @return uint8_t Binary representation of pin state
     */
    uint8_t readGPIOA(){return readRegister(MCP23017_GPIOA);}
    /**
     * @brief Read only GPIOB
     * 
     * @return uint8_t Binary representation of pin state
     */
    uint8_t readGPIOB(){return readRegister(MCP23017_GPIOB);}
private:
    uint8_t bitForPin(uint8_t pin);
    uint8_t regForPin(uint8_t pin, uint8_t portAaddr, uint8_t portBaddr);

    /**
     * Utility private method to update a register associated with a pin (whether
     * port A/B) reads its value, updates the particular bit, and writes its
     * value.
     */
    void updateRegisterBit(uint8_t p, uint8_t pValue, uint8_t portAaddr, uint8_t portBaddr);
    I2C_HandleTypeDef *_hi2c;
    uint8_t _i2caddress = 0x20; // 0x20 is the base adress

};

#endif