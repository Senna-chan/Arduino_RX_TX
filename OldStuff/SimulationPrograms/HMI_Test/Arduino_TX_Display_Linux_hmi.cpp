#include "Arduino_TX_Display_Linux_hmi.h"
// Start UserCode : Vars

s_channelMapping detectedIO1;
s_channelMapping detectedIO2;
//HardwareSerial HMISerial = HardwareSerial(PC11, PC10);
HardwareSerial HMISerial = HardwareSerial(PD6,PD5);
int8_t detectingIO = 0;
int8_t channelToEditIdx = -1;
int8_t channelToEdit = -1;

HMI_Button* chEditButtons[RC_MAX_CHANNELS]{
	&e_setch1 ,
	&e_setch2 ,
	&e_setch3 ,
	&e_setch4 ,
	&e_setch5 ,
	&e_setch6 ,
	&e_setch7 ,
	&e_setch8 ,
	&e_setch9 ,
	&e_setch10,
	&e_setch11,
	&e_setch12,
	&e_setch13,
	&e_setch14,
	&e_setch15,
	&e_setch16,
	&e_setch17,
	&e_setch18,
	&e_setch19,
	&e_setch20,
	&e_setch21,
	&e_setch22,
	&e_setch23,
	&e_setch24,
};

// WHY HERE!
#define RCIO		((1 << OUTPUTMODE_RC) | (1 << OUTPUTMODE_IO))
#define RCIODAC		((1 << OUTPUTMODE_RC) | (1 << OUTPUTMODE_IO) | (1 << OUTPUTMODE_DAC))
#define RCIOPWM		((1 << OUTPUTMODE_RC) | (1 << OUTPUTMODE_IO) | (1 << OUTPUTMODE_PWM))
#define RCIOPWMSTEP	((1 << OUTPUTMODE_RC) | (1 << OUTPUTMODE_IO) | (1 << OUTPUTMODE_PWM) | (1 << OUTPUTMODE_STEP))

// Output options for the channels
uint8_t channelOutputOptions[RC_MAX_CHANNELS] = {
	RCIOPWM, // CH1
	RCIOPWM, // CH2
	RCIO,
	RCIO,
	RCIODAC,
	RCIODAC,
	RCIO,
	RCIOPWMSTEP,
	RCIOPWMSTEP,
	RCIOPWMSTEP,
	RCIOPWMSTEP,
	RCIO,
	RCIO,
	RCIO,
	RCIO,
	RCIOPWMSTEP,
	RCIOPWMSTEP,
	0,
	0,
	0,
	0,
	0,
	0,
	0
};
// end why here


// End UserCode : Vars


HMI_Page p_BasePage = HMI_Page(PAGE_TYPES::BASEPAGE, BasePage,"BasePage");
HMI_Text e_nBatPercent = HMI_Text(nBatPercent,"nBatPercent");
HMI_Button e_BTN_Quit = HMI_Button(BTN_Quit,"BTN_Quit");

HMI_Page p_E_PG_MAIN = HMI_Page(PAGE_TYPES::NORMAL, E_PG_MAIN,"E_PG_MAIN");
HMI_Button e_navRC = HMI_Button(navRC,"navRC");
HMI_Button e_navRAW = HMI_Button(navRAW,"navRAW");
HMI_Button e_navSETADC = HMI_Button(navSETADC,"navSETADC");
HMI_Button e_navSETCH = HMI_Button(navSETCH,"navSETCH");
HMI_Button e_navMODEL = HMI_Button(navMODEL,"navMODEL");

