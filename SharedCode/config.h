#pragma once

#include <Arduino.h>
#include <nrf24.h>

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

// HMI defines
#define HMI_RX					PD6
#define HMI_TX					PD5

// NRF defines
#define RF_SPI_BUS				SPI3
#define cePin					PB6 // Chip enable(RX/TX)
#define csnPin					PB7	// SPI Chip Select
#define irqPin					PB8


// First one is TX->RX second one is RX->TX
//extern uint8_t nrfAddress[2][5];
extern uint8_t nrfAddress[3];
extern bool isTransmitter;


// ADC defines
#define batIndex				10		// Index in ADCDMA buffer for battery
#define ADCCHANNELNUMBERS		10		// Amount of RC ADC Channels
#define DMABUFFERSIZE			15		// Amount of ADC DMA channels
extern uint16_t ADCDMABuffer[DMABUFFERSIZE];

// I2C defines
#define CALEXPENDER_INT_PIN		PB13	// Pin on which the calibratebutton expender interrupts
#define IOEXPENDER_INT_PIN		PB14	// Pin on which the oneway expender interrupts
#define ENCODER_INT_PIN			PB12	// Pin on which the encoder interrupts


// I2C Addresses
#define ENCODER_ADDR			0x42
#define EEPROM_ADDR				0x50	// 24LC256 EEPROM Address in i2c bus 
#define CALEXPENDER_ADDR		7
#define IOEXPANDER1_ADDR		2
#define IOEXPANDER2_ADDR		1


#define SETTINGSVERSION			18
#define EEPROMFULLWIPE			false



void common_nRFInit();