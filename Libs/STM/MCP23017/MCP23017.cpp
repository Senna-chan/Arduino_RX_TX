#include "MCP23017.h"
#include "ArduMath.hpp"
/**
 * Bit number associated to a give Pin
 */
uint8_t MCP23017::bitForPin(uint8_t pin) { return pin % 8; }

/**
 * Register address, port dependent, for a given PIN
 */
uint8_t MCP23017::regForPin(uint8_t pin, uint8_t portAaddr,
                                     uint8_t portBaddr) {
  return (pin < 8) ? portAaddr : portBaddr;
}

/**
 * Reads a given register of 8 bits
 */
uint8_t MCP23017::readRegister(uint8_t addr) {
  uint8_t data = 0;
  auto hal_status = HAL_I2C_Mem_Read(_hi2c, _i2caddress << 1, addr, 1, &data, 1, 0xFF);
  if(hal_status != HAL_OK) Error_Handler();
  return data;
}

void MCP23017::writeRegister(uint8_t regAddr, uint8_t regValue) {
  auto hal_status = HAL_I2C_Mem_Write(_hi2c, _i2caddress << 1, regAddr, 1, &regValue, 1, 0xFF);
  if(hal_status != HAL_OK) Error_Handler();
}

void MCP23017::updateRegister(uint8_t regAddr, uint8_t regValue) {
  uint8_t value = readRegister(regAddr);
  value &= regValue;
  writeRegister(regAddr, value);
}


uint16_t MCP23017::readRegister16(uint8_t addr) {
  uint8_t data[2] = {0};
  auto hal_status = HAL_I2C_Mem_Read(_hi2c, _i2caddress << 1, addr, 1, data, 2, 0xFF);
  if(hal_status != HAL_OK) Error_Handler();
  return data[1] << 8 | data[0];
}

void MCP23017::writeRegister16(uint8_t regAddr, uint16_t regValue) {

  uint8_t data[2] = {regValue & 0xFF, regValue >> 8};
  auto hal_status = HAL_I2C_Mem_Write(_hi2c, _i2caddress << 1, regAddr, 1, data, 2, 0xFF);
  if(hal_status != HAL_OK) Error_Handler();
}

void MCP23017::updateRegister16(uint8_t regAddr, uint16_t regValue) {
  uint16_t value = readRegister16(regAddr);
  value &= regValue;
  writeRegister16(regAddr, value);
}


/**
 * Helper to update a single bit of an A/B register.
 * - Reads the current register value
 * - Writes the new register value
 */
void MCP23017::updateRegisterBit(uint8_t pin, uint8_t pValue,
                                          uint8_t portAaddr,
                                          uint8_t portBaddr) {
  uint8_t regValue;
  uint8_t regAddr = regForPin(pin, portAaddr, portBaddr);
  uint8_t bit = bitForPin(pin);
  regValue = readRegister(regAddr);

  // set the value for the particular bit
  bitWrite(regValue, bit, pValue);

  writeRegister(regAddr, regValue);
}

////////////////////////////////////////////////////////////////////////////////

void MCP23017::begin(I2C_HandleTypeDef *hi2c, uint16_t address) {
  if (address > 7) {
    address = 7;
  }
  _i2caddress |= address;
  _hi2c = hi2c;
}

void MCP23017::bulkPinMode(uint32_t pins, uint32_t mode, uint32_t pullup, bool invertSignal, bool interrupt, uint32_t interruptMode)
{
  updateRegister16(MCP23017_IODIRA, mode == GPIO_MODE_INPUT ? pins : ~pins);
  updateRegister16(MCP23017_GPPUA, pullup == GPIO_PULLUP ? pins : ~pins);
  updateRegister16(MCP23017_IPOLA, invertSignal ? pins : ~pins);
  updateRegister16(MCP23017_GPINTENA, interrupt ? pins : ~pins);
  if(!interrupt) return;
  if(interruptMode == GPIO_MODE_IT_RISING_FALLING) {
    updateRegister16(MCP23017_INTCONA, ~pins);
  } else {
    updateRegister16(MCP23017_INTCONA, pins);
    updateRegister16(MCP23017_DEFVALA, interruptMode == GPIO_MODE_IT_FALLING ? pins : ~pins);
  }
}


void MCP23017::pinMode(uint8_t p, uint8_t d) {
  updateRegisterBit(p, (d == GPIO_MODE_INPUT), MCP23017_IODIRA, MCP23017_IODIRB);
}

/*!
 * @brief Writes to a pin on the MCP23017
 * @param pin Pin to write to
 * @param d What to write to the pin
 */
void MCP23017::digitalWrite(uint8_t pin, uint8_t d) {
  uint8_t gpio;
  uint8_t bit = bitForPin(pin);

  // read the current GPIO output latches
  uint8_t regAddr = regForPin(pin, MCP23017_OLATA, MCP23017_OLATB);
  gpio = readRegister(regAddr);

  // set the pin and direction
  bitWrite(gpio, bit, d);

  // write the new GPIO
  regAddr = regForPin(pin, MCP23017_GPIOA, MCP23017_GPIOB);
  writeRegister(regAddr, gpio);
}

