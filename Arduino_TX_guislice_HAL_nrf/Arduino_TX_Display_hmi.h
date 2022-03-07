#ifndef _HMIDISPLAY_h
#define _HMIDISPLAY_h

// Write your code between the two usercode sections to not lose your code with updates

#include <GUISlice_HMI_Lib.h>

// Start UserCode : Includes
#include "config.h"
#include "Structs.h"
// End UserCode : Includes

enum HMIPageElems{
	BasePage, E_PG_MAIN, DisplayValues, setReverse, setDefaults, calibrations, setModel, 
};
enum HMIObjElems{
	E_ELEM_BTN65, E_ELEM_TEXT267, E_ELEM_TEXT269, E_ELEM_TEXT271, E_ELEM_TEXT273, E_ELEM_TEXT275, E_ELEM_TEXT277, E_ELEM_TEXT279, 
	E_ELEM_TEXT281, E_ELEM_TEXT922, E_ELEM_TEXT923, E_ELEM_TEXT924, E_ELEM_TEXT925, E_ELEM_TEXT926, E_ELEM_TEXT927, E_ELEM_TEXT928, 
	E_ELEM_TEXT929, E_ELEM_TEXT930, E_ELEM_TEXT931, E_ELEM_TEXT952, b0, b1, b2, b3, 
	b4, b5, b6, c1, c10, c2, c3, c4, 
	c5, c6, c7, c8, c9, d1, d10, d2, 
	d3, d4, d5, d6, d7, d8, d9, deadzone0, 
	deadzonetxt, h1, h10, h2, h3, h4, h5, h6, 
	h7, h8, h9, l1, l10, l2, l3, l4, 
	l5, l6, l7, l8, l9, m0, m1, m10, 
	m11, m12, m13, m14, m15, m16, m17, m2, 
	m3, m4, m5, m6, m7, m8, m9, mn0, 
	mn1, mn2, mn3, mn4, mn5, mn6, mn7, n0, 
	n1, n10, n11, n12, n13, n14, n15, n16, 
	n17, n18, n19, n2, n20, n21, n22, n23, 
	n3, n4, n5, n6, n7, n8, n9, nBatPercent, 
	rev0, rev1, rev10, rev11, rev12, rev13, rev14, rev15, 
	rev16, rev17, rev18, rev19, rev2, rev20, rev21, rev22, 
	rev23, rev3, rev4, rev5, rev6, rev7, rev8, rev9, 
	revtxt0, revtxt1, revtxt10, revtxt11, revtxt12, revtxt13, revtxt14, revtxt15, 
	revtxt16, revtxt17, revtxt18, revtxt19, revtxt2, revtxt20, revtxt21, revtxt22, 
	revtxt23, revtxt3, revtxt4, revtxt5, revtxt6, revtxt7, revtxt8, revtxt9, 
	saveButton0, saveButton1, sdn0, sdn1, sdn10, sdn11, sdn12, sdn13, 
	sdn14, sdn15, sdn16, sdn17, sdn18, sdn19, sdn2, sdn20, 
	sdn21, sdn22, sdn23, sdn3, sdn4, sdn5, sdn6, sdn7, 
	sdn8, sdn9, sdt0, sdt1, sdt10, sdt11, sdt12, sdt13, 
	sdt14, sdt15, sdt16, sdt17, sdt18, sdt19, sdt2, sdt20, 
	sdt21, sdt22, sdt23, sdt3, sdt4, sdt5, sdt6, sdt7, 
	sdt8, sdt9, t0, t1, t10, t11, t12, t13, 
	t14, t15, t16, t17, t18, t19, t2, t20, 
	t21, t22, t23, t3, t4, t5, t6, t7, 
	t8, t9, 
};

extern HMI_Page p_BasePage;
extern HMI_Text e_nBatPercent;

extern HMI_Page p_E_PG_MAIN;
extern HMI_Button e_b0;
extern HMI_Button e_b1;
extern HMI_Button e_b2;
extern HMI_Button e_b3;
extern HMI_Button e_b5;

