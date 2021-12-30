#include "HMIDisplay.h"
#include "Vars.h"

int currentPage = 0;

void emptyCallback(void *ptr){ }

HMIPage page0 = HMI_Page(0, 0, "page0");
HMI_Button b0p0 = HMI_Button(0, 1, "b0");
HMI_Button b1p0 = HMI_Button(0, 2, "b1");
HMI_Button b2p0 = HMI_Button(0, 3, "b2");

HMI_Page page1 = HMI_Page(1, 0, "page1");
HMI_Button l0p1 = HMI_Button(1, 1, "l0");
HMI_Number r0p1 = HMI_Number(1, 2, "r0");
HMI_Number t0p1 = HMI_Number(1, 3, "t0");
HMI_Hotspot m0p1 = HMI_Hotspot(1, 4, "m0");
HMI_Button h0p1 = HMI_Button(1, 5, "h0");
HMI_Number o0p1 = HMI_Number(1, 6, "o0");
HMI_Button l1p1 = HMI_Button(1, 7, "l1");
HMI_Number r1p1 = HMI_Number(1, 8, "r1");
HMI_Number t1p1 = HMI_Number(1, 9, "t1");
HMI_Hotspot m1p1 = HMI_Hotspot(1, 10, "m1");
HMI_Button h1p1 = HMI_Button(1, 11, "h1");
HMI_Number o1p1 = HMI_Number(1, 12, "o1");
HMI_Button l2p1 = HMI_Button(1, 13, "l2");
HMI_Number r2p1 = HMI_Number(1, 14, "r2");
HMI_Number t2p1 = HMI_Number(1, 15, "t2");
HMI_Hotspot m2p1 = HMI_Hotspot(1, 16, "m2");
HMI_Button h2p1 = HMI_Button(1, 17, "h2");
HMI_Number o2p1 = HMI_Number(1, 18, "o2");
HMI_Button l3p1 = HMI_Button(1, 19, "l3");
HMI_Number r3p1 = HMI_Number(1, 20, "r3");
HMI_Number t3p1 = HMI_Number(1, 21, "t3");
HMI_Hotspot m3p1 = HMI_Hotspot(1, 22, "m3");
HMI_Button h3p1 = HMI_Button(1, 23, "h3");
HMI_Number o3p1 = HMI_Number(1, 24, "o3");
HMI_Button l4p1 = HMI_Button(1, 25, "l4");
HMI_Number r4p1 = HMI_Number(1, 26, "r4");
HMI_Number t4p1 = HMI_Number(1, 27, "t4");
HMI_Hotspot m4p1 = HMI_Hotspot(1, 28, "m4");
HMI_Button h4p1 = HMI_Button(1, 29, "h4");
HMI_Number o4p1 = HMI_Number(1, 30, "o4");
HMI_Button l5p1 = HMI_Button(1, 31, "l5");
HMI_Number r5p1 = HMI_Number(1, 32, "r5");
HMI_Number t5p1 = HMI_Number(1, 33, "t5");
HMI_Hotspot m5p1 = HMI_Hotspot(1, 34, "m5");
HMI_Button h5p1 = HMI_Button(1, 35, "h5");
HMI_Number o5p1 = HMI_Number(1, 36, "o5");
HMI_Button l6p1 = HMI_Button(1, 37, "l6");
HMI_Number r6p1 = HMI_Number(1, 38, "r6");
HMI_Number t6p1 = HMI_Number(1, 39, "t6");
HMI_Hotspot m6p1 = HMI_Hotspot(1, 40, "m6");
HMI_Button h6p1 = HMI_Button(1, 41, "h6");
HMI_Number o6p1 = HMI_Number(1, 42, "o6");
HMI_Button l7p1 = HMI_Button(1, 43, "l7");
HMI_Number r7p1 = HMI_Number(1, 44, "r7");
HMI_Number t7p1 = HMI_Number(1, 45, "t7");
HMI_Hotspot m7p1 = HMI_Hotspot(1, 46, "m7");
HMI_Button h7p1 = HMI_Button(1, 47, "h7");
HMI_Number o7p1 = HMI_Number(1, 48, "o7");
HMI_Button saveButton0p1 = HMI_Button(1, 49, "saveButton0");
HMI_Slider deadzone0p1 = HMI_Slider(1, 50, "deadzone0");
HMI_Text deadzonev0p1 = HMI_Text(1, 51, "deadzonev0");

