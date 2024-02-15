/*
 Name:		SerialControlLibTest.ino
 Created:	10/5/2022 11:45:58 AM
 Author:	Senna
*/

#include "SerialControlLibrary.h"

SerialControlLibrary scl;
void resetMCU() {
	NVIC_SystemReset();
}

void help() {
	Serial.println("Help:");
	Serial.println("* to reset MCU");
	Serial.println("d{data} to test data");
}

void datatest(const char* data) {
	Serial.print("DataTest: ");
	Serial.println(data);
}

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);
	Serial.println("Init SerialControlLib");
	scl.init(&Serial1);
	scl.addVoidCallback("*", resetMCU);
	scl.addVoidCallback("h", help);
	scl.addDataCallback("d", datatest);
}

// the loop function runs over and over again until power down or reset
void loop() {
	scl.loop();
}
