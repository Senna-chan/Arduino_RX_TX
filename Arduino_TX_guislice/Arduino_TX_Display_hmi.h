#ifndef _HMIDISPLAY_h
#define _HMIDISPLAY_h

// Write your code between the two usercode sections to not lose your code with updates

#include <GUISlice_HMI_Lib.h>

// Start UserCode : Includes
#include "config.h"
// End UserCode : Includes

enum HMIElems{
	BasePage, 
	nBatPercent, 
	E_PG_MAIN, 
	b0, b1, b2, b3, b5, 
	calibrations, 
	E_ELEM_TEXT922, E_ELEM_TEXT923, E_ELEM_TEXT924, E_ELEM_TEXT925, E_ELEM_TEXT926, E_ELEM_TEXT927, E_ELEM_TEXT928, E_ELEM_TEXT929, 
	E_ELEM_TEXT930, E_ELEM_TEXT931, d1, l1, m1, h1, d2, l2, 
	m2, h2, d3, l3, m3, h3, d4, l4, 
	m4, h4, d5, l5, m5, h5, d6, l6, 
	m6, h6, d7, l7, m7, h7, d8, l8, 
	m8, h8, d9, l9, m9, h9, d10, l10, 
	m10, h10, E_ELEM_TEXT952, deadzonetxt, deadzone0, saveButton0, 
	DisplayValues, 
	t0, n0, t1, n1, t2, n2, t3, n3, 
	t4, n4, t5, n5, t6, n6, t7, n7, 
	t8, n8, t9, n9, t10, n10, t11, n11, 
	t12, n12, t13, n13, t14, n14, t15, n15, 
	t16, n16, t17, n17, t18, n18, t19, n19, 
	t20, n20, t21, n21, t22, n22, t23, n23, 
	b4, 
	setReverse, 
	revtxt0, rev0, revtxt1, rev1, revtxt2, rev2, revtxt3, rev3, 
	revtxt4, rev4, revtxt5, rev5, revtxt6, rev6, revtxt7, rev7, 
	revtxt8, rev8, revtxt9, rev9, revtxt10, rev10, revtxt11, rev11, 
	revtxt12, rev12, revtxt13, rev13, revtxt14, rev14, revtxt15, rev15, 
	revtxt16, rev16, revtxt17, rev17, revtxt18, rev18, revtxt19, rev19, 
	revtxt20, rev20, revtxt21, rev21, revtxt22, rev22, revtxt23, rev23, 
	saveButton1, 
	setDefaults, 
	sdt0, sdn0, sdt1, sdn1, sdt2, sdn2, sdt3, sdn3, 
	sdt4, sdn4, sdt5, sdn5, sdt6, sdn6, sdt7, sdn7, 
	sdt8, sdn8, sdt9, sdn9, sdt10, sdn10, sdt11, sdn11, 
	sdt12, sdn12, sdt13, sdn13, sdt14, sdn14, sdt15, sdn15, 
	sdt16, sdn16, sdt17, sdn17, sdt18, sdn18, sdt19, sdn19, 
	sdt20, sdn20, sdt21, sdn21, sdt22, sdn22, sdt23, sdn23, 
	b6, 
};

extern HMI_Page p_BasePage;
extern HMI_Text e_nBatPercent;

extern HMI_Page p_E_PG_MAIN;
extern HMI_Button e_b0;
extern HMI_Button e_b1;
extern HMI_Button e_b2;
extern HMI_Button e_b3;
extern HMI_Button e_b5;

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
extern HMI_Button e_l1;
extern HMI_Button e_m1;
extern HMI_Button e_h1;
extern HMI_Text e_d2;
extern HMI_Button e_l2;
extern HMI_Button e_m2;
extern HMI_Button e_h2;
extern HMI_Text e_d3;
extern HMI_Button e_l3;
extern HMI_Button e_m3;
extern HMI_Button e_h3;
extern HMI_Text e_d4;
extern HMI_Button e_l4;
extern HMI_Button e_m4;
extern HMI_Button e_h4;
extern HMI_Text e_d5;
extern HMI_Button e_l5;
extern HMI_Button e_m5;
extern HMI_Button e_h5;
extern HMI_Text e_d6;
extern HMI_Button e_l6;
extern HMI_Button e_m6;
extern HMI_Button e_h6;
extern HMI_Text e_d7;
extern HMI_Button e_l7;
extern HMI_Button e_m7;
extern HMI_Button e_h7;
extern HMI_Text e_d8;
extern HMI_Button e_l8;
extern HMI_Button e_m8;
extern HMI_Button e_h8;
extern HMI_Text e_d9;
extern HMI_Button e_l9;
extern HMI_Button e_m9;
extern HMI_Button e_h9;
extern HMI_Text e_d10;
extern HMI_Button e_l10;
extern HMI_Button e_m10;
extern HMI_Button e_h10;
extern HMI_Text e_E_ELEM_TEXT952;
extern HMI_Text e_deadzonetxt;
extern HMI_Button e_saveButton0;

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

extern HMI_Object *hmiObjects[];

void defaultCallback(HMI_Object* obj);

void initHMI();

// Start UserCode : VarsFunctions

// End UserCode : VarsFunctions



#endif