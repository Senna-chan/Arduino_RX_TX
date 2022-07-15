/*
 Name:		PlotterLib.h
 Created:	4/19/2022 9:55:41 PM
 Author:	Senna
 Editor:	http://www.visualmicro.com
*/

#ifndef _PlotterLib_h
#define _PlotterLib_h

#if defined(ARDUINO)
	#include <Arduino.h>
#else

#endif

#include <SerialControlLibrary.h>
#include <vector>

class PlotterLib{
private:
	struct dataPtrStruct {
		uint8_t dataSize;
		double* ptr;
		char name[20] = { 0 }; // Already assign memory
		bool isFloat;
	};
#ifdef ARDUINO
	HardwareSerial* serial;
#endif
	UART_HandleTypeDef* uart;
	std::vector<dataPtrStruct> dataPtrs;
	uint32_t lastTransmitTime = 0;
	uint32_t transmitInterval = 100;
	uint8_t plotterNumber = 1;
	PlotterLib* nextPlotter;
	bool isMaster = false; // If this is true than it is the first in a row of plotters
	const char* plotName;
	SerialControlLibrary* serialControl;
	bool enabled = true;
	void transmitData();
	void insertDataPtr(double* ptr, char* name, uint8_t dataSize, bool isFloat = false);
	void serialSetPlotState(const char* data);
public:
#ifdef ARDUINO
	void init(HardwareSerial* serial, char* plotname, SerialControlLibrary* serialControl = nullptr);
#else 
	void init(UART_HandleTypeDef* uartTypeDef, char* plotname, SerialControlLibrary* serialControl = nullptr);
#endif
	void setPlotState(bool active);
	void loop();
	void transmitPlotInfo();
	void retransmitAllPlotInfo();
	void addPlotData(uint8_t* dataPtr, char* name);
	void addPlotData(uint16_t* dataPtr, char* name);
	void addPlotData(uint32_t* dataPtr, char* name);
	void addPlotData(uint64_t* dataPtr, char* name);
	void addPlotData(float* dataPtr, char* name);
	void addPlotData(double* dataPtr, char* name);
	PlotterLib* addNewPlotter(char* name);
	void setTransmitInterval(uint32_t interval) {
		transmitInterval = interval;
	}
	uint32_t getTransmitInterval() {
		return transmitInterval;
	}
	void forceTransmit() {
		transmitData();
	}
	const char* getPlotterName() { return plotName; }
};
// Generic plotter for everything
extern PlotterLib Plotter;

#endif

