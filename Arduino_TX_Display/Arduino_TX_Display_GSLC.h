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
#include "elem/XKeyPad_Num.h"
#include "elem/XListbox.h"
#include "elem/XSlider.h"
#include "elem/XTogglebtn.h"

// Ensure optional features are enabled in the configuration
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
enum {BasePage,E_PG_MAIN,calibrations,DisplayRawValues,DisplayRcValues
      ,channelSettings,setupChannel,setupOutputPWM,setupOutputStepper
      ,setupOutputNotNeeded,setModel,transmittingSettings
      ,E_POP_KEYPAD_NUM};
enum {E_ELEM_BTN279,E_ELEM_BTN65,E_ELEM_TEXT305,E_ELEM_TEXT307
      ,E_ELEM_TEXT309,E_ELEM_TEXT312,E_ELEM_TEXT330,E_ELEM_TEXT332
      ,E_ELEM_TEXT667,E_ELEM_TEXT669,E_ELEM_TEXT670,E_ELEM_TEXT673
      ,E_ELEM_TEXT674,E_ELEM_TEXT675,E_ELEM_TEXT676,E_ELEM_TEXT677
      ,E_ELEM_TEXT729,E_ELEM_TEXT730,E_ELEM_TEXT731,E_ELEM_TEXT732
      ,E_ELEM_TEXT733,E_ELEM_TEXT734,E_ELEM_TEXT735,E_ELEM_TEXT736
      ,E_ELEM_TEXT745,E_ELEM_TEXT746,E_ELEM_TEXT748,E_ELEM_TEXT749
      ,E_ELEM_TEXT750,E_ELEM_TEXT751,E_ELEM_TEXT752,E_ELEM_TEXT753
      ,E_ELEM_TEXT754,E_ELEM_TEXT755,E_ELEM_TEXT756,E_ELEM_TEXT757
      ,E_ELEM_TEXT758,E_ELEM_TEXT759,E_ELEM_TEXT760,E_ELEM_TEXT761
      ,E_ELEM_TEXT762,E_ELEM_TEXT763,E_ELEM_TEXT922,E_ELEM_TEXT923
      ,E_ELEM_TEXT924,E_ELEM_TEXT925,E_ELEM_TEXT926,E_ELEM_TEXT927
      ,E_ELEM_TEXT928,E_ELEM_TEXT929,E_ELEM_TEXT930,E_ELEM_TEXT931
      ,E_ELEM_TEXT952,b0,b1,b2,b3,b4,b5,backbtncal,backbtnchconf
      ,backbtnchs,backbtnchsandsendstorx,backbtnsetupNotNeeded
      ,backbtnsetupPWM,backbtnsetupStepper,c1,c10,c2,c3,c4,c5,c6,c7,c8
      ,c9,channelname,channelval,configuredIO1,configuredIO2,d1,d10,d2
      ,d3,d4,d5,d6,d7,d8,d9,dcurio,deadzone0,deadzonetxt,defaultval
      ,detectIO1,detectIO2,dprevio,drbackbtn,h1,h10,h2,h3,h4,h5,h6,h7
      ,h8,h9,l1,l10,l2,l3,l4,l5,l6,l7,l8,l9,lsbChannelOutputType,m1,m10
      ,m2,m3,m4,m5,m6,m7,m8,m9,n0,n1,n10,n11,n12,n13,n14,n15,n16,n17
      ,n18,n19,n2,n20,n21,n22,n23,n3,n4,n5,n6,n7,n8,n9,nBatPercent,nr0
      ,nr1,nr2,nr3,nr4,nr5,nr6,nr7,nr8,nr9,pwmCenterZero,pwmFreq
      ,reverse,reversetxt,savebtncal,savebtnchconf,setch1,setch10
      ,setch11,setch12,setch13,setch14,setch15,setch16,setch17,setch18
      ,setch19,setch2,setch20,setch21,setch22,setch23,setch24,setch3
      ,setch4,setch5,setch6,setch7,setch8,setch9,settingstxtorxprogress
      ,sm0,sm1,sm2,sm3,sm4,sm5,sm6,sm7,stepCenterZero,stepMaxFreq
      ,stepMinFreq,t0,t1,t10,t11,t12,t13,t14,t15,t16,t17,t18,t19,t2,t20
      ,t21,t22,t23,t3,t4,t5,t6,t7,t8,t9,tr0,tr1,tr2,tr3,tr4,tr5,tr6,tr7
      ,tr8,tr9,E_ELEM_KEYPAD_NUM};
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
#define MAX_PAGE                13

#define MAX_ELEM_BasePage 1 // # Elems total on page
#define MAX_ELEM_BasePage_RAM MAX_ELEM_BasePage // # Elems in RAM

#define MAX_ELEM_PG_MAIN 5 // # Elems total on page
#define MAX_ELEM_PG_MAIN_RAM MAX_ELEM_PG_MAIN // # Elems in RAM

