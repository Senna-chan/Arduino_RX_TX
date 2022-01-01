#pragma once

#include <Arduino.h>


/**
ADC1 GPIO Configuration
PC0     ------> ADC1_IN10
PC1     ------> ADC1_IN11
PC2     ------> ADC1_IN12
PC3     ------> ADC1_IN13
PA1     ------> ADC1_IN1
PA2     ------> ADC1_IN2
PA3     ------> ADC1_IN3
PA4     ------> ADC1_IN4
PA5     ------> ADC1_IN5
PA6     ------> ADC1_IN6
PA7     ------> ADC1_IN7
PC4     ------> ADC1_IN14
PC5     ------> ADC1_IN15
PB0     ------> ADC1_IN8
PB1     ------> ADC1_IN9
*/


// NRF defines
#define RF_SPI_BUS				SPI1
#define RF24CS					PB7 // SPI CHIP SELECT
#define RF24INT					PB8  // NRF IRQ Pin
#define RF24CE					PB6  //RADIO CHIP ENABLE

// ADC defines
#define batIndex				10 // Index in ADCDMA buffer for battery
#define CHANNELNUMBERS			10 // Amount of RC ADC Channels
#define DMABUFFERSIZE			15 // Amount of ADC DMA channels
extern uint16_t ADCDMABuffer[DMABUFFERSIZE];

// I2C defines
#define CALEXPENDER_INT_PIN		PB0	// Pin on which the calibratebutton expender interrupts
#define ENCODER_INT_PIN			PB1	// Pin on which the encoder interrupts
#define ENCODER_ADDR			0x40
#define EEPROM_ADDR				0x50 // 24LC256 EEPROM Address in i2c bus 

#define CALEXPENDER_ADDR		0b000
#define ONEWAYEXPENDER_ADDR		0b000
#define TWOWAYEXPENDER_ADDR		0b000
