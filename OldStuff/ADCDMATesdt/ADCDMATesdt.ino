/*
 Name:		ADCDMATesdt.ino
 Created:	11/29/2021 9:32:23 PM
 Author:	Senna
*/





#include "stm32yyxx_ll_bus.h"
#include "stm32yyxx_ll_rcc.h"
#include "stm32yyxx_ll_system.h"
#include "stm32yyxx_ll_utils.h"
#include "stm32yyxx_ll_cortex.h"
#include "stm32yyxx_ll_gpio.h"
#include "stm32yyxx_ll_exti.h"
#include "stm32yyxx_ll_adc.h"
#include "stm32yyxx_ll_dma.h"
#include "stm32yyxx_ll_pwr.h"

#define ADC_CONVERTED_DATA_BUFFER_SIZE   ((uint32_t)   11)
/* Variables for ADC conversion data */
__IO uint16_t aADCxConvertedData[ADC_CONVERTED_DATA_BUFFER_SIZE]; /* ADC group regular conversion data */

void AdcGrpRegularOverrunError_Callback(void)
{
    /* Note: Disable ADC interruption that caused this error before entering in */
    /*       infinite loop below.                                               */

    /* Disable ADC group regular overrun interruption */
    LL_ADC_DisableIT_OVR(ADC1);

    Serial.println("OVR");
}

void AdcDmaTransferError_Callback()
{
    /* Error detected during DMA transfer */
    Serial.println("DMAERR");
}


/* Variable to report status of DMA transfer of ADC group regular conversions */
/*  0: DMA transfer is not completed                                          */
/*  1: DMA transfer is completed                                              */
/*  2: DMA transfer has not been started yet (initial state)                  */
__IO uint8_t ubDmaTransferStatus = 2; /* Variable set into DMA interruption callback */

/* Variable to report status of ADC group regular sequence conversions:       */
/*  0: ADC group regular sequence conversions are not completed               */
/*  1: ADC group regular sequence conversions are completed                   */
__IO uint8_t ubAdcGrpRegularSequenceConvStatus = 0; /* Variable set into ADC interruption callback */

/* Variable to report number of ADC group regular sequence completed          */
static uint32_t ubAdcGrpRegularSequenceConvCount = 0; /* Variable set into ADC interruption callback */

void AdcDmaTransferComplete_Callback()
{
    /* For this example purpose, check that DMA transfer status is matching     */
    /* ADC group regular sequence status:                                       */
    if (ubAdcGrpRegularSequenceConvStatus != 1)
    {
        AdcDmaTransferError_Callback();
    }

    /* Reset status variable of ADC group regular sequence */
    ubAdcGrpRegularSequenceConvStatus = 0;
}

/**
  * @brief  ADC group regular end of sequence conversions interruption callback
  * @note   This function is executed when the ADC group regular
  *         sequencer has converted all ranks of the sequence.
  * @retval None
  */
void AdcGrpRegularSequenceConvComplete_Callback()
{
    /* Update status variable of ADC group regular sequence */
    ubAdcGrpRegularSequenceConvStatus = 1;
    ubAdcGrpRegularSequenceConvCount++;
}

extern "C" void DMA2_Stream0_IRQHandler(void)
{
    /* Check whether DMA transfer complete caused the DMA interruption */
    if (LL_DMA_IsActiveFlag_TC0(DMA2) == 1)
    {
        /*  Clear Stream  transfer complete flag*/
        LL_DMA_ClearFlag_TC0(DMA2);
        /* Call interruption treatment function */
        AdcDmaTransferComplete_Callback();
    }

    /* Check whether DMA transfer error caused the DMA interruption */
    if (LL_DMA_IsActiveFlag_TE0(DMA2) == 1)
    {
        /* Clear flag DMA transfer error */
        LL_DMA_ClearFlag_TE0(DMA2);

        /* Call interruption treatment function */
        AdcDmaTransferError_Callback();
    }
}

