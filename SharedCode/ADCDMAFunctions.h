// ADCDMAFunctions.h

#ifndef _ADCDMAFUNCTIONS_h
#define _ADCDMAFUNCTIONS_h

#include <Arduino.h>
#include "config.h"

ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

void ADCInit();
void ADCStart();
void ADCStop();


#endif

