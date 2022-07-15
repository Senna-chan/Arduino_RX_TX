/*
 Name:		PlotterTest.ino
 Created:	4/19/2022 10:06:44 PM
 Author:	Senna
*/

#include <SerialControlLibrary.h>
#include <PlotterLib.h>
#include <config.h>
#include "ADCDMAFunctions.h"

float randomNumber1 = 5.0f;
float randomNumber2 = 5.0f;
float randomNumber3 = 5.0f;
float randomNumber4 = 5.0f;

SerialControlLibrary scl;

extern "C" void _Error_Handler(const char* file, int line) {
	int count = 0;
	while (1) {
		if (++count % 10 == 0) {
			Serial.printf("Error in file '%s' Line %d\n", file, line);
		}
		if (count == 100) HAL_NVIC_SystemReset();
		digitalToggle(LED_BUILTIN);
		delay(250);
	}
}

void sendPlotterInfo(const char* data) {
	Serial.println("Retransmitting plotterinfo");
	Plotter.retransmitAllPlotInfo();
}

void resetMCU(const char* data) {
	NVIC_SystemReset();
}

// the setup function runs once when you press reset or power the board
void setup() {
	Serial1.begin(115200);
	Serial.println("Starting plotter test");

	ADCInit();

	ADCStart();

	Plotter.init(Serial1.getHandle(),"ADCPlotter");
	Plotter.setTransmitInterval(100);
	Plotter.addPlotData(&ADCDMABuffer[3], "ADC1");
	Plotter.addPlotData(&ADCDMABuffer[4], "ADC2");
	Plotter.addPlotData(&ADCDMABuffer[5], "ADC3");

	PlotterLib* randoPlot = Plotter.addNewPlotter("RANDOPLOTTER");
	randoPlot->addPlotData(&randomNumber1, "RANDOM1");
	randoPlot->addPlotData(&randomNumber2, "RANDOM2");
	randoPlot->addPlotData(&randomNumber3, "RANDOM3");
	randoPlot->addPlotData(&randomNumber4, "RANDOM4");

	scl.init(&Serial1);
	scl.addCallback("@PI", sendPlotterInfo);
	scl.addCallback("*", resetMCU);
	Serial.println("Started plotter test");
}
uint32_t lastRandomTime = millis();
// the loop function runs over and over again until power down or reset
void loop() {
	scl.loop();
	if (millis() - lastRandomTime > 500) {
		lastRandomTime = millis();
		randomNumber1 = (float)random(0, UINT16_MAX) / (float)random(1, 8);
		randomNumber2 = (float)random(0, UINT16_MAX) / (float)random(1, 8);
		randomNumber3 = (float)random(0, UINT16_MAX) / (float)random(1, 8);
		randomNumber4 = (float)random(0, UINT16_MAX) / (float)random(1, 8);
	}
	Plotter.loop();
}
