#pragma once

#include <Arduino.h>

#define CALEXPENDER_INT_PIN	PB4	// Pin on which the calibratebutton expender interrupts
#define ENCODER_INT_PIN		PB5	// Pin on which the encoder interrupts
#define ch1Pin				PA1
#define ch2Pin				PA2
#define ch3Pin				PA3
#define ch4Pin				PA4
#define ch5Pin				PA5
#define ch6Pin				PA6
#define ch7Pin				PA7
#define ch8Pin				PC4
#define ch9Pin				PC5
#define ch10Pin				PB0
#define stick1BTNPin		PE7
#define stick2BTNPin		PE8
#define batPin				PB1
#define CHANNELNUMBERS		10


extern uint16_t chPins[CHANNELNUMBERS];

#define RF24CS					PB12 // SPI CHIP SELECT
#define RF24INT					PC7  // NRF IRQ Pin
#define RF24CE					PC6  //RADIO CHIP ENABLE

#define EEPROM_ADDRESS			0x50 // 24LC256 EEPROM Address in i2c bus 



#define twoWayAddr	 0b001
#define oneWayAddr	 0b010
#define calAddr		 0b111