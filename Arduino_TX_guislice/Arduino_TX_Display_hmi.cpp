#include "Arduino_TX_Display_hmi.h"
// Start UserCode : Vars

HardwareSerial Serial3 = HardwareSerial(PD6, PD5);
// End UserCode : Vars


HMI_Page p_BasePage = HMI_Page(PAGE_TYPES::BASEPAGE, BasePage,"BasePage");
HMI_Text e_nBatPercent = HMI_Text(nBatPercent,"nBatPercent");

HMI_Page p_E_PG_MAIN = HMI_Page(PAGE_TYPES::NORMAL, E_PG_MAIN,"E_PG_MAIN");
HMI_Button e_b0 = HMI_Button(b0,"b0");
HMI_Button e_b1 = HMI_Button(b1,"b1");
HMI_Button e_b2 = HMI_Button(b2,"b2");
HMI_Button e_b3 = HMI_Button(b3,"b3");
HMI_Button e_b5 = HMI_Button(b5,"b5");

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
HMI_Button e_l1 = HMI_Button(l1,"l1");
HMI_Button e_m1 = HMI_Button(m1,"m1");
HMI_Button e_h1 = HMI_Button(h1,"h1");
HMI_Text e_d2 = HMI_Text(d2,"d2");
HMI_Button e_l2 = HMI_Button(l2,"l2");
HMI_Button e_m2 = HMI_Button(m2,"m2");
HMI_Button e_h2 = HMI_Button(h2,"h2");
HMI_Text e_d3 = HMI_Text(d3,"d3");
HMI_Button e_l3 = HMI_Button(l3,"l3");
HMI_Button e_m3 = HMI_Button(m3,"m3");
HMI_Button e_h3 = HMI_Button(h3,"h3");
HMI_Text e_d4 = HMI_Text(d4,"d4");
HMI_Button e_l4 = HMI_Button(l4,"l4");
HMI_Button e_m4 = HMI_Button(m4,"m4");
HMI_Button e_h4 = HMI_Button(h4,"h4");
HMI_Text e_d5 = HMI_Text(d5,"d5");
HMI_Button e_l5 = HMI_Button(l5,"l5");
HMI_Button e_m5 = HMI_Button(m5,"m5");
HMI_Button e_h5 = HMI_Button(h5,"h5");
HMI_Text e_d6 = HMI_Text(d6,"d6");
HMI_Button e_l6 = HMI_Button(l6,"l6");
HMI_Button e_m6 = HMI_Button(m6,"m6");
HMI_Button e_h6 = HMI_Button(h6,"h6");
HMI_Text e_d7 = HMI_Text(d7,"d7");
HMI_Button e_l7 = HMI_Button(l7,"l7");
HMI_Button e_m7 = HMI_Button(m7,"m7");
HMI_Button e_h7 = HMI_Button(h7,"h7");
HMI_Text e_d8 = HMI_Text(d8,"d8");
HMI_Button e_l8 = HMI_Button(l8,"l8");
HMI_Button e_m8 = HMI_Button(m8,"m8");
HMI_Button e_h8 = HMI_Button(h8,"h8");
HMI_Text e_d9 = HMI_Text(d9,"d9");
HMI_Button e_l9 = HMI_Button(l9,"l9");
HMI_Button e_m9 = HMI_Button(m9,"m9");
HMI_Button e_h9 = HMI_Button(h9,"h9");
HMI_Text e_d10 = HMI_Text(d10,"d10");
HMI_Button e_l10 = HMI_Button(l10,"l10");
HMI_Button e_m10 = HMI_Button(m10,"m10");
HMI_Button e_h10 = HMI_Button(h10,"h10");
HMI_Text e_E_ELEM_TEXT952 = HMI_Text(E_ELEM_TEXT952,"E_ELEM_TEXT952");
HMI_Text e_deadzonetxt = HMI_Text(deadzonetxt,"deadzonetxt");
HMI_Button e_saveButton0 = HMI_Button(saveButton0,"saveButton0");

HMI_Page p_DisplayValues = HMI_Page(PAGE_TYPES::NORMAL, DisplayValues,"DisplayValues");
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
HMI_Button e_b4 = HMI_Button(b4,"b4");

