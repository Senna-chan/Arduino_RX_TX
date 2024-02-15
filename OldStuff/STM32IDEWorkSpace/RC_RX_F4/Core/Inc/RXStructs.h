/*
 * RXStructs.h
 *
 *  Created on: Jul 15, 2022
 *      Author: Senna
 */

#ifndef INC_RXSTRUCTS_H_
#define INC_RXSTRUCTS_H_

typedef struct
{
	uint8_t currentOutputMode;
	TIM_HandleTypeDef* mainTimer; 		// Used for setting up the timers correctly
	uint8_t mainTimerCH; 				// Used for setting up the timers correctly
	__IO uint32_t* timOutput;			// Direct timer output
	__IO uint32_t* miscOutput;// Used for either DAC or misc timer output
	TIM_HandleTypeDef* miscTimConf; 	// Used to be able to set misc timer options like frequency and duty
	uint8_t miscTimCH; 				// Used to be able to set misc timer channel options
	GPIO_TypeDef* muxGPIO;	// GPIO that the mux selector is on
	uint8_t muxPIN;						// PIN That the mux selector is on
} channelOutputConfig;



#endif /* INC_RXSTRUCTS_H_ */
