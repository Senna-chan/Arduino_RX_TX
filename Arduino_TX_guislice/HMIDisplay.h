#ifndef _HMIDISPLAY_h
#define _HMIDISPLAY_h

#include "GUISlice_HMI.h"

extern int currentPage;

extern HMI_Page page0;
extern HMI_Button b0p0;
extern HMI_Button b1p0;
extern HMI_Button b2p0;

extern HMI_Page page1;
extern HMI_Button l0p1;
extern HMI_Number r0p1;
extern HMI_Number t0p1;
extern HMI_Hotspot m0p1;
extern HMI_Button h0p1;
extern HMI_Number o0p1;
extern HMI_Button l1p1;
extern HMI_Number r1p1;
extern HMI_Number t1p1;
extern HMI_Hotspot m1p1;
extern HMI_Button h1p1;
extern HMI_Number o1p1;
extern HMI_Button l2p1;
extern HMI_Number r2p1;
extern HMI_Number t2p1;
extern HMI_Hotspot m2p1;
extern HMI_Button h2p1;
extern HMI_Number o2p1;
extern HMI_Button l3p1;
extern HMI_Number r3p1;
extern HMI_Number t3p1;
extern HMI_Hotspot m3p1;
extern HMI_Button h3p1;
extern HMI_Number o3p1;
extern HMI_Button l4p1;
extern HMI_Number r4p1;
extern HMI_Number t4p1;
extern HMI_Hotspot m4p1;
extern HMI_Button h4p1;
extern HMI_Number o4p1;
extern HMI_Button l5p1;
extern HMI_Number r5p1;
extern HMI_Number t5p1;
extern HMI_Hotspot m5p1;
extern HMI_Button h5p1;
extern HMI_Number o5p1;
extern HMI_Button l6p1;
extern HMI_Number r6p1;
extern HMI_Number t6p1;
extern HMI_Hotspot m6p1;
extern HMI_Button h6p1;
extern HMI_Number o6p1;
extern HMI_Button l7p1;
extern HMI_Number r7p1;
extern HMI_Number t7p1;
extern HMI_Hotspot m7p1;
extern HMI_Button h7p1;
extern HMI_Number o7p1;
extern HMI_Button saveButton0p1;
extern HMI_Slider deadzone0p1;
extern HMI_Text deadzonev0p1;

extern HMI_Page page2;
extern HMI_Number n0p2;
extern HMI_Number n1p2;
extern HMI_Number n2p2;
extern HMI_Number n3p2;
extern HMI_Number n4p2;
extern HMI_Number n5p2;
extern HMI_Number n6p2;
extern HMI_Number n7p2;
extern HMI_Text t0p2;
extern HMI_Text t1p2;
extern HMI_Text t2p2;
extern HMI_Text t3p2;
extern HMI_Text t4p2;
extern HMI_Text t5p2;
extern HMI_Text t6p2;
extern HMI_Text t7p2;
extern HMI_Text t8p2;
extern HMI_Text t9p2;
extern HMI_Button b0p2;
extern HMI_Text bools0p2;

extern HMI_Page page3;
extern HMI_DSButton rev0p3;
extern HMI_DSButton rev1p3;
extern HMI_DSButton rev2p3;
extern HMI_DSButton rev3p3;
extern HMI_DSButton rev4p3;
extern HMI_DSButton rev5p3;
extern HMI_DSButton rev6p3;
extern HMI_DSButton rev7p3;
extern HMI_DSButton rev8p3;
extern HMI_DSButton rev9p3;
extern HMI_DSButton rev10p3;
extern HMI_DSButton rev11p3;
extern HMI_DSButton rev12p3;
extern HMI_DSButton rev13p3;
extern HMI_DSButton rev14p3;
extern HMI_DSButton rev15p3;
extern HMI_Button saveButton0p3;


extern HMI_Touch *HMI__listen_list[];

void InitHMI_tion();

//region usercode

//endregion usercode
#endif