HMI_Page p_setReverse = HMI_Page(PAGE_TYPES::NORMAL, setReverse,"setReverse");
HMI_Text e_revtxt0 = HMI_Text(revtxt0,"revtxt0");
HMI_Toggle e_rev0 = HMI_Toggle(rev0,"rev0");
HMI_Text e_revtxt1 = HMI_Text(revtxt1,"revtxt1");
HMI_Toggle e_rev1 = HMI_Toggle(rev1,"rev1");
HMI_Text e_revtxt2 = HMI_Text(revtxt2,"revtxt2");
HMI_Toggle e_rev2 = HMI_Toggle(rev2,"rev2");
HMI_Text e_revtxt3 = HMI_Text(revtxt3,"revtxt3");
HMI_Toggle e_rev3 = HMI_Toggle(rev3,"rev3");
HMI_Text e_revtxt4 = HMI_Text(revtxt4,"revtxt4");
HMI_Toggle e_rev4 = HMI_Toggle(rev4,"rev4");
HMI_Text e_revtxt5 = HMI_Text(revtxt5,"revtxt5");
HMI_Toggle e_rev5 = HMI_Toggle(rev5,"rev5");
HMI_Text e_revtxt6 = HMI_Text(revtxt6,"revtxt6");
HMI_Toggle e_rev6 = HMI_Toggle(rev6,"rev6");
HMI_Text e_revtxt7 = HMI_Text(revtxt7,"revtxt7");
HMI_Toggle e_rev7 = HMI_Toggle(rev7,"rev7");
HMI_Text e_revtxt8 = HMI_Text(revtxt8,"revtxt8");
HMI_Toggle e_rev8 = HMI_Toggle(rev8,"rev8");
HMI_Text e_revtxt9 = HMI_Text(revtxt9,"revtxt9");
HMI_Toggle e_rev9 = HMI_Toggle(rev9,"rev9");
HMI_Text e_revtxt10 = HMI_Text(revtxt10,"revtxt10");
HMI_Toggle e_rev10 = HMI_Toggle(rev10,"rev10");
HMI_Text e_revtxt11 = HMI_Text(revtxt11,"revtxt11");
HMI_Toggle e_rev11 = HMI_Toggle(rev11,"rev11");
HMI_Text e_revtxt12 = HMI_Text(revtxt12,"revtxt12");
HMI_Toggle e_rev12 = HMI_Toggle(rev12,"rev12");
HMI_Text e_revtxt13 = HMI_Text(revtxt13,"revtxt13");
HMI_Toggle e_rev13 = HMI_Toggle(rev13,"rev13");
HMI_Text e_revtxt14 = HMI_Text(revtxt14,"revtxt14");
HMI_Toggle e_rev14 = HMI_Toggle(rev14,"rev14");
HMI_Text e_revtxt15 = HMI_Text(revtxt15,"revtxt15");
HMI_Toggle e_rev15 = HMI_Toggle(rev15,"rev15");
HMI_Text e_revtxt16 = HMI_Text(revtxt16,"revtxt16");
HMI_Toggle e_rev16 = HMI_Toggle(rev16,"rev16");
HMI_Text e_revtxt17 = HMI_Text(revtxt17,"revtxt17");
HMI_Toggle e_rev17 = HMI_Toggle(rev17,"rev17");
HMI_Text e_revtxt18 = HMI_Text(revtxt18,"revtxt18");
HMI_Toggle e_rev18 = HMI_Toggle(rev18,"rev18");
HMI_Text e_revtxt19 = HMI_Text(revtxt19,"revtxt19");
HMI_Toggle e_rev19 = HMI_Toggle(rev19,"rev19");
HMI_Text e_revtxt20 = HMI_Text(revtxt20,"revtxt20");
HMI_Toggle e_rev20 = HMI_Toggle(rev20,"rev20");
HMI_Text e_revtxt21 = HMI_Text(revtxt21,"revtxt21");
HMI_Toggle e_rev21 = HMI_Toggle(rev21,"rev21");
HMI_Text e_revtxt22 = HMI_Text(revtxt22,"revtxt22");
HMI_Toggle e_rev22 = HMI_Toggle(rev22,"rev22");
HMI_Text e_revtxt23 = HMI_Text(revtxt23,"revtxt23");
HMI_Toggle e_rev23 = HMI_Toggle(rev23,"rev23");
HMI_Button e_saveButton1 = HMI_Button(saveButton1,"saveButton1");

