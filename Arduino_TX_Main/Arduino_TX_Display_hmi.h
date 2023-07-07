#ifndef _HMIDISPLAY_h
#define _HMIDISPLAY_h

// Write your code between the two usercode sections to not lose your code with updates

#include <GUISlice_HMI_Lib.h>

// Start UserCode : Includes
#include "SharedVars.h"
#include "config.h"
#include "Structs.h"
#include <MyHelpers.h>
#include "settingsHelper.h"
// End UserCode : Includes

enum HMIPageElems{
	BasePage, E_PG_MAIN, calibrations, DisplayRawValues, DisplayRcValues, channelSettings, setupChannel, setupOutputPWM, setupOutputStepper, setupOutputNotNeeded, setModel, transmittingSettings, E_POP_KEYPAD_NUM, 
};
enum HMIObjElems{
	E_ELEM_BTN279, E_ELEM_BTN65, E_ELEM_TEXT305, E_ELEM_TEXT307, E_ELEM_TEXT309, E_ELEM_TEXT312, E_ELEM_TEXT330, E_ELEM_TEXT332, 
	E_ELEM_TEXT667, E_ELEM_TEXT669, E_ELEM_TEXT670, E_ELEM_TEXT674, E_ELEM_TEXT675, E_ELEM_TEXT676, E_ELEM_TEXT729, E_ELEM_TEXT730, 
	E_ELEM_TEXT731, E_ELEM_TEXT732, E_ELEM_TEXT733, E_ELEM_TEXT734, E_ELEM_TEXT735, E_ELEM_TEXT736, E_ELEM_TEXT745, E_ELEM_TEXT746, 
	E_ELEM_TEXT748, E_ELEM_TEXT749, E_ELEM_TEXT750, E_ELEM_TEXT751, E_ELEM_TEXT752, E_ELEM_TEXT753, E_ELEM_TEXT754, E_ELEM_TEXT755, 
	E_ELEM_TEXT756, E_ELEM_TEXT757, E_ELEM_TEXT758, E_ELEM_TEXT759, E_ELEM_TEXT760, E_ELEM_TEXT761, E_ELEM_TEXT762, E_ELEM_TEXT763, 
	E_ELEM_TEXT765, E_ELEM_TEXT766, E_ELEM_TEXT767, E_ELEM_TEXT768, E_ELEM_TEXT769, E_ELEM_TEXT770, E_ELEM_TEXT771, E_ELEM_TEXT772, 
	E_ELEM_TEXT773, E_ELEM_TEXT774, E_ELEM_TEXT775, E_ELEM_TEXT776, E_ELEM_TEXT777, E_ELEM_TEXT778, E_ELEM_TEXT779, E_ELEM_TEXT780, 
	E_ELEM_TEXT781, E_ELEM_TEXT782, E_ELEM_TEXT783, E_ELEM_TEXT784, E_ELEM_TEXT785, E_ELEM_TEXT786, E_ELEM_TEXT787, E_ELEM_TEXT788, 
	E_ELEM_TEXT789, E_ELEM_TEXT790, E_ELEM_TEXT791, E_ELEM_TEXT792, E_ELEM_TEXT793, E_ELEM_TEXT794, E_ELEM_TEXT795, E_ELEM_TEXT796, 
	E_ELEM_TEXT797, E_ELEM_TEXT798, E_ELEM_TEXT799, E_ELEM_TEXT800, E_ELEM_TEXT801, E_ELEM_TEXT802, E_ELEM_TEXT803, E_ELEM_TEXT804, 
	E_ELEM_TEXT805, E_ELEM_TEXT922, E_ELEM_TEXT923, E_ELEM_TEXT924, E_ELEM_TEXT925, E_ELEM_TEXT926, E_ELEM_TEXT927, E_ELEM_TEXT928, 
	E_ELEM_TEXT929, E_ELEM_TEXT930, E_ELEM_TEXT931, E_ELEM_TEXT952, b0, b1, b2, b3, 
	b4, b5, backbtncal, backbtnchconf, backbtnchs, backbtnchsandsendstorx, backbtnsetupNotNeeded, backbtnsetupPWM, 
	backbtnsetupStepper, c1, c10, c2, c3, c4, c5, c6, 
	c7, c8, c9, channelname, channelval, configuredIO1, configuredIO2, d1, 
	d10, d2, d3, d4, d5, d6, d7, d8, 
	d9, dcurio, deadzone0, deadzonetxt, defaultval, detectIO1, detectIO2, dprevio, 
	drbackbtn, h1, h10, h2, h3, h4, h5, h6, 
	h7, h8, h9, l1, l10, l2, l3, l4, 
	l5, l6, l7, l8, l9, lsbChannelOutputType, m1, m10, 
	m2, m3, m4, m5, m6, m7, m8, m9, 
	n0, n1, n10, n11, n12, n13, n14, n15, 
	n16, n17, n18, n19, n2, n20, n21, n22, 
	n23, n3, n4, n5, n6, n7, n8, n9, 
	nBatPercent, nr0, nr1, nr2, nr3, nr4, nr5, nr6, 
	nr7, nr8, nr9, pwmCenterZero, pwmFreq, reverse, reversetxt, savebtncal, 
	savebtnchconf, setch1, setch10, setch11, setch12, setch13, setch14, setch15, 
	setch16, setch17, setch18, setch19, setch2, setch20, setch21, setch22, 
	setch23, setch24, setch3, setch4, setch5, setch6, setch7, setch8, 
	setch9, settingstxtorxprogress, sm0, sm1, sm2, sm3, sm4, sm5, 
	sm6, sm7, stepMaxFreq, stepMinFreq, t0, t1, t10, t11, 
	t12, t13, t14, t15, t16, t17, t18, t19, 
	t2, t20, t21, t22, t23, t3, t4, t5, 
	t6, t7, t8, t9, tr0, tr1, tr2, tr3, 
	tr4, tr5, tr6, tr7, tr8, tr9, E_ELEM_KEYPAD_NUM, 
};

