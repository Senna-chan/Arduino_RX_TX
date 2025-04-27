// settingsHelper.h

#ifndef _SETTINGSHELPER_h
#define _SETTINGSHELPER_h

#include "../SharedCode/Config.h"

#include "Structs.h"
#include <main.h>

bool readSettings();
void saveSettings();

void generateDefaultSettings();
void loadSettings(bool forceReset = false);
void PrintCalValues();

#endif

