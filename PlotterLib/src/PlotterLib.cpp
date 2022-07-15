/*
 Name:		PlotterLib.cpp
 Created:	4/19/2022 9:55:41 PM
 Author:	Senna
 Editor:	http://www.visualmicro.com
*/

#include "PlotterLib.h"

void PlotterLib::transmitData()
{
	if (!enabled) return; // No transmitting of data
	char* msgBuf = (char*)malloc(dataPtrs.size() * 8 + 10);
	char* dataBuf = (char*)malloc(dataPtrs.size() * 8);
	memset(msgBuf, 0, dataPtrs.size() * 8 + 10);
	memset(dataBuf, 0, dataPtrs.size() * 8);
	char* msgBufPtr = msgBuf;
	char* dataBufPtr = dataBuf;
	
	msgBufPtr += sprintf(msgBufPtr, "@PS");
	*dataBufPtr = plotterNumber; dataBufPtr += 1;

	for (int i = 0; i < dataPtrs.size(); i++) {
		dataPtrStruct dataPtr = dataPtrs.at(i);
		*dataBufPtr = dataPtr.dataSize; dataBufPtr += 1;
		switch (dataPtr.dataSize) {
		case 1:

			memcpy(dataBufPtr, (uint8_t*)dataPtr.ptr, dataPtr.dataSize); dataBufPtr += dataPtr.dataSize;
			break;
		case 2:
			memcpy(dataBufPtr, (uint16_t*)dataPtr.ptr, dataPtr.dataSize); dataBufPtr += dataPtr.dataSize;
			break;
		case 4:
			if (dataPtr.isFloat) {
				memcpy(dataBufPtr, (float*)dataPtr.ptr, dataPtr.dataSize); dataBufPtr += dataPtr.dataSize;
			}
			else {
				memcpy(dataBufPtr, (uint32_t*)dataPtr.ptr, dataPtr.dataSize); dataBufPtr += dataPtr.dataSize;
			}
			break;
		case 8:

			if (dataPtr.isFloat) {
				memcpy(dataBufPtr, dataPtr.ptr, dataPtr.dataSize); dataBufPtr += dataPtr.dataSize;
			}
			else {
				memcpy(dataBufPtr, (uint64_t*)dataPtr.ptr, dataPtr.dataSize); dataBufPtr += dataPtr.dataSize;
			}
		}
	}
	*msgBufPtr = (uint8_t)(dataBufPtr - dataBuf); msgBufPtr += 1;
	memcpy(msgBufPtr, dataBuf, dataBufPtr - dataBuf);
	msgBufPtr += (dataBufPtr - dataBuf);
	msgBufPtr += sprintf(msgBufPtr, "@PE\r\n");
	
	//String msg = String(msgBuf);
#ifdef ARDUINO
	serial->write((uint8_t*)msgBuf, msgBufPtr - msgBuf);
#else
	HAL_StatusTypeDef status = HAL_UART_Transmit(uart, (uint8_t*)msgBuf, msgBufPtr - msgBuf, 1000);
	if (status != HAL_OK) {
		printf("ERROR TRANSMITTING PLOTDATA");
	}
#endif
	free(msgBuf);
	free(dataBuf);
}



void PlotterLib::insertDataPtr(double* ptr, char* name, uint8_t dataSize, bool isFloat)
{
	if (strlen(name) > 20) {
		Error_Handler();
	}
	dataPtrStruct dataPtr;
	dataPtr.dataSize = dataSize;
	dataPtr.ptr = ptr;
	memmove(dataPtr.name, name, strlen(name));
	//dataPtr.name = name;
	dataPtr.isFloat = isFloat;
	dataPtrs.push_back(dataPtr);
	if (lastTransmitTime != 0) {
		transmitPlotInfo(); // Plotdata changed.
	}
	Serial.printf("Adding '%s' to plotter '%s'\r\n", dataPtr.name, plotName);
}
void PlotterLib::serialSetPlotState(const char* data)
{
	if (strlen(data) == 1) {
		bool activate = data[0] == 1;
		setPlotState(activate);
		if (nextPlotter != nullptr) {
			nextPlotter->serialSetPlotState(data);
		}
	}
	else 
	{
		uint8_t plotNumber = data[0];
		bool activate = data[1] == 1;
		if (plotterNumber == plotNumber) {
			setPlotState(activate);
			return; // No need to check the other plotters
		}
		if (nextPlotter != nullptr) {
			nextPlotter->serialSetPlotState(data);
		}
	}
}

