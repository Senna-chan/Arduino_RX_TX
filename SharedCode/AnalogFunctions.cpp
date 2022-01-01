#include "AnalogFunctions.h"

void AnalogFunctions::init()
{
	for (int i = 0; i < CHANNELNUMBERS; i++) // Setup channel(analog) pins
	{
		pinMode(chPins[i], INPUT_ANALOG);
	}
}

void MX_DMA_Init(void)
{
	__HAL_RCC_DMA2_CLK_ENABLE();
	HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 1, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
}

void AnalogFunctions::initADC()
{
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)dmaBuffer, 15);
}

extern "C" void ADC_IRQHandler(void)
{
	HAL_ADC_IRQHandler(&hadc1);
}

extern "C" void DMA2_Stream0_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&hdma_adc1);
}

void AnalogFunctions::printChangedChannels()
{
	bool changedValue = false;
	for (int i = 0; i < CHANNELNUMBERS; i++)
	{
		if (oldChannelData[i] != channelData[i]) {
			if (abs(oldChannelData[i] - channelData[i]) < 20) continue; // Small deadzone
			if (!changedValue) {
				changedValue = true;
				Serial.print("Changed values: ");
			}
			Serial.printf("CH%02d O%04d N%04d ",i, oldChannelData[i], channelData[i]);
		}
	}
	if (changedValue) Serial.println();
}