extern HMI_Page p_BasePage;
extern HMI_Text e_nBatPercent;

extern HMI_Page p_E_PG_MAIN;
extern HMI_Button e_b0;
extern HMI_Button e_b1;
extern HMI_Button e_b2;
extern HMI_Button e_b3;
extern HMI_Button e_b4;

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
extern HMI_Button e_backbtncal;
extern HMI_Button e_savebtncal;

extern HMI_Page p_DisplayRawValues;
extern HMI_Text e_tr0;
extern HMI_Text e_nr0;
extern HMI_Text e_tr1;
extern HMI_Text e_nr1;
extern HMI_Text e_tr2;
extern HMI_Text e_nr2;
extern HMI_Text e_tr3;
extern HMI_Text e_nr3;
extern HMI_Text e_tr4;
extern HMI_Text e_nr4;
extern HMI_Text e_tr5;
extern HMI_Text e_nr5;
extern HMI_Text e_tr6;
extern HMI_Text e_nr6;
extern HMI_Text e_tr7;
extern HMI_Text e_nr7;
extern HMI_Text e_tr8;
extern HMI_Text e_nr8;
extern HMI_Text e_tr9;
extern HMI_Text e_nr9;
extern HMI_Text e_E_ELEM_TEXT332;
extern HMI_Text e_dprevio;
extern HMI_Text e_E_ELEM_TEXT330;
extern HMI_Text e_dcurio;
extern HMI_Button e_drbackbtn;

extern HMI_Page p_DisplayRcValues;
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
extern HMI_Button e_b5;