HMI_Page p_calibrations = HMI_Page(PAGE_TYPES::NORMAL, calibrations,"calibrations");
HMI_Text e_E_ELEM_TEXT922 = HMI_Text(E_ELEM_TEXT922,"E_ELEM_TEXT922");
HMI_Text e_E_ELEM_TEXT923 = HMI_Text(E_ELEM_TEXT923,"E_ELEM_TEXT923");
HMI_Text e_E_ELEM_TEXT924 = HMI_Text(E_ELEM_TEXT924,"E_ELEM_TEXT924");
HMI_Text e_E_ELEM_TEXT925 = HMI_Text(E_ELEM_TEXT925,"E_ELEM_TEXT925");
HMI_Text e_E_ELEM_TEXT926 = HMI_Text(E_ELEM_TEXT926,"E_ELEM_TEXT926");
HMI_Text e_E_ELEM_TEXT927 = HMI_Text(E_ELEM_TEXT927,"E_ELEM_TEXT927");
HMI_Text e_E_ELEM_TEXT928 = HMI_Text(E_ELEM_TEXT928,"E_ELEM_TEXT928");
HMI_Text e_E_ELEM_TEXT929 = HMI_Text(E_ELEM_TEXT929,"E_ELEM_TEXT929");
HMI_Text e_E_ELEM_TEXT930 = HMI_Text(E_ELEM_TEXT930,"E_ELEM_TEXT930");
HMI_Text e_E_ELEM_TEXT931 = HMI_Text(E_ELEM_TEXT931,"E_ELEM_TEXT931");
HMI_Text e_d1 = HMI_Text(d1,"d1");
HMI_Text e_c1 = HMI_Text(c1,"c1");
HMI_Button e_l1 = HMI_Button(l1,"l1");
HMI_Button e_m1 = HMI_Button(m1,"m1");
HMI_Button e_h1 = HMI_Button(h1,"h1");
HMI_Text e_d2 = HMI_Text(d2,"d2");
HMI_Text e_c2 = HMI_Text(c2,"c2");
HMI_Button e_l2 = HMI_Button(l2,"l2");
HMI_Button e_m2 = HMI_Button(m2,"m2");
HMI_Button e_h2 = HMI_Button(h2,"h2");
HMI_Text e_d3 = HMI_Text(d3,"d3");
HMI_Text e_c3 = HMI_Text(c3,"c3");
HMI_Button e_l3 = HMI_Button(l3,"l3");
HMI_Button e_m3 = HMI_Button(m3,"m3");
HMI_Button e_h3 = HMI_Button(h3,"h3");
HMI_Text e_d4 = HMI_Text(d4,"d4");
HMI_Text e_c4 = HMI_Text(c4,"c4");
HMI_Button e_l4 = HMI_Button(l4,"l4");
HMI_Button e_m4 = HMI_Button(m4,"m4");
HMI_Button e_h4 = HMI_Button(h4,"h4");
HMI_Text e_d5 = HMI_Text(d5,"d5");
HMI_Text e_c5 = HMI_Text(c5,"c5");
HMI_Button e_l5 = HMI_Button(l5,"l5");
HMI_Button e_m5 = HMI_Button(m5,"m5");
HMI_Button e_h5 = HMI_Button(h5,"h5");
HMI_Text e_d6 = HMI_Text(d6,"d6");
HMI_Text e_c6 = HMI_Text(c6,"c6");
HMI_Button e_l6 = HMI_Button(l6,"l6");
HMI_Button e_m6 = HMI_Button(m6,"m6");
HMI_Button e_h6 = HMI_Button(h6,"h6");
HMI_Text e_d7 = HMI_Text(d7,"d7");
HMI_Text e_c7 = HMI_Text(c7,"c7");
HMI_Button e_l7 = HMI_Button(l7,"l7");
HMI_Button e_m7 = HMI_Button(m7,"m7");
HMI_Button e_h7 = HMI_Button(h7,"h7");
HMI_Text e_d8 = HMI_Text(d8,"d8");
HMI_Text e_c8 = HMI_Text(c8,"c8");
HMI_Button e_l8 = HMI_Button(l8,"l8");
HMI_Button e_m8 = HMI_Button(m8,"m8");
HMI_Button e_h8 = HMI_Button(h8,"h8");
HMI_Text e_d9 = HMI_Text(d9,"d9");
HMI_Text e_c9 = HMI_Text(c9,"c9");
HMI_Button e_l9 = HMI_Button(l9,"l9");
HMI_Button e_m9 = HMI_Button(m9,"m9");
HMI_Button e_h9 = HMI_Button(h9,"h9");
HMI_Text e_d10 = HMI_Text(d10,"d10");
HMI_Text e_c10 = HMI_Text(c10,"c10");
HMI_Button e_l10 = HMI_Button(l10,"l10");
HMI_Button e_m10 = HMI_Button(m10,"m10");
HMI_Button e_h10 = HMI_Button(h10,"h10");
HMI_Text e_E_ELEM_TEXT952 = HMI_Text(E_ELEM_TEXT952,"E_ELEM_TEXT952");
HMI_Text e_deadzonetxt = HMI_Text(deadzonetxt,"deadzonetxt");
HMI_Slider e_deadzone0 = HMI_Slider(deadzone0,"deadzone0");
HMI_Button e_backbtncal = HMI_Button(backbtncal,"backbtncal");
HMI_Button e_savebtncal = HMI_Button(savebtncal,"savebtncal");

HMI_Page p_DisplayRawValues = HMI_Page(PAGE_TYPES::NORMAL, DisplayRawValues,"DisplayRawValues");
HMI_Text e_tr0 = HMI_Text(tr0,"tr0");
HMI_Text e_nr0 = HMI_Text(nr0,"nr0");
HMI_Text e_tr1 = HMI_Text(tr1,"tr1");
HMI_Text e_nr1 = HMI_Text(nr1,"nr1");
HMI_Text e_tr2 = HMI_Text(tr2,"tr2");
HMI_Text e_nr2 = HMI_Text(nr2,"nr2");
HMI_Text e_tr3 = HMI_Text(tr3,"tr3");
HMI_Text e_nr3 = HMI_Text(nr3,"nr3");
HMI_Text e_tr4 = HMI_Text(tr4,"tr4");
HMI_Text e_nr4 = HMI_Text(nr4,"nr4");
HMI_Text e_tr5 = HMI_Text(tr5,"tr5");
HMI_Text e_nr5 = HMI_Text(nr5,"nr5");
HMI_Text e_tr6 = HMI_Text(tr6,"tr6");
HMI_Text e_nr6 = HMI_Text(nr6,"nr6");
HMI_Text e_tr7 = HMI_Text(tr7,"tr7");
HMI_Text e_nr7 = HMI_Text(nr7,"nr7");
HMI_Text e_tr8 = HMI_Text(tr8,"tr8");
HMI_Text e_nr8 = HMI_Text(nr8,"nr8");
HMI_Text e_tr9 = HMI_Text(tr9,"tr9");
HMI_Text e_nr9 = HMI_Text(nr9,"nr9");
HMI_Text e_E_ELEM_TEXT332 = HMI_Text(E_ELEM_TEXT332,"E_ELEM_TEXT332");
HMI_Text e_dprevio = HMI_Text(dprevio,"dprevio");
HMI_Text e_E_ELEM_TEXT330 = HMI_Text(E_ELEM_TEXT330,"E_ELEM_TEXT330");
HMI_Text e_dcurio = HMI_Text(dcurio,"dcurio");
HMI_Button e_drbackbtn = HMI_Button(drbackbtn,"drbackbtn");