extern HMI_Page p_DisplayValues;
extern HMI_Text e_t0;
extern HMI_Text e_n0;
extern HMI_Text e_t1;
extern HMI_Text e_n1;
extern HMI_Text e_t2;
extern HMI_Text e_n2;
extern HMI_Text e_t3;
extern HMI_Text e_n3;
extern HMI_Text e_t4;
extern HMI_Text e_n4;
extern HMI_Text e_t5;
extern HMI_Text e_n5;
extern HMI_Text e_t6;
extern HMI_Text e_n6;
extern HMI_Text e_t7;
extern HMI_Text e_n7;
extern HMI_Text e_t8;
extern HMI_Text e_n8;
extern HMI_Text e_t9;
extern HMI_Text e_n9;
extern HMI_Text e_t10;
extern HMI_Text e_n10;
extern HMI_Text e_t11;
extern HMI_Text e_n11;
extern HMI_Text e_t12;
extern HMI_Text e_n12;
extern HMI_Text e_t13;
extern HMI_Text e_n13;
extern HMI_Text e_t14;
extern HMI_Text e_n14;
extern HMI_Text e_t15;
extern HMI_Text e_n15;
extern HMI_Text e_t16;
extern HMI_Text e_n16;
extern HMI_Text e_t17;
extern HMI_Text e_n17;
extern HMI_Text e_t18;
extern HMI_Text e_n18;
extern HMI_Text e_t19;
extern HMI_Text e_n19;
extern HMI_Text e_t20;
extern HMI_Text e_n20;
extern HMI_Text e_t21;
extern HMI_Text e_n21;
extern HMI_Text e_t22;
extern HMI_Text e_n22;
extern HMI_Text e_t23;
extern HMI_Text e_n23;
extern HMI_Button e_b4;

extern HMI_Page p_setReverse;
extern HMI_Text e_revtxt0;
extern HMI_Toggle e_rev0;
extern HMI_Text e_revtxt1;
extern HMI_Toggle e_rev1;
extern HMI_Text e_revtxt2;
extern HMI_Toggle e_rev2;
extern HMI_Text e_revtxt3;
extern HMI_Toggle e_rev3;
extern HMI_Text e_revtxt4;
extern HMI_Toggle e_rev4;
extern HMI_Text e_revtxt5;
extern HMI_Toggle e_rev5;
extern HMI_Text e_revtxt6;
extern HMI_Toggle e_rev6;
extern HMI_Text e_revtxt7;
extern HMI_Toggle e_rev7;
extern HMI_Text e_revtxt8;
extern HMI_Toggle e_rev8;
extern HMI_Text e_revtxt9;
extern HMI_Toggle e_rev9;
extern HMI_Text e_revtxt10;
extern HMI_Toggle e_rev10;
extern HMI_Text e_revtxt11;
extern HMI_Toggle e_rev11;
extern HMI_Text e_revtxt12;
extern HMI_Toggle e_rev12;
extern HMI_Text e_revtxt13;
extern HMI_Toggle e_rev13;
extern HMI_Text e_revtxt14;
extern HMI_Toggle e_rev14;
extern HMI_Text e_revtxt15;
extern HMI_Toggle e_rev15;
extern HMI_Text e_revtxt16;
extern HMI_Toggle e_rev16;
extern HMI_Text e_revtxt17;
extern HMI_Toggle e_rev17;
extern HMI_Text e_revtxt18;
extern HMI_Toggle e_rev18;
extern HMI_Text e_revtxt19;
extern HMI_Toggle e_rev19;
extern HMI_Text e_revtxt20;
extern HMI_Toggle e_rev20;
extern HMI_Text e_revtxt21;
extern HMI_Toggle e_rev21;
extern HMI_Text e_revtxt22;
extern HMI_Toggle e_rev22;
extern HMI_Text e_revtxt23;
extern HMI_Toggle e_rev23;
extern HMI_Button e_saveButton1;

extern HMI_Page p_setDefaults;
extern HMI_Text e_sdt0;
extern HMI_Text e_sdn0;
extern HMI_Text e_sdt1;
extern HMI_Text e_sdn1;
extern HMI_Text e_sdt2;
extern HMI_Text e_sdn2;
extern HMI_Text e_sdt3;
extern HMI_Text e_sdn3;
extern HMI_Text e_sdt4;
extern HMI_Text e_sdn4;
extern HMI_Text e_sdt5;
extern HMI_Text e_sdn5;
extern HMI_Text e_sdt6;
extern HMI_Text e_sdn6;
extern HMI_Text e_sdt7;
extern HMI_Text e_sdn7;
extern HMI_Text e_sdt8;
extern HMI_Text e_sdn8;
extern HMI_Text e_sdt9;
extern HMI_Text e_sdn9;
extern HMI_Text e_sdt10;
extern HMI_Text e_sdn10;
extern HMI_Text e_sdt11;
extern HMI_Text e_sdn11;
extern HMI_Text e_sdt12;
extern HMI_Text e_sdn12;
extern HMI_Text e_sdt13;
extern HMI_Text e_sdn13;
extern HMI_Text e_sdt14;
extern HMI_Text e_sdn14;
extern HMI_Text e_sdt15;
extern HMI_Text e_sdn15;
extern HMI_Text e_sdt16;
extern HMI_Text e_sdn16;
extern HMI_Text e_sdt17;
extern HMI_Text e_sdn17;
extern HMI_Text e_sdt18;
extern HMI_Text e_sdn18;
extern HMI_Text e_sdt19;
extern HMI_Text e_sdn19;
extern HMI_Text e_sdt20;
extern HMI_Text e_sdn20;
extern HMI_Text e_sdt21;
extern HMI_Text e_sdn21;
extern HMI_Text e_sdt22;
extern HMI_Text e_sdn22;
extern HMI_Text e_sdt23;
extern HMI_Text e_sdn23;
extern HMI_Button e_b6;

