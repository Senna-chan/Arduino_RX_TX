//<File !Start!>
// FILE: [Arduino_TX_Display_GSLC.h]
// Created by GUIslice Builder version: [0.16.b006]
//
// GUIslice Builder Generated GUI Framework File
//
// For the latest guides, updates and support view:
// https://github.com/ImpulseAdventure/GUIslice
//
//<File !End!>

#ifndef _GUISLICE_GEN_H
#define _GUISLICE_GEN_H

// ------------------------------------------------
// Headers to include
// ------------------------------------------------
#include "GUIslice.h"
#include "GUIslice_drv.h"

// Include any extended elements
//<Includes !Start!>
// Include extended elements
#include "elem/XSlider.h"
#include "elem/XTogglebtn.h"
//<Includes !End!>

// ------------------------------------------------
// Headers and Defines for fonts
// Note that font files are located within the Adafruit-GFX library folder:
// ------------------------------------------------
//<Fonts !Start!>
#if defined(DRV_DISP_TFT_ESPI)
  #error Project tab->Target Platform should be tft_espi
#endif
#include <Adafruit_GFX.h>
//<Fonts !End!>

// ------------------------------------------------
// Defines for resources
// ------------------------------------------------
//<Resources !Start!>
//<Resources !End!>

// ------------------------------------------------
// Enumerations for pages, elements, fonts, images
// ------------------------------------------------
//<Enum !Start!>
enum {BasePage,E_PG_MAIN,DisplayValues,setReverse,setDefaults
      ,calibrations,setModel};
enum {E_ELEM_BTN65,E_ELEM_TEXT267,E_ELEM_TEXT269,E_ELEM_TEXT271
      ,E_ELEM_TEXT273,E_ELEM_TEXT275,E_ELEM_TEXT277,E_ELEM_TEXT279
      ,E_ELEM_TEXT281,E_ELEM_TEXT922,E_ELEM_TEXT923,E_ELEM_TEXT924
      ,E_ELEM_TEXT925,E_ELEM_TEXT926,E_ELEM_TEXT927,E_ELEM_TEXT928
      ,E_ELEM_TEXT929,E_ELEM_TEXT930,E_ELEM_TEXT931,E_ELEM_TEXT952,b0
      ,b1,b2,b3,b4,b5,b6,c1,c10,c2,c3,c4,c5,c6,c7,c8,c9,d1,d10,d2,d3,d4
      ,d5,d6,d7,d8,d9,deadzone0,deadzonetxt,h1,h10,h2,h3,h4,h5,h6,h7,h8
      ,h9,l1,l10,l2,l3,l4,l5,l6,l7,l8,l9,m0,m1,m10,m11,m12,m13,m14,m15
      ,m16,m17,m2,m3,m4,m5,m6,m7,m8,m9,mn0,mn1,mn2,mn3,mn4,mn5,mn6,mn7
      ,n0,n1,n10,n11,n12,n13,n14,n15,n16,n17,n18,n19,n2,n20,n21,n22,n23
      ,n3,n4,n5,n6,n7,n8,n9,nBatPercent,rev0,rev1,rev10,rev11,rev12
      ,rev13,rev14,rev15,rev16,rev17,rev18,rev19,rev2,rev20,rev21,rev22
      ,rev23,rev3,rev4,rev5,rev6,rev7,rev8,rev9,revtxt0,revtxt1
      ,revtxt10,revtxt11,revtxt12,revtxt13,revtxt14,revtxt15,revtxt16
      ,revtxt17,revtxt18,revtxt19,revtxt2,revtxt20,revtxt21,revtxt22
      ,revtxt23,revtxt3,revtxt4,revtxt5,revtxt6,revtxt7,revtxt8,revtxt9
      ,saveButton0,saveButton1,sdn0,sdn1,sdn10,sdn11,sdn12,sdn13,sdn14
      ,sdn15,sdn16,sdn17,sdn18,sdn19,sdn2,sdn20,sdn21,sdn22,sdn23,sdn3
      ,sdn4,sdn5,sdn6,sdn7,sdn8,sdn9,sdt0,sdt1,sdt10,sdt11,sdt12,sdt13
      ,sdt14,sdt15,sdt16,sdt17,sdt18,sdt19,sdt2,sdt20,sdt21,sdt22,sdt23
      ,sdt3,sdt4,sdt5,sdt6,sdt7,sdt8,sdt9,t0,t1,t10,t11,t12,t13,t14,t15
      ,t16,t17,t18,t19,t2,t20,t21,t22,t23,t3,t4,t5,t6,t7,t8,t9};
// Must use separate enum for fonts with MAX_FONT at end to use gslc_FontSet.
enum {E_BUILTIN5X8,MAX_FONT};
//<Enum !End!>

// ------------------------------------------------
// Instantiate the GUI
// ------------------------------------------------

// ------------------------------------------------
// Define the maximum number of elements and pages
// ------------------------------------------------
//<ElementDefines !Start!>
#define MAX_PAGE                7

#define MAX_ELEM_BasePage 1 // # Elems total on page
#define MAX_ELEM_BasePage_RAM MAX_ELEM_BasePage // # Elems in RAM

#define MAX_ELEM_PG_MAIN 5 // # Elems total on page
#define MAX_ELEM_PG_MAIN_RAM MAX_ELEM_PG_MAIN // # Elems in RAM