HMI_Page p_DisplayRcValues = HMI_Page(PAGE_TYPES::NORMAL, DisplayRcValues,"DisplayRcValues");
HMI_Text e_t0 = HMI_Text(t0,"t0");
HMI_Text e_n0 = HMI_Text(n0,"n0");
HMI_Text e_t1 = HMI_Text(t1,"t1");
HMI_Text e_n1 = HMI_Text(n1,"n1");
HMI_Text e_t2 = HMI_Text(t2,"t2");
HMI_Text e_n2 = HMI_Text(n2,"n2");
HMI_Text e_t3 = HMI_Text(t3,"t3");
HMI_Text e_n3 = HMI_Text(n3,"n3");
HMI_Text e_t4 = HMI_Text(t4,"t4");
HMI_Text e_n4 = HMI_Text(n4,"n4");
HMI_Text e_t5 = HMI_Text(t5,"t5");
HMI_Text e_n5 = HMI_Text(n5,"n5");
HMI_Text e_t6 = HMI_Text(t6,"t6");
HMI_Text e_n6 = HMI_Text(n6,"n6");
HMI_Text e_t7 = HMI_Text(t7,"t7");
HMI_Text e_n7 = HMI_Text(n7,"n7");
HMI_Text e_t8 = HMI_Text(t8,"t8");
HMI_Text e_n8 = HMI_Text(n8,"n8");
HMI_Text e_t9 = HMI_Text(t9,"t9");
HMI_Text e_n9 = HMI_Text(n9,"n9");
HMI_Text e_t10 = HMI_Text(t10,"t10");
HMI_Text e_n10 = HMI_Text(n10,"n10");
HMI_Text e_t11 = HMI_Text(t11,"t11");
HMI_Text e_n11 = HMI_Text(n11,"n11");
HMI_Text e_t12 = HMI_Text(t12,"t12");
HMI_Text e_n12 = HMI_Text(n12,"n12");
HMI_Text e_t13 = HMI_Text(t13,"t13");
HMI_Text e_n13 = HMI_Text(n13,"n13");
HMI_Text e_t14 = HMI_Text(t14,"t14");
HMI_Text e_n14 = HMI_Text(n14,"n14");
HMI_Text e_t15 = HMI_Text(t15,"t15");
HMI_Text e_n15 = HMI_Text(n15,"n15");
HMI_Text e_t16 = HMI_Text(t16,"t16");
HMI_Text e_n16 = HMI_Text(n16,"n16");
HMI_Text e_t17 = HMI_Text(t17,"t17");
HMI_Text e_n17 = HMI_Text(n17,"n17");
HMI_Text e_t18 = HMI_Text(t18,"t18");
HMI_Text e_n18 = HMI_Text(n18,"n18");
HMI_Text e_t19 = HMI_Text(t19,"t19");
HMI_Text e_n19 = HMI_Text(n19,"n19");
HMI_Text e_t20 = HMI_Text(t20,"t20");
HMI_Text e_n20 = HMI_Text(n20,"n20");
HMI_Text e_t21 = HMI_Text(t21,"t21");
HMI_Text e_n21 = HMI_Text(n21,"n21");
HMI_Text e_t22 = HMI_Text(t22,"t22");
HMI_Text e_n22 = HMI_Text(n22,"n22");
HMI_Text e_t23 = HMI_Text(t23,"t23");
HMI_Text e_n23 = HMI_Text(n23,"n23");
HMI_Button e_b5 = HMI_Button(b5,"b5");

HMI_Page p_channelSettings = HMI_Page(PAGE_TYPES::NORMAL, channelSettings,"channelSettings");
HMI_Button e_setch1 = HMI_Button(setch1,"setch1");
HMI_Button e_setch2 = HMI_Button(setch2,"setch2");
HMI_Button e_setch3 = HMI_Button(setch3,"setch3");
HMI_Button e_setch4 = HMI_Button(setch4,"setch4");
HMI_Button e_setch5 = HMI_Button(setch5,"setch5");
HMI_Button e_setch6 = HMI_Button(setch6,"setch6");
HMI_Button e_setch7 = HMI_Button(setch7,"setch7");
HMI_Button e_setch8 = HMI_Button(setch8,"setch8");
HMI_Button e_setch9 = HMI_Button(setch9,"setch9");
HMI_Button e_setch10 = HMI_Button(setch10,"setch10");
HMI_Button e_setch11 = HMI_Button(setch11,"setch11");
HMI_Button e_setch12 = HMI_Button(setch12,"setch12");
HMI_Button e_setch13 = HMI_Button(setch13,"setch13");
HMI_Button e_setch14 = HMI_Button(setch14,"setch14");
HMI_Button e_setch15 = HMI_Button(setch15,"setch15");
HMI_Button e_setch16 = HMI_Button(setch16,"setch16");
HMI_Button e_setch17 = HMI_Button(setch17,"setch17");
HMI_Button e_setch18 = HMI_Button(setch18,"setch18");
HMI_Button e_setch19 = HMI_Button(setch19,"setch19");
HMI_Button e_setch20 = HMI_Button(setch20,"setch20");
HMI_Button e_setch21 = HMI_Button(setch21,"setch21");
HMI_Button e_setch22 = HMI_Button(setch22,"setch22");
HMI_Button e_setch23 = HMI_Button(setch23,"setch23");
HMI_Button e_setch24 = HMI_Button(setch24,"setch24");
HMI_Button e_backbtnchs = HMI_Button(backbtnchs,"backbtnchs");
HMI_Button e_backbtnchsandsendstorx = HMI_Button(backbtnchsandsendstorx,"backbtnchsandsendstorx");

HMI_Page p_transmittingSettings = HMI_Page(PAGE_TYPES::POPUP, transmittingSettings,"transmittingSettings");
HMI_Text e_E_ELEM_TEXT745 = HMI_Text(E_ELEM_TEXT745,"E_ELEM_TEXT745");
HMI_Text e_E_ELEM_TEXT746 = HMI_Text(E_ELEM_TEXT746,"E_ELEM_TEXT746");
HMI_Text e_settingstxtorxprogress = HMI_Text(settingstxtorxprogress,"settingstxtorxprogress");