extern HMI_Page p_calibrations;
extern HMI_Text e_E_ELEM_TEXT922;
extern HMI_Text e_E_ELEM_TEXT923;
extern HMI_Text e_E_ELEM_TEXT924;
extern HMI_Text e_E_ELEM_TEXT925;
extern HMI_Text e_E_ELEM_TEXT926;
extern HMI_Text e_E_ELEM_TEXT927;
extern HMI_Text e_E_ELEM_TEXT928;
extern HMI_Text e_E_ELEM_TEXT929;
extern HMI_Text e_E_ELEM_TEXT930;
extern HMI_Text e_E_ELEM_TEXT931;
extern HMI_Text e_d1;
extern HMI_Text e_c1;
extern HMI_Button e_l1;
extern HMI_Button e_m1;
extern HMI_Button e_h1;
extern HMI_Text e_d2;
extern HMI_Text e_c2;
extern HMI_Button e_l2;
extern HMI_Button e_m2;
extern HMI_Button e_h2;
extern HMI_Text e_d3;
extern HMI_Text e_c3;
extern HMI_Button e_l3;
extern HMI_Button e_m3;
extern HMI_Button e_h3;
extern HMI_Text e_d4;
extern HMI_Text e_c4;
extern HMI_Button e_l4;
extern HMI_Button e_m4;
extern HMI_Button e_h4;
extern HMI_Text e_d5;
extern HMI_Text e_c5;
extern HMI_Button e_l5;
extern HMI_Button e_m5;
extern HMI_Button e_h5;
extern HMI_Text e_d6;
extern HMI_Text e_c6;
extern HMI_Button e_l6;
extern HMI_Button e_m6;
extern HMI_Button e_h6;
extern HMI_Text e_d7;
extern HMI_Text e_c7;
extern HMI_Button e_l7;
extern HMI_Button e_m7;
extern HMI_Button e_h7;
extern HMI_Text e_d8;
extern HMI_Text e_c8;
extern HMI_Button e_l8;
extern HMI_Button e_m8;
extern HMI_Button e_h8;
extern HMI_Text e_d9;
extern HMI_Text e_c9;
extern HMI_Button e_l9;
extern HMI_Button e_m9;
extern HMI_Button e_h9;
extern HMI_Text e_d10;
extern HMI_Text e_c10;
extern HMI_Button e_l10;
extern HMI_Button e_m10;
extern HMI_Button e_h10;
extern HMI_Text e_E_ELEM_TEXT952;
extern HMI_Text e_deadzonetxt;
extern HMI_Slider e_deadzone0;
extern HMI_Button e_saveButton0;

extern HMI_Page p_setModel;
extern HMI_Text e_mn0;
extern HMI_Text e_E_ELEM_TEXT267;
extern HMI_Toggle e_m0;
extern HMI_Text e_mn1;
extern HMI_Text e_E_ELEM_TEXT269;
extern HMI_Toggle e_m11;
extern HMI_Text e_mn2;
extern HMI_Text e_E_ELEM_TEXT271;
extern HMI_Toggle e_m12;
extern HMI_Text e_mn3;
extern HMI_Text e_E_ELEM_TEXT273;
extern HMI_Toggle e_m13;
extern HMI_Text e_mn4;
extern HMI_Text e_E_ELEM_TEXT275;
extern HMI_Toggle e_m14;
extern HMI_Text e_mn5;
extern HMI_Text e_E_ELEM_TEXT277;
extern HMI_Toggle e_m15;
extern HMI_Text e_mn6;
extern HMI_Text e_E_ELEM_TEXT279;
extern HMI_Toggle e_m16;
extern HMI_Text e_mn7;
extern HMI_Text e_E_ELEM_TEXT281;
extern HMI_Toggle e_m17;
extern HMI_Button e_E_ELEM_BTN65;

extern HMI_Object *hmiObjects[];

void defaultCallback(HMI_Object* obj);

void initHMI();

// Start UserCode : VarsFunctions
void doNavigation(HMI_Object* obj);
void setupMinMaxMid(HMI_Object* obj);
// End UserCode : VarsFunctions



#endif