// settingsHelper.h

#ifndef _SETTINGSHELPER_h
#define _SETTINGSHELPER_h

#include <Arduino.h>
#include "config.h"
#include "Structs.h"


bool readSettings();
void saveSettings();

void generateDefaultSettings();
void loadSettings(bool forceReset = false);
void PrintCalValues();

#endif