/*!
 * @brief Enables the pull-up resistor on the specified pin
 * @param p Pin to set
 * @param d Value to set the pin
 */
void MCP23017::pullUp(uint8_t p, uint8_t d) {
  updateRegisterBit(p, d, MCP23017_GPPUA, MCP23017_GPPUB);
}

/*!
 * @brief Reads the specified pin
 * @param pin Pin to read
 * @return Value of the pin
 */
uint8_t MCP23017::digitalRead(uint8_t pin) {
  uint8_t bit = bitForPin(pin);
  uint8_t regAddr = regForPin(pin, MCP23017_GPIOA, MCP23017_GPIOB);
  return (readRegister(regAddr) >> bit) & 0x1;
}

/**
 * Configures the interrupt system. both port A and B are assigned the same
 * configuration.
 * @param mirroring Mirroring will OR both INTA and INTB pins.
 * @param openDrain Opendrain will set the INT pin to value or open drain.
 * @param polarity polarity will set LOW or HIGH on interrupt.
 * Default values after Power On Reset are: (false, false, LOW)
 * If you are connecting the INTA/B pin to arduino 2/3, you should configure the
 * interupt handling as FALLING with the default configuration.
 */
void MCP23017::setupInterrupts(uint8_t mirroring, uint8_t openDrain,
                                        uint8_t polarity) {
  // configure the port A
  uint8_t ioconfValue = readRegister(MCP23017_IOCONA);
  bitWrite(ioconfValue, 6, mirroring);
  bitWrite(ioconfValue, 2, openDrain);
  bitWrite(ioconfValue, 1, polarity);
  writeRegister(MCP23017_IOCONA, ioconfValue);

  // Configure the port B
  ioconfValue = readRegister(MCP23017_IOCONB);
  bitWrite(ioconfValue, 6, mirroring);
  bitWrite(ioconfValue, 2, openDrain);
  bitWrite(ioconfValue, 1, polarity);
  writeRegister(MCP23017_IOCONB, ioconfValue);
}

/**
 * Set's up a pin for interrupt. uses arduino MODEs: GPIO_MODE_IT_RISING_FALLING, GPIO_MODE_IT_FALLING, GPIO_MODE_IT_RISING.
 *
 * Note that the interrupt condition finishes when you read the information
 * about the port / value that caused the interrupt or you read the port itself.
 * Check the datasheet can be confusing.
 * @param pin Pin to set
 * @param mode Mode to set the pin
 *
 */
void MCP23017::setupInterruptPin(uint8_t pin, uint8_t mode) {

  // set the pin interrupt control (0 means change, 1 means compare against
  // given value);
  updateRegisterBit(pin, (mode != GPIO_MODE_IT_RISING_FALLING), MCP23017_INTCONA, MCP23017_INTCONB);
  // if the mode is not CHANGE, we need to set up a default value, different
  // value triggers interrupt

  // In a RISING interrupt the default value is 0, interrupt is triggered when
  // the pin goes to 1. In a FALLING interrupt the default value is 1, interrupt
  // is triggered when pin goes to 0.
  updateRegisterBit(pin, (mode == GPIO_MODE_IT_FALLING), MCP23017_DEFVALA, MCP23017_DEFVALB);

  // enable the pin for interrupt
  updateRegisterBit(pin, GPIO_PIN_SET, MCP23017_GPINTENA, MCP23017_GPINTENB);
}

/**
 * Disable a pin for interrupt.
 *
 * @param pin Pin to set
 *
 */
void MCP23017::disableInterruptPin(uint8_t pin) {
  // disable the pin for interrupt
  updateRegisterBit(pin, 0, MCP23017_GPINTENA, MCP23017_GPINTENB);
}

/*!
 * @brief Gets the last interrupt pin
 * @return Returns the last interrupt pin
 */
uint8_t MCP23017::getLastInterruptPin() {
  uint8_t intf;

  // try port A
  intf = readRegister(MCP23017_INTFA);
  for (int i = 0; i < 8; i++)
    if (bitRead(intf, i))
      return i;

  // try port B
  intf = readRegister(MCP23017_INTFB);
  for (int i = 0; i < 8; i++)
    if (bitRead(intf, i))
      return i + 8;

  return MCP23017_INT_ERR;
}
/*!
 * @brief Gets the value of the last interrupt pin
 * @return Returns the value of the last interrupt pin
 */
uint8_t MCP23017::getLastInterruptPinValue() {
  uint8_t intPin = getLastInterruptPin();
  if (intPin != MCP23017_INT_ERR) {
    uint8_t intcapreg = regForPin(intPin, MCP23017_INTCAPA, MCP23017_INTCAPB);
    uint8_t bit = bitForPin(intPin);
    return (readRegister(intcapreg) >> bit) & (0x01);
  }

  return MCP23017_INT_ERR;
}