extern HMI_Page p_channelSettings;
extern HMI_Button e_setch1;
extern HMI_Button e_setch2;
extern HMI_Button e_setch3;
extern HMI_Button e_setch4;
extern HMI_Button e_setch5;
extern HMI_Button e_setch6;
extern HMI_Button e_setch7;
extern HMI_Button e_setch8;
extern HMI_Button e_setch9;
extern HMI_Button e_setch10;
extern HMI_Button e_setch11;
extern HMI_Button e_setch12;
extern HMI_Button e_setch13;
extern HMI_Button e_setch14;
extern HMI_Button e_setch15;
extern HMI_Button e_setch16;
extern HMI_Button e_setch17;
extern HMI_Button e_setch18;
extern HMI_Button e_setch19;
extern HMI_Button e_setch20;
extern HMI_Button e_setch21;
extern HMI_Button e_setch22;
extern HMI_Button e_setch23;
extern HMI_Button e_setch24;
extern HMI_Button e_backbtnchs;
extern HMI_Button e_backbtnchsandsendstorx;

extern HMI_Page p_setupChannel;
extern HMI_Text e_channelname;
extern HMI_Text e_E_ELEM_TEXT312;
extern HMI_Text e_channelval;
extern HMI_Text e_reversetxt;
extern HMI_Toggle e_reverse;
extern HMI_Button e_detectIO1;
extern HMI_Button e_detectIO2;
extern HMI_Text e_E_ELEM_TEXT305;
extern HMI_Text e_configuredIO1;
extern HMI_Text e_E_ELEM_TEXT307;
extern HMI_Text e_configuredIO2;
extern HMI_Text e_E_ELEM_TEXT309;
extern HMI_Text e_defaultval;
extern HMI_Button e_savebtnchconf;
extern HMI_Button e_backbtnchconf;
extern HMI_Listbox e_lsbChannelOutputType;
extern HMI_Button e_E_ELEM_BTN279;
extern HMI_Text e_E_ELEM_TEXT797;
extern HMI_Toggle e_pwmCenterZero;

extern HMI_Page p_setupOutputPWM;
extern HMI_Text e_E_ELEM_TEXT674;
extern HMI_Text e_E_ELEM_TEXT667;
extern HMI_Text e_pwmFreq;
extern HMI_Button e_backbtnsetupPWM;

extern HMI_Page p_setupOutputStepper;
extern HMI_Text e_E_ELEM_TEXT675;
extern HMI_Text e_E_ELEM_TEXT669;
extern HMI_Text e_stepMinFreq;
extern HMI_Text e_E_ELEM_TEXT670;
extern HMI_Text e_stepMaxFreq;
extern HMI_Button e_backbtnsetupStepper;

extern HMI_Page p_setupOutputNotNeeded;
extern HMI_Text e_E_ELEM_TEXT676;
extern HMI_Button e_backbtnsetupNotNeeded;

