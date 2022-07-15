#include "main.h"
#include "stm32f407xx.h"
/**
 * This is a on demand backport of the HardwareTimer in arduino
 */

typedef enum {
  RESOLUTION_1B_COMPARE_FORMAT = 1,  // used for Dutycycle: [0 .. 1]
  RESOLUTION_2B_COMPARE_FORMAT,      // used for Dutycycle: [0 .. 3]
  RESOLUTION_3B_COMPARE_FORMAT,      // used for Dutycycle: [0 .. 7]
  RESOLUTION_4B_COMPARE_FORMAT,      // used for Dutycycle: [0 .. 15]
  RESOLUTION_5B_COMPARE_FORMAT,      // used for Dutycycle: [0 .. 31]
  RESOLUTION_6B_COMPARE_FORMAT,      // used for Dutycycle: [0 .. 63]
  RESOLUTION_7B_COMPARE_FORMAT,      // used for Dutycycle: [0 .. 127]
  RESOLUTION_8B_COMPARE_FORMAT,      // used for Dutycycle: [0 .. 255]
  RESOLUTION_9B_COMPARE_FORMAT,      // used for Dutycycle: [0 .. 511]
  RESOLUTION_10B_COMPARE_FORMAT,     // used for Dutycycle: [0 .. 1023]
  RESOLUTION_11B_COMPARE_FORMAT,     // used for Dutycycle: [0 .. 2047]
  RESOLUTION_12B_COMPARE_FORMAT,     // used for Dutycycle: [0 .. 4095]
  RESOLUTION_13B_COMPARE_FORMAT,     // used for Dutycycle: [0 .. 8191]
  RESOLUTION_14B_COMPARE_FORMAT,     // used for Dutycycle: [0 .. 16383]
  RESOLUTION_15B_COMPARE_FORMAT,     // used for Dutycycle: [0 .. 32767]
  RESOLUTION_16B_COMPARE_FORMAT,     // used for Dutycycle: [0 .. 65535]

  TICK_COMPARE_FORMAT = 0x80, // default
  MICROSEC_COMPARE_FORMAT,
  HERTZ_COMPARE_FORMAT,
  PERCENT_COMPARE_FORMAT, // used for Dutycycle
} TimerCompareFormat_t;

class TimerHelpers{
private:
	TIM_HandleTypeDef *_timer;
	uint32_t getTimerClkFreq();
	uint8_t getTimerClkSrc();
public:

	void init(TIM_HandleTypeDef *_timer);

	uint32_t getOverflow(TimerFormat_t format);
	void 	 setOverflow(uint32_t overflow, TimerFormat_t format);

};
