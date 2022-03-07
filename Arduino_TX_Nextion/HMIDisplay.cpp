#include "HMIDisplay.h"
#include "Vars.h"

int currentPage = 0;

void emptyCallback(void *ptr){ }

HMIPage page0 = NexPage(0, 0, "page0");
NexButton b0p0 = NexButton(0, 1, "b0");
NexButton b1p0 = NexButton(0, 2, "b1");
NexButton b2p0 = NexButton(0, 3, "b2");

NexPage page1 = NexPage(1, 0, "page1");
NexButton l0p1 = NexButton(1, 1, "l0");
NexNumber r0p1 = NexNumber(1, 2, "r0");
NexNumber t0p1 = NexNumber(1, 3, "t0");
NexHotspot m0p1 = NexHotspot(1, 4, "m0");
NexButton h0p1 = NexButton(1, 5, "h0");
NexNumber o0p1 = NexNumber(1, 6, "o0");
NexButton l1p1 = NexButton(1, 7, "l1");
NexNumber r1p1 = NexNumber(1, 8, "r1");
NexNumber t1p1 = NexNumber(1, 9, "t1");
NexHotspot m1p1 = NexHotspot(1, 10, "m1");
NexButton h1p1 = NexButton(1, 11, "h1");
NexNumber o1p1 = NexNumber(1, 12, "o1");
NexButton l2p1 = NexButton(1, 13, "l2");
NexNumber r2p1 = NexNumber(1, 14, "r2");
NexNumber t2p1 = NexNumber(1, 15, "t2");
NexHotspot m2p1 = NexHotspot(1, 16, "m2");
NexButton h2p1 = NexButton(1, 17, "h2");
NexNumber o2p1 = NexNumber(1, 18, "o2");
NexButton l3p1 = NexButton(1, 19, "l3");
NexNumber r3p1 = NexNumber(1, 20, "r3");
NexNumber t3p1 = NexNumber(1, 21, "t3");
NexHotspot m3p1 = NexHotspot(1, 22, "m3");
NexButton h3p1 = NexButton(1, 23, "h3");
NexNumber o3p1 = NexNumber(1, 24, "o3");
NexButton l4p1 = NexButton(1, 25, "l4");
NexNumber r4p1 = NexNumber(1, 26, "r4");
NexNumber t4p1 = NexNumber(1, 27, "t4");
NexHotspot m4p1 = NexHotspot(1, 28, "m4");
NexButton h4p1 = NexButton(1, 29, "h4");
NexNumber o4p1 = NexNumber(1, 30, "o4");
NexButton l5p1 = NexButton(1, 31, "l5");
NexNumber r5p1 = NexNumber(1, 32, "r5");
NexNumber t5p1 = NexNumber(1, 33, "t5");
NexHotspot m5p1 = NexHotspot(1, 34, "m5");
NexButton h5p1 = NexButton(1, 35, "h5");
NexNumber o5p1 = NexNumber(1, 36, "o5");
NexButton l6p1 = NexButton(1, 37, "l6");
NexNumber r6p1 = NexNumber(1, 38, "r6");
NexNumber t6p1 = NexNumber(1, 39, "t6");
NexHotspot m6p1 = NexHotspot(1, 40, "m6");
NexButton h6p1 = NexButton(1, 41, "h6");
NexNumber o6p1 = NexNumber(1, 42, "o6");
NexButton l7p1 = NexButton(1, 43, "l7");
NexNumber r7p1 = NexNumber(1, 44, "r7");
NexNumber t7p1 = NexNumber(1, 45, "t7");
NexHotspot m7p1 = NexHotspot(1, 46, "m7");
NexButton h7p1 = NexButton(1, 47, "h7");
NexNumber o7p1 = NexNumber(1, 48, "o7");
NexButton saveButton0p1 = NexButton(1, 49, "saveButton0");
NexSlider deadzone0p1 = NexSlider(1, 50, "deadzone0");
NexText deadzonev0p1 = NexText(1, 51, "deadzonev0");

NexPage page2 = NexPage(2, 0, "page2");
NexNumber n0p2 = NexNumber(2, 1, "n0");
NexNumber n1p2 = NexNumber(2, 2, "n1");
NexNumber n2p2 = NexNumber(2, 3, "n2");
NexNumber n3p2 = NexNumber(2, 4, "n3");
NexNumber n4p2 = NexNumber(2, 5, "n4");
NexNumber n5p2 = NexNumber(2, 6, "n5");
NexNumber n6p2 = NexNumber(2, 7, "n6");
NexNumber n7p2 = NexNumber(2, 8, "n7");
NexText t0p2 = NexText(2, 9, "t0");
NexText t1p2 = NexText(2, 10, "t1");
NexText t2p2 = NexText(2, 11, "t2");
NexText t3p2 = NexText(2, 12, "t3");
NexText t4p2 = NexText(2, 13, "t4");
NexText t5p2 = NexText(2, 14, "t5");
NexText t6p2 = NexText(2, 15, "t6");
NexText t7p2 = NexText(2, 16, "t7");
NexText t8p2 = NexText(2, 17, "t8");
NexText t9p2 = NexText(2, 18, "t9");
NexButton b0p2 = NexButton(2, 19, "b0");
NexText bools0p2 = NexText(2, 20, "bools0");

