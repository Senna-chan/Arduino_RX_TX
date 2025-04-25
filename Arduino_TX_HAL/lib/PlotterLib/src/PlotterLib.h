/*
 Name:		PlotterLib.h
 Created:	4/19/2022 9:55:41 PM
 Author:	Senna
 Editor:	http://www.visualmicro.com
*/

#ifndef PLOTTERLIB_H
#define PLOTTERLIB_H

#include "main.h"
#include <SerialControlLibrary.h>
#include <vector>

class PlotterLib {
private:
    struct dataPtrStruct {
        uint8_t dataSize;
        void* ptr;
        char name[20] = { 0 }; // pre-assign memory
    };
#ifdef ARDUINO
    HardwareSerial* serial;
#endif
    HardwareSerial* serial;
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
    void insertDataPtr(void* ptr, const char* name, uint8_t dataSize);
    void serialSetPlotState(const char* data);

public:
#ifdef ARDUINO
    void init(HardwareSerial* serial, const char* plotname, SerialControlLibrary* serialControl = nullptr);
#else
    void init(UART_HandleTypeDef* uartTypeDef, const char* plotname, SerialControlLibrary* serialControl = nullptr);
#endif
    void setPlotState(bool active);
    void loop();
    void transmitPlotInfo();
    void retransmitAllPlotInfo();
    template <std::integral T>
    void addPlotData(T* dataPtr, const char* name) {
        insertDataPtr(dataPtr, name, sizeof(T));
    };
    PlotterLib* addNewPlotter(const char* name);
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
