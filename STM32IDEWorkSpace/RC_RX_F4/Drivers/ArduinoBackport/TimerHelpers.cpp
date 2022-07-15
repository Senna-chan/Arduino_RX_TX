#include "TimerHelpers.hpp"

/**
  * @brief  This function return the timer clock source.
  * @param  tim: timer instance
  * @retval 1 = PCLK1 or 2 = PCLK2
  */
uint8_t TimerHelpers::getTimerClkSrc()
{
  uint8_t clkSrc = 0;


#if defined(STM32F0xx) || defined(STM32G0xx)
    /* TIMx source CLK is PCKL1 */
    clkSrc = 1;
#else
  {
    /* Get source clock depending on TIM instance */
    switch (_timer->Instance) {
#if defined(TIM2_BASE)
      case (uint32_t)TIM2:
#endif
#if defined(TIM3_BASE)
      case (uint32_t)TIM3:
#endif
#if defined(TIM4_BASE)
      case (uint32_t)TIM4:
#endif
#if defined(TIM5_BASE)
      case (uint32_t)TIM5:
#endif
#if defined(TIM6_BASE)
      case (uint32_t)TIM6:
#endif
#if defined(TIM7_BASE)
      case (uint32_t)TIM7:
#endif
#if defined(TIM12_BASE)
      case (uint32_t)TIM12:
#endif
#if defined(TIM13_BASE)
      case (uint32_t)TIM13:
#endif
#if defined(TIM14_BASE)
      case (uint32_t)TIM14:
#endif
#if defined(TIM18_BASE)
      case (uint32_t)TIM18:
#endif
        clkSrc = 1;
        break;
#if defined(TIM1_BASE)
      case (uint32_t)TIM1:
#endif
#if defined(TIM8_BASE)
      case (uint32_t)TIM8:
#endif
#if defined(TIM9_BASE)
      case (uint32_t)TIM9:
#endif
#if defined(TIM10_BASE)
      case (uint32_t)TIM10:
#endif
#if defined(TIM11_BASE)
      case (uint32_t)TIM11:
#endif
#if defined(TIM15_BASE)
      case (uint32_t)TIM15:
#endif
#if defined(TIM16_BASE)
      case (uint32_t)TIM16:
#endif
#if defined(TIM17_BASE)
      case (uint32_t)TIM17:
#endif
#if defined(TIM19_BASE)
      case (uint32_t)TIM19:
#endif
#if defined(TIM20_BASE)
      case (uint32_t)TIM20:
#endif
#if defined(TIM21_BASE)
      case (uint32_t)TIM21:
#endif
#if defined(TIM22_BASE)
      case (uint32_t)TIM22:
#endif
        clkSrc = 2;
        break;
      default:
        _Error_Handler("TIM: Unknown timer instance", (int)tim);
        break;
    }
#endif
  return clkSrc;
}


/**
  * @brief  This function return the timer clock frequency.
  * @param  None
  * @retval frequency in Hz
  */
uint32_t TimerHelpers::getTimerClkFreq()
{
#if defined(STM32MP1xx)
  uint8_t timerClkSrc = getTimerClkSrc(_timerObj.handle.Instance);
  uint64_t clkSelection = timerClkSrc == 1 ? RCC_PERIPHCLK_TIMG1 : RCC_PERIPHCLK_TIMG2;
  return HAL_RCCEx_GetPeriphCLKFreq(clkSelection);
#else
  RCC_ClkInitTypeDef    clkconfig = {};
  uint32_t              pFLatency = 0U;
  uint32_t              uwTimclock = 0U, uwAPBxPrescaler = 0U;

  /* Get clock configuration */
  HAL_RCC_GetClockConfig(&clkconfig, &pFLatency);
  switch (getTimerClkSrc(_timerObj.handle.Instance)) {
    case 1:
      uwAPBxPrescaler = clkconfig.APB1CLKDivider;
      uwTimclock = HAL_RCC_GetPCLK1Freq();
      break;
#if !defined(STM32F0xx) && !defined(STM32G0xx)
    case 2:
      uwAPBxPrescaler = clkconfig.APB2CLKDivider;
      uwTimclock = HAL_RCC_GetPCLK2Freq();
      break;
#endif
    default:
    case 0: // Unknown timer clock source
      Error_Handler();
      break;
  }

#if defined(STM32H7xx)
  /* When TIMPRE bit of the RCC_CFGR register is reset,
   *   if APBx prescaler is 1 or 2 then TIMxCLK = HCLK,
   *   otherwise TIMxCLK = 2x PCLKx.
   * When TIMPRE bit in the RCC_CFGR register is set,
   *   if APBx prescaler is 1,2 or 4, then TIMxCLK = HCLK,
   *   otherwise TIMxCLK = 4x PCLKx
   */
  RCC_PeriphCLKInitTypeDef PeriphClkConfig = {};
  HAL_RCCEx_GetPeriphCLKConfig(&PeriphClkConfig);

  if (PeriphClkConfig.TIMPresSelection == RCC_TIMPRES_ACTIVATED) {
    switch (uwAPBxPrescaler) {
      default:
      case RCC_APB1_DIV1:
      case RCC_APB1_DIV2:
      case RCC_APB1_DIV4:
      /* case RCC_APB2_DIV1: */
      case RCC_APB2_DIV2:
      case RCC_APB2_DIV4:
        /* Note: in such cases, HCLK = (APBCLK * DIVx) */
        uwTimclock = HAL_RCC_GetHCLKFreq();
        break;
      case RCC_APB1_DIV8:
      case RCC_APB1_DIV16:
      case RCC_APB2_DIV8:
      case RCC_APB2_DIV16:
        uwTimclock *= 4;
        break;
    }
  } else {
    switch (uwAPBxPrescaler) {
      default:
      case RCC_APB1_DIV1:
      case RCC_APB1_DIV2:
      /* case RCC_APB2_DIV1: */
      case RCC_APB2_DIV2:
        /* Note: in such cases, HCLK = (APBCLK * DIVx) */
        uwTimclock = HAL_RCC_GetHCLKFreq();
        break;
      case RCC_APB1_DIV4:
      case RCC_APB1_DIV8:
      case RCC_APB1_DIV16:
      case RCC_APB2_DIV4:
      case RCC_APB2_DIV8:
      case RCC_APB2_DIV16:
        uwTimclock *= 2;
        break;
    }
  }
#else
  /* When TIMPRE bit of the RCC_DCKCFGR register is reset,
   *   if APBx prescaler is 1, then TIMxCLK = PCLKx,
   *   otherwise TIMxCLK = 2x PCLKx.
   * When TIMPRE bit in the RCC_DCKCFGR register is set,
   *   if APBx prescaler is 1,2 or 4, then TIMxCLK = HCLK,
   *   otherwise TIMxCLK = 4x PCLKx
   */
#if defined(STM32F4xx) || defined(STM32F7xx)
#if !defined(STM32F405xx) && !defined(STM32F415xx) &&\
    !defined(STM32F407xx) && !defined(STM32F417xx)
  RCC_PeriphCLKInitTypeDef PeriphClkConfig = {};
  HAL_RCCEx_GetPeriphCLKConfig(&PeriphClkConfig);

  if (PeriphClkConfig.TIMPresSelection == RCC_TIMPRES_ACTIVATED)
    switch (uwAPBxPrescaler) {
      default:
      case RCC_HCLK_DIV1:
      case RCC_HCLK_DIV2:
      case RCC_HCLK_DIV4:
        /* Note: in such cases, HCLK = (APBCLK * DIVx) */
        uwTimclock = HAL_RCC_GetHCLKFreq();
        break;
      case RCC_HCLK_DIV8:
      case RCC_HCLK_DIV16:
        uwTimclock *= 4;
        break;
    } else
#endif
#endif
    switch (uwAPBxPrescaler) {
      default:
      case RCC_HCLK_DIV1:
        // uwTimclock*=1;
        break;
      case RCC_HCLK_DIV2:
      case RCC_HCLK_DIV4:
      case RCC_HCLK_DIV8:
      case RCC_HCLK_DIV16:
        uwTimclock *= 2;
        break;
    }
#endif /* STM32H7xx */
  return uwTimclock;
#endif /* STM32MP1xx */
}

/**
  * @brief  Retrieve overflow (rollover) value from hardware register
  * @param  format of returned value. If omitted default format is Tick
  * @retval overflow depending on format value:
  *           TICK_FORMAT:     return number of tick for overflow
  *           MICROSEC_FORMAT: return number of microsecondes for overflow
  *           HERTZ_FORMAT:    return frequency in hertz for overflow
  */
uint32_t TimerHelpers::getOverflow(TimerFormat_t format)
{
  // Hardware register correspond to period count-1. Example ARR register value 9 means period of 10 timer cycle
  uint32_t ARR_RegisterValue = _timer->Instance.ARR;
  uint32_t Prescalerfactor = _timer->Instance.PSC 1;
  uint32_t return_value;
  switch (format) {
    case MICROSEC_FORMAT:
      return_value = (uint32_t)(((ARR_RegisterValue + 1) * Prescalerfactor * 1000000.0) / getTimerClkFreq());
      break;
    case HERTZ_FORMAT:
      return_value = (uint32_t)(getTimerClkFreq() / ((ARR_RegisterValue + 1) * Prescalerfactor));
      break;
    case TICK_FORMAT:
    default :
      return_value = ARR_RegisterValue + 1;
      break;
  }
  return return_value;
}

/**
  * @brief  Set overflow (rollover)
  *
  *         Note that by default, the new value will not be applied
  *         immediately, but become effective at the next update event
  *         (usually the next timer overflow). See setPreloadEnable()
  *         for controlling this behaviour.
  * @param  overflow: depend on format parameter
  * @param  format of overflow parameter. If omitted default format is Tick
  *           TICK_FORMAT:     overflow is the number of tick for overflow
  *           MICROSEC_FORMAT: overflow is the number of microsecondes for overflow
  *           HERTZ_FORMAT:    overflow is the frequency in hertz for overflow
  * @retval None
  */
void TimerHelpers::setOverflow(uint32_t overflow, TimerFormat_t format)
{
  uint32_t ARR_RegisterValue;
  uint32_t PeriodTicks;
  uint32_t Prescalerfactor;
  uint32_t period_cyc;
  // Remark: Hardware register correspond to period count-1. Example ARR register value 9 means period of 10 timer cycle
  switch (format) {
    case MICROSEC_FORMAT:
      period_cyc = overflow * (getTimerClkFreq() / 1000000);
      Prescalerfactor = (period_cyc / 0x10000) + 1;
      LL_TIM_SetPrescaler(_timerObj.handle.Instance, Prescalerfactor - 1);
      PeriodTicks = period_cyc / Prescalerfactor;
      break;
    case HERTZ_FORMAT:
      period_cyc = getTimerClkFreq() / overflow;
      Prescalerfactor = (period_cyc / 0x10000) + 1;
      LL_TIM_SetPrescaler(_timerObj.handle.Instance, Prescalerfactor - 1);
      PeriodTicks = period_cyc / Prescalerfactor;
      break;
    case TICK_FORMAT:
    default :
      PeriodTicks = overflow;
      break;
  }

  if (PeriodTicks > 0) {
    // The register specifies the maximum value, so the period is really one tick longer
    ARR_RegisterValue = PeriodTicks - 1;
  } else {
    // But do not underflow in case a zero period was given somehow.
    ARR_RegisterValue = 0;
  }
  __HAL_TIM_SET_AUTORELOAD(&_timerObj.handle, ARR_RegisterValue);
}
