//
//
//

#include "ADCDMAFunctions.h"
#include "main.h"
#include "adc.h"
#include "dma.h"

// extern "C" void ADC_IRQHandler(void)
// {
//     HAL_ADC_IRQHandler(&hadc1);
// }

void ADCStart()
{
    HAL_ADC_Start_DMA(&hadc1, (uint32_t*)ADCDMABuffer, DMABUFFERSIZE);
}

void ADCStop()
{
    HAL_ADC_Stop_DMA(&hadc1);
}