HMI_Page p_setupChannel = HMI_Page(PAGE_TYPES::NORMAL, setupChannel,"setupChannel");
HMI_Text e_channelname = HMI_Text(channelname,"channelname");
HMI_Text e_E_ELEM_TEXT312 = HMI_Text(E_ELEM_TEXT312,"E_ELEM_TEXT312");
HMI_Text e_channelval = HMI_Text(channelval,"channelval");
HMI_Text e_reversetxt = HMI_Text(reversetxt,"reversetxt");
HMI_Toggle e_reverse = HMI_Toggle(reverse,"reverse");
HMI_Text e_E_ELEM_TEXT797 = HMI_Text(E_ELEM_TEXT797,"E_ELEM_TEXT797");
HMI_Toggle e_centeredStick = HMI_Toggle(centeredStick,"centeredStick");
HMI_Button e_detectIO1 = HMI_Button(detectIO1,"detectIO1");
HMI_Button e_detectIO2 = HMI_Button(detectIO2,"detectIO2");
HMI_Text e_E_ELEM_TEXT305 = HMI_Text(E_ELEM_TEXT305,"E_ELEM_TEXT305");
HMI_Text e_configuredIO1 = HMI_Text(configuredIO1,"configuredIO1");
HMI_Text e_E_ELEM_TEXT307 = HMI_Text(E_ELEM_TEXT307,"E_ELEM_TEXT307");
HMI_Text e_configuredIO2 = HMI_Text(configuredIO2,"configuredIO2");
HMI_Text e_E_ELEM_TEXT309 = HMI_Text(E_ELEM_TEXT309,"E_ELEM_TEXT309");
HMI_Text e_defaultval = HMI_Text(defaultval,"defaultval");
HMI_Button e_savebtnchconf = HMI_Button(savebtnchconf,"savebtnchconf");
HMI_Button e_backbtnchconf = HMI_Button(backbtnchconf,"backbtnchconf");
HMI_Listbox e_lsbChannelOutputType = HMI_Listbox(lsbChannelOutputType,"lsbChannelOutputType");
HMI_Button e_E_ELEM_BTN279 = HMI_Button(E_ELEM_BTN279,"E_ELEM_BTN279");

HMI_Page p_setupOutputPWM = HMI_Page(PAGE_TYPES::NORMAL, setupOutputPWM,"setupOutputPWM");
HMI_Text e_E_ELEM_TEXT674 = HMI_Text(E_ELEM_TEXT674,"E_ELEM_TEXT674");
HMI_Text e_E_ELEM_TEXT667 = HMI_Text(E_ELEM_TEXT667,"E_ELEM_TEXT667");
HMI_Text e_pwmFreq = HMI_Text(pwmFreq,"pwmFreq");
HMI_Button e_backbtnsetupPWM = HMI_Button(backbtnsetupPWM,"backbtnsetupPWM");

HMI_Page p_setupOutputStepper = HMI_Page(PAGE_TYPES::NORMAL, setupOutputStepper,"setupOutputStepper");
HMI_Text e_E_ELEM_TEXT675 = HMI_Text(E_ELEM_TEXT675,"E_ELEM_TEXT675");
HMI_Text e_E_ELEM_TEXT669 = HMI_Text(E_ELEM_TEXT669,"E_ELEM_TEXT669");
HMI_Text e_stepMinFreq = HMI_Text(stepMinFreq,"stepMinFreq");
HMI_Text e_E_ELEM_TEXT670 = HMI_Text(E_ELEM_TEXT670,"E_ELEM_TEXT670");
HMI_Text e_stepMaxFreq = HMI_Text(stepMaxFreq,"stepMaxFreq");
HMI_Button e_backbtnsetupStepper = HMI_Button(backbtnsetupStepper,"backbtnsetupStepper");

HMI_Page p_setupOutputNotNeeded = HMI_Page(PAGE_TYPES::NORMAL, setupOutputNotNeeded,"setupOutputNotNeeded");
HMI_Text e_E_ELEM_TEXT676 = HMI_Text(E_ELEM_TEXT676,"E_ELEM_TEXT676");
HMI_Button e_backbtnsetupNotNeeded = HMI_Button(backbtnsetupNotNeeded,"backbtnsetupNotNeeded");

HMI_Page p_setModel = HMI_Page(PAGE_TYPES::NORMAL, setModel,"setModel");
HMI_Text e_txt_ch1 = HMI_Text(txt_ch1,"txt_ch1");
HMI_Toggle e_sm0 = HMI_Toggle(sm0,"sm0");
HMI_Text e_txt_ch2 = HMI_Text(txt_ch2,"txt_ch2");
HMI_Toggle e_sm1 = HMI_Toggle(sm1,"sm1");
HMI_Text e_txt_ch3 = HMI_Text(txt_ch3,"txt_ch3");
HMI_Toggle e_sm2 = HMI_Toggle(sm2,"sm2");
HMI_Text e_txt_ch4 = HMI_Text(txt_ch4,"txt_ch4");
HMI_Toggle e_sm3 = HMI_Toggle(sm3,"sm3");
HMI_Text e_txt_ch5 = HMI_Text(txt_ch5,"txt_ch5");
HMI_Toggle e_sm4 = HMI_Toggle(sm4,"sm4");
HMI_Text e_txt_ch6 = HMI_Text(txt_ch6,"txt_ch6");
HMI_Toggle e_sm5 = HMI_Toggle(sm5,"sm5");
HMI_Text e_txt_ch7 = HMI_Text(txt_ch7,"txt_ch7");
HMI_Toggle e_sm6 = HMI_Toggle(sm6,"sm6");
HMI_Text e_txt_ch8 = HMI_Text(txt_ch8,"txt_ch8");
HMI_Toggle e_sm7 = HMI_Toggle(sm7,"sm7");
HMI_Button e_E_ELEM_BTN65 = HMI_Button(E_ELEM_BTN65,"E_ELEM_BTN65");

