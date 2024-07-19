/*
 Name:		ADCTest.ino
 Created:	8/17/2021 7:12:16 PM
 Author:	Senna
*/

#include "config.h" 
#include "AnalogFunctions.h"

AnalogFunctions af;

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);
	Serial.println("Started ADCTest");
	af.init();
}
 
// the loop function runs over and over again until power down or reset
void loop() {
	af.readChannels();
	//af.printChangedChannels();
	for(int i = 0; i < CHANNELNUMBERS; i++)
	{
		Serial.printf("CH%02d %04d ", i + 1, af.channelData[i]);
	}
	Serial.println();
	delay(10);
}