NexPage page3 = NexPage(3, 0, "page3");
NexDSButton rev0p3 = NexDSButton(3, 1, "rev0");
NexDSButton rev1p3 = NexDSButton(3, 2, "rev1");
NexDSButton rev2p3 = NexDSButton(3, 3, "rev2");
NexDSButton rev3p3 = NexDSButton(3, 4, "rev3");
NexDSButton rev4p3 = NexDSButton(3, 5, "rev4");
NexDSButton rev5p3 = NexDSButton(3, 6, "rev5");
NexDSButton rev6p3 = NexDSButton(3, 7, "rev6");
NexDSButton rev7p3 = NexDSButton(3, 8, "rev7");
NexDSButton rev8p3 = NexDSButton(3, 9, "rev8");
NexDSButton rev9p3 = NexDSButton(3, 10, "rev9");
NexDSButton rev10p3 = NexDSButton(3, 11, "rev10");
NexDSButton rev11p3 = NexDSButton(3, 12, "rev11");
NexDSButton rev12p3 = NexDSButton(3, 13, "rev12");
NexDSButton rev13p3 = NexDSButton(3, 14, "rev13");
NexDSButton rev14p3 = NexDSButton(3, 15, "rev14");
NexDSButton rev15p3 = NexDSButton(3, 16, "rev15");
NexButton saveButton0p3 = NexButton(3, 17, "saveButton0");
NexTouch *Nex_listen_list[] = {
	&page0,
	&b0p0,
	&b1p0,
	&b2p0,
	&page1,
	&l0p1,
	&r0p1,
	&t0p1,
	&m0p1,
	&h0p1,
	&o0p1,
	&l1p1,
	&r1p1,
	&t1p1,
	&m1p1,
	&h1p1,
	&o1p1,
	&l2p1,
	&r2p1,
	&t2p1,
	&m2p1,
	&h2p1,
	&o2p1,
	&l3p1,
	&r3p1,
	&t3p1,
	&m3p1,
	&h3p1,
	&o3p1,
	&l4p1,
	&r4p1,
	&t4p1,
	&m4p1,
	&h4p1,
	&o4p1,
	&l5p1,
	&r5p1,
	&t5p1,
	&m5p1,
	&h5p1,
	&o5p1,
	&l6p1,
	&r6p1,
	&t6p1,
	&m6p1,
	&h6p1,
	&o6p1,
	&l7p1,
	&r7p1,
	&t7p1,
	&m7p1,
	&h7p1,
	&o7p1,
	&saveButton0p1,
	&deadzone0p1,
	&deadzonev0p1,
	&page2,
	&n0p2,
	&n1p2,
	&n2p2,
	&n3p2,
	&n4p2,
	&n5p2,
	&n6p2,
	&n7p2,
	&t0p2,
	&t1p2,
	&t2p2,
	&t3p2,
	&t4p2,
	&t5p2,
	&t6p2,
	&t7p2,
	&t8p2,
	&t9p2,
	&b0p2,
	&bools0p2,
	&page3,
	&rev0p3,
	&rev1p3,
	&rev2p3,
	&rev3p3,
	&rev4p3,
	&rev5p3,
	&rev6p3,
	&rev7p3,
	&rev8p3,
	&rev9p3,
	&rev10p3,
	&rev11p3,
	&rev12p3,
	&rev13p3,
	&rev14p3,
	&rev15p3,
	&saveButton0p3,
	NULL
};


//region usercode
#include <eepromi2c_Anything.h>
void chCalPushEvent(void* ptr)
{
	NexTouch* obj = (NexTouch*)ptr;
	const char *objName = obj->getObjName();
	char type = objName[0];
	byte channel = (byte)objName[1] - 48; // From charNumber to real number
	uint16_t analogValue = analogRead(chPins[channel]);
	if (type == 'l')
	{
		settings.model[settings.activeModel].calibration.chMin[channel] = analogValue;
#if DEBUG
		Serial.printf("Min calibration for channel %d is %d\r\n", channel + 1, analogValue);
#endif
	}
	if (type == 'm')
	{
		settings.model[settings.activeModel].calibration.chMid[channel] = analogValue;
#if DEBUG
		Serial.printf("Mid calibration for channel %d is %d\r\n", channel + 1, analogValue);
#endif
	}
	if (type == 'h')
	{
		settings.model[settings.activeModel].calibration.chMax[channel] = analogValue;
#if DEBUG
		Serial.printf("Max calibration for channel %d is %d\r\n", channel + 1, analogValue);
#endif
	}
}

