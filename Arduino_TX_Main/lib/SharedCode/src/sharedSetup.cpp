#include <Arduino.h>
#include <Wire.h>
#include "config.h"

#include "sharedSetup.h"

void setupWire1()
{
    Wire.setSCL(WIRE1_SCL);
    Wire.setSDA(WIRE1_SDA);
    Wire.begin();
    Wire.setClock(100000);
}
