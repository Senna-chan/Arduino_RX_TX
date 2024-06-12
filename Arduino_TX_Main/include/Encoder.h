// Encoder.h

#ifndef _ENCODER_h
#define _ENCODER_h

#if defined(ARDUINO)
	#include <Arduino.h>
	#include "STMRTOSIncludes.h"
#endif

#include <i2cEncoderLibV2.h>
#include <Wire.h>
#include "config.h"

extern TaskHandle_t encoder_taskHandle;			// Task for handling encoder

extern i2cEncoderLibV2 encoder;

bool setupEncoder();

void setEncoderValues(encoderStruct* values);

void processEncoder(void* parameter);

#endif