#define MAX_ELEM_DisplayValues 49 // # Elems total on page
#define MAX_ELEM_DisplayValues_RAM MAX_ELEM_DisplayValues // # Elems in RAM

#define MAX_ELEM_setReverse 49 // # Elems total on page
#define MAX_ELEM_setReverse_RAM MAX_ELEM_setReverse // # Elems in RAM

#define MAX_ELEM_setDefaults 49 // # Elems total on page
#define MAX_ELEM_setDefaults_RAM MAX_ELEM_setDefaults // # Elems in RAM

#define MAX_ELEM_calibrations 64 // # Elems total on page
#define MAX_ELEM_calibrations_RAM MAX_ELEM_calibrations // # Elems in RAM

#define MAX_ELEM_setModel 25 // # Elems total on page
#define MAX_ELEM_setModel_RAM MAX_ELEM_setModel // # Elems in RAM
//<ElementDefines !End!>

// ------------------------------------------------
// Create element storage
// ------------------------------------------------
gslc_tsGui                      m_gui;
gslc_tsDriver                   m_drv;
gslc_tsFont                     m_asFont[MAX_FONT];
gslc_tsPage                     m_asPage[MAX_PAGE];

//<GUI_Extra_Elements !Start!>
gslc_tsElem                     m_asBasePage1Elem[MAX_ELEM_BasePage_RAM];
gslc_tsElemRef                  m_asBasePage1ElemRef[MAX_ELEM_BasePage];
gslc_tsElem                     m_asPage1Elem[MAX_ELEM_PG_MAIN_RAM];
gslc_tsElemRef                  m_asPage1ElemRef[MAX_ELEM_PG_MAIN];
gslc_tsElem                     m_asPage3Elem[MAX_ELEM_DisplayValues_RAM];
gslc_tsElemRef                  m_asPage3ElemRef[MAX_ELEM_DisplayValues];
gslc_tsElem                     m_asPage4Elem[MAX_ELEM_setReverse_RAM];
gslc_tsElemRef                  m_asPage4ElemRef[MAX_ELEM_setReverse];
gslc_tsElem                     m_asPage6Elem[MAX_ELEM_setDefaults_RAM];
gslc_tsElemRef                  m_asPage6ElemRef[MAX_ELEM_setDefaults];
gslc_tsElem                     m_asPage8Elem[MAX_ELEM_calibrations_RAM];
gslc_tsElemRef                  m_asPage8ElemRef[MAX_ELEM_calibrations];
gslc_tsElem                     m_asPage9Elem[MAX_ELEM_setModel_RAM];
gslc_tsElemRef                  m_asPage9ElemRef[MAX_ELEM_setModel];
gslc_tsXTogglebtn               m_asXToggle1;
gslc_tsXTogglebtn               m_asXToggle2;
gslc_tsXTogglebtn               m_asXToggle3;
gslc_tsXTogglebtn               m_asXToggle4;
gslc_tsXTogglebtn               m_asXToggle5;
gslc_tsXTogglebtn               m_asXToggle6;
gslc_tsXTogglebtn               m_asXToggle7;
gslc_tsXTogglebtn               m_asXToggle8;
gslc_tsXTogglebtn               m_asXToggle9;
gslc_tsXTogglebtn               m_asXToggle10;
gslc_tsXTogglebtn               m_asXToggle11;
gslc_tsXTogglebtn               m_asXToggle12;
gslc_tsXTogglebtn               m_asXToggle13;
gslc_tsXTogglebtn               m_asXToggle14;
gslc_tsXTogglebtn               m_asXToggle15;
gslc_tsXTogglebtn               m_asXToggle16;
gslc_tsXTogglebtn               m_asXToggle17;
gslc_tsXTogglebtn               m_asXToggle18;
gslc_tsXTogglebtn               m_asXToggle19;
gslc_tsXTogglebtn               m_asXToggle20;
gslc_tsXTogglebtn               m_asXToggle21;
gslc_tsXTogglebtn               m_asXToggle22;
gslc_tsXTogglebtn               m_asXToggle23;
gslc_tsXTogglebtn               m_asXToggle24;
gslc_tsXSlider                  m_sXSlider2;
gslc_tsXTogglebtn               m_asXToggle33;
gslc_tsXTogglebtn               m_asXToggle34;
gslc_tsXTogglebtn               m_asXToggle35;
gslc_tsXTogglebtn               m_asXToggle36;
gslc_tsXTogglebtn               m_asXToggle37;
gslc_tsXTogglebtn               m_asXToggle38;
gslc_tsXTogglebtn               m_asXToggle39;
gslc_tsXTogglebtn               m_asXToggle40;

#define MAX_STR                 100

//<GUI_Extra_Elements !End!>

// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Element References for direct access
//<Extern_References !Start!>
extern gslc_tsElemRef* m_pElemSlider2;
extern gslc_tsElemRef* m_pElemToggle1;
extern gslc_tsElemRef* m_pElemToggle10;
extern gslc_tsElemRef* m_pElemToggle11;
extern gslc_tsElemRef* m_pElemToggle12;
extern gslc_tsElemRef* m_pElemToggle13;
extern gslc_tsElemRef* m_pElemToggle14;
extern gslc_tsElemRef* m_pElemToggle15;
extern gslc_tsElemRef* m_pElemToggle16;
extern gslc_tsElemRef* m_pElemToggle17;
extern gslc_tsElemRef* m_pElemToggle18;
extern gslc_tsElemRef* m_pElemToggle19;
extern gslc_tsElemRef* m_pElemToggle2;
extern gslc_tsElemRef* m_pElemToggle20;
extern gslc_tsElemRef* m_pElemToggle21;
extern gslc_tsElemRef* m_pElemToggle22;
extern gslc_tsElemRef* m_pElemToggle23;
extern gslc_tsElemRef* m_pElemToggle24;
extern gslc_tsElemRef* m_pElemToggle3;
extern gslc_tsElemRef* m_pElemToggle33;
extern gslc_tsElemRef* m_pElemToggle34;
extern gslc_tsElemRef* m_pElemToggle35;
extern gslc_tsElemRef* m_pElemToggle36;
extern gslc_tsElemRef* m_pElemToggle37;
extern gslc_tsElemRef* m_pElemToggle38;
extern gslc_tsElemRef* m_pElemToggle39;
extern gslc_tsElemRef* m_pElemToggle4;
extern gslc_tsElemRef* m_pElemToggle40;
extern gslc_tsElemRef* m_pElemToggle5;
extern gslc_tsElemRef* m_pElemToggle6;
extern gslc_tsElemRef* m_pElemToggle7;
extern gslc_tsElemRef* m_pElemToggle8;
extern gslc_tsElemRef* m_pElemToggle9;
//<Extern_References !End!>

// Define debug message function
static int16_t DebugOut(char ch);

// ------------------------------------------------
// Callback Methods
// ------------------------------------------------
bool CbBtnCommon(void* pvGui,void *pvElemRef,gslc_teTouch eTouch,int16_t nX,int16_t nY);
bool CbCheckbox(void* pvGui, void* pvElemRef, int16_t nSelId, bool bState);
bool CbDrawScanner(void* pvGui,void* pvElemRef,gslc_teRedrawType eRedraw);
bool CbKeypad(void* pvGui, void *pvElemRef, int16_t nState, void* pvData);
bool CbListbox(void* pvGui, void* pvElemRef, int16_t nSelId);
bool CbSlidePos(void* pvGui,void* pvElemRef,int16_t nPos);
bool CbSpinner(void* pvGui, void *pvElemRef, int16_t nState, void* pvData);
bool CbTickScanner(void* pvGui,void* pvScope);