#ifdef ARDUINO
void PlotterLib::init(HardwareSerial* serial, char* plotname, SerialControlLibrary* serialControl) {
	this->serial = serial;
#else
void PlotterLib::init(UART_HandleTypeDef * uartTypeDef, char* plotname, SerialControlLibrary* serialControl) {
	this->uart = uart;
#endif
	this->serialControl = serialControl;
	if (serialControl != nullptr) {
		printf("Attaching serialcontrol callbacks");
		serialControl->addVoidCallback("@PI", std::bind(&PlotterLib::retransmitAllPlotInfo, this));
		serialControl->addDataCallback("@PE", std::bind(&PlotterLib::serialSetPlotState, this, std::placeholders::_1));
	}
	plotName = plotname;
	isMaster = true;
}

void PlotterLib::setPlotState(bool active)
{
	enabled = active;
}

void PlotterLib::loop()
{
	if (HAL_GetTick() - lastTransmitTime > transmitInterval) {
		if (lastTransmitTime == 0) {
			transmitPlotInfo();
		}

		lastTransmitTime = HAL_GetTick();
		transmitData();
	}
	if (nextPlotter != nullptr) {
		nextPlotter->loop();
	}
}

void PlotterLib::transmitPlotInfo()
{
	char* msgBuf = (char*)malloc(dataPtrs.size() * 40);
	memset(msgBuf, 0, dataPtrs.size() * 40);
	char* msgBufPtr = msgBuf;

	msgBufPtr += sprintf(msgBufPtr, "@PIS|%s|%d|%d", plotName, plotterNumber, dataPtrs.size());

	for (int i = 0; i < dataPtrs.size(); i++) {
		dataPtrStruct dataPtr = dataPtrs.at(i);
		msgBufPtr += sprintf(msgBufPtr, "|%d,%s,%d", i, dataPtr.name, dataPtr.isFloat);
	}
	msgBufPtr += sprintf(msgBufPtr, "@PIE\r\n");
#ifdef ARDUINO
	serial->write((uint8_t*)msgBuf, msgBufPtr - msgBuf);
#else
	HAL_StatusTypeDef status = HAL_UART_Transmit(uart, (uint8_t*)msgBuf, msgBufPtr - msgBuf, 1000);
	if (status != HAL_OK) {
		printf("ERROR TRANSMITTING PLOTINFO");
	}
#endif
	free(msgBuf);

	return;
	
}

void PlotterLib::retransmitAllPlotInfo()
{
	transmitPlotInfo();
	if(nextPlotter != nullptr) {
		nextPlotter->transmitPlotInfo();
	}
}

void PlotterLib::addPlotData(uint8_t* dataPtr,char* name)
{
	insertDataPtr((double*)dataPtr, name, 1);
}

void PlotterLib::addPlotData(uint16_t* dataPtr,char* name)
{
	insertDataPtr((double*)dataPtr, name, 2);
}

void PlotterLib::addPlotData(uint32_t* dataPtr,char* name)
{
	insertDataPtr((double*)dataPtr, name, 4);
}

void PlotterLib::addPlotData(uint64_t* dataPtr,char* name)
{
	insertDataPtr((double*)dataPtr, name, 8);
}


void PlotterLib::addPlotData(float* dataPtr,char* name)
{
	insertDataPtr((double*)dataPtr, name, 4,true);
}

void PlotterLib::addPlotData(double* dataPtr,char* name)
{
	insertDataPtr((double*)dataPtr, name, 8, true);
}

PlotterLib* PlotterLib::addNewPlotter(char* plotname)
{
	PlotterLib* plotter = this;
	while (true) {
		if (nextPlotter == nullptr) {
			nextPlotter = new PlotterLib();
			nextPlotter->plotterNumber = plotterNumber + 1;
			nextPlotter->uart = this->uart;
			nextPlotter->serial = this->serial;
			nextPlotter->plotName = plotname;
			plotter = nextPlotter;
			break;
		}
		else {
			plotter = nextPlotter;
		}
	}
	return plotter;
}

PlotterLib Plotter;