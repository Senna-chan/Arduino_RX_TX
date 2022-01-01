#ifndef _HMIDISPLAY_h
#define _HMIDISPLAY_h

// Write your code between the two usercode sections to not lose your code with updates

#include <GUISlice_HMI.h>

// Start UserCode : Includes

// End UserCode : Includes

enum HMIElems{
	E_PG_MAIN, 

};

extern HMI_Page E_PG_MAIN;

extern HMI_Object *hmiObjects[];

void emptyCallback(HMI_Object* obj);

void initHMI();

// Start UserCode : VarsFunctions

// End UserCode : VarsFunctions



#endif