HMI_Page p_setDefaults = HMI_Page(PAGE_TYPES::NORMAL, setDefaults,"setDefaults");
HMI_Text e_sdt0 = HMI_Text(sdt0,"sdt0");
HMI_Text e_sdn0 = HMI_Text(sdn0,"sdn0");
HMI_Text e_sdt1 = HMI_Text(sdt1,"sdt1");
HMI_Text e_sdn1 = HMI_Text(sdn1,"sdn1");
HMI_Text e_sdt2 = HMI_Text(sdt2,"sdt2");
HMI_Text e_sdn2 = HMI_Text(sdn2,"sdn2");
HMI_Text e_sdt3 = HMI_Text(sdt3,"sdt3");
HMI_Text e_sdn3 = HMI_Text(sdn3,"sdn3");
HMI_Text e_sdt4 = HMI_Text(sdt4,"sdt4");
HMI_Text e_sdn4 = HMI_Text(sdn4,"sdn4");
HMI_Text e_sdt5 = HMI_Text(sdt5,"sdt5");
HMI_Text e_sdn5 = HMI_Text(sdn5,"sdn5");
HMI_Text e_sdt6 = HMI_Text(sdt6,"sdt6");
HMI_Text e_sdn6 = HMI_Text(sdn6,"sdn6");
HMI_Text e_sdt7 = HMI_Text(sdt7,"sdt7");
HMI_Text e_sdn7 = HMI_Text(sdn7,"sdn7");
HMI_Text e_sdt8 = HMI_Text(sdt8,"sdt8");
HMI_Text e_sdn8 = HMI_Text(sdn8,"sdn8");
HMI_Text e_sdt9 = HMI_Text(sdt9,"sdt9");
HMI_Text e_sdn9 = HMI_Text(sdn9,"sdn9");
HMI_Text e_sdt10 = HMI_Text(sdt10,"sdt10");
HMI_Text e_sdn10 = HMI_Text(sdn10,"sdn10");
HMI_Text e_sdt11 = HMI_Text(sdt11,"sdt11");
HMI_Text e_sdn11 = HMI_Text(sdn11,"sdn11");
HMI_Text e_sdt12 = HMI_Text(sdt12,"sdt12");
HMI_Text e_sdn12 = HMI_Text(sdn12,"sdn12");
HMI_Text e_sdt13 = HMI_Text(sdt13,"sdt13");
HMI_Text e_sdn13 = HMI_Text(sdn13,"sdn13");
HMI_Text e_sdt14 = HMI_Text(sdt14,"sdt14");
HMI_Text e_sdn14 = HMI_Text(sdn14,"sdn14");
HMI_Text e_sdt15 = HMI_Text(sdt15,"sdt15");
HMI_Text e_sdn15 = HMI_Text(sdn15,"sdn15");
HMI_Text e_sdt16 = HMI_Text(sdt16,"sdt16");
HMI_Text e_sdn16 = HMI_Text(sdn16,"sdn16");
HMI_Text e_sdt17 = HMI_Text(sdt17,"sdt17");
HMI_Text e_sdn17 = HMI_Text(sdn17,"sdn17");
HMI_Text e_sdt18 = HMI_Text(sdt18,"sdt18");
HMI_Text e_sdn18 = HMI_Text(sdn18,"sdn18");
HMI_Text e_sdt19 = HMI_Text(sdt19,"sdt19");
HMI_Text e_sdn19 = HMI_Text(sdn19,"sdn19");
HMI_Text e_sdt20 = HMI_Text(sdt20,"sdt20");
HMI_Text e_sdn20 = HMI_Text(sdn20,"sdn20");
HMI_Text e_sdt21 = HMI_Text(sdt21,"sdt21");
HMI_Text e_sdn21 = HMI_Text(sdn21,"sdn21");
HMI_Text e_sdt22 = HMI_Text(sdt22,"sdt22");
HMI_Text e_sdn22 = HMI_Text(sdn22,"sdn22");
HMI_Text e_sdt23 = HMI_Text(sdt23,"sdt23");
HMI_Text e_sdn23 = HMI_Text(sdn23,"sdn23");
HMI_Button e_b6 = HMI_Button(b6,"b6");
HMI_Object *hmiObjects[] = {
&e_b0,
&e_b1,
&e_b2,
&e_b3,
&e_b5,
&e_l1,
&e_m1,
&e_h1,
&e_l2,
&e_m2,
&e_h2,
&e_l3,
&e_m3,
&e_h3,
&e_l4,
&e_m4,
&e_h4,
&e_l5,
&e_m5,
&e_h5,
&e_l6,
&e_m6,
&e_h6,
&e_l7,
&e_m7,
&e_h7,
&e_l8,
&e_m8,
&e_h8,
&e_l9,
&e_m9,
&e_h9,
&e_l10,
&e_m10,
&e_h10,
&e_saveButton0,
&e_rev0,
&e_rev1,
&e_rev2,
&e_rev3,
&e_rev4,
&e_rev5,
&e_rev6,
&e_rev7,
&e_rev8,
&e_rev9,
&e_rev10,
&e_rev11,
&e_rev12,
&e_rev13,
&e_rev14,
&e_rev15,
&e_rev16,
&e_rev17,
&e_rev18,
&e_rev19,
&e_rev20,
&e_rev21,
&e_rev22,
&e_rev23,
&e_saveButton1,
NULL
};

