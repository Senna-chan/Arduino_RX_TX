// settingsHelper.h

#ifndef _SETTINGSHELPER_h
#define _SETTINGSHELPER_h

#include "Config.h"

#include <main.h>
#include "Structs.h"

bool readSettings();
void saveSettings();

void generateDefaultSettings();
void loadSettings(bool forceReset = false);
void PrintCalValues();

#endif

