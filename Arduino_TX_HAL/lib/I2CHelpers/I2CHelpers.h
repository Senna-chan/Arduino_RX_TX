#ifndef _I2CHELPERS_H
#define _I2CHELPERS_H

#include "main.h"

bool I2CDeviceConnected(I2C_HandleTypeDef *i2c, uint8_t address){
    auto hal_status = HAL_I2C_IsDeviceReady(i2c, address << 1, 3, 5);
    return hal_status == HAL_OK;
}

#endif