HMI_Object *hmiObjects[] = {
&e_nBatPercent,
&e_BTN_Quit,
&p_E_PG_MAIN,
&e_navRC,
&e_navRAW,
&e_navSETADC,
&e_navSETCH,
&e_navMODEL,
&p_calibrations,
&e_E_ELEM_TEXT922,
&e_E_ELEM_TEXT923,
&e_E_ELEM_TEXT924,
&e_E_ELEM_TEXT925,
&e_E_ELEM_TEXT926,
&e_E_ELEM_TEXT927,
&e_E_ELEM_TEXT928,
&e_E_ELEM_TEXT929,
&e_E_ELEM_TEXT930,
&e_E_ELEM_TEXT931,
&e_d1,
&e_c1,
&e_l1,
&e_m1,
&e_h1,
&e_d2,
&e_c2,
&e_l2,
&e_m2,
&e_h2,
&e_d3,
&e_c3,
&e_l3,
&e_m3,
&e_h3,
&e_d4,
&e_c4,
&e_l4,
&e_m4,
&e_h4,
&e_d5,
&e_c5,
&e_l5,
&e_m5,
&e_h5,
&e_d6,
&e_c6,
&e_l6,
&e_m6,
&e_h6,
&e_d7,
&e_c7,
&e_l7,
&e_m7,
&e_h7,
&e_d8,
&e_c8,
&e_l8,
&e_m8,
&e_h8,
&e_d9,
&e_c9,
&e_l9,
&e_m9,
&e_h9,
&e_d10,
&e_c10,
&e_l10,
&e_m10,
&e_h10,
&e_E_ELEM_TEXT952,
&e_deadzonetxt,
&e_deadzone0,
&e_backbtncal,
&e_savebtncal,
&p_DisplayRawValues,
&e_tr0,
&e_nr0,
&e_tr1,
&e_nr1,
&e_tr2,
&e_nr2,
&e_tr3,
&e_nr3,
&e_tr4,
&e_nr4,
&e_tr5,
&e_nr5,
&e_tr6,
&e_nr6,
&e_tr7,
&e_nr7,
&e_tr8,
&e_nr8,
&e_tr9,
&e_nr9,
&e_E_ELEM_TEXT332,
&e_dprevio,
&e_E_ELEM_TEXT330,
&e_dcurio,
&e_drbackbtn,
&p_DisplayRcValues,
&e_t0,
&e_n0,
&e_t1,
&e_n1,
&e_t2,
&e_n2,
&e_t3,
&e_n3,
&e_t4,
&e_n4,
&e_t5,
&e_n5,
&e_t6,
&e_n6,
&e_t7,
&e_n7,
&e_t8,
&e_n8,
&e_t9,
&e_n9,
&e_t10,
&e_n10,
&e_t11,
&e_n11,
&e_t12,
&e_n12,
&e_t13,
&e_n13,
&e_t14,
&e_n14,
&e_t15,
&e_n15,
&e_t16,
&e_n16,
&e_t17,
&e_n17,
&e_t18,
&e_n18,
&e_t19,
&e_n19,
&e_t20,
&e_n20,
&e_t21,
&e_n21,
&e_t22,
&e_n22,
&e_t23,
&e_n23,
&e_b5,
&p_channelSettings,
&e_setch1,
&e_setch2,
&e_setch3,
&e_setch4,
&e_setch5,
&e_setch6,
&e_setch7,
&e_setch8,
&e_setch9,
&e_setch10,
&e_setch11,
&e_setch12,
&e_setch13,
&e_setch14,
&e_setch15,
&e_setch16,
&e_setch17,
&e_setch18,
&e_setch19,
&e_setch20,
&e_setch21,
&e_setch22,
&e_setch23,
&e_setch24,
&e_backbtnchs,
&e_backbtnchsandsendstorx,
&p_transmittingSettings,
&e_E_ELEM_TEXT745,
&e_E_ELEM_TEXT746,
&e_settingstxtorxprogress,
&p_setupChannel,
&e_channelname,
&e_E_ELEM_TEXT312,
&e_channelval,
&e_reversetxt,
&e_reverse,
&e_E_ELEM_TEXT797,
&e_centeredStick,
&e_detectIO1,
&e_detectIO2,
&e_E_ELEM_TEXT305,
&e_configuredIO1,
&e_E_ELEM_TEXT307,
&e_configuredIO2,
&e_E_ELEM_TEXT309,
&e_defaultval,
&e_savebtnchconf,
&e_backbtnchconf,
&e_lsbChannelOutputType,
&e_E_ELEM_BTN279,
&p_setupOutputPWM,
&e_E_ELEM_TEXT674,
&e_E_ELEM_TEXT667,
&e_pwmFreq,
&e_backbtnsetupPWM,
&p_setupOutputStepper,
&e_E_ELEM_TEXT675,
&e_E_ELEM_TEXT669,
&e_stepMinFreq,
&e_E_ELEM_TEXT670,
&e_stepMaxFreq,
&e_backbtnsetupStepper,
&p_setupOutputNotNeeded,
&e_E_ELEM_TEXT676,
&e_backbtnsetupNotNeeded,
&p_setModel,
&e_txt_ch1,
&e_sm0,
&e_txt_ch2,
&e_sm1,
&e_txt_ch3,
&e_sm2,
&e_txt_ch4,
&e_sm3,
&e_txt_ch5,
&e_sm4,
&e_txt_ch6,
&e_sm5,
&e_txt_ch7,
&e_sm6,
&e_txt_ch8,
&e_sm7,
&e_E_ELEM_BTN65,
NULL
};

void defaultCallback(HMI_Object* obj){
// Start UserCode : defaultCallback
	Serial.printf("Default callback for object %s\n", obj->getName());

// End UserCode : defaultCallback

}