void defaultCallback(HMI_Object* obj){
// Start UserCode : defaultCallback
	Serial.printf("Default callback for object %s", obj->getName());
// End UserCode : defaultCallback

}

void initHMI(){
// Start UserCode : PreInit
	HMI.setHMISerial(&Serial3);
// End UserCode : PreInit

	HMI.begin();
	e_b0.addTouchDownCallback(defaultCallback);
	e_b1.addTouchDownCallback(defaultCallback);
	e_b2.addTouchDownCallback(defaultCallback);
	e_b3.addTouchDownCallback(defaultCallback);
	e_b5.addTouchDownCallback(defaultCallback);
	e_l1.addTouchDownCallback(defaultCallback);
	e_m1.addTouchDownCallback(defaultCallback);
	e_h1.addTouchDownCallback(defaultCallback);
	e_l2.addTouchDownCallback(defaultCallback);
	e_m2.addTouchDownCallback(defaultCallback);
	e_h2.addTouchDownCallback(defaultCallback);
	e_l3.addTouchDownCallback(defaultCallback);
	e_m3.addTouchDownCallback(defaultCallback);
	e_h3.addTouchDownCallback(defaultCallback);
	e_l4.addTouchDownCallback(defaultCallback);
	e_m4.addTouchDownCallback(defaultCallback);
	e_h4.addTouchDownCallback(defaultCallback);
	e_l5.addTouchDownCallback(defaultCallback);
	e_m5.addTouchDownCallback(defaultCallback);
	e_h5.addTouchDownCallback(defaultCallback);
	e_l6.addTouchDownCallback(defaultCallback);
	e_m6.addTouchDownCallback(defaultCallback);
	e_h6.addTouchDownCallback(defaultCallback);
	e_l7.addTouchDownCallback(defaultCallback);
	e_m7.addTouchDownCallback(defaultCallback);
	e_h7.addTouchDownCallback(defaultCallback);
	e_l8.addTouchDownCallback(defaultCallback);
	e_m8.addTouchDownCallback(defaultCallback);
	e_h8.addTouchDownCallback(defaultCallback);
	e_l9.addTouchDownCallback(defaultCallback);
	e_m9.addTouchDownCallback(defaultCallback);
	e_h9.addTouchDownCallback(defaultCallback);
	e_l10.addTouchDownCallback(defaultCallback);
	e_m10.addTouchDownCallback(defaultCallback);
	e_h10.addTouchDownCallback(defaultCallback);
	e_saveButton0.addTouchDownCallback(defaultCallback);
	e_rev0.addTouchDownCallback(defaultCallback);
	e_rev1.addTouchDownCallback(defaultCallback);
	e_rev2.addTouchDownCallback(defaultCallback);
	e_rev3.addTouchDownCallback(defaultCallback);
	e_rev4.addTouchDownCallback(defaultCallback);
	e_rev5.addTouchDownCallback(defaultCallback);
	e_rev6.addTouchDownCallback(defaultCallback);
	e_rev7.addTouchDownCallback(defaultCallback);
	e_rev8.addTouchDownCallback(defaultCallback);
	e_rev9.addTouchDownCallback(defaultCallback);
	e_rev10.addTouchDownCallback(defaultCallback);
	e_rev11.addTouchDownCallback(defaultCallback);
	e_rev12.addTouchDownCallback(defaultCallback);
	e_rev13.addTouchDownCallback(defaultCallback);
	e_rev14.addTouchDownCallback(defaultCallback);
	e_rev15.addTouchDownCallback(defaultCallback);
	e_rev16.addTouchDownCallback(defaultCallback);
	e_rev17.addTouchDownCallback(defaultCallback);
	e_rev18.addTouchDownCallback(defaultCallback);
	e_rev19.addTouchDownCallback(defaultCallback);
	e_rev20.addTouchDownCallback(defaultCallback);
	e_rev21.addTouchDownCallback(defaultCallback);
	e_rev22.addTouchDownCallback(defaultCallback);
	e_rev23.addTouchDownCallback(defaultCallback);
	e_saveButton1.addTouchDownCallback(defaultCallback);
// Start UserCode : PostInit

// End UserCode : PostInit

}
// Start UserCode : Functions

// End UserCode : Functions

