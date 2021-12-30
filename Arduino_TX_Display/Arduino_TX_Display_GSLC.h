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
enum {E_PG_MAIN,E_PG_MINMAX};
enum {BTN_CH_MAPPING,BTN_SETUP_MINMAX,BTN_START,E_ELEM_BTN10
      ,E_ELEM_BTN11,E_ELEM_BTN12,E_ELEM_BTN13,E_ELEM_BTN14,E_ELEM_BTN15
      ,E_ELEM_BTN16,E_ELEM_BTN17,E_ELEM_BTN18,E_ELEM_BTN19,E_ELEM_BTN20
      ,E_ELEM_BTN4,E_ELEM_BTN5,E_ELEM_BTN6,E_ELEM_BTN7,E_ELEM_BTN8
      ,E_ELEM_BTN9,E_ELEM_TEXT1,E_ELEM_TEXT2,E_ELEM_TEXT3,E_ELEM_TEXT4
      ,E_ELEM_TEXT5,E_ELEM_TEXT6,E_ELEM_TEXT7,E_ELEM_TEXT8};
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
#define MAX_PAGE                2

#define MAX_ELEM_PG_MAIN 3 // # Elems total on page
#define MAX_ELEM_PG_MAIN_RAM MAX_ELEM_PG_MAIN // # Elems in RAM

#define MAX_ELEM_PG_MINMAX 25 // # Elems total on page
#define MAX_ELEM_PG_MINMAX_RAM MAX_ELEM_PG_MINMAX // # Elems in RAM
//<ElementDefines !End!>

// ------------------------------------------------
// Create element storage
// ------------------------------------------------
gslc_tsGui                      m_gui;
gslc_tsDriver                   m_drv;
gslc_tsFont                     m_asFont[MAX_FONT];
gslc_tsPage                     m_asPage[MAX_PAGE];

//<GUI_Extra_Elements !Start!>
gslc_tsElem                     m_asPage1Elem[MAX_ELEM_PG_MAIN_RAM];
gslc_tsElemRef                  m_asPage1ElemRef[MAX_ELEM_PG_MAIN];
gslc_tsElem                     m_asPage2Elem[MAX_ELEM_PG_MINMAX_RAM];
gslc_tsElemRef                  m_asPage2ElemRef[MAX_ELEM_PG_MINMAX];

#define MAX_STR                 100

//<GUI_Extra_Elements !End!>

// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Element References for direct access
//<Extern_References !Start!>
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
  gslc_PageAdd(&m_gui,E_PG_MAIN,m_asPage1Elem,MAX_ELEM_PG_MAIN_RAM,m_asPage1ElemRef,MAX_ELEM_PG_MAIN);
  gslc_PageAdd(&m_gui,E_PG_MINMAX,m_asPage2Elem,MAX_ELEM_PG_MINMAX_RAM,m_asPage2ElemRef,MAX_ELEM_PG_MINMAX);

  // NOTE: The current page defaults to the first page added. Here we explicitly
  //       ensure that the main page is the correct page no matter the add order.
  gslc_SetPageCur(&m_gui,E_PG_MAIN);
  
  // Set Background to a flat color
  gslc_SetBkgndColor(&m_gui,GSLC_COL_BLACK);

  // -----------------------------------
  // PAGE: E_PG_MAIN
  
  
  // create BTN_START button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,BTN_START,E_PG_MAIN,
    (gslc_tsRect){10,20,100,20},(char*)"Start",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // create BTN_SETUP_MINMAX button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,BTN_SETUP_MINMAX,E_PG_MAIN,
    (gslc_tsRect){10,60,100,20},(char*)"Setup min/max",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // create BTN_CH_MAPPING button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,BTN_CH_MAPPING,E_PG_MAIN,
    (gslc_tsRect){10,100,100,20},(char*)"Channel mapping",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);

  // -----------------------------------
  // PAGE: E_PG_MINMAX
  
  
  // create E_ELEM_BTN4 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN4,E_PG_MINMAX,
    (gslc_tsRect){10,20,40,30},(char*)"MIN",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create E_ELEM_BTN5 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN5,E_PG_MINMAX,
    (gslc_tsRect){10,60,40,30},(char*)"MIN",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create E_ELEM_BTN6 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN6,E_PG_MINMAX,
    (gslc_tsRect){10,99,40,30},(char*)"MIN",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create E_ELEM_BTN7 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN7,E_PG_MINMAX,
    (gslc_tsRect){10,139,40,30},(char*)"MIN",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create E_ELEM_BTN8 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN8,E_PG_MINMAX,
    (gslc_tsRect){180,20,40,30},(char*)"MIN",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create E_ELEM_BTN9 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN9,E_PG_MINMAX,
    (gslc_tsRect){180,60,40,30},(char*)"MIN",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create E_ELEM_BTN10 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN10,E_PG_MINMAX,
    (gslc_tsRect){180,100,40,30},(char*)"MIN",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create E_ELEM_BTN11 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN11,E_PG_MINMAX,
    (gslc_tsRect){180,140,40,30},(char*)"MIN",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create E_ELEM_BTN12 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN12,E_PG_MINMAX,
    (gslc_tsRect){101,19,40,30},(char*)"MAX",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create E_ELEM_BTN13 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN13,E_PG_MINMAX,
    (gslc_tsRect){101,59,40,30},(char*)"MAX",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create E_ELEM_BTN14 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN14,E_PG_MINMAX,
    (gslc_tsRect){101,98,40,30},(char*)"MAX",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create E_ELEM_BTN15 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN15,E_PG_MINMAX,
    (gslc_tsRect){101,138,40,30},(char*)"MAX",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create E_ELEM_BTN16 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN16,E_PG_MINMAX,
    (gslc_tsRect){268,19,40,30},(char*)"MAX",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create E_ELEM_BTN17 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN17,E_PG_MINMAX,
    (gslc_tsRect){268,59,40,30},(char*)"MAX",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create E_ELEM_BTN18 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN18,E_PG_MINMAX,
    (gslc_tsRect){268,99,40,30},(char*)"MAX",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create E_ELEM_BTN19 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN19,E_PG_MINMAX,
    (gslc_tsRect){268,139,40,30},(char*)"MAX",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create E_ELEM_TEXT1 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT1,E_PG_MINMAX,(gslc_tsRect){65,30,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT2 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT2,E_PG_MINMAX,(gslc_tsRect){65,70,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT3 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT3,E_PG_MINMAX,(gslc_tsRect){65,108,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT4 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT4,E_PG_MINMAX,(gslc_tsRect){65,148,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT5 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT5,E_PG_MINMAX,(gslc_tsRect){233,31,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT6 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT6,E_PG_MINMAX,(gslc_tsRect){233,71,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT7 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT7,E_PG_MINMAX,(gslc_tsRect){233,109,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT8 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT8,E_PG_MINMAX,(gslc_tsRect){233,149,25,10},
    (char*)"0000",0,E_BUILTIN5X8);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // create E_ELEM_BTN20 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN20,E_PG_MINMAX,
    (gslc_tsRect){120,190,80,30},(char*)"SAVE",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
//<InitGUI !End!>

//<Startup !Start!>
//<Startup !End!>

}

#endif // end _GUISLICE_GEN_H