extern "C" void ADC_IRQHandler(void)
{
    /* Check whether ADC group regular overrun caused the ADC interruption */
    if (LL_ADC_IsActiveFlag_OVR(ADC1) != 0)
    {
        /* Clear flag ADC group regular overrun */
        LL_ADC_ClearFlag_OVR(ADC1);

        /* Call interruption treatment function */
        AdcGrpRegularOverrunError_Callback();
    }
    /* Check whether ADC group regular end of sequence conversions caused       */
    /* the ADC interruption.                                                    */
    /* Note: On this STM32 serie, ADC group regular end of conversion           */
    /*       must be selected among end of unitary conversion                   */
    /*       or end of sequence conversions.                                    */
    /*       Refer to function "LL_ADC_REG_SetFlagEndOfConversion()".           */
    else /* if(LL_ADC_IsActiveFlag_EOCS(ADC1) != 0) */
    {
        /* Clear flag ADC group regular end of sequence conversions */
        LL_ADC_ClearFlag_EOCS(ADC1);

        /* Call interruption treatment function */
        AdcGrpRegularSequenceConvComplete_Callback();
    }
}


void Configure_DMA(void)
{
    /*## Configuration of NVIC #################################################*/
    /* Configure NVIC to enable DMA interruptions */
    NVIC_SetPriority(DMA2_Stream0_IRQn, 1);  /* DMA IRQ lower priority than ADC IRQ */
    NVIC_EnableIRQ(DMA2_Stream0_IRQn);

    /*## Configuration of DMA ##################################################*/
    /* Enable the peripheral clock of DMA */
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2);

    /* Configure the DMA transfer */
    /*  - DMA transfer in circular mode to match with ADC configuration:        */
    /*    DMA unlimited requests.                                               */
    /*  - DMA transfer from ADC without address increment.                      */
    /*  - DMA transfer to memory with address increment.                        */
    /*  - DMA transfer from ADC by half-word to match with ADC configuration:   */
    /*    ADC resolution 12 bits.                                               */
    /*  - DMA transfer to memory by half-word to match with ADC conversion data */
    /*    buffer variable type: half-word.                                      */
    LL_DMA_SetChannelSelection(DMA2, LL_DMA_STREAM_0, LL_DMA_CHANNEL_0);
    LL_DMA_ConfigTransfer(DMA2,
        LL_DMA_STREAM_0,
        LL_DMA_DIRECTION_PERIPH_TO_MEMORY |
        LL_DMA_MODE_CIRCULAR |
        LL_DMA_PERIPH_NOINCREMENT |
        LL_DMA_MEMORY_INCREMENT |
        LL_DMA_PDATAALIGN_HALFWORD |
        LL_DMA_MDATAALIGN_HALFWORD |
        LL_DMA_PRIORITY_HIGH);

    /* Set DMA transfer addresses of source and destination */
    LL_DMA_ConfigAddresses(DMA2,
        LL_DMA_STREAM_0,
        LL_ADC_DMA_GetRegAddr(ADC1, LL_ADC_DMA_REG_REGULAR_DATA),
        (uint32_t)&aADCxConvertedData,
        LL_DMA_DIRECTION_PERIPH_TO_MEMORY);

    /* Set DMA transfer size */
    LL_DMA_SetDataLength(DMA2,
        LL_DMA_STREAM_0,
        ADC_CONVERTED_DATA_BUFFER_SIZE);

    /* Enable DMA transfer interruption: transfer complete */
    LL_DMA_EnableIT_TC(DMA2,
        LL_DMA_STREAM_0);

    /* Enable DMA transfer interruption: transfer error */
    LL_DMA_EnableIT_TE(DMA2,
        LL_DMA_STREAM_0);

    /*## Activation of DMA #####################################################*/
    /* Enable the DMA transfer */
    LL_DMA_EnableStream(DMA2, LL_DMA_STREAM_0);
}

void enableADC() {
    if (LL_ADC_IsEnabled(ADC1) == 0)
    {
        /* Enable ADC */
        LL_ADC_Enable(ADC1);

    }
}

