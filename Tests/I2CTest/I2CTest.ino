/*
 Name:		I2CTest.ino
 Created:	11/3/2023 11:12:16 AM
 Author:	Senna
*/

// the setup function runs once when you press reset or power the board
#include <MyHelpers.h>
#include <Wire.h>

void setup() {
	Serial.begin(115200);
	Wire.setSCL(PB_10);
	Wire.setSDA(PB_11);
	Wire.begin();
	Wire.setClock(400000);
	Serial.printf("Wire SCL PB10, SDA PB11, Freq 400KhZ");
}

// the loop function runs over and over again until power down or reset
void loop() {
	scanI2C(&Wire, &Serial);
	delay(5000);
}