void initHMI(){
// Start UserCode : PreInit
	HMI.setHMISerial(&HMISerial);
// End UserCode : PreInit

	HMI.begin();
	e_BTN_Quit.addTouchUpCallback(doNavigation);
	e_navRC.addTouchUpCallback(doNavigation);
	e_navRAW.addTouchUpCallback(doNavigation);
	e_navSETADC.addTouchUpCallback(doNavigation);
	e_navSETCH.addTouchUpCallback(doNavigation);
	e_navMODEL.addTouchUpCallback(doNavigation);
	e_l1.addTouchUpCallback(setupMinMaxMid);
	e_m1.addTouchUpCallback(setupMinMaxMid);
	e_h1.addTouchUpCallback(setupMinMaxMid);
	e_l2.addTouchUpCallback(setupMinMaxMid);
	e_m2.addTouchUpCallback(setupMinMaxMid);
	e_h2.addTouchUpCallback(setupMinMaxMid);
	e_l3.addTouchUpCallback(setupMinMaxMid);
	e_m3.addTouchUpCallback(setupMinMaxMid);
	e_h3.addTouchUpCallback(setupMinMaxMid);
	e_l4.addTouchUpCallback(setupMinMaxMid);
	e_m4.addTouchUpCallback(setupMinMaxMid);
	e_h4.addTouchUpCallback(setupMinMaxMid);
	e_l5.addTouchUpCallback(setupMinMaxMid);
	e_m5.addTouchUpCallback(setupMinMaxMid);
	e_h5.addTouchUpCallback(setupMinMaxMid);
	e_l6.addTouchUpCallback(setupMinMaxMid);
	e_m6.addTouchUpCallback(setupMinMaxMid);
	e_h6.addTouchUpCallback(setupMinMaxMid);
	e_l7.addTouchUpCallback(setupMinMaxMid);
	e_m7.addTouchUpCallback(setupMinMaxMid);
	e_h7.addTouchUpCallback(setupMinMaxMid);
	e_l8.addTouchUpCallback(setupMinMaxMid);
	e_m8.addTouchUpCallback(setupMinMaxMid);
	e_h8.addTouchUpCallback(setupMinMaxMid);
	e_l9.addTouchUpCallback(setupMinMaxMid);
	e_m9.addTouchUpCallback(setupMinMaxMid);
	e_h9.addTouchUpCallback(setupMinMaxMid);
	e_l10.addTouchUpCallback(setupMinMaxMid);
	e_m10.addTouchUpCallback(setupMinMaxMid);
	e_h10.addTouchUpCallback(setupMinMaxMid);
	e_deadzone0.addTouchUpCallback(defaultCallback);
	e_backbtncal.addTouchUpCallback(doNavigation);
	e_savebtncal.addTouchUpCallback(doNavigation);
	e_drbackbtn.addTouchUpCallback(doNavigation);
	e_b5.addTouchUpCallback(doNavigation);
	e_setch1.addTouchUpCallback(doNavigation);
	e_setch2.addTouchUpCallback(doNavigation);
	e_setch3.addTouchUpCallback(doNavigation);
	e_setch4.addTouchUpCallback(doNavigation);
	e_setch5.addTouchUpCallback(doNavigation);
	e_setch6.addTouchUpCallback(doNavigation);
	e_setch7.addTouchUpCallback(doNavigation);
	e_setch8.addTouchUpCallback(doNavigation);
	e_setch9.addTouchUpCallback(doNavigation);
	e_setch10.addTouchUpCallback(doNavigation);
	e_setch11.addTouchUpCallback(doNavigation);
	e_setch12.addTouchUpCallback(doNavigation);
	e_setch13.addTouchUpCallback(doNavigation);
	e_setch14.addTouchUpCallback(doNavigation);
	e_setch15.addTouchUpCallback(doNavigation);
	e_setch16.addTouchUpCallback(doNavigation);
	e_setch17.addTouchUpCallback(doNavigation);
	e_setch18.addTouchUpCallback(doNavigation);
	e_setch19.addTouchUpCallback(doNavigation);
	e_setch20.addTouchUpCallback(doNavigation);
	e_setch21.addTouchUpCallback(doNavigation);
	e_setch22.addTouchUpCallback(doNavigation);
	e_setch23.addTouchUpCallback(doNavigation);
	e_setch24.addTouchUpCallback(doNavigation);
	e_backbtnchs.addTouchUpCallback(doNavigation);
	e_backbtnchsandsendstorx.addTouchUpCallback(doNavigation);
	e_reverse.addValueChangedCallback(emptyCallback);
	//e_centeredStick.addValueChangedCallback(setupPWM);
	e_detectIO1.addTouchUpCallback(doDetectIO1);
	e_detectIO2.addTouchUpCallback(doDetectIO2);
	e_defaultval.addValueChangedCallback(emptyCallback);
	e_savebtnchconf.addTouchUpCallback(doNavigation);
	e_backbtnchconf.addTouchUpCallback(doNavigation);
	e_lsbChannelOutputType.addValueChangedCallback(listboxChanged);
	e_E_ELEM_BTN279.addTouchUpCallback(doNavigation);
	e_pwmFreq.addValueChangedCallback(setupPWM);
	e_backbtnsetupPWM.addTouchUpCallback(doNavigation);
	e_stepMinFreq.addValueChangedCallback(setupStepper);
	e_stepMaxFreq.addValueChangedCallback(setupStepper);
	e_backbtnsetupStepper.addTouchUpCallback(doNavigation);
	e_backbtnsetupNotNeeded.addTouchUpCallback(doNavigation);
	e_sm0.addTouchUpCallback(defaultCallback);
	e_sm1.addTouchUpCallback(defaultCallback);
	e_sm2.addTouchUpCallback(defaultCallback);
	e_sm3.addTouchUpCallback(defaultCallback);
	e_sm4.addTouchUpCallback(defaultCallback);
	e_sm5.addTouchUpCallback(defaultCallback);
	e_sm6.addTouchUpCallback(defaultCallback);
	e_sm7.addTouchUpCallback(defaultCallback);
	e_E_ELEM_BTN65.addTouchUpCallback(doNavigation);
// Start UserCode : PostInit

// End UserCode : PostInit

}
// Start UserCode : Functions

void setupStepper(HMI_Object* obj) {
	if (obj->getElementId() == stepMinFreq) {
		settings.model[settings.activeModel].channel_settings[channelToEditIdx].stepperConfig.minFrequency = String(((HMI_Text*)obj)->getText()).toInt();
	}
	if (obj->getElementId() == stepMaxFreq) {
		settings.model[settings.activeModel].channel_settings[channelToEditIdx].stepperConfig.maxFrequency = String(((HMI_Text*)obj)->getText()).toInt();
	}
}