void saveButtonPushEvent(void* ptr)
{
	eeWrite(0, settings);
}

void setReverse(void* ptr)
{
	NexTouch* obj = (NexTouch*)ptr;
	const char* objName = obj->getObjName();
	char type = objName[0];
}

void setPagePushEventt(void* ptr)
{
	NexPage* page = (NexPage*)ptr;
	Serial.println(page->getObjPid());
	currentPage = page->getObjPid();
	if(currentPage == 1)
	{
		deadzonev0p1.setText(String(settings.deadzone).c_str());
		deadzone0p1.setValue(settings.deadzone);
	}
}

void deadZoneSliderRelease(void* ptr)
{
	uint32_t deadZoneValue = 0;
	deadzone0p1.getValue(&deadZoneValue);
	settings.deadzone = (uint8_t)deadZoneValue;
}

//endregion usercode

void setPagePushEvent(void *ptr)         
{                                        
	NexPage *page = (NexPage *)ptr;      
	Serial.println(page->getObjPid());   
	currentPage = page->getObjPid();     
}                                        
                                        
void InitNextion()
{
	if(!NexInit())
	{
		Serial.println("Failed to init Nextion display");
		while (1);
	}
	page0.attachPush(setPagePushEventt, &page0);
	page1.attachPush(setPagePushEventt, &page1);
	l0p1.attachPush(chCalPushEvent,&l0p1);
	m0p1.attachPush(chCalPushEvent,&m0p1);
	h0p1.attachPush(chCalPushEvent,&h0p1);
	l1p1.attachPush(chCalPushEvent,&l1p1);
	m1p1.attachPush(chCalPushEvent,&m1p1);
	h1p1.attachPush(chCalPushEvent,&h1p1);
	l2p1.attachPush(chCalPushEvent,&l2p1);
	m2p1.attachPush(chCalPushEvent,&m2p1);
	h2p1.attachPush(chCalPushEvent,&h2p1);
	l3p1.attachPush(chCalPushEvent,&l3p1);
	m3p1.attachPush(chCalPushEvent,&m3p1);
	h3p1.attachPush(chCalPushEvent,&h3p1);
	l4p1.attachPush(chCalPushEvent,&l4p1);
	m4p1.attachPush(chCalPushEvent,&m4p1);
	h4p1.attachPush(chCalPushEvent,&h4p1);
	l5p1.attachPush(chCalPushEvent,&l5p1);
	m5p1.attachPush(chCalPushEvent,&m5p1);
	h5p1.attachPush(chCalPushEvent,&h5p1);
	l6p1.attachPush(chCalPushEvent,&l6p1);
	m6p1.attachPush(chCalPushEvent,&m6p1);
	h6p1.attachPush(chCalPushEvent,&h6p1);
	l7p1.attachPush(chCalPushEvent,&l7p1);
	m7p1.attachPush(chCalPushEvent,&m7p1);
	h7p1.attachPush(chCalPushEvent,&h7p1);
	saveButton0p1.attachPush(saveButtonPushEvent,&saveButton0p1);
	deadzone0p1.attachPop(deadZoneSliderRelease,&deadzone0p1);
	page2.attachPush(setPagePushEventt, &page2);
	page3.attachPush(setPagePushEventt, &page3);
	rev0p3.attachPush(setReverse,&rev0p3);
	rev1p3.attachPush(setReverse,&rev1p3);
	rev2p3.attachPush(setReverse,&rev2p3);
	rev3p3.attachPush(setReverse,&rev3p3);
	rev4p3.attachPush(setReverse,&rev4p3);
	rev5p3.attachPush(setReverse,&rev5p3);
	rev6p3.attachPush(setReverse,&rev6p3);
	rev7p3.attachPush(setReverse,&rev7p3);
	rev8p3.attachPush(setReverse,&rev8p3);
	rev9p3.attachPush(setReverse,&rev9p3);
	rev10p3.attachPush(setReverse,&rev10p3);
	rev11p3.attachPush(setReverse,&rev11p3);
	rev12p3.attachPush(setReverse,&rev12p3);
	rev13p3.attachPush(setReverse,&rev13p3);
	rev14p3.attachPush(setReverse,&rev14p3);
	rev15p3.attachPush(setReverse,&rev15p3);
	saveButton0p3.attachPush(saveButtonPushEvent,&saveButton0p3);
}

