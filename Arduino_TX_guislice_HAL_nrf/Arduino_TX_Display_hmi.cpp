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
HMI_Button e_saveButton0 = HMI_Button(saveButton0,"saveButton0");

HMI_Page p_setModel = HMI_Page(PAGE_TYPES::NORMAL, setModel,"setModel");
HMI_Text e_mn0 = HMI_Text(mn0,"mn0");
HMI_Text e_E_ELEM_TEXT267 = HMI_Text(E_ELEM_TEXT267,"E_ELEM_TEXT267");
HMI_Toggle e_m0 = HMI_Toggle(m0,"m0");
HMI_Text e_mn1 = HMI_Text(mn1,"mn1");
HMI_Text e_E_ELEM_TEXT269 = HMI_Text(E_ELEM_TEXT269,"E_ELEM_TEXT269");
HMI_Toggle e_m11 = HMI_Toggle(m11,"m11");
HMI_Text e_mn2 = HMI_Text(mn2,"mn2");
HMI_Text e_E_ELEM_TEXT271 = HMI_Text(E_ELEM_TEXT271,"E_ELEM_TEXT271");
HMI_Toggle e_m12 = HMI_Toggle(m12,"m12");
HMI_Text e_mn3 = HMI_Text(mn3,"mn3");
HMI_Text e_E_ELEM_TEXT273 = HMI_Text(E_ELEM_TEXT273,"E_ELEM_TEXT273");
HMI_Toggle e_m13 = HMI_Toggle(m13,"m13");
HMI_Text e_mn4 = HMI_Text(mn4,"mn4");
HMI_Text e_E_ELEM_TEXT275 = HMI_Text(E_ELEM_TEXT275,"E_ELEM_TEXT275");
HMI_Toggle e_m14 = HMI_Toggle(m14,"m14");
HMI_Text e_mn5 = HMI_Text(mn5,"mn5");
HMI_Text e_E_ELEM_TEXT277 = HMI_Text(E_ELEM_TEXT277,"E_ELEM_TEXT277");
HMI_Toggle e_m15 = HMI_Toggle(m15,"m15");
HMI_Text e_mn6 = HMI_Text(mn6,"mn6");
HMI_Text e_E_ELEM_TEXT279 = HMI_Text(E_ELEM_TEXT279,"E_ELEM_TEXT279");
HMI_Toggle e_m16 = HMI_Toggle(m16,"m16");
HMI_Text e_mn7 = HMI_Text(mn7,"mn7");
HMI_Text e_E_ELEM_TEXT281 = HMI_Text(E_ELEM_TEXT281,"E_ELEM_TEXT281");
HMI_Toggle e_m17 = HMI_Toggle(m17,"m17");
HMI_Button e_E_ELEM_BTN65 = HMI_Button(E_ELEM_BTN65,"E_ELEM_BTN65");
HMI_Object *hmiObjects[] = {
&e_nBatPercent,
&p_E_PG_MAIN,
&e_b0,
&e_b1,
&e_b2,
&e_b3,
&e_b5,
&p_DisplayValues,
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
&e_b4,
&p_setReverse,
&e_revtxt0,
&e_rev0,
&e_revtxt1,
&e_rev1,
&e_revtxt2,
&e_rev2,
&e_revtxt3,
&e_rev3,
&e_revtxt4,
&e_rev4,
&e_revtxt5,
&e_rev5,
&e_revtxt6,
&e_rev6,
&e_revtxt7,
&e_rev7,
&e_revtxt8,
&e_rev8,
&e_revtxt9,
&e_rev9,
&e_revtxt10,
&e_rev10,
&e_revtxt11,
&e_rev11,
&e_revtxt12,
&e_rev12,
&e_revtxt13,
&e_rev13,
&e_revtxt14,
&e_rev14,
&e_revtxt15,
&e_rev15,
&e_revtxt16,
&e_rev16,
&e_revtxt17,
&e_rev17,
&e_revtxt18,
&e_rev18,
&e_revtxt19,
&e_rev19,
&e_revtxt20,
&e_rev20,
&e_revtxt21,
&e_rev21,
&e_revtxt22,
&e_rev22,
&e_revtxt23,
&e_rev23,
&e_saveButton1,
&p_setDefaults,
&e_sdt0,
&e_sdn0,
&e_sdt1,
&e_sdn1,
&e_sdt2,
&e_sdn2,
&e_sdt3,
&e_sdn3,
&e_sdt4,
&e_sdn4,
&e_sdt5,
&e_sdn5,
&e_sdt6,
&e_sdn6,
&e_sdt7,
&e_sdn7,
&e_sdt8,
&e_sdn8,
&e_sdt9,
&e_sdn9,
&e_sdt10,
&e_sdn10,
&e_sdt11,
&e_sdn11,
&e_sdt12,
&e_sdn12,
&e_sdt13,
&e_sdn13,
&e_sdt14,
&e_sdn14,
&e_sdt15,
&e_sdn15,
&e_sdt16,
&e_sdn16,
&e_sdt17,
&e_sdn17,
&e_sdt18,
&e_sdn18,
&e_sdt19,
&e_sdn19,
&e_sdt20,
&e_sdn20,
&e_sdt21,
&e_sdn21,
&e_sdt22,
&e_sdn22,
&e_sdt23,
&e_sdn23,
&e_b6,
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
&e_saveButton0,
&p_setModel,
&e_mn0,
&e_E_ELEM_TEXT267,
&e_m0,
&e_mn1,
&e_E_ELEM_TEXT269,
&e_m11,
&e_mn2,
&e_E_ELEM_TEXT271,
&e_m12,
&e_mn3,
&e_E_ELEM_TEXT273,
&e_m13,
&e_mn4,
&e_E_ELEM_TEXT275,
&e_m14,
&e_mn5,
&e_E_ELEM_TEXT277,
&e_m15,
&e_mn6,
&e_E_ELEM_TEXT279,
&e_m16,
&e_mn7,
&e_E_ELEM_TEXT281,
&e_m17,
&e_E_ELEM_BTN65,
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
	e_b0.addTouchUpCallback(doNavigation);
	e_b1.addTouchUpCallback(doNavigation);
	e_b2.addTouchUpCallback(doNavigation);
	e_b3.addTouchUpCallback(doNavigation);
	e_b5.addTouchUpCallback(doNavigation);
	e_b4.addTouchUpCallback(doNavigation);
	e_rev0.addTouchUpCallback(defaultCallback);
	e_rev1.addTouchUpCallback(defaultCallback);
	e_rev2.addTouchUpCallback(defaultCallback);
	e_rev3.addTouchUpCallback(defaultCallback);
	e_rev4.addTouchUpCallback(defaultCallback);
	e_rev5.addTouchUpCallback(defaultCallback);
	e_rev6.addTouchUpCallback(defaultCallback);
	e_rev7.addTouchUpCallback(defaultCallback);
	e_rev8.addTouchUpCallback(defaultCallback);
	e_rev9.addTouchUpCallback(defaultCallback);
	e_rev10.addTouchUpCallback(defaultCallback);
	e_rev11.addTouchUpCallback(defaultCallback);
	e_rev12.addTouchUpCallback(defaultCallback);
	e_rev13.addTouchUpCallback(defaultCallback);
	e_rev14.addTouchUpCallback(defaultCallback);
	e_rev15.addTouchUpCallback(defaultCallback);
	e_rev16.addTouchUpCallback(defaultCallback);
	e_rev17.addTouchUpCallback(defaultCallback);
	e_rev18.addTouchUpCallback(defaultCallback);
	e_rev19.addTouchUpCallback(defaultCallback);
	e_rev20.addTouchUpCallback(defaultCallback);
	e_rev21.addTouchUpCallback(defaultCallback);
	e_rev22.addTouchUpCallback(defaultCallback);
	e_rev23.addTouchUpCallback(defaultCallback);
	e_saveButton1.addTouchUpCallback(doNavigation);
	e_b6.addTouchUpCallback(doNavigation);
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
	e_saveButton0.addTouchUpCallback(doNavigation);
	e_m0.addTouchUpCallback(defaultCallback);
	e_m11.addTouchUpCallback(defaultCallback);
	e_m12.addTouchUpCallback(defaultCallback);
	e_m13.addTouchUpCallback(defaultCallback);
	e_m14.addTouchUpCallback(defaultCallback);
	e_m15.addTouchUpCallback(defaultCallback);
	e_m16.addTouchUpCallback(defaultCallback);
	e_m17.addTouchUpCallback(defaultCallback);
	e_E_ELEM_BTN65.addTouchUpCallback(doNavigation);
// Start UserCode : PostInit

// End UserCode : PostInit

}
// Start UserCode : Functions
void doNavigation(HMI_Object* navBtn) {
	switch (navBtn->getElementId()) {
	case b0:
		p_DisplayValues.navigateTo();
		break;
	case b1:
		p_calibrations.navigateTo();
		break;
	case b2:
		p_setReverse.navigateTo();
		break;
	case b3:
		p_setModel.navigateTo();
		break;
	case b5:
		p_calibrations.navigateTo();
		break;
	case b4:
	case saveButton0:
		saveSettings();
		p_E_PG_MAIN.navigateTo();
		break;
	case saveButton1:
	case E_ELEM_BTN65:
	case b6:
		p_E_PG_MAIN.navigateTo();
		break;
	}
}
void setupMinMaxMid(HMI_Object* obj)
{
	String objName = String(obj->getName());
	int objCHId = objName.substring(1).toInt();
	uint16_t adcVal = ADCDMABuffer[objCHId - 1];
	if (objName.charAt(0) == 'l') {
		settings.model[settings.activeModel].channel_settings.chMin[objCHId - 1] = adcVal;
		Serial.printf("Setting min of ch%d to %d\n", objCHId, adcVal);
	} else if (objName.charAt(0) == 'm') {
		settings.model[settings.activeModel].channel_settings.chMid[objCHId - 1] = adcVal;
		Serial.printf("Setting mid of ch%d to %d\n", objCHId, adcVal);
	} else if (objName.charAt(0) == 'h') {
		settings.model[settings.activeModel].channel_settings.chMax[objCHId - 1] = adcVal;
		Serial.printf("Setting max of ch%d to %d\n", objCHId, adcVal);
	}
}
// End UserCode : Functions

