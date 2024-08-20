// CheapLegoHub.h

#ifndef _CHEAPLEGOHUB_h
#define _CHEAPLEGOHUB_h

#if defined(ARDUINO)
	#include <Arduino.h>
#endif

#include "ArduinoBLE.h"

class CheapLegoHub
{
	enum Direction{

	};
	
public:
	void StartScan();
	bool Connect();
	bool Disconnect();
	//bool SetValue(Direction direction, uint8_t value);
	void Send();
	/**
	 * Directly sets the values of the ports without buffering. 
	 * Be sure to notice the limitations of the device. 
	 * AB and CD together is always the same speed(But can be different direction) for both axis. The value being used will be the highest value. E and F are individual
	 * 
	 * 
	 * \param a -255 - 255
	 * \param b -255 - 255
	 * \param c -255 - 255
	 * \param d -255 - 255
	 * \param e -255 - 255
	 * \param f -255 - 255
	 * \return bool if values are accepted
	 */
	bool SetValue(int a, int b, int c, int d, int e, int f);
	/**
	 * Stops all motors.
	 * 
	 */
	void Stop();

	bool IsConnected();
private:
	int returnClippedValue(int val);
	/**
	 * Change the input val1 and val2 to get the diagonal value.
	 * 
	 * \param val1
	 * \param val2
	 * \return val1 or val2 have been changed
	 */
	bool doDiagonalChange(int *val1, int *val2);

	BLECharacteristic output;
	BLEDevice device;
	bool bleDeviceFound = false;

	const char* deviceUUID = "f0ff";
	const char* serviceUUID = "fff0";
	const char* characteristicUUID = "fff2";

	const int maxValue = 255;
	static const int dataSize = 14;
	const uint8_t stopCommand[dataSize] = { 0x5a, 0x6b, 0x02, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xd0 };
	uint8_t dataBuffer[dataSize] = { 0x5a, 0x6b, 0x02, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xd0 };
	
	uint8_t ABDirIndex = 5;
	uint8_t ABValueIndex = 6;
	uint8_t CDDirIndex = 7;
	uint8_t CDValueIndex = 8;
	uint8_t EFDirIndex = 10;
	uint8_t EValueIndex = 11;
	uint8_t FValueIndex = 12;

	uint8_t axis1bit = (1 << 0); // Base number is axis1 positive. Left shift by one to get negative direction
	uint8_t axis2bit = (1 << 2); // Base number is axis1 positive. Left shift by one to get negative direction

	//uint8_t A_POS = (1 << 0);
	//uint8_t A_NEG = (1 << 1);
	//uint8_t B_POS = (1 << 2);
	//uint8_t B_NEG = (1 << 3);
	//uint8_t C_POS = A_POS;
	//uint8_t C_NEG = A_NEG;
	//uint8_t D_POS = B_POS;
	//uint8_t D_NEG = B_NEG;
	//uint8_t E_POS = A_POS;
	//uint8_t E_NEG = A_NEG;
	//uint8_t F_POS = B_POS;
	//uint8_t F_NEG = B_NEG;
};

#endif