void setupPWM(HMI_Object* obj) {
	if (obj->getElementId() == pwmFreq) {
		settings.model[settings.activeModel].channel_settings[channelToEditIdx].pwmConfig.frequency = String(((HMI_Text*)obj)->getText()).toInt();
	}
}

void listboxChanged(HMI_Object* obj) {
	HMI_Listbox* lsb = (HMI_Listbox*)obj;
	switch (obj->getElementId()) {
		case lsbChannelOutputType:
			Serial.printf("ChannelOutput is now: %s\r\n", lsb->getText());
			if(strcmp(lsb->getText(), "RC") == 0){
				settings.model[settings.activeModel].channel_settings[channelToEditIdx].outputMode = OUTPUTMODE_RC;
			}
			else if (strcmp(lsb->getText(), "IO") == 0) {
				settings.model[settings.activeModel].channel_settings[channelToEditIdx].outputMode = OUTPUTMODE_IO;
			}
			else if (strcmp(lsb->getText(), "PWM") == 0) {
				settings.model[settings.activeModel].channel_settings[channelToEditIdx].outputMode = OUTPUTMODE_PWM;
			}
			else if (strcmp(lsb->getText(), "STEPPER") == 0) {
				settings.model[settings.activeModel].channel_settings[channelToEditIdx].outputMode = OUTPUTMODE_STEP;
			}
			else if (strcmp(lsb->getText(), "DAC") == 0) {
				settings.model[settings.activeModel].channel_settings[channelToEditIdx].outputMode = OUTPUTMODE_DAC;
			}
			break;
		default:
			break;
	}
}

void doNavigation(HMI_Object* navBtn) {
	switch (navBtn->getElementId()) {
		case BTN_Quit:
		{
			NVIC_SystemReset();
		}
		break;

		case navMODEL:
			p_setModel.navigateTo();
			break;
		case navRAW:
			p_DisplayRawValues.navigateTo();
			break;
	case navRC:
		p_DisplayRcValues.navigateTo();
		break;
	case navSETADC:
		p_calibrations.navigateTo();
		break;
	case navSETCH:{
		p_channelSettings.navigateTo();
		for (int i = 0; i < RC_MAX_CHANNELS; i++) {
			delay(20);
			auto cs = settings.model[settings.activeModel].channel_settings[i];
			if (cs.channelMapping[0].type == 0 && cs.channelMapping[1].type == 0) {
				chEditButtons[i]->setBackgroundColor(0xFF, 0, 0);
			}
			else {
				chEditButtons[i]->setBackgroundColor(0, 0xFF, 0);
			}
		}
		HMI.refreshDisplay();
		break;
	}
	case backbtnchconf: {
		auto cs = settings.model[settings.activeModel].channel_settings[channelToEditIdx];
		if (cs.channelMapping[0].type == 0 && cs.channelMapping[1].type == 0) {
			chEditButtons[channelToEditIdx]->setBackgroundColor(0xFF, 0, 0, true);
		}
		else {
			chEditButtons[channelToEditIdx]->setBackgroundColor(0, 0xFF, 0, true);
		}
		p_channelSettings.navigateTo();
		break;
	}
	case savebtncal:
	case backbtnchs:
	case drbackbtn:
		//saveSettings(); // TODO: Check how to seperate settings from main ino into own file
	case E_ELEM_BTN65:
	case backbtncal:
	case b5:
		p_E_PG_MAIN.navigateTo();
		break;
	case setch1:
	case setch2:
	case setch3:
	case setch4:
	case setch5:
	case setch6:
	case setch7:
	case setch8:
	case setch9:
	case setch10:
	case setch11:
	case setch12:
	case setch13:
	case setch14:
	case setch15:
	case setch16:
	case setch17:
	case setch18:
	case setch19:
	case setch20:
	case setch21:
	case setch22:
	case setch23:
	case setch24: {
		channelToEdit = atoi(&navBtn->getName()[5]);
		channelToEditIdx = channelToEdit - 1;
		navigateToChannelEditor();
		break;
	}
	case savebtnchconf: {
		uint16_t chDef = atoi(e_defaultval.getText());
		Serial.printf("New channel %d default = '%d'\tNew reverse '%d'\tNew IO1 '%s%d' New IO2 '%s%d'\n", channelToEdit, chDef, e_reverse.getState(), 
			detectedIO1.type == CTYPE_NONE ? "NONE" : detectedIO1.type == CTYPE_IO ? "IO" : "ADC", detectedIO1.index,
			detectedIO2.type == CTYPE_NONE ? "NONE" : detectedIO2.type == CTYPE_IO ? "IO" : "ADC", detectedIO2.index
		);
		settings.model[settings.activeModel].channel_settings[channelToEditIdx].channelMapping[0].type = detectedIO1.type;
		settings.model[settings.activeModel].channel_settings[channelToEditIdx].channelMapping[1].type = detectedIO2.type;
		settings.model[settings.activeModel].channel_settings[channelToEditIdx].channelMapping[0].index = detectedIO1.index;
		settings.model[settings.activeModel].channel_settings[channelToEditIdx].channelMapping[1].index = detectedIO2.index;
		settings.model[settings.activeModel].channel_settings[channelToEditIdx].chDefaults = chDef;
		if (e_reverse.getState()) {
			bitSet(settings.model[settings.activeModel].channelReversed, channelToEditIdx);
		}
		else {
			bitClear(settings.model[settings.activeModel].channelReversed, channelToEditIdx);
		}
		settings.model[settings.activeModel].channel_settings[channelToEditIdx].centeredStick = e_centeredStick.getState();

		p_channelSettings.navigateTo();
		break;
	}
	case E_ELEM_BTN279:
		if (settings.model[settings.activeModel].channel_settings[channelToEditIdx].outputMode == OUTPUTMODE_STEP) {
			p_setupOutputStepper.navigateTo();
			e_stepMinFreq.setValue(settings.model[settings.activeModel].channel_settings[channelToEditIdx].stepperConfig.minFrequency);
			e_stepMaxFreq.setValue(settings.model[settings.activeModel].channel_settings[channelToEditIdx].stepperConfig.maxFrequency);
			

		} else if (settings.model[settings.activeModel].channel_settings[channelToEditIdx].outputMode == OUTPUTMODE_PWM) {
			p_setupOutputPWM.navigateTo();
			e_pwmFreq.setValue(settings.model[settings.activeModel].channel_settings[channelToEditIdx].pwmConfig.frequency);
		}
		else {
			p_setupOutputNotNeeded.navigateTo();
		}
		break;
	case backbtnsetupPWM:
		navigateToChannelEditor();
		break;
	case backbtnsetupStepper:
		navigateToChannelEditor();
		break;
	case backbtnsetupNotNeeded:
		navigateToChannelEditor();
		break;
	case backbtnchsandsendstorx:
		// Trigger transmitting 
		transmitSettingsToRX();
		p_E_PG_MAIN.navigateTo();
		break;
	default:
		Serial.printf("nav button '%s' not parsed yet\n", navBtn->getName());
		break;
	}
}