// ------------------------------------------------
// Create page elements
// ------------------------------------------------
void InitGUIslice_gen()
{
  gslc_tsElemRef* pElemRef = NULL;

  if (!gslc_Init(&m_gui,&m_drv,m_asPage,MAX_PAGE,m_asFont,MAX_FONT)) { return; }

  // ------------------------------------------------
  // Load Fonts
  // ------------------------------------------------
//<Load_Fonts !Start!>
    if (!gslc_FontSet(&m_gui,E_BUILTIN5X8,GSLC_FONTREF_PTR,NULL,1)) { return; }
//<Load_Fonts !End!>

//<InitGUI !Start!>
  gslc_PageAdd(&m_gui,BasePage,m_asBasePage1Elem,MAX_ELEM_BasePage_RAM,m_asBasePage1ElemRef,MAX_ELEM_BasePage);
  gslc_PageSetHmiEvents(&m_gui,BasePage, true, false);
  gslc_PageAdd(&m_gui,E_PG_MAIN,m_asPage1Elem,MAX_ELEM_PG_MAIN_RAM,m_asPage1ElemRef,MAX_ELEM_PG_MAIN);
  gslc_PageSetHmiEvents(&m_gui,E_PG_MAIN, false, false);
  gslc_PageAdd(&m_gui,DisplayValues,m_asPage3Elem,MAX_ELEM_DisplayValues_RAM,m_asPage3ElemRef,MAX_ELEM_DisplayValues);
  gslc_PageSetHmiEvents(&m_gui,DisplayValues, true, false);
  gslc_PageAdd(&m_gui,setReverse,m_asPage4Elem,MAX_ELEM_setReverse_RAM,m_asPage4ElemRef,MAX_ELEM_setReverse);
  gslc_PageSetHmiEvents(&m_gui,setReverse, true, false);
  gslc_PageAdd(&m_gui,setDefaults,m_asPage6Elem,MAX_ELEM_setDefaults_RAM,m_asPage6ElemRef,MAX_ELEM_setDefaults);
  gslc_PageSetHmiEvents(&m_gui,setDefaults, true, false);
  gslc_PageAdd(&m_gui,calibrations,m_asPage8Elem,MAX_ELEM_calibrations_RAM,m_asPage8ElemRef,MAX_ELEM_calibrations);
  gslc_PageSetHmiEvents(&m_gui,calibrations, true, false);
  gslc_PageAdd(&m_gui,setModel,m_asPage9Elem,MAX_ELEM_setModel_RAM,m_asPage9ElemRef,MAX_ELEM_setModel);
  gslc_PageSetHmiEvents(&m_gui,setModel, true, false);

  // Now mark BasePage as a "base" page which means that it's elements
  // are always visible. This is useful for common page elements.
  gslc_SetPageBase(&m_gui, BasePage);


  // NOTE: The current page defaults to the first page added. Here we explicitly
  //       ensure that the main page is the correct page no matter the add order.
  gslc_SetPageCur(&m_gui,E_PG_MAIN);
  
  // Set Background to a flat color
  gslc_SetBkgndColor(&m_gui,GSLC_COL_BLACK);

  // -----------------------------------
  // PAGE: BasePage
  
  
  // Create nBatPercent text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,nBatPercent,BasePage,(gslc_tsRect){0,0,73,10},
    (char*)"Battery 100%",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);

  // -----------------------------------
  // PAGE: E_PG_MAIN
  
  
  // create b0 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,b0,E_PG_MAIN,
    (gslc_tsRect){20,40,100,25},(char*)"Start",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create b1 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,b1,E_PG_MAIN,
    (gslc_tsRect){20,80,100,25},(char*)"setup min/max",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create b2 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,b2,E_PG_MAIN,
    (gslc_tsRect){20,120,100,25},(char*)"Setup reverse",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create b3 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,b3,E_PG_MAIN,
    (gslc_tsRect){20,160,100,25},(char*)"Choose model",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create b5 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,b5,E_PG_MAIN,
    (gslc_tsRect){20,200,100,25},(char*)"Setup Defaults",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);

  // -----------------------------------
  // PAGE: DisplayValues
  
  
  // Create t0 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t0,DisplayValues,(gslc_tsRect){5,15,19,10},
    (char*)"ch1",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n0 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n0,DisplayValues,(gslc_tsRect){45,15,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t1 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t1,DisplayValues,(gslc_tsRect){5,35,19,10},
    (char*)"ch2",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n1 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n1,DisplayValues,(gslc_tsRect){45,35,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t2 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t2,DisplayValues,(gslc_tsRect){5,55,19,10},
    (char*)"ch3",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n2 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n2,DisplayValues,(gslc_tsRect){45,55,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t3 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t3,DisplayValues,(gslc_tsRect){5,75,19,10},
    (char*)"ch4",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n3 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n3,DisplayValues,(gslc_tsRect){45,75,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t4 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t4,DisplayValues,(gslc_tsRect){5,95,19,10},
    (char*)"ch5",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n4 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n4,DisplayValues,(gslc_tsRect){45,95,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t5 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t5,DisplayValues,(gslc_tsRect){5,115,19,10},
    (char*)"ch6",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n5 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n5,DisplayValues,(gslc_tsRect){45,115,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t6 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t6,DisplayValues,(gslc_tsRect){5,135,19,10},
    (char*)"ch7",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n6 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n6,DisplayValues,(gslc_tsRect){45,135,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t7 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t7,DisplayValues,(gslc_tsRect){5,155,19,10},
    (char*)"ch8",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n7 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n7,DisplayValues,(gslc_tsRect){45,155,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t8 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t8,DisplayValues,(gslc_tsRect){95,15,19,10},
    (char*)"ch9",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n8 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n8,DisplayValues,(gslc_tsRect){135,15,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t9 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t9,DisplayValues,(gslc_tsRect){95,35,25,10},
    (char*)"ch10",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n9 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n9,DisplayValues,(gslc_tsRect){135,35,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t10 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t10,DisplayValues,(gslc_tsRect){95,55,25,10},
    (char*)"ch11",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n10 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n10,DisplayValues,(gslc_tsRect){135,55,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t11 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t11,DisplayValues,(gslc_tsRect){95,75,25,10},
    (char*)"ch12",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n11 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n11,DisplayValues,(gslc_tsRect){135,75,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t12 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t12,DisplayValues,(gslc_tsRect){95,95,25,10},
    (char*)"ch13",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n12 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n12,DisplayValues,(gslc_tsRect){135,95,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t13 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t13,DisplayValues,(gslc_tsRect){95,115,25,10},
    (char*)"ch14",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n13 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n13,DisplayValues,(gslc_tsRect){135,115,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t14 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t14,DisplayValues,(gslc_tsRect){95,135,25,10},
    (char*)"ch15",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n14 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n14,DisplayValues,(gslc_tsRect){135,135,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t15 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t15,DisplayValues,(gslc_tsRect){95,155,25,10},
    (char*)"ch16",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n15 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n15,DisplayValues,(gslc_tsRect){135,155,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t16 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t16,DisplayValues,(gslc_tsRect){185,15,25,10},
    (char*)"ch17",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n16 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n16,DisplayValues,(gslc_tsRect){235,15,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t17 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t17,DisplayValues,(gslc_tsRect){185,35,25,10},
    (char*)"ch18",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n17 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n17,DisplayValues,(gslc_tsRect){235,35,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t18 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t18,DisplayValues,(gslc_tsRect){185,55,25,10},
    (char*)"ch19",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n18 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n18,DisplayValues,(gslc_tsRect){235,55,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t19 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t19,DisplayValues,(gslc_tsRect){185,75,25,10},
    (char*)"ch20",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n19 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n19,DisplayValues,(gslc_tsRect){235,75,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t20 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t20,DisplayValues,(gslc_tsRect){185,95,25,10},
    (char*)"ch21",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n20 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n20,DisplayValues,(gslc_tsRect){235,95,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t21 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t21,DisplayValues,(gslc_tsRect){185,115,25,10},
    (char*)"ch22",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n21 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n21,DisplayValues,(gslc_tsRect){235,115,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t22 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t22,DisplayValues,(gslc_tsRect){185,135,25,10},
    (char*)"ch23",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n22 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n22,DisplayValues,(gslc_tsRect){235,135,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t23 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t23,DisplayValues,(gslc_tsRect){185,155,25,10},
    (char*)"ch24",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n23 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n23,DisplayValues,(gslc_tsRect){235,155,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // create b4 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,b4,DisplayValues,
    (gslc_tsRect){0,180,80,40},(char*)"Back",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);

  // -----------------------------------
  // PAGE: setReverse
  
  
  // Create revtxt0 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,revtxt0,setReverse,(gslc_tsRect){13,37,19,10},
    (char*)"ch1",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button rev0
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,rev0,setReverse,&m_asXToggle1,
    (gslc_tsRect){5,15,35,20},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pElemToggle1 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create revtxt1 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,revtxt1,setReverse,(gslc_tsRect){53,37,19,10},
    (char*)"ch2",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button rev1
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,rev1,setReverse,&m_asXToggle2,
    (gslc_tsRect){45,15,35,20},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pElemToggle2 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create revtxt2 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,revtxt2,setReverse,(gslc_tsRect){93,37,19,10},
    (char*)"ch3",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button rev2
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,rev2,setReverse,&m_asXToggle3,
    (gslc_tsRect){85,15,35,20},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pElemToggle3 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create revtxt3 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,revtxt3,setReverse,(gslc_tsRect){133,37,19,10},
    (char*)"ch4",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button rev3
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,rev3,setReverse,&m_asXToggle4,
    (gslc_tsRect){125,15,35,20},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pElemToggle4 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create revtxt4 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,revtxt4,setReverse,(gslc_tsRect){173,37,19,10},
    (char*)"ch5",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button rev4
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,rev4,setReverse,&m_asXToggle5,
    (gslc_tsRect){165,15,35,20},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pElemToggle5 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create revtxt5 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,revtxt5,setReverse,(gslc_tsRect){213,37,19,10},
    (char*)"ch6",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button rev5
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,rev5,setReverse,&m_asXToggle6,
    (gslc_tsRect){205,15,35,20},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pElemToggle6 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create revtxt6 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,revtxt6,setReverse,(gslc_tsRect){253,37,19,10},
    (char*)"ch7",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button rev6
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,rev6,setReverse,&m_asXToggle7,
    (gslc_tsRect){245,15,35,20},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pElemToggle7 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create revtxt7 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,revtxt7,setReverse,(gslc_tsRect){293,37,19,10},
    (char*)"ch8",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button rev7
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,rev7,setReverse,&m_asXToggle8,
    (gslc_tsRect){285,15,35,20},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pElemToggle8 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create revtxt8 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,revtxt8,setReverse,(gslc_tsRect){13,97,19,10},
    (char*)"ch9",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button rev8
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,rev8,setReverse,&m_asXToggle9,
    (gslc_tsRect){5,75,35,20},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pElemToggle9 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create revtxt9 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,revtxt9,setReverse,(gslc_tsRect){50,97,25,10},
    (char*)"ch10",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button rev9
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,rev9,setReverse,&m_asXToggle10,
    (gslc_tsRect){45,75,35,20},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pElemToggle10 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create revtxt10 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,revtxt10,setReverse,(gslc_tsRect){90,97,25,10},
    (char*)"ch11",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button rev10
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,rev10,setReverse,&m_asXToggle11,
    (gslc_tsRect){85,75,35,20},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pElemToggle11 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create revtxt11 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,revtxt11,setReverse,(gslc_tsRect){130,97,25,10},
    (char*)"ch12",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button rev11
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,rev11,setReverse,&m_asXToggle12,
    (gslc_tsRect){125,75,35,20},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pElemToggle12 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create revtxt12 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,revtxt12,setReverse,(gslc_tsRect){170,97,25,10},
    (char*)"ch13",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button rev12
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,rev12,setReverse,&m_asXToggle13,
    (gslc_tsRect){165,75,35,20},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pElemToggle13 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create revtxt13 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,revtxt13,setReverse,(gslc_tsRect){210,97,25,10},
    (char*)"ch14",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button rev13
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,rev13,setReverse,&m_asXToggle14,
    (gslc_tsRect){205,75,35,20},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pElemToggle14 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create revtxt14 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,revtxt14,setReverse,(gslc_tsRect){250,97,25,10},
    (char*)"ch15",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button rev14
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,rev14,setReverse,&m_asXToggle15,
    (gslc_tsRect){245,75,35,20},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pElemToggle15 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create revtxt15 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,revtxt15,setReverse,(gslc_tsRect){290,97,25,10},
    (char*)"ch16",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button rev15
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,rev15,setReverse,&m_asXToggle16,
    (gslc_tsRect){285,75,35,20},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pElemToggle16 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create revtxt16 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,revtxt16,setReverse,(gslc_tsRect){10,157,25,10},
    (char*)"ch17",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button rev16
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,rev16,setReverse,&m_asXToggle17,
    (gslc_tsRect){5,135,35,20},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pElemToggle17 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create revtxt17 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,revtxt17,setReverse,(gslc_tsRect){50,157,25,10},
    (char*)"ch18",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button rev17
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,rev17,setReverse,&m_asXToggle18,
    (gslc_tsRect){45,135,35,20},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pElemToggle18 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create revtxt18 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,revtxt18,setReverse,(gslc_tsRect){90,157,25,10},
    (char*)"ch19",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button rev18
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,rev18,setReverse,&m_asXToggle19,
    (gslc_tsRect){85,135,35,20},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pElemToggle19 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create revtxt19 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,revtxt19,setReverse,(gslc_tsRect){130,157,25,10},
    (char*)"ch20",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button rev19
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,rev19,setReverse,&m_asXToggle20,
    (gslc_tsRect){125,135,35,20},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pElemToggle20 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create revtxt20 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,revtxt20,setReverse,(gslc_tsRect){170,157,25,10},
    (char*)"ch21",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button rev20
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,rev20,setReverse,&m_asXToggle21,
    (gslc_tsRect){165,135,35,20},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pElemToggle21 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create revtxt21 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,revtxt21,setReverse,(gslc_tsRect){210,157,25,10},
    (char*)"ch22",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button rev21
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,rev21,setReverse,&m_asXToggle22,
    (gslc_tsRect){205,135,35,20},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pElemToggle22 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create revtxt22 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,revtxt22,setReverse,(gslc_tsRect){250,157,25,10},
    (char*)"ch23",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button rev22
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,rev22,setReverse,&m_asXToggle23,
    (gslc_tsRect){245,135,35,20},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pElemToggle23 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create revtxt23 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,revtxt23,setReverse,(gslc_tsRect){290,157,25,10},
    (char*)"ch24",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button rev23
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,rev23,setReverse,&m_asXToggle24,
    (gslc_tsRect){285,135,35,20},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pElemToggle24 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create saveButton1 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,saveButton1,setReverse,
    (gslc_tsRect){110,180,100,40},(char*)"Save",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);

  // -----------------------------------
  // PAGE: setDefaults
  
  
  // Create sdt0 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdt0,setDefaults,(gslc_tsRect){5,10,19,10},
    (char*)"ch1",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdn0 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdn0,setDefaults,(gslc_tsRect){45,10,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdt1 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdt1,setDefaults,(gslc_tsRect){5,30,19,10},
    (char*)"ch2",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdn1 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdn1,setDefaults,(gslc_tsRect){45,30,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdt2 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdt2,setDefaults,(gslc_tsRect){5,50,19,10},
    (char*)"ch3",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdn2 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdn2,setDefaults,(gslc_tsRect){45,50,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdt3 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdt3,setDefaults,(gslc_tsRect){5,70,19,10},
    (char*)"ch4",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdn3 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdn3,setDefaults,(gslc_tsRect){45,70,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdt4 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdt4,setDefaults,(gslc_tsRect){5,90,19,10},
    (char*)"ch5",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdn4 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdn4,setDefaults,(gslc_tsRect){45,90,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdt5 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdt5,setDefaults,(gslc_tsRect){5,110,19,10},
    (char*)"ch6",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdn5 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdn5,setDefaults,(gslc_tsRect){45,110,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdt6 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdt6,setDefaults,(gslc_tsRect){5,130,19,10},
    (char*)"ch7",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdn6 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdn6,setDefaults,(gslc_tsRect){45,130,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdt7 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdt7,setDefaults,(gslc_tsRect){5,150,19,10},
    (char*)"ch8",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdn7 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdn7,setDefaults,(gslc_tsRect){45,150,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdt8 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdt8,setDefaults,(gslc_tsRect){95,10,19,10},
    (char*)"ch9",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdn8 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdn8,setDefaults,(gslc_tsRect){135,10,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdt9 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdt9,setDefaults,(gslc_tsRect){95,30,25,10},
    (char*)"ch10",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdn9 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdn9,setDefaults,(gslc_tsRect){135,30,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdt10 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdt10,setDefaults,(gslc_tsRect){95,50,25,10},
    (char*)"ch11",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdn10 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdn10,setDefaults,(gslc_tsRect){135,50,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdt11 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdt11,setDefaults,(gslc_tsRect){95,70,25,10},
    (char*)"ch12",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdn11 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdn11,setDefaults,(gslc_tsRect){135,70,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdt12 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdt12,setDefaults,(gslc_tsRect){95,90,25,10},
    (char*)"ch13",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdn12 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdn12,setDefaults,(gslc_tsRect){135,90,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdt13 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdt13,setDefaults,(gslc_tsRect){95,110,25,10},
    (char*)"ch14",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdn13 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdn13,setDefaults,(gslc_tsRect){135,110,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdt14 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdt14,setDefaults,(gslc_tsRect){95,130,25,10},
    (char*)"ch15",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdn14 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdn14,setDefaults,(gslc_tsRect){135,130,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdt15 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdt15,setDefaults,(gslc_tsRect){95,150,25,10},
    (char*)"ch16",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdn15 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdn15,setDefaults,(gslc_tsRect){135,150,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdt16 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdt16,setDefaults,(gslc_tsRect){185,10,25,10},
    (char*)"ch17",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdn16 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdn16,setDefaults,(gslc_tsRect){235,10,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdt17 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdt17,setDefaults,(gslc_tsRect){185,30,25,10},
    (char*)"ch18",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdn17 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdn17,setDefaults,(gslc_tsRect){235,30,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdt18 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdt18,setDefaults,(gslc_tsRect){185,50,25,10},
    (char*)"ch19",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdn18 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdn18,setDefaults,(gslc_tsRect){235,50,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdt19 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdt19,setDefaults,(gslc_tsRect){185,70,25,10},
    (char*)"ch20",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdn19 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdn19,setDefaults,(gslc_tsRect){235,70,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdt20 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdt20,setDefaults,(gslc_tsRect){185,90,25,10},
    (char*)"ch21",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdn20 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdn20,setDefaults,(gslc_tsRect){235,90,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdt21 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdt21,setDefaults,(gslc_tsRect){185,110,25,10},
    (char*)"ch22",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdn21 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdn21,setDefaults,(gslc_tsRect){235,110,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdt22 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdt22,setDefaults,(gslc_tsRect){185,130,25,10},
    (char*)"ch23",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdn22 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdn22,setDefaults,(gslc_tsRect){235,130,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdt23 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdt23,setDefaults,(gslc_tsRect){185,150,25,10},
    (char*)"ch24",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create sdn23 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,sdn23,setDefaults,(gslc_tsRect){235,150,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // create b6 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,b6,setDefaults,
    (gslc_tsRect){0,180,80,40},(char*)"Back",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);

  // -----------------------------------
  // PAGE: calibrations
  
  
  // Create E_ELEM_TEXT922 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT922,calibrations,(gslc_tsRect){40,20,19,10},
    (char*)"CH1",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT923 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT923,calibrations,(gslc_tsRect){40,60,19,10},
    (char*)"CH2",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT924 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT924,calibrations,(gslc_tsRect){40,100,19,10},
    (char*)"CH3",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT925 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT925,calibrations,(gslc_tsRect){40,140,19,10},
    (char*)"CH4",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT926 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT926,calibrations,(gslc_tsRect){40,180,19,10},
    (char*)"CH5",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT927 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT927,calibrations,(gslc_tsRect){190,20,19,10},
    (char*)"CH6",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT928 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT928,calibrations,(gslc_tsRect){190,60,19,10},
    (char*)"CH7",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT929 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT929,calibrations,(gslc_tsRect){190,100,19,10},
    (char*)"CH8",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT930 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT930,calibrations,(gslc_tsRect){190,140,19,10},
    (char*)"CH9",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT931 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT931,calibrations,(gslc_tsRect){190,180,25,10},
    (char*)"CH10",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create d1 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,d1,calibrations,(gslc_tsRect){70,20,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create c1 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,c1,calibrations,(gslc_tsRect){110,20,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // create l1 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,l1,calibrations,
    (gslc_tsRect){30,35,35,20},(char*)"min",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create m1 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,m1,calibrations,
    (gslc_tsRect){65,35,35,20},(char*)"mid",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create h1 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,h1,calibrations,
    (gslc_tsRect){100,35,35,20},(char*)"max",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create d2 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,d2,calibrations,(gslc_tsRect){70,60,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create c2 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,c2,calibrations,(gslc_tsRect){110,60,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // create l2 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,l2,calibrations,
    (gslc_tsRect){30,75,35,20},(char*)"min",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create m2 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,m2,calibrations,
    (gslc_tsRect){65,75,35,20},(char*)"mid",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create h2 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,h2,calibrations,
    (gslc_tsRect){100,75,35,20},(char*)"max",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create d3 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,d3,calibrations,(gslc_tsRect){70,100,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create c3 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,c3,calibrations,(gslc_tsRect){110,100,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // create l3 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,l3,calibrations,
    (gslc_tsRect){30,115,35,20},(char*)"min",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create m3 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,m3,calibrations,
    (gslc_tsRect){65,115,35,20},(char*)"mid",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create h3 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,h3,calibrations,
    (gslc_tsRect){100,115,35,20},(char*)"max",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create d4 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,d4,calibrations,(gslc_tsRect){70,140,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create c4 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,c4,calibrations,(gslc_tsRect){110,140,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // create l4 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,l4,calibrations,
    (gslc_tsRect){30,155,35,20},(char*)"min",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create m4 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,m4,calibrations,
    (gslc_tsRect){65,155,35,20},(char*)"mid",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create h4 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,h4,calibrations,
    (gslc_tsRect){100,155,35,20},(char*)"max",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create d5 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,d5,calibrations,(gslc_tsRect){70,180,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create c5 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,c5,calibrations,(gslc_tsRect){110,180,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // create l5 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,l5,calibrations,
    (gslc_tsRect){30,195,35,20},(char*)"min",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create m5 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,m5,calibrations,
    (gslc_tsRect){65,195,35,20},(char*)"mid",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create h5 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,h5,calibrations,
    (gslc_tsRect){100,195,35,20},(char*)"max",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create d6 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,d6,calibrations,(gslc_tsRect){220,20,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create c6 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,c6,calibrations,(gslc_tsRect){260,20,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // create l6 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,l6,calibrations,
    (gslc_tsRect){180,35,35,20},(char*)"min",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create m6 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,m6,calibrations,
    (gslc_tsRect){215,35,35,20},(char*)"mid",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create h6 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,h6,calibrations,
    (gslc_tsRect){250,35,35,20},(char*)"max",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create d7 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,d7,calibrations,(gslc_tsRect){220,60,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create c7 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,c7,calibrations,(gslc_tsRect){260,60,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // create l7 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,l7,calibrations,
    (gslc_tsRect){180,75,35,20},(char*)"min",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create m7 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,m7,calibrations,
    (gslc_tsRect){215,75,35,20},(char*)"mid",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create h7 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,h7,calibrations,
    (gslc_tsRect){250,75,35,20},(char*)"max",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create d8 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,d8,calibrations,(gslc_tsRect){220,100,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create c8 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,c8,calibrations,(gslc_tsRect){260,100,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // create l8 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,l8,calibrations,
    (gslc_tsRect){180,115,35,20},(char*)"min",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create m8 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,m8,calibrations,
    (gslc_tsRect){215,115,35,20},(char*)"mid",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create h8 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,h8,calibrations,
    (gslc_tsRect){250,115,35,20},(char*)"max",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create d9 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,d9,calibrations,(gslc_tsRect){220,140,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create c9 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,c9,calibrations,(gslc_tsRect){260,140,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // create l9 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,l9,calibrations,
    (gslc_tsRect){180,155,35,20},(char*)"min",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create m9 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,m9,calibrations,
    (gslc_tsRect){215,155,35,20},(char*)"mid",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create h9 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,h9,calibrations,
    (gslc_tsRect){250,155,35,20},(char*)"max",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create d10 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,d10,calibrations,(gslc_tsRect){220,180,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create c10 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,c10,calibrations,(gslc_tsRect){260,180,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // create l10 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,l10,calibrations,
    (gslc_tsRect){180,195,35,20},(char*)"min",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create m10 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,m10,calibrations,
    (gslc_tsRect){215,195,35,20},(char*)"mid",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create h10 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,h10,calibrations,
    (gslc_tsRect){250,195,35,20},(char*)"max",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create E_ELEM_TEXT952 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT952,calibrations,(gslc_tsRect){120,5,79,10},
    (char*)"deadzone: +/-",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create deadzonetxt text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,deadzonetxt,calibrations,(gslc_tsRect){150,15,13,10},
    (char*)"20",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);

  // Create slider deadzone0 
  pElemRef = gslc_ElemXSliderCreate(&m_gui,deadzone0,calibrations,&m_sXSlider2,
          (gslc_tsRect){150,30,20,200},0,100,0,5,false);
  gslc_ElemXSliderSetStyle(&m_gui,pElemRef,false,GSLC_COL_BLUE,10,5,GSLC_COL_BLUE);
  gslc_ElemXSliderSetPosFunc(&m_gui,pElemRef,&CbSlidePos);
  m_pElemSlider2 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create saveButton0 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,saveButton0,calibrations,
    (gslc_tsRect){0,20,20,20},(char*)"B",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);

  // -----------------------------------
  // PAGE: setModel
  
  
  // Create mn0 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,mn0,setModel,(gslc_tsRect){5,5,25,10},
    (char*)"",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT267 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT267,setModel,(gslc_tsRect){40,20,19,10},
    (char*)"ch1",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button m0
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,m0,setModel,&m_asXToggle33,
    (gslc_tsRect){5,10,30,30},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pElemToggle33 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create mn1 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,mn1,setModel,(gslc_tsRect){35,5,25,10},
    (char*)"",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT269 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT269,setModel,(gslc_tsRect){70,20,19,10},
    (char*)"ch2",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button m11
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,m11,setModel,&m_asXToggle34,
    (gslc_tsRect){35,10,30,30},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pElemToggle34 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create mn2 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,mn2,setModel,(gslc_tsRect){65,5,25,10},
    (char*)"",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT271 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT271,setModel,(gslc_tsRect){100,20,19,10},
    (char*)"ch3",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button m12
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,m12,setModel,&m_asXToggle35,
    (gslc_tsRect){65,10,30,30},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pElemToggle35 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create mn3 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,mn3,setModel,(gslc_tsRect){95,5,25,10},
    (char*)"",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT273 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT273,setModel,(gslc_tsRect){130,20,19,10},
    (char*)"ch4",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button m13
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,m13,setModel,&m_asXToggle36,
    (gslc_tsRect){95,10,30,30},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pElemToggle36 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create mn4 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,mn4,setModel,(gslc_tsRect){125,5,25,10},
    (char*)"",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT275 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT275,setModel,(gslc_tsRect){160,20,19,10},
    (char*)"ch5",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button m14
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,m14,setModel,&m_asXToggle37,
    (gslc_tsRect){125,10,30,30},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pElemToggle37 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create mn5 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,mn5,setModel,(gslc_tsRect){155,5,25,10},
    (char*)"",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT277 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT277,setModel,(gslc_tsRect){190,20,19,10},
    (char*)"ch6",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button m15
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,m15,setModel,&m_asXToggle38,
    (gslc_tsRect){155,10,30,30},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pElemToggle38 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create mn6 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,mn6,setModel,(gslc_tsRect){185,5,25,10},
    (char*)"",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT279 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT279,setModel,(gslc_tsRect){220,20,19,10},
    (char*)"ch7",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button m16
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,m16,setModel,&m_asXToggle39,
    (gslc_tsRect){185,10,30,30},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pElemToggle39 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create mn7 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,mn7,setModel,(gslc_tsRect){215,5,25,10},
    (char*)"",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT281 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT281,setModel,(gslc_tsRect){250,20,19,10},
    (char*)"ch8",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button m17
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,m17,setModel,&m_asXToggle40,
    (gslc_tsRect){215,10,30,30},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pElemToggle40 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create E_ELEM_BTN65 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN65,setModel,
    (gslc_tsRect){100,150,60,20},(char*)"Back",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
//<InitGUI !End!>

//<Startup !Start!>
//<Startup !End!>

}

#endif // end _GUISLICE_GEN_H