extern HMI_Page p_setModel;
extern HMI_Text e_E_ELEM_TEXT729;
extern HMI_Toggle e_sm0;
extern HMI_Text e_E_ELEM_TEXT730;
extern HMI_Toggle e_sm1;
extern HMI_Text e_E_ELEM_TEXT731;
extern HMI_Toggle e_sm2;
extern HMI_Text e_E_ELEM_TEXT732;
extern HMI_Toggle e_sm3;
extern HMI_Text e_E_ELEM_TEXT733;
extern HMI_Toggle e_sm4;
extern HMI_Text e_E_ELEM_TEXT734;
extern HMI_Toggle e_sm5;
extern HMI_Text e_E_ELEM_TEXT735;
extern HMI_Toggle e_sm6;
extern HMI_Text e_E_ELEM_TEXT736;
extern HMI_Toggle e_sm7;
extern HMI_Button e_E_ELEM_BTN65;
extern HMI_Text e_E_ELEM_TEXT748;
extern HMI_Text e_E_ELEM_TEXT749;
extern HMI_Text e_E_ELEM_TEXT750;
extern HMI_Text e_E_ELEM_TEXT751;
extern HMI_Text e_E_ELEM_TEXT752;
extern HMI_Text e_E_ELEM_TEXT753;
extern HMI_Text e_E_ELEM_TEXT754;
extern HMI_Text e_E_ELEM_TEXT755;
extern HMI_Text e_E_ELEM_TEXT756;
extern HMI_Text e_E_ELEM_TEXT757;
extern HMI_Text e_E_ELEM_TEXT758;
extern HMI_Text e_E_ELEM_TEXT759;
extern HMI_Text e_E_ELEM_TEXT760;
extern HMI_Text e_E_ELEM_TEXT761;
extern HMI_Text e_E_ELEM_TEXT762;
extern HMI_Text e_E_ELEM_TEXT763;
extern HMI_Text e_E_ELEM_TEXT765;
extern HMI_Text e_E_ELEM_TEXT766;
extern HMI_Text e_E_ELEM_TEXT767;
extern HMI_Text e_E_ELEM_TEXT768;
extern HMI_Text e_E_ELEM_TEXT769;
extern HMI_Text e_E_ELEM_TEXT770;
extern HMI_Text e_E_ELEM_TEXT771;
extern HMI_Text e_E_ELEM_TEXT772;
extern HMI_Text e_E_ELEM_TEXT773;
extern HMI_Text e_E_ELEM_TEXT774;
extern HMI_Text e_E_ELEM_TEXT775;
extern HMI_Text e_E_ELEM_TEXT776;
extern HMI_Text e_E_ELEM_TEXT777;
extern HMI_Text e_E_ELEM_TEXT778;
extern HMI_Text e_E_ELEM_TEXT779;
extern HMI_Text e_E_ELEM_TEXT780;
extern HMI_Text e_E_ELEM_TEXT781;
extern HMI_Text e_E_ELEM_TEXT782;
extern HMI_Text e_E_ELEM_TEXT783;
extern HMI_Text e_E_ELEM_TEXT784;
extern HMI_Text e_E_ELEM_TEXT785;
extern HMI_Text e_E_ELEM_TEXT786;
extern HMI_Text e_E_ELEM_TEXT787;
extern HMI_Text e_E_ELEM_TEXT788;
extern HMI_Text e_E_ELEM_TEXT789;
extern HMI_Text e_E_ELEM_TEXT790;
extern HMI_Text e_E_ELEM_TEXT791;
extern HMI_Text e_E_ELEM_TEXT792;
extern HMI_Text e_E_ELEM_TEXT793;
extern HMI_Text e_E_ELEM_TEXT794;
extern HMI_Text e_E_ELEM_TEXT795;
extern HMI_Text e_E_ELEM_TEXT796;
extern HMI_Text e_E_ELEM_TEXT798;
extern HMI_Text e_E_ELEM_TEXT799;
extern HMI_Text e_E_ELEM_TEXT800;
extern HMI_Text e_E_ELEM_TEXT801;
extern HMI_Text e_E_ELEM_TEXT802;
extern HMI_Text e_E_ELEM_TEXT803;
extern HMI_Text e_E_ELEM_TEXT804;
extern HMI_Text e_E_ELEM_TEXT805;

extern HMI_Page p_transmittingSettings;
extern HMI_Text e_E_ELEM_TEXT745;
extern HMI_Text e_E_ELEM_TEXT746;
extern HMI_Text e_settingstxtorxprogress;

extern HMI_Object *hmiObjects[];

void defaultCallback(HMI_Object* obj);

void initHMI();

// Start UserCode : VarsFunctions
void transmitSettingsToRX(); // Defined in main ino


void emptyCallback(HMI_Object* obj);
extern s_channelMapping detectedIO1;
extern s_channelMapping detectedIO2;

extern int8_t detectingIO;
extern int8_t channelToEditIdx;
extern int8_t channelToEdit;
void doDetectIO1(HMI_Object* obj);
void doDetectIO2(HMI_Object* obj);

void listboxChanged(HMI_Object* obj);

void doNavigation(HMI_Object* obj);
void navigateToChannelEditor();
void setupMinMaxMid(HMI_Object* obj);
void setupStepper(HMI_Object* obj);
void setupPWM(HMI_Object* obj);

// End UserCode : VarsFunctions



#endif