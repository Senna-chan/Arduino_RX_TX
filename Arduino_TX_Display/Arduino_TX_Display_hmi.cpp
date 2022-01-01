#include "Arduino_TX_Display_hmi.cpp"
// Start UserCode : Vars

// End UserCode : Vars


HMI_Page E_PG_MAIN = HMI_Page(PAGE_TYPES::NORMAL,E_PG_MAIN,"E_PG_MAIN");
HMI_Object *hmiObjects[] = {
NULL
};

void emptyCallback(HMI_Object* obj){}

void initHMI(){
	HMI.begin();
// Start UserCode : Init

// End UserCode : Init

}
// Start UserCode : Functions

// End UserCode : Functions

