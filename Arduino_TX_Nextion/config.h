#pragma once

#define CALEXPENDER_INT_PIN		PB4	// Pin on which the calibratebutton expender interrupts
#define ENCODER_INT_PIN			PB5	// Pin on which the encoder interrupts
#define ch1Pin					PA0
#define ch2Pin					PA1
#define ch3Pin					PA2
#define ch4Pin					PA3
#define ch5Pin					PA4
#define ch6Pin					PA5
#define ch7Pin					PA6
#define ch8Pin					PB0
#define ch9Pin					PB1
#define ch10Pin					PC4
#define ch11Pin					PC5
#define ch12Pin					PC3
#define batPin					PC0
#define CHANNELNUMBERS			12

#define RF24CS					PB12 // SPI CHIP SELECT
#define RF24INT					PC7  // NRF IRQ Pin
#define RF24CE					PC6  //RADIO CHIP ENABLE

#define EEPROM_ADDRESS			0x50 // 24LC256 EEPROM Address in i2c bus 