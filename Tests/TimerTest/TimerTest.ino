/*
 Name:		TimerTest.ino
 Created:	8/29/2019 11:01:34 AM
 Author:	David
*/
HardwareTimer Timer2 = HardwareTimer(TIM2);

extern "C" void _Error_Handler(const char* file, int line)
{
	Serial.print("Error in file ");
	Serial.print(file);
	Serial.print(" at line ");
	Serial.println(line);
	for (;;) {
		delay(1000);
	}
}

void pc11High(HardwareTimer *timer)
{
	digitalWrite(LED_BUILTIN, HIGH);
	digitalWrite(PC11, HIGH);
}
void pc11Low(HardwareTimer *timer)
{
	digitalWrite(LED_BUILTIN, LOW);
	digitalWrite(PC11, LOW);
}
// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(PC11, OUTPUT);
	digitalWrite(PC11, HIGH);
	digitalWrite(LED_BUILTIN, HIGH);
	delay(2000);
	Serial.println("Begin Timer test");
	Timer2.pause();
	Timer2.setPrescaleFactor(72);
	Timer2.setOverflow(5000);
	Timer2.setMode(1, TIMER_OUTPUT_COMPARE_PWM1, PA15);
	Timer2.setMode(2, TIMER_OUTPUT_COMPARE_PWM1);
	Timer2.setCaptureCompare(1, 1000);
	Timer2.setCaptureCompare(2, 1500);
	Timer2.attachInterrupt(pc11High);
	Timer2.attachInterrupt(2, pc11Low);
	Timer2.resume();
	Timer2.refresh();
	delay(100);
}
int16_t r1,r2;
// the loop function runs over and over again until power down or reset
void loop() {
	r1 = 1500 + random(-500, 500);
	r2 = 1500 + random(-500, 500);
	printf("Setting channel 1 to %i and channel 2 to %i\r\n",r1, r2);
	Timer2.setCaptureCompare(1, r1);
	Timer2.setCaptureCompare(2, r2);
	delay(2000);
}