HMI_Page page2 = HMI_Page(2, 0, "page2");
HMI_Number n0p2 = HMI_Number(2, 1, "n0");
HMI_Number n1p2 = HMI_Number(2, 2, "n1");
HMI_Number n2p2 = HMI_Number(2, 3, "n2");
HMI_Number n3p2 = HMI_Number(2, 4, "n3");
HMI_Number n4p2 = HMI_Number(2, 5, "n4");
HMI_Number n5p2 = HMI_Number(2, 6, "n5");
HMI_Number n6p2 = HMI_Number(2, 7, "n6");
HMI_Number n7p2 = HMI_Number(2, 8, "n7");
HMI_Text t0p2 = HMI_Text(2, 9, "t0");
HMI_Text t1p2 = HMI_Text(2, 10, "t1");
HMI_Text t2p2 = HMI_Text(2, 11, "t2");
HMI_Text t3p2 = HMI_Text(2, 12, "t3");
HMI_Text t4p2 = HMI_Text(2, 13, "t4");
HMI_Text t5p2 = HMI_Text(2, 14, "t5");
HMI_Text t6p2 = HMI_Text(2, 15, "t6");
HMI_Text t7p2 = HMI_Text(2, 16, "t7");
HMI_Text t8p2 = HMI_Text(2, 17, "t8");
HMI_Text t9p2 = HMI_Text(2, 18, "t9");
HMI_Button b0p2 = HMI_Button(2, 19, "b0");
HMI_Text bools0p2 = HMI_Text(2, 20, "bools0");

HMI_Page page3 = HMI_Page(3, 0, "page3");
HMI_DSButton rev0p3 = HMI_DSButton(3, 1, "rev0");
HMI_DSButton rev1p3 = HMI_DSButton(3, 2, "rev1");
HMI_DSButton rev2p3 = HMI_DSButton(3, 3, "rev2");
HMI_DSButton rev3p3 = HMI_DSButton(3, 4, "rev3");
HMI_DSButton rev4p3 = HMI_DSButton(3, 5, "rev4");
HMI_DSButton rev5p3 = HMI_DSButton(3, 6, "rev5");
HMI_DSButton rev6p3 = HMI_DSButton(3, 7, "rev6");
HMI_DSButton rev7p3 = HMI_DSButton(3, 8, "rev7");
HMI_DSButton rev8p3 = HMI_DSButton(3, 9, "rev8");
HMI_DSButton rev9p3 = HMI_DSButton(3, 10, "rev9");
HMI_DSButton rev10p3 = HMI_DSButton(3, 11, "rev10");
HMI_DSButton rev11p3 = HMI_DSButton(3, 12, "rev11");
HMI_DSButton rev12p3 = HMI_DSButton(3, 13, "rev12");
HMI_DSButton rev13p3 = HMI_DSButton(3, 14, "rev13");
HMI_DSButton rev14p3 = HMI_DSButton(3, 15, "rev14");
HMI_DSButton rev15p3 = HMI_DSButton(3, 16, "rev15");
HMI_Button saveButton0p3 = HMI_Button(3, 17, "saveButton0");
HMI_Touch *HMI__listen_list[] = {
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
	HMI_Touch* obj = (HMI_Touch*)ptr;
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
	HMI_Touch* obj = (HMI_Touch*)ptr;
	const char* objName = obj->getObjName();
	char type = objName[0];
}

void setPagePushEventt(void* ptr)
{
	HMI_Page* page = (HMI_Page*)ptr;
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
	HMI_Page *page = (HMI_Page *)ptr;      
	Serial.println(page->getObjPid());   
	currentPage = page->getObjPid();     
}                                        
                                        
void InitGUISlice()
{
	if(!HMI_Init())
	{
		Serial.println("Failed to init HMI_tion display");
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

