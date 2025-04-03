#ifndef _I2C_HELPERS_H
#define _I2C_HELPERS_H

#include "main.h"
#include "i2c.h"

bool I2CDeviceConnected(I2C_HandleTypeDef *i2c, uint8_t address);
void scanI2C(I2C_HandleTypeDef *i2c);

#endif