#define MAX_ELEM_calibrations 65 // # Elems total on page
#define MAX_ELEM_calibrations_RAM MAX_ELEM_calibrations // # Elems in RAM

#define MAX_ELEM_DisplayRawValues 25 // # Elems total on page
#define MAX_ELEM_DisplayRawValues_RAM MAX_ELEM_DisplayRawValues // # Elems in RAM

#define MAX_ELEM_DisplayRcValues 49 // # Elems total on page
#define MAX_ELEM_DisplayRcValues_RAM MAX_ELEM_DisplayRcValues // # Elems in RAM

#define MAX_ELEM_channelSettings 26 // # Elems total on page
#define MAX_ELEM_channelSettings_RAM MAX_ELEM_channelSettings // # Elems in RAM

#define MAX_ELEM_setupChannel 17 // # Elems total on page
#define MAX_ELEM_setupChannel_RAM MAX_ELEM_setupChannel // # Elems in RAM

#define MAX_ELEM_setupOutputPWM 6 // # Elems total on page
#define MAX_ELEM_setupOutputPWM_RAM MAX_ELEM_setupOutputPWM // # Elems in RAM

#define MAX_ELEM_setupOutputStepper 8 // # Elems total on page
#define MAX_ELEM_setupOutputStepper_RAM MAX_ELEM_setupOutputStepper // # Elems in RAM

#define MAX_ELEM_setupOutputNotNeeded 2 // # Elems total on page
#define MAX_ELEM_setupOutputNotNeeded_RAM MAX_ELEM_setupOutputNotNeeded // # Elems in RAM

#define MAX_ELEM_setModel 33 // # Elems total on page
#define MAX_ELEM_setModel_RAM MAX_ELEM_setModel // # Elems in RAM

#define MAX_ELEM_transmittingSettings 3 // # Elems total on page
#define MAX_ELEM_transmittingSettings_RAM MAX_ELEM_transmittingSettings // # Elems in RAM
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
gslc_tsElem                     m_asPage23Elem[MAX_ELEM_calibrations_RAM];
gslc_tsElemRef                  m_asPage23ElemRef[MAX_ELEM_calibrations];
gslc_tsElem                     m_asPage24Elem[MAX_ELEM_DisplayRawValues_RAM];
gslc_tsElemRef                  m_asPage24ElemRef[MAX_ELEM_DisplayRawValues];
gslc_tsElem                     m_asPage25Elem[MAX_ELEM_DisplayRcValues_RAM];
gslc_tsElemRef                  m_asPage25ElemRef[MAX_ELEM_DisplayRcValues];
gslc_tsElem                     m_asPage26Elem[MAX_ELEM_channelSettings_RAM];
gslc_tsElemRef                  m_asPage26ElemRef[MAX_ELEM_channelSettings];
gslc_tsElem                     m_asPage27Elem[MAX_ELEM_setupChannel_RAM];
gslc_tsElemRef                  m_asPage27ElemRef[MAX_ELEM_setupChannel];
gslc_tsElem                     m_asPage32Elem[MAX_ELEM_setupOutputPWM_RAM];
gslc_tsElemRef                  m_asPage32ElemRef[MAX_ELEM_setupOutputPWM];
gslc_tsElem                     m_asPage33Elem[MAX_ELEM_setupOutputStepper_RAM];
gslc_tsElemRef                  m_asPage33ElemRef[MAX_ELEM_setupOutputStepper];
gslc_tsElem                     m_asPage34Elem[MAX_ELEM_setupOutputNotNeeded_RAM];
gslc_tsElemRef                  m_asPage34ElemRef[MAX_ELEM_setupOutputNotNeeded];
gslc_tsElem                     m_asPage37Elem[MAX_ELEM_setModel_RAM];
gslc_tsElemRef                  m_asPage37ElemRef[MAX_ELEM_setModel];
gslc_tsElem                     m_asPopup12Elem[MAX_ELEM_transmittingSettings_RAM];
gslc_tsElemRef                  m_asPopup12ElemRef[MAX_ELEM_transmittingSettings];
gslc_tsElem                     m_asKeypadNumElem[1];
gslc_tsElemRef                  m_asKeypadNumElemRef[1];
gslc_tsXKeyPad                  m_sKeyPadNum;
gslc_tsXSlider                  m_sXSlider4;
gslc_tsXTogglebtn               m_asXToggle52;
gslc_tsXListbox                 m_sListbox2;
// - Note that XLISTBOX_BUF_OH_R is extra required per item
char                            m_acListboxBuf2[22 + XLISTBOX_BUF_OH_R];
gslc_tsXTogglebtn               m_asXToggle70;
gslc_tsXTogglebtn               m_asXToggle71;
gslc_tsXTogglebtn               m_asXToggle88;
gslc_tsXTogglebtn               m_asXToggle89;
gslc_tsXTogglebtn               m_asXToggle90;
gslc_tsXTogglebtn               m_asXToggle91;
gslc_tsXTogglebtn               m_asXToggle92;
gslc_tsXTogglebtn               m_asXToggle93;
gslc_tsXTogglebtn               m_asXToggle94;
gslc_tsXTogglebtn               m_asXToggle95;

