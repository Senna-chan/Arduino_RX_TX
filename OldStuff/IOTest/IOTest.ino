/*
 Name:		IOTest.ino
 Created:	1/3/2022 10:53:02 PM
 Author:	Senna
*/

// the setup function runs once when you press reset or power the board
void setup() {
	pinMode(PB6, OUTPUT);
	pinMode(PB7, OUTPUT);
}

// the loop function runs over and over again until power down or reset
void loop() {
	digitalToggle(PB6);
	delay(20);
	digitalToggle(PB7);
	delay(20);
}