void configureADC() {
    __IO uint32_t wait_loop_index = 0;

    /*## Configuration of GPIO used by ADC channels ############################*/

    /* Note: On this STM32 device, ADC1 channel 4 is mapped on GPIO pin PA.04 */

    /* Enable GPIO Clock */
    //LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);

    /* Configure GPIO in analog mode to be used as ADC input */
    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_4, LL_GPIO_MODE_ANALOG);

    /*## Configuration of NVIC #################################################*/
    /* Configure NVIC to enable ADC1 interruptions */
    NVIC_SetPriority(ADC_IRQn, 0); /* ADC IRQ greater priority than DMA IRQ */
    NVIC_EnableIRQ(ADC_IRQn);

    /*## Configuration of ADC ##################################################*/

    /*## Configuration of ADC hierarchical scope: common to several ADC ########*/

    /* Enable ADC clock (core clock) */
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC1);

    /* Note: Hardware constraint (refer to description of the functions         */
    /*       below):                                                            */
    /*       On this STM32 serie, setting of these features are not             */
    /*       conditioned to ADC state.                                          */
    /*       However, in order to be compliant with other STM32 series          */
    /*       and to show the best practice usages, ADC state is checked.        */
    /*       Software can be optimized by removing some of these checks, if     */
    /*       they are not relevant considering previous settings and actions    */
    /*       in user application.                                               */
    if (__LL_ADC_IS_ENABLED_ALL_COMMON_INSTANCE() == 0)
    {
        /* Note: Call of the functions below are commented because they are       */
        /*       useless in this example:                                         */
        /*       setting corresponding to default configuration from reset state. */

        /* Set ADC clock (conversion clock) common to several ADC instances */
        LL_ADC_SetCommonClock(__LL_ADC_COMMON_INSTANCE(ADC1), LL_ADC_CLOCK_SYNC_PCLK_DIV2);

    }


    /*## Configuration of ADC hierarchical scope: ADC instance #################*/

    /* Note: Hardware constraint (refer to description of the functions         */
    /*       below):                                                            */
    /*       On this STM32 serie, setting of these features are not             */
    /*       conditioned to ADC state.                                          */
    /*       However, ADC state is checked anyway with standard requirements    */
    /*       (refer to description of this function).                           */
    if (LL_ADC_IsEnabled(ADC1) == 0)
    {
        /* Note: Call of the functions below are commented because they are       */
        /*       useless in this example:                                         */
        /*       setting corresponding to default configuration from reset state. */

        /* Set ADC data resolution */
         LL_ADC_SetResolution(ADC1, LL_ADC_RESOLUTION_10B);

        /* Set ADC conversion data alignment */
        // LL_ADC_SetResolution(ADC1, LL_ADC_DATA_ALIGN_RIGHT);

        /* Set Set ADC sequencers scan mode, for all ADC groups                   */
        /* (group regular, group injected).                                       */
        LL_ADC_SetSequencersScanMode(ADC1, LL_ADC_SEQ_SCAN_ENABLE);

    }


    /*## Configuration of ADC hierarchical scope: ADC group regular ############*/

    /* Note: Hardware constraint (refer to description of the functions         */
    /*       below):                                                            */
    /*       On this STM32 serie, setting of these features are not             */
    /*       conditioned to ADC state.                                          */
    /*       However, ADC state is checked anyway with standard requirements    */
    /*       (refer to description of this function).                           */
    if (LL_ADC_IsEnabled(ADC1) == 0)
    {
        /* Set ADC group regular trigger source */
        LL_ADC_REG_SetTriggerSource(ADC1, LL_ADC_REG_TRIG_SOFTWARE);

        /* Set ADC group regular trigger polarity */
        // LL_ADC_REG_SetTriggerEdge(ADC1, LL_ADC_REG_TRIG_EXT_RISING);

        /* Set ADC group regular continuous mode */
        LL_ADC_REG_SetContinuousMode(ADC1, LL_ADC_REG_CONV_SINGLE);

        /* Set ADC group regular conversion data transfer */
        LL_ADC_REG_SetDMATransfer(ADC1, LL_ADC_REG_DMA_TRANSFER_UNLIMITED);

        /* Specify which ADC flag between EOC (end of unitary conversion)         */
        /* or EOS (end of sequence conversions) is used to indicate               */
        /* the end of conversion.                                                 */
        // LL_ADC_REG_SetFlagEndOfConversion(ADC1, LL_ADC_REG_FLAG_EOC_SEQUENCE_CONV);

        /* Set ADC group regular sequencer */
        /* Note: On this STM32 serie, ADC group regular sequencer is              */
        /*       fully configurable: sequencer length and each rank               */
        /*       affectation to a channel are configurable.                       */
        /*       Refer to description of function                                 */
        /*       "LL_ADC_REG_SetSequencerLength()".                               */

        /* Set ADC group regular sequencer length and scan direction */
        LL_ADC_REG_SetSequencerLength(ADC1, LL_ADC_REG_SEQ_SCAN_ENABLE_11RANKS);

        /* Set ADC group regular sequencer discontinuous mode */
        // LL_ADC_REG_SetSequencerDiscont(ADC1, LL_ADC_REG_SEQ_DISCONT_DISABLE);

        /* Set ADC group regular sequence: channel on the selected sequence rank. */
        LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1,  LL_ADC_CHANNEL_1);
        LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_2,  LL_ADC_CHANNEL_2);
        LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_3,  LL_ADC_CHANNEL_3);
        LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_4,  LL_ADC_CHANNEL_8);
        LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_5,  LL_ADC_CHANNEL_9);
        LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_6,  LL_ADC_CHANNEL_10);
        LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_7,  LL_ADC_CHANNEL_11);
        LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_8,  LL_ADC_CHANNEL_12);
        LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_9,  LL_ADC_CHANNEL_13);
        LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_10, LL_ADC_CHANNEL_14);
        LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_11, LL_ADC_CHANNEL_15);
    }


    /*## Configuration of ADC hierarchical scope: ADC group injected ###########*/

    /* Note: Hardware constraint (refer to description of the functions         */
    /*       below):                                                            */
    /*       On this STM32 serie, setting of these features are not             */
    /*       conditioned to ADC state.                                          */
    /*       However, ADC state is checked anyway with standard requirements    */
    /*       (refer to description of this function).                           */
    if (LL_ADC_IsEnabled(ADC1) == 0)
    {
        /* Note: Call of the functions below are commented because they are       */
        /*       useless in this example:                                         */
        /*       setting corresponding to default configuration from reset state. */

        /* Set ADC group injected trigger source */
        // LL_ADC_INJ_SetTriggerSource(ADC1, LL_ADC_INJ_TRIG_SOFTWARE);

        /* Set ADC group injected trigger polarity */
        // LL_ADC_INJ_SetTriggerEdge(ADC1, LL_ADC_INJ_TRIG_EXT_RISING);

        /* Set ADC group injected conversion trigger  */
        // LL_ADC_INJ_SetTrigAuto(ADC1, LL_ADC_INJ_TRIG_INDEPENDENT);

        /* Set ADC group injected sequencer */
        /* Note: On this STM32 serie, ADC group injected sequencer is             */
        /*       fully configurable: sequencer length and each rank               */
        /*       affectation to a channel are configurable.                       */
        /*       Refer to description of function                                 */
        /*       "LL_ADC_INJ_SetSequencerLength()".                               */

        /* Set ADC group injected sequencer length and scan direction */
        // LL_ADC_INJ_SetSequencerLength(ADC1, LL_ADC_INJ_SEQ_SCAN_DISABLE);

        /* Set ADC group injected sequencer discontinuous mode */
        // LL_ADC_INJ_SetSequencerDiscont(ADC1, LL_ADC_INJ_SEQ_DISCONT_DISABLE);

        /* Set ADC group injected sequence: channel on the selected sequence rank. */
        // LL_ADC_INJ_SetSequencerRanks(ADC1, LL_ADC_INJ_RANK_1, LL_ADC_CHANNEL_4);
    }


    /*## Configuration of ADC hierarchical scope: channels #####################*/

    /* Note: Hardware constraint (refer to description of the functions         */
    /*       below):                                                            */
    /*       On this STM32 serie, setting of these features are not             */
    /*       conditioned to ADC state.                                          */
    /*       However, in order to be compliant with other STM32 series          */
    /*       and to show the best practice usages, ADC state is checked.        */
    /*       Software can be optimized by removing some of these checks, if     */
    /*       they are not relevant considering previous settings and actions    */
    /*       in user application.                                               */
    if (LL_ADC_IsEnabled(ADC1) == 0)
    {
        /* Set ADC channels sampling time */
        /* Note: Considering interruption occurring after each ADC group          */
        /*       regular sequence conversions                                     */
        /*       (IT from DMA transfer complete),                                 */
        /*       select sampling time and ADC clock with sufficient               */
        /*       duration to not create an overhead situation in IRQHandler.      */
        /* Note: Set long sampling time due to internal channels (VrefInt,        */
        /*       temperature sensor) constraints.                                 */
        /*       Refer to description of function                                 */
        /*       "LL_ADC_SetChannelSamplingTime()".                               */
        LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_3,  LL_ADC_SAMPLINGTIME_28CYCLES);
        LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_4,  LL_ADC_SAMPLINGTIME_28CYCLES);
        LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_5,  LL_ADC_SAMPLINGTIME_28CYCLES);
        LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_7,  LL_ADC_SAMPLINGTIME_28CYCLES);
        LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_8,  LL_ADC_SAMPLINGTIME_28CYCLES);
        LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_9,  LL_ADC_SAMPLINGTIME_28CYCLES);
        LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_14, LL_ADC_SAMPLINGTIME_28CYCLES);
        LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_15, LL_ADC_SAMPLINGTIME_28CYCLES);
        LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_17, LL_ADC_SAMPLINGTIME_28CYCLES);
        LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_18, LL_ADC_SAMPLINGTIME_28CYCLES);
        LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_11, LL_ADC_SAMPLINGTIME_28CYCLES);

    }


    /*## Configuration of ADC transversal scope: analog watchdog ###############*/

    /* Note: On this STM32 serie, there is only 1 analog watchdog available.    */

    /* Set ADC analog watchdog: channels to be monitored */
    // LL_ADC_SetAnalogWDMonitChannels(ADC1, LL_ADC_AWD_DISABLE);

    /* Set ADC analog watchdog: thresholds */
    // LL_ADC_SetAnalogWDThresholds(ADC1, LL_ADC_AWD_THRESHOLD_HIGH, __LL_ADC_DIGITAL_SCALE(LL_ADC_RESOLUTION_12B));
    // LL_ADC_SetAnalogWDThresholds(ADC1, LL_ADC_AWD_THRESHOLD_LOW, 0x000);


    /*## Configuration of ADC transversal scope: oversampling ##################*/

    /* Note: Feature not available on this STM32 serie */


    /*## Configuration of ADC interruptions ####################################*/
    /* Enable interruption ADC group regular end of unitary conversion          */
    /* or end of sequence conversions.                                          */
    /* Note: On this STM32 serie, ADC group regular end of conversion           */
    /*       must be selected among end of unitary conversion                   */
    /*       or end of sequence conversions.                                    */
    /*       Refer to function "LL_ADC_REG_SetFlagEndOfConversion()".           */
    LL_ADC_EnableIT_EOCS(ADC1);

    /* Enable interruption ADC group regular overrun */
    LL_ADC_EnableIT_OVR(ADC1);

    /* Note: in this example, ADC group regular end of conversions              */
    /*       (number of ADC conversions defined by DMA buffer size)             */
    /*       are notified by DMA transfer interruptions).                       */
    /*       ADC interruptions of end of conversion are enabled optionally,     */
    /*       as demonstration purpose in this example.                          */

}

extern "C" void _Error_Handler(const char* file, int line) {
    Serial.printf("Error in file %s at line %d\n", file, line);
}

// the setup function runs once when you press reset or power the board
void setup() {
    Serial.begin(115200);
    Serial.println("ADCDMA Test");
    Configure_DMA();
    configureADC();

    enableADC();
    LL_ADC_REG_StartConversionSWStart(ADC1);
}

// the loop function runs over and over again until power down or reset
void loop() {
  if(Serial.available()){
      char c = Serial.read();
      if (c == 'r') {
          Serial.println("Starting conversion");
          LL_ADC_REG_StartConversionSWStart(ADC1);
      }
      else if (c == '*') {
          Serial.println("RESET");
          delay(10);
          NVIC_SystemReset();
      }
  }
}