#define MAX_STR                 100

//<GUI_Extra_Elements !End!>

// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Element References for direct access
//<Extern_References !Start!>
extern gslc_tsElemRef* m_pDeadzone0;
extern gslc_tsElemRef* m_pDefaultval;
extern gslc_tsElemRef* m_pListSlider2;
extern gslc_tsElemRef* m_pLsbchanneloutputtype;
extern gslc_tsElemRef* m_pPwmcenterzero;
extern gslc_tsElemRef* m_pPwmfreq;
extern gslc_tsElemRef* m_pReverse;
extern gslc_tsElemRef* m_pSm0;
extern gslc_tsElemRef* m_pSm1;
extern gslc_tsElemRef* m_pSm2;
extern gslc_tsElemRef* m_pSm3;
extern gslc_tsElemRef* m_pSm4;
extern gslc_tsElemRef* m_pSm5;
extern gslc_tsElemRef* m_pSm6;
extern gslc_tsElemRef* m_pSm7;
extern gslc_tsElemRef* m_pStepcenterzero;
extern gslc_tsElemRef* m_pStepmaxfreq;
extern gslc_tsElemRef* m_pStepminfreq;
extern gslc_tsElemRef* m_pElemKeyPadNum;
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
  gslc_PageSetHmiEvents(&m_gui,BasePage, false, false);
  gslc_PageAdd(&m_gui,E_PG_MAIN,m_asPage1Elem,MAX_ELEM_PG_MAIN_RAM,m_asPage1ElemRef,MAX_ELEM_PG_MAIN);
  gslc_PageSetHmiEvents(&m_gui,E_PG_MAIN, true, false);
  gslc_PageAdd(&m_gui,calibrations,m_asPage23Elem,MAX_ELEM_calibrations_RAM,m_asPage23ElemRef,MAX_ELEM_calibrations);
  gslc_PageSetHmiEvents(&m_gui,calibrations, true, false);
  gslc_PageAdd(&m_gui,DisplayRawValues,m_asPage24Elem,MAX_ELEM_DisplayRawValues_RAM,m_asPage24ElemRef,MAX_ELEM_DisplayRawValues);
  gslc_PageSetHmiEvents(&m_gui,DisplayRawValues, true, false);
  gslc_PageAdd(&m_gui,DisplayRcValues,m_asPage25Elem,MAX_ELEM_DisplayRcValues_RAM,m_asPage25ElemRef,MAX_ELEM_DisplayRcValues);
  gslc_PageSetHmiEvents(&m_gui,DisplayRcValues, true, false);
  gslc_PageAdd(&m_gui,channelSettings,m_asPage26Elem,MAX_ELEM_channelSettings_RAM,m_asPage26ElemRef,MAX_ELEM_channelSettings);
  gslc_PageSetHmiEvents(&m_gui,channelSettings, true, false);
  gslc_PageAdd(&m_gui,setupChannel,m_asPage27Elem,MAX_ELEM_setupChannel_RAM,m_asPage27ElemRef,MAX_ELEM_setupChannel);
  gslc_PageSetHmiEvents(&m_gui,setupChannel, true, false);
  gslc_PageAdd(&m_gui,setupOutputPWM,m_asPage32Elem,MAX_ELEM_setupOutputPWM_RAM,m_asPage32ElemRef,MAX_ELEM_setupOutputPWM);
  gslc_PageSetHmiEvents(&m_gui,setupOutputPWM, false, false);
  gslc_PageAdd(&m_gui,setupOutputStepper,m_asPage33Elem,MAX_ELEM_setupOutputStepper_RAM,m_asPage33ElemRef,MAX_ELEM_setupOutputStepper);
  gslc_PageSetHmiEvents(&m_gui,setupOutputStepper, false, false);
  gslc_PageAdd(&m_gui,setupOutputNotNeeded,m_asPage34Elem,MAX_ELEM_setupOutputNotNeeded_RAM,m_asPage34ElemRef,MAX_ELEM_setupOutputNotNeeded);
  gslc_PageSetHmiEvents(&m_gui,setupOutputNotNeeded, false, false);
  gslc_PageAdd(&m_gui,setModel,m_asPage37Elem,MAX_ELEM_setModel_RAM,m_asPage37ElemRef,MAX_ELEM_setModel);
  gslc_PageSetHmiEvents(&m_gui,setModel, true, false);
  gslc_PageAdd(&m_gui,transmittingSettings,m_asPopup12Elem,MAX_ELEM_transmittingSettings_RAM,m_asPopup12ElemRef,MAX_ELEM_transmittingSettings);
  gslc_PageSetHmiEvents(&m_gui,transmittingSettings, false, false);
  gslc_PageAdd(&m_gui,E_POP_KEYPAD_NUM,m_asKeypadNumElem,1,m_asKeypadNumElemRef,1);  // KeyPad

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
    (gslc_tsRect){20,40,130,25},(char*)"Display RC Channels",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create b1 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,b1,E_PG_MAIN,
    (gslc_tsRect){20,120,130,25},(char*)"Setup ADC Params",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create b2 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,b2,E_PG_MAIN,
    (gslc_tsRect){20,160,130,25},(char*)"Setup channels",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create b3 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,b3,E_PG_MAIN,
    (gslc_tsRect){20,200,130,25},(char*)"Choose model",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create b4 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,b4,E_PG_MAIN,
    (gslc_tsRect){20,80,130,25},(char*)"Display RAW Channels",0,E_BUILTIN5X8,&CbBtnCommon);
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
  pElemRef = gslc_ElemXSliderCreate(&m_gui,deadzone0,calibrations,&m_sXSlider4,
          (gslc_tsRect){150,30,20,200},0,100,0,5,false);
  gslc_ElemXSliderSetStyle(&m_gui,pElemRef,false,GSLC_COL_BLUE,10,5,GSLC_COL_BLUE);
  gslc_ElemXSliderSetPosFunc(&m_gui,pElemRef,&CbSlidePos);
  m_pDeadzone0 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create backbtncal button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,backbtncal,calibrations,
    (gslc_tsRect){0,20,20,20},(char*)"B",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create savebtncal button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,savebtncal,calibrations,
    (gslc_tsRect){143,215,30,20},(char*)"SAVE",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);

  // -----------------------------------
  // PAGE: DisplayRawValues
  
  
  // Create tr0 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,tr0,DisplayRawValues,(gslc_tsRect){5,25,25,10},
    (char*)"ADC1",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create nr0 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,nr0,DisplayRawValues,(gslc_tsRect){45,25,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create tr1 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,tr1,DisplayRawValues,(gslc_tsRect){5,45,25,10},
    (char*)"ADC2",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create nr1 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,nr1,DisplayRawValues,(gslc_tsRect){45,45,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create tr2 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,tr2,DisplayRawValues,(gslc_tsRect){5,65,25,10},
    (char*)"ADC3",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create nr2 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,nr2,DisplayRawValues,(gslc_tsRect){45,65,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create tr3 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,tr3,DisplayRawValues,(gslc_tsRect){5,85,25,10},
    (char*)"ADC4",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create nr3 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,nr3,DisplayRawValues,(gslc_tsRect){45,85,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create tr4 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,tr4,DisplayRawValues,(gslc_tsRect){5,105,25,10},
    (char*)"ADC5",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create nr4 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,nr4,DisplayRawValues,(gslc_tsRect){45,105,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create tr5 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,tr5,DisplayRawValues,(gslc_tsRect){5,125,25,10},
    (char*)"ADC6",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create nr5 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,nr5,DisplayRawValues,(gslc_tsRect){45,125,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create tr6 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,tr6,DisplayRawValues,(gslc_tsRect){5,145,25,10},
    (char*)"ADC7",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create nr6 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,nr6,DisplayRawValues,(gslc_tsRect){45,145,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create tr7 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,tr7,DisplayRawValues,(gslc_tsRect){5,165,25,10},
    (char*)"ADC8",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create nr7 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,nr7,DisplayRawValues,(gslc_tsRect){45,165,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create tr8 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,tr8,DisplayRawValues,(gslc_tsRect){5,185,25,10},
    (char*)"ADC9",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create nr8 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,nr8,DisplayRawValues,(gslc_tsRect){45,185,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create tr9 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,tr9,DisplayRawValues,(gslc_tsRect){5,205,31,10},
    (char*)"ADC10",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create nr9 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,nr9,DisplayRawValues,(gslc_tsRect){45,205,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT332 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT332,DisplayRawValues,(gslc_tsRect){170,20,37,10},
    (char*)"PrevIO",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create dprevio text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,dprevio,DisplayRawValues,(gslc_tsRect){100,35,193,10},
    (char*)"00000000000000000000000000000000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT330 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT330,DisplayRawValues,(gslc_tsRect){173,65,31,10},
    (char*)"CurIO",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create dcurio text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,dcurio,DisplayRawValues,(gslc_tsRect){100,50,193,10},
    (char*)"00000000000000000000000000000000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // create drbackbtn button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,drbackbtn,DisplayRawValues,
    (gslc_tsRect){140,180,80,40},(char*)"Back",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);

  // -----------------------------------
  // PAGE: DisplayRcValues
  
  
  // Create t0 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t0,DisplayRcValues,(gslc_tsRect){5,15,19,10},
    (char*)"ch1",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n0 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n0,DisplayRcValues,(gslc_tsRect){45,15,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t1 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t1,DisplayRcValues,(gslc_tsRect){5,35,19,10},
    (char*)"ch2",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n1 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n1,DisplayRcValues,(gslc_tsRect){45,35,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t2 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t2,DisplayRcValues,(gslc_tsRect){5,55,19,10},
    (char*)"ch3",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n2 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n2,DisplayRcValues,(gslc_tsRect){45,55,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t3 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t3,DisplayRcValues,(gslc_tsRect){5,75,19,10},
    (char*)"ch4",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n3 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n3,DisplayRcValues,(gslc_tsRect){45,75,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t4 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t4,DisplayRcValues,(gslc_tsRect){5,95,19,10},
    (char*)"ch5",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n4 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n4,DisplayRcValues,(gslc_tsRect){45,95,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t5 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t5,DisplayRcValues,(gslc_tsRect){5,115,19,10},
    (char*)"ch6",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n5 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n5,DisplayRcValues,(gslc_tsRect){45,115,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t6 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t6,DisplayRcValues,(gslc_tsRect){5,135,19,10},
    (char*)"ch7",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n6 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n6,DisplayRcValues,(gslc_tsRect){45,135,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t7 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t7,DisplayRcValues,(gslc_tsRect){5,155,19,10},
    (char*)"ch8",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n7 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n7,DisplayRcValues,(gslc_tsRect){45,155,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t8 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t8,DisplayRcValues,(gslc_tsRect){95,15,19,10},
    (char*)"ch9",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n8 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n8,DisplayRcValues,(gslc_tsRect){135,15,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t9 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t9,DisplayRcValues,(gslc_tsRect){95,35,25,10},
    (char*)"ch10",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n9 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n9,DisplayRcValues,(gslc_tsRect){135,35,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t10 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t10,DisplayRcValues,(gslc_tsRect){95,55,25,10},
    (char*)"ch11",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n10 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n10,DisplayRcValues,(gslc_tsRect){135,55,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t11 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t11,DisplayRcValues,(gslc_tsRect){95,75,25,10},
    (char*)"ch12",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n11 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n11,DisplayRcValues,(gslc_tsRect){135,75,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t12 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t12,DisplayRcValues,(gslc_tsRect){95,95,25,10},
    (char*)"ch13",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n12 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n12,DisplayRcValues,(gslc_tsRect){135,95,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t13 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t13,DisplayRcValues,(gslc_tsRect){95,115,25,10},
    (char*)"ch14",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n13 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n13,DisplayRcValues,(gslc_tsRect){135,115,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t14 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t14,DisplayRcValues,(gslc_tsRect){95,135,25,10},
    (char*)"ch15",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n14 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n14,DisplayRcValues,(gslc_tsRect){135,135,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t15 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t15,DisplayRcValues,(gslc_tsRect){95,155,25,10},
    (char*)"ch16",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n15 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n15,DisplayRcValues,(gslc_tsRect){135,155,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t16 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t16,DisplayRcValues,(gslc_tsRect){185,15,25,10},
    (char*)"ch17",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n16 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n16,DisplayRcValues,(gslc_tsRect){235,15,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t17 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t17,DisplayRcValues,(gslc_tsRect){185,35,25,10},
    (char*)"ch18",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n17 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n17,DisplayRcValues,(gslc_tsRect){235,35,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t18 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t18,DisplayRcValues,(gslc_tsRect){185,55,25,10},
    (char*)"ch19",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n18 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n18,DisplayRcValues,(gslc_tsRect){235,55,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t19 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t19,DisplayRcValues,(gslc_tsRect){185,75,25,10},
    (char*)"ch20",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n19 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n19,DisplayRcValues,(gslc_tsRect){235,75,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t20 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t20,DisplayRcValues,(gslc_tsRect){185,95,25,10},
    (char*)"ch21",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n20 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n20,DisplayRcValues,(gslc_tsRect){235,95,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t21 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t21,DisplayRcValues,(gslc_tsRect){185,115,25,10},
    (char*)"ch22",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n21 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n21,DisplayRcValues,(gslc_tsRect){235,115,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t22 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t22,DisplayRcValues,(gslc_tsRect){185,135,25,10},
    (char*)"ch23",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n22 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n22,DisplayRcValues,(gslc_tsRect){235,135,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t23 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t23,DisplayRcValues,(gslc_tsRect){185,155,25,10},
    (char*)"ch24",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n23 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n23,DisplayRcValues,(gslc_tsRect){235,155,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // create b5 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,b5,DisplayRcValues,
    (gslc_tsRect){0,180,80,40},(char*)"Back",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);

  // -----------------------------------
  // PAGE: channelSettings
  
  
  // create setch1 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch1,channelSettings,
    (gslc_tsRect){5,35,30,20},(char*)"ch1",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch2 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch2,channelSettings,
    (gslc_tsRect){45,35,30,20},(char*)"ch2",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch3 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch3,channelSettings,
    (gslc_tsRect){85,35,30,20},(char*)"ch3",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch4 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch4,channelSettings,
    (gslc_tsRect){125,35,30,20},(char*)"ch4",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch5 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch5,channelSettings,
    (gslc_tsRect){165,35,30,20},(char*)"ch5",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch6 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch6,channelSettings,
    (gslc_tsRect){205,35,30,20},(char*)"ch6",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch7 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch7,channelSettings,
    (gslc_tsRect){245,35,30,20},(char*)"ch7",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch8 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch8,channelSettings,
    (gslc_tsRect){285,35,30,20},(char*)"ch8",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch9 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch9,channelSettings,
    (gslc_tsRect){5,75,30,20},(char*)"ch9",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch10 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch10,channelSettings,
    (gslc_tsRect){45,75,30,20},(char*)"ch10",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch11 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch11,channelSettings,
    (gslc_tsRect){85,75,30,20},(char*)"ch11",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch12 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch12,channelSettings,
    (gslc_tsRect){125,75,30,20},(char*)"ch12",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch13 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch13,channelSettings,
    (gslc_tsRect){165,75,30,20},(char*)"ch13",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch14 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch14,channelSettings,
    (gslc_tsRect){205,75,30,20},(char*)"ch14",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch15 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch15,channelSettings,
    (gslc_tsRect){245,75,30,20},(char*)"ch15",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch16 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch16,channelSettings,
    (gslc_tsRect){285,75,30,20},(char*)"ch16",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch17 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch17,channelSettings,
    (gslc_tsRect){5,115,30,20},(char*)"ch17",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch18 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch18,channelSettings,
    (gslc_tsRect){45,115,30,20},(char*)"ch18",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch19 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch19,channelSettings,
    (gslc_tsRect){85,115,30,20},(char*)"ch19",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch20 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch20,channelSettings,
    (gslc_tsRect){125,115,30,20},(char*)"ch20",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch21 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch21,channelSettings,
    (gslc_tsRect){165,115,30,20},(char*)"ch21",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch22 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch22,channelSettings,
    (gslc_tsRect){205,115,30,20},(char*)"ch22",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch23 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch23,channelSettings,
    (gslc_tsRect){245,115,30,20},(char*)"ch23",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch24 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch24,channelSettings,
    (gslc_tsRect){285,115,30,20},(char*)"ch24",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create backbtnchs button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,backbtnchs,channelSettings,
    (gslc_tsRect){10,180,100,40},(char*)"Back",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create backbtnchsandsendstorx button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,backbtnchsandsendstorx,channelSettings,
    (gslc_tsRect){110,180,200,40},(char*)"Back and send settings",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);

  // -----------------------------------
  // PAGE: setupChannel
  
  
  // Create channelname text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,channelname,setupChannel,(gslc_tsRect){140,20,31,10},
    (char*)"ch???",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT312 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT312,setupChannel,(gslc_tsRect){120,45,31,10},
    (char*)"RCval",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create channelval text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,channelval,setupChannel,(gslc_tsRect){160,45,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create reversetxt text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,reversetxt,setupChannel,(gslc_tsRect){192,170,43,10},
    (char*)"reverse",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button reverse
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,reverse,setupChannel,&m_asXToggle52,
    (gslc_tsRect){240,165,35,20},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pReverse = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, true);
  
  // create detectIO1 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,detectIO1,setupChannel,
    (gslc_tsRect){220,80,80,20},(char*)"Detect IO",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create detectIO2 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,detectIO2,setupChannel,
    (gslc_tsRect){220,110,80,20},(char*)"Detect IO",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create E_ELEM_TEXT305 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT305,setupChannel,(gslc_tsRect){160,85,19,10},
    (char*)"IO1",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create configuredIO1 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,configuredIO1,setupChannel,(gslc_tsRect){190,85,25,10},
    (char*)"NONE",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT307 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT307,setupChannel,(gslc_tsRect){160,115,19,10},
    (char*)"IO2",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create configuredIO2 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,configuredIO2,setupChannel,(gslc_tsRect){190,115,25,10},
    (char*)"NONE",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT309 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT309,setupChannel,(gslc_tsRect){140,143,79,10},
    (char*)"Default value",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create defaultval numeric input field
  static char m_sInputNumber4[7] = "";
  pElemRef = gslc_ElemCreateTxt(&m_gui,defaultval,setupChannel,(gslc_tsRect){230,138,40,20},
    (char*)m_sInputNumber4,7,E_BUILTIN5X8);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,5);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  m_pDefaultval = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, true);
  
  // create savebtnchconf button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,savebtnchconf,setupChannel,
    (gslc_tsRect){80,210,150,20},(char*)"Save channel config",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create backbtnchconf button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,backbtnchconf,setupChannel,
    (gslc_tsRect){10,210,40,20},(char*)"Back",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
   
  // Create listbox
  pElemRef = gslc_ElemXListboxCreate(&m_gui,lsbChannelOutputType,setupChannel,&m_sListbox2,
    (gslc_tsRect){0,70,130,100},E_BUILTIN5X8,
    (uint8_t*)&m_acListboxBuf2,sizeof(m_acListboxBuf2),0);
  gslc_ElemXListboxSetSize(&m_gui, pElemRef, 5, 1); // 5 rows, 1 columns
  gslc_ElemXListboxItemsSetSize(&m_gui, pElemRef, XLISTBOX_SIZE_AUTO, XLISTBOX_SIZE_AUTO);
  gslc_ElemSetTxtMarginXY(&m_gui, pElemRef, 5, 0);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE,GSLC_COL_BLACK,GSLC_COL_GRAY);
  gslc_ElemXListboxSetSelFunc(&m_gui, pElemRef, &CbListbox);
  gslc_ElemXListboxAddItem(&m_gui, pElemRef, "RC");
  gslc_ElemXListboxAddItem(&m_gui, pElemRef, "IO");
  gslc_ElemXListboxAddItem(&m_gui, pElemRef, "PWM");
  gslc_ElemXListboxAddItem(&m_gui, pElemRef, "STEPPER");
  gslc_ElemXListboxAddItem(&m_gui, pElemRef, "DAC");
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  m_pLsbchanneloutputtype = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, true);
  
  // create E_ELEM_BTN279 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN279,setupChannel,
    (gslc_tsRect){10,180,120,20},(char*)"Setup output type",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,false);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);

  // -----------------------------------
  // PAGE: setupOutputPWM
  
  
  // Create E_ELEM_TEXT674 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT674,setupOutputPWM,(gslc_tsRect){100,20,115,10},
    (char*)"Setup PWM Paramters",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT667 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT667,setupOutputPWM,(gslc_tsRect){76,65,79,10},
    (char*)"PWM Frequency",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create pwmFreq numeric input field
  static char m_sInputNumber22[7] = "";
  pElemRef = gslc_ElemCreateTxt(&m_gui,pwmFreq,setupOutputPWM,(gslc_tsRect){160,60,40,20},
    (char*)m_sInputNumber22,7,E_BUILTIN5X8);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,5);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  m_pPwmfreq = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, true);
  
  // Create E_ELEM_TEXT673 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT673,setupOutputPWM,(gslc_tsRect){88,95,67,10},
    (char*)"Center is 0",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button pwmCenterZero
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,pwmCenterZero,setupOutputPWM,&m_asXToggle70,
    (gslc_tsRect){160,90,35,20},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pPwmcenterzero = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, true);
  
  // create backbtnsetupPWM button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,backbtnsetupPWM,setupOutputPWM,
    (gslc_tsRect){10,210,40,20},(char*)"Back",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);

  // -----------------------------------
  // PAGE: setupOutputStepper
  
  
  // Create E_ELEM_TEXT675 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT675,setupOutputStepper,(gslc_tsRect){100,20,139,10},
    (char*)"Setup Stepper Paramters",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT669 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT669,setupOutputStepper,(gslc_tsRect){76,65,79,10},
    (char*)"Min frequency",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create stepMinFreq numeric input field
  static char m_sInputNumber23[7] = "";
  pElemRef = gslc_ElemCreateTxt(&m_gui,stepMinFreq,setupOutputStepper,(gslc_tsRect){160,60,40,20},
    (char*)m_sInputNumber23,7,E_BUILTIN5X8);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,5);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  m_pStepminfreq = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, true);
  
  // Create E_ELEM_TEXT670 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT670,setupOutputStepper,(gslc_tsRect){76,95,79,10},
    (char*)"Max frequency",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create stepMaxFreq numeric input field
  static char m_sInputNumber24[7] = "";
  pElemRef = gslc_ElemCreateTxt(&m_gui,stepMaxFreq,setupOutputStepper,(gslc_tsRect){160,90,40,20},
    (char*)m_sInputNumber24,7,E_BUILTIN5X8);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,5);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  m_pStepmaxfreq = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, true);
  
  // Create E_ELEM_TEXT677 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT677,setupOutputStepper,(gslc_tsRect){88,125,67,10},
    (char*)"Center is 0",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button stepCenterZero
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,stepCenterZero,setupOutputStepper,&m_asXToggle71,
    (gslc_tsRect){160,120,35,20},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pStepcenterzero = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, true);
  
  // create backbtnsetupStepper button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,backbtnsetupStepper,setupOutputStepper,
    (gslc_tsRect){10,210,40,20},(char*)"Back",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);

  // -----------------------------------
  // PAGE: setupOutputNotNeeded
  
  
  // Create E_ELEM_TEXT676 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT676,setupOutputNotNeeded,(gslc_tsRect){100,110,97,10},
    (char*)"Setup not needed",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // create backbtnsetupNotNeeded button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,backbtnsetupNotNeeded,setupOutputNotNeeded,
    (gslc_tsRect){10,210,40,20},(char*)"Back",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);

  // -----------------------------------
  // PAGE: setModel
  
  
  // Create E_ELEM_TEXT729 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT729,setModel,(gslc_tsRect){11,42,19,10},
    (char*)"ch1",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button sm0
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,sm0,setModel,&m_asXToggle88,
    (gslc_tsRect){5,10,30,30},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pSm0 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create E_ELEM_TEXT730 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT730,setModel,(gslc_tsRect){41,42,19,10},
    (char*)"ch2",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button sm1
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,sm1,setModel,&m_asXToggle89,
    (gslc_tsRect){35,10,30,30},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pSm1 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create E_ELEM_TEXT731 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT731,setModel,(gslc_tsRect){71,42,19,10},
    (char*)"ch3",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button sm2
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,sm2,setModel,&m_asXToggle90,
    (gslc_tsRect){65,10,30,30},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pSm2 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create E_ELEM_TEXT732 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT732,setModel,(gslc_tsRect){101,42,19,10},
    (char*)"ch4",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button sm3
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,sm3,setModel,&m_asXToggle91,
    (gslc_tsRect){95,10,30,30},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pSm3 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create E_ELEM_TEXT733 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT733,setModel,(gslc_tsRect){131,42,19,10},
    (char*)"ch5",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button sm4
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,sm4,setModel,&m_asXToggle92,
    (gslc_tsRect){125,10,30,30},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pSm4 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create E_ELEM_TEXT734 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT734,setModel,(gslc_tsRect){161,42,19,10},
    (char*)"ch6",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button sm5
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,sm5,setModel,&m_asXToggle93,
    (gslc_tsRect){155,10,30,30},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pSm5 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create E_ELEM_TEXT735 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT735,setModel,(gslc_tsRect){191,42,19,10},
    (char*)"ch7",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button sm6
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,sm6,setModel,&m_asXToggle94,
    (gslc_tsRect){185,10,30,30},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pSm6 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create E_ELEM_TEXT736 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT736,setModel,(gslc_tsRect){221,42,19,10},
    (char*)"ch8",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button sm7
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,sm7,setModel,&m_asXToggle95,
    (gslc_tsRect){215,10,30,30},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pSm7 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create E_ELEM_BTN65 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN65,setModel,
    (gslc_tsRect){100,150,60,20},(char*)"Back",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create E_ELEM_TEXT748 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT748,setModel,(gslc_tsRect){11,42,19,10},
    (char*)"ch1",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT749 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT749,setModel,(gslc_tsRect){41,42,19,10},
    (char*)"ch2",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT750 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT750,setModel,(gslc_tsRect){71,42,19,10},
    (char*)"ch3",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT751 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT751,setModel,(gslc_tsRect){101,42,19,10},
    (char*)"ch4",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT752 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT752,setModel,(gslc_tsRect){131,42,19,10},
    (char*)"ch5",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT753 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT753,setModel,(gslc_tsRect){161,42,19,10},
    (char*)"ch6",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT754 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT754,setModel,(gslc_tsRect){191,42,19,10},
    (char*)"ch7",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT755 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT755,setModel,(gslc_tsRect){221,42,19,10},
    (char*)"ch8",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT756 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT756,setModel,(gslc_tsRect){11,42,19,10},
    (char*)"ch1",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT757 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT757,setModel,(gslc_tsRect){41,42,19,10},
    (char*)"ch2",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT758 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT758,setModel,(gslc_tsRect){71,42,19,10},
    (char*)"ch3",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT759 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT759,setModel,(gslc_tsRect){101,42,19,10},
    (char*)"ch4",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT760 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT760,setModel,(gslc_tsRect){131,42,19,10},
    (char*)"ch5",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT761 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT761,setModel,(gslc_tsRect){161,42,19,10},
    (char*)"ch6",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT762 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT762,setModel,(gslc_tsRect){191,42,19,10},
    (char*)"ch7",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT763 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT763,setModel,(gslc_tsRect){221,42,19,10},
    (char*)"ch8",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);

  // -----------------------------------
  // PAGE: transmittingSettings
  
  
  // Create E_ELEM_TEXT745 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT745,transmittingSettings,(gslc_tsRect){90,70,127,10},
    (char*)"Transmitting settings",0,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_TOP_MID);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT746 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT746,transmittingSettings,(gslc_tsRect){60,90,181,10},
    (char*)"Please wait for it to complete",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create settingstxtorxprogress text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,settingstxtorxprogress,transmittingSettings,(gslc_tsRect){60,110,181,10},
    (char*)"Currently at packet ??? of ???",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);

  // -----------------------------------
  // PAGE: E_POP_KEYPAD_NUM
  
  static gslc_tsXKeyPadCfg_Num sCfg;
  sCfg = gslc_ElemXKeyPadCfgInit_Num();
  gslc_ElemXKeyPadCfgSetFloatEn_Num(&sCfg, true);
  gslc_ElemXKeyPadCfgSetSignEn_Num(&sCfg, true);
  m_pElemKeyPadNum = gslc_ElemXKeyPadCreate_Num(&m_gui, E_ELEM_KEYPAD_NUM, E_POP_KEYPAD_NUM,
    &m_sKeyPadNum, 65, 80, E_BUILTIN5X8, &sCfg);
  gslc_ElemXKeyPadValSetCb(&m_gui, m_pElemKeyPadNum, &CbKeypad);
//<InitGUI !End!>

//<Startup !Start!>
//<Startup !End!>

}

#endif // end _GUISLICE_GEN_H
