#ifndef ANALOGFUNCTIONS_H
#define ANALOGFUNCTIONS_H

#include <Arduino.h>
#include "config.h" 


class AnalogFunctions
{
public:
	void init();
	void initADC();
	void printChangedChannels();
};

#endif