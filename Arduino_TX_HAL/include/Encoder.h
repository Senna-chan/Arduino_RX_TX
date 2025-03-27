// Encoder.h

#ifndef _ATXH_ENCODER_H
#define _ATXH_ENCODER_H


#include <I2CEncoder.h>

#include "Arduino_TX_HAL.h"

extern TaskHandle_t encoder_taskHandle;			// Task for handling encoder

extern I2CEncoder encoder;

/**
 * @brief (re)configured encoders.
 */
void configureEncoder();
void processEncoder(void* parameter);

#endif