void navigateToChannelEditor() {
	p_setupChannel.navigateTo();
	uint32_t startTime = millis();
	char chstr[8];
	sprintf(chstr, "CH%d", channelToEdit);
	e_detectIO1.setValue("Detect IO1");
	e_detectIO2.setValue("Detect IO2");
	uint8_t outputModesOptions = channelOutputOptions[channelToEditIdx];
	char io1Str[8] = "NONE";
	char io2Str[8] = "NONE";
	int8_t io1t = settings.model[settings.activeModel].channel_settings[channelToEditIdx].channelMapping[0].type;
	int8_t io2t = settings.model[settings.activeModel].channel_settings[channelToEditIdx].channelMapping[1].type;
	int8_t io1 = settings.model[settings.activeModel].channel_settings[channelToEditIdx].channelMapping[0].index;
	int8_t io2 = settings.model[settings.activeModel].channel_settings[channelToEditIdx].channelMapping[1].index;
	if (io1t != CTYPE_NONE) {
		if (io1t == CTYPE_IO) {
			sprintf(io1Str, "IO%d", io1);
		}
		else {
			sprintf(io1Str, "ADC%u", io1);
		}
	}
	if (io2t != CTYPE_NONE) {
		if (io2t == CTYPE_IO) {
			sprintf(io2Str, "IO%u", io2);
		}
		else {
			sprintf(io2Str, "ADC%u", io2);
		}
	}
	e_channelname.setValue(chstr);
	e_configuredIO1.setValue(io1Str);
	e_configuredIO2.setValue(io2Str);
	e_reverse.setState(bitRead(settings.model[settings.activeModel].channelReversed, channelToEditIdx));
	e_defaultval.setValue(settings.model[settings.activeModel].channel_settings[channelToEditIdx].chDefaults);
	detectedIO1 = settings.model[settings.activeModel].channel_settings[channelToEditIdx].channelMapping[0];
	detectedIO2 = settings.model[settings.activeModel].channel_settings[channelToEditIdx].channelMapping[1];
	e_lsbChannelOutputType.selectItem((int16_t)settings.model[settings.activeModel].channel_settings[channelToEditIdx].outputMode);
	e_centeredStick.setState(settings.model[settings.activeModel].channel_settings[channelToEditIdx].centeredStick);
	for (int i = 0; i <= OUTPUTMODE_DAC ; i++) {
		if (!bitRead(outputModesOptions, i)) {
			Serial.printf("Bit %d is not set. Setting list item to \"NONE\"\r\n", i);
			e_lsbChannelOutputType.overrideListItem(i, "NONE");
		}
		else {
			e_lsbChannelOutputType.overrideListItem(i, OUTPUTMODE_STR_TABLE[i]);
		}
	}
	uint32_t totalTime = millis() - startTime;
	Serial.printf("Time to process %4d ms channel to edit %d. Default val '%d' reverse '%d' IO1 %s IO2 %s OUTPUTOPTIONS ",
		totalTime, channelToEdit, settings.model[settings.activeModel].channel_settings[channelToEditIdx].chDefaults, bitRead(settings.model[settings.activeModel].channelReversed, channelToEditIdx), io1Str, io2Str);
	printBits(&Serial, outputModesOptions, true);

}

void setupMinMaxMid(HMI_Object* obj)
{
	int objCHId = atoi(&obj->getName()[1]);
	int objCHIdIdx = objCHId - 1;
	uint16_t adcVal = rawChannels[objCHIdIdx];
	if (obj->getName()[0] == 'l') {
		settings.model[settings.activeModel].channel_settings[objCHIdIdx].chMin = adcVal;
		Serial.printf("Setting min of ch%d to %d\n", objCHId, adcVal);
	} else if (obj->getName()[0] == 'm') {
		settings.model[settings.activeModel].channel_settings[objCHIdIdx].chMid = adcVal;
		Serial.printf("Setting mid of ch%d to %d\n", objCHId, adcVal);
	} else if (obj->getName()[0] == 'h') {
		settings.model[settings.activeModel].channel_settings[objCHIdIdx].chMax = adcVal;
		Serial.printf("Setting max of ch%d to %d\n", objCHId, adcVal);
	}
}

void emptyCallback(HMI_Object* obj)
{
}

void doDetectIO1(HMI_Object* obj) {
	detectingIO = 1;
	e_detectIO1.setValue("Detecting IO1");
}

void doDetectIO2(HMI_Object* obj) {
	detectingIO = 2;
	e_detectIO2.setValue("Detecting IO2");
}
// End UserCode : Functions

