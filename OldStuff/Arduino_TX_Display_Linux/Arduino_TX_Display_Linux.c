//<File !Start!>
// FILE: [Arduino_TX_Display_Linux.c]
// Created by GUIslice Builder version: [0.16.b006]
//
// GUIslice Builder Generated File
//
// For the latest guides, updates and support view:
// https://github.com/ImpulseAdventure/GUIslice
//
//<File !End!>
//

// ------------------------------------------------
// Headers to include
// ------------------------------------------------
#include "GUIslice.h"
#include "GUIslice_drv.h"
#include "serial.h"

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
// Defines for resources
// ------------------------------------------------
#define MAX_PATH  255
//<PathStorage !Start!>
//<PathStorage !End!>

// ------------------------------------------------
// Headers and Defines for fonts
// ------------------------------------------------
//<Fonts !Start!>
#define FONT_FREE_MONO9 "/usr/share/fonts/truetype/freefont/FreeMono.ttf"
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
      ,channelSettings,transmittingSettings,setupChannel,setupOutputPWM
      ,setupOutputStepper,setupOutputNotNeeded,setModel
      ,E_POP_KEYPAD_NUM};
enum {BTN_Quit,E_ELEM_BTN279,E_ELEM_BTN65,E_ELEM_TEXT305,E_ELEM_TEXT307
      ,E_ELEM_TEXT309,E_ELEM_TEXT312,E_ELEM_TEXT330,E_ELEM_TEXT332
      ,E_ELEM_TEXT667,E_ELEM_TEXT669,E_ELEM_TEXT670,E_ELEM_TEXT674
      ,E_ELEM_TEXT675,E_ELEM_TEXT676,E_ELEM_TEXT745,E_ELEM_TEXT746
      ,E_ELEM_TEXT797,E_ELEM_TEXT922,E_ELEM_TEXT923,E_ELEM_TEXT924
      ,E_ELEM_TEXT925,E_ELEM_TEXT926,E_ELEM_TEXT927,E_ELEM_TEXT928
      ,E_ELEM_TEXT929,E_ELEM_TEXT930,E_ELEM_TEXT931,E_ELEM_TEXT952,b5
      ,backbtncal,backbtnchconf,backbtnchs,backbtnchsandsendstorx
      ,backbtnsetupNotNeeded,backbtnsetupPWM,backbtnsetupStepper,c1,c10
      ,c2,c3,c4,c5,c6,c7,c8,c9,centeredStick,channelname,channelval
      ,configuredIO1,configuredIO2,d1,d10,d2,d3,d4,d5,d6,d7,d8,d9
      ,dcurio,deadzone0,deadzonetxt,defaultval,detectIO1,detectIO2
      ,dprevio,drbackbtn,h1,h10,h2,h3,h4,h5,h6,h7,h8,h9,l1,l10,l2,l3,l4
      ,l5,l6,l7,l8,l9,lsbChannelOutputType,m1,m10,m2,m3,m4,m5,m6,m7,m8
      ,m9,n0,n1,n10,n11,n12,n13,n14,n15,n16,n17,n18,n19,n2,n20,n21,n22
      ,n23,n3,n4,n5,n6,n7,n8,n9,nBatPercent,navMODEL,navRAW,navRC
      ,navSETADC,navSETCH,nr0,nr1,nr2,nr3,nr4,nr5,nr6,nr7,nr8,nr9
      ,pwmFreq,reverse,reversetxt,savebtncal,savebtnchconf,setch1
      ,setch10,setch11,setch12,setch13,setch14,setch15,setch16,setch17
      ,setch18,setch19,setch2,setch20,setch21,setch22,setch23,setch24
      ,setch3,setch4,setch5,setch6,setch7,setch8,setch9
      ,settingstxtorxprogress,sm0,sm1,sm2,sm3,sm4,sm5,sm6,sm7
      ,stepMaxFreq,stepMinFreq,t0,t1,t10,t11,t12,t13,t14,t15,t16,t17
      ,t18,t19,t2,t20,t21,t22,t23,t3,t4,t5,t6,t7,t8,t9,tr0,tr1,tr2,tr3
      ,tr4,tr5,tr6,tr7,tr8,tr9,txt_ch1,txt_ch2,txt_ch3,txt_ch4,txt_ch5
      ,txt_ch6,txt_ch7,txt_ch8,E_ELEM_KEYPAD_NUM};
// Must use separate enum for fonts with MAX_FONT at end to use gslc_FontSet.
enum {E_FREEMONO9PT,MAX_FONT};
//<Enum !End!>

// ------------------------------------------------
// Instantiate the GUI
// ------------------------------------------------

// ------------------------------------------------
// Define the maximum number of elements and pages
// ------------------------------------------------
//<ElementDefines !Start!>
#define MAX_PAGE                13

#define MAX_ELEM_BasePage 2                                          // # Elems total on page
#define MAX_ELEM_BasePage_RAM MAX_ELEM_BasePage // # Elems in RAM

#define MAX_ELEM_PG_MAIN 5                                          // # Elems total on page
#define MAX_ELEM_PG_MAIN_RAM MAX_ELEM_PG_MAIN // # Elems in RAM

#define MAX_ELEM_calibrations 65                                         // # Elems total on page
#define MAX_ELEM_calibrations_RAM MAX_ELEM_calibrations // # Elems in RAM

#define MAX_ELEM_DisplayRawValues 25                                         // # Elems total on page
#define MAX_ELEM_DisplayRawValues_RAM MAX_ELEM_DisplayRawValues // # Elems in RAM

#define MAX_ELEM_DisplayRcValues 49                                         // # Elems total on page
#define MAX_ELEM_DisplayRcValues_RAM MAX_ELEM_DisplayRcValues // # Elems in RAM

#define MAX_ELEM_channelSettings 26                                         // # Elems total on page
#define MAX_ELEM_channelSettings_RAM MAX_ELEM_channelSettings // # Elems in RAM

#define MAX_ELEM_transmittingSettings 3                                          // # Elems total on page
#define MAX_ELEM_transmittingSettings_RAM MAX_ELEM_transmittingSettings // # Elems in RAM

#define MAX_ELEM_setupChannel 19                                         // # Elems total on page
#define MAX_ELEM_setupChannel_RAM MAX_ELEM_setupChannel // # Elems in RAM

#define MAX_ELEM_setupOutputPWM 4                                          // # Elems total on page
#define MAX_ELEM_setupOutputPWM_RAM MAX_ELEM_setupOutputPWM // # Elems in RAM

#define MAX_ELEM_setupOutputStepper 6                                          // # Elems total on page
#define MAX_ELEM_setupOutputStepper_RAM MAX_ELEM_setupOutputStepper // # Elems in RAM

#define MAX_ELEM_setupOutputNotNeeded 2                                          // # Elems total on page
#define MAX_ELEM_setupOutputNotNeeded_RAM MAX_ELEM_setupOutputNotNeeded // # Elems in RAM

#define MAX_ELEM_setModel 17                                         // # Elems total on page
#define MAX_ELEM_setModel_RAM MAX_ELEM_setModel // # Elems in RAM
//<ElementDefines !End!>

// ------------------------------------------------
// Create element storage
// ------------------------------------------------
// GUI Elements
gslc_tsGui                      m_gui;
gslc_tsDriver                   m_drv;
gslc_tsFont                     m_asFont[MAX_FONT];
gslc_tsPage                     m_asPage[MAX_PAGE];

//<GUI_Extra_Elements !Start!>
gslc_tsElem                     m_asBasePage2Elem[MAX_ELEM_BasePage_RAM];
gslc_tsElemRef                  m_asBasePage2ElemRef[MAX_ELEM_BasePage];
gslc_tsElem                     m_asPage1Elem[MAX_ELEM_PG_MAIN_RAM];
gslc_tsElemRef                  m_asPage1ElemRef[MAX_ELEM_PG_MAIN];
gslc_tsElem                     m_asPage39Elem[MAX_ELEM_calibrations_RAM];
gslc_tsElemRef                  m_asPage39ElemRef[MAX_ELEM_calibrations];
gslc_tsElem                     m_asPage40Elem[MAX_ELEM_DisplayRawValues_RAM];
gslc_tsElemRef                  m_asPage40ElemRef[MAX_ELEM_DisplayRawValues];
gslc_tsElem                     m_asPage41Elem[MAX_ELEM_DisplayRcValues_RAM];
gslc_tsElemRef                  m_asPage41ElemRef[MAX_ELEM_DisplayRcValues];
gslc_tsElem                     m_asPage42Elem[MAX_ELEM_channelSettings_RAM];
gslc_tsElemRef                  m_asPage42ElemRef[MAX_ELEM_channelSettings];
gslc_tsElem                     m_asPopup13Elem[MAX_ELEM_transmittingSettings_RAM];
gslc_tsElemRef                  m_asPopup13ElemRef[MAX_ELEM_transmittingSettings];
gslc_tsElem                     m_asPage43Elem[MAX_ELEM_setupChannel_RAM];
gslc_tsElemRef                  m_asPage43ElemRef[MAX_ELEM_setupChannel];
gslc_tsElem                     m_asPage44Elem[MAX_ELEM_setupOutputPWM_RAM];
gslc_tsElemRef                  m_asPage44ElemRef[MAX_ELEM_setupOutputPWM];
gslc_tsElem                     m_asPage45Elem[MAX_ELEM_setupOutputStepper_RAM];
gslc_tsElemRef                  m_asPage45ElemRef[MAX_ELEM_setupOutputStepper];
gslc_tsElem                     m_asPage46Elem[MAX_ELEM_setupOutputNotNeeded_RAM];
gslc_tsElemRef                  m_asPage46ElemRef[MAX_ELEM_setupOutputNotNeeded];
gslc_tsElem                     m_asPage49Elem[MAX_ELEM_setModel_RAM];
gslc_tsElemRef                  m_asPage49ElemRef[MAX_ELEM_setModel];
gslc_tsElem                     m_asKeypadNumElem[1];
gslc_tsElemRef                  m_asKeypadNumElemRef[1];
gslc_tsXKeyPad                  m_sKeyPadNum;
gslc_tsXSlider                  m_sXSlider6;
gslc_tsXTogglebtn               m_asXToggle100;
gslc_tsXTogglebtn               m_asXToggle101;
gslc_tsXListbox                 m_sListbox3;
// - Note that XLISTBOX_BUF_OH_R is extra required per item
char                            m_acListboxBuf3[60 + XLISTBOX_BUF_OH_R];
gslc_tsXTogglebtn               m_asXToggle118;
gslc_tsXTogglebtn               m_asXToggle119;
gslc_tsXTogglebtn               m_asXToggle120;
gslc_tsXTogglebtn               m_asXToggle121;
gslc_tsXTogglebtn               m_asXToggle122;
gslc_tsXTogglebtn               m_asXToggle123;
gslc_tsXTogglebtn               m_asXToggle124;
gslc_tsXTogglebtn               m_asXToggle125;

#define MAX_STR                 100

//<GUI_Extra_Elements !End!>

// ------------------------------------------------
// Program Globals
// ------------------------------------------------
bool m_bQuit = false;

int serial_fd;

// Save some element references for direct access
//<Save_References !Start!>
gslc_tsElemRef*  m_pCenteredstick  = NULL;
gslc_tsElemRef*  m_pDeadzone0      = NULL;
gslc_tsElemRef*  m_pDefaultval     = NULL;
gslc_tsElemRef*  m_pLsbchanneloutputtype= NULL;
gslc_tsElemRef*  m_pPwmfreq        = NULL;
gslc_tsElemRef*  m_pReverse        = NULL;
gslc_tsElemRef*  m_pSm0            = NULL;
gslc_tsElemRef*  m_pSm1            = NULL;
gslc_tsElemRef*  m_pSm2            = NULL;
gslc_tsElemRef*  m_pSm3            = NULL;
gslc_tsElemRef*  m_pSm4            = NULL;
gslc_tsElemRef*  m_pSm5            = NULL;
gslc_tsElemRef*  m_pSm6            = NULL;
gslc_tsElemRef*  m_pSm7            = NULL;
gslc_tsElemRef*  m_pStepmaxfreq    = NULL;
gslc_tsElemRef*  m_pStepminfreq    = NULL;
gslc_tsElemRef*  m_pElemKeyPadNum  = NULL;
//<Save_References !End!>


// Configure environment variables suitable for display
// - These may need modification to match your system
//   environment and display type
// - Defaults for GSLC_DEV_FB and GSLC_DEV_TOUCH are in GUIslice_config.h
// - Note that the environment variable settings can
//   also be set directly within the shell via export
//   (or init script).
//   - eg. export TSLIB_FBDEVICE=/dev/fb1
void UserInitEnv()
{
#if defined(DRV_DISP_SDL1) || defined(DRV_DISP_SDL2)
  setenv((char*)"FRAMEBUFFER",GSLC_DEV_FB,1);
  setenv((char*)"SDL_FBDEV",GSLC_DEV_FB,1);
  setenv((char*)"SDL_VIDEODRIVER",GSLC_DEV_VID_DRV,1);
#endif

#if defined(DRV_TOUCH_TSLIB)
  setenv((char*)"TSLIB_FBDEVICE",GSLC_DEV_FB,1);
  setenv((char*)"TSLIB_TSDEVICE",GSLC_DEV_TOUCH,1);
  setenv((char*)"TSLIB_CALIBFILE",(char*)"/etc/pointercal",1);
  setenv((char*)"TSLIB_CONFFILE",(char*)"/etc/ts.conf",1);
  setenv((char*)"TSLIB_PLUGINDIR",(char*)"/usr/local/lib/ts",1);
#endif
}

static int16_t HmiOut(char ch)
{
    uint8_t buf[1] = {ch};
    write(serial_fd, buf, 1);
    return 0;
}
static int16_t HmiIn()
{
  uint8_t buf[1] = {0};
  size_t readBytes = read(serial_fd, buf, 1);
  if(readBytes == 0)
  {
    return -1;
  }
  return buf[0];
}
// Define debug message function
static int16_t DebugOut(char ch) { fputc(ch,stderr); return 0; }

static void HmiInit(const char* serialPort){
    serial_fd = open_port(serialPort, B115200);
    if(serial_fd == 0)
    {
        printf("ERROR, Serialport not opened");
        exit(1);
    }
}


// ------------------------------------------------
// Callback Methods
// ------------------------------------------------
// Common Button callback
bool CbBtnCommon(void* pvGui,void *pvElemRef,gslc_teTouch eTouch,int16_t nX,int16_t nY)
{
  // Typecast the parameters to match the GUI and element types
  gslc_tsGui*     pGui     = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem*    pElem    = gslc_GetElemFromRef(pGui,pElemRef);

  if ( eTouch == GSLC_TOUCH_UP_IN ) {
    // From the element's ID we can determine which button was pressed.
    switch (pElem->nId) {
//<Button Enums !Start!>
      case BTN_Quit:
        m_bQuit = true;
        break;
      case navRC:
        //TODO- Replace with button handling code
        break;
      case navRAW:
        //TODO- Replace with button handling code
        break;
      case navSETADC:
        //TODO- Replace with button handling code
        break;
      case navSETCH:
        //TODO- Replace with button handling code
        break;
      case navMODEL:
        //TODO- Replace with button handling code
        break;
      case l1:
        //TODO- Replace with button handling code
        break;
      case m1:
        //TODO- Replace with button handling code
        break;
      case h1:
        //TODO- Replace with button handling code
        break;
      case l2:
        //TODO- Replace with button handling code
        break;
      case m2:
        //TODO- Replace with button handling code
        break;
      case h2:
        //TODO- Replace with button handling code
        break;
      case l3:
        //TODO- Replace with button handling code
        break;
      case m3:
        //TODO- Replace with button handling code
        break;
      case h3:
        //TODO- Replace with button handling code
        break;
      case l4:
        //TODO- Replace with button handling code
        break;
      case m4:
        //TODO- Replace with button handling code
        break;
      case h4:
        //TODO- Replace with button handling code
        break;
      case l5:
        //TODO- Replace with button handling code
        break;
      case m5:
        //TODO- Replace with button handling code
        break;
      case h5:
        //TODO- Replace with button handling code
        break;
      case l6:
        //TODO- Replace with button handling code
        break;
      case m6:
        //TODO- Replace with button handling code
        break;
      case h6:
        //TODO- Replace with button handling code
        break;
      case l7:
        //TODO- Replace with button handling code
        break;
      case m7:
        //TODO- Replace with button handling code
        break;
      case h7:
        //TODO- Replace with button handling code
        break;
      case l8:
        //TODO- Replace with button handling code
        break;
      case m8:
        //TODO- Replace with button handling code
        break;
      case h8:
        //TODO- Replace with button handling code
        break;
      case l9:
        //TODO- Replace with button handling code
        break;
      case m9:
        //TODO- Replace with button handling code
        break;
      case h9:
        //TODO- Replace with button handling code
        break;
      case l10:
        //TODO- Replace with button handling code
        break;
      case m10:
        //TODO- Replace with button handling code
        break;
      case h10:
        //TODO- Replace with button handling code
        break;
      case backbtncal:
        //TODO- Replace with button handling code
        break;
      case savebtncal:
        //TODO- Replace with button handling code
        break;
      case drbackbtn:
        //TODO- Replace with button handling code
        break;
      case b5:
        //TODO- Replace with button handling code
        break;
      case setch1:
        //TODO- Replace with button handling code
        break;
      case setch2:
        //TODO- Replace with button handling code
        break;
      case setch3:
        //TODO- Replace with button handling code
        break;
      case setch4:
        //TODO- Replace with button handling code
        break;
      case setch5:
        //TODO- Replace with button handling code
        break;
      case setch6:
        //TODO- Replace with button handling code
        break;
      case setch7:
        //TODO- Replace with button handling code
        break;
      case setch8:
        //TODO- Replace with button handling code
        break;
      case setch9:
        //TODO- Replace with button handling code
        break;
      case setch10:
        //TODO- Replace with button handling code
        break;
      case setch11:
        //TODO- Replace with button handling code
        break;
      case setch12:
        //TODO- Replace with button handling code
        break;
      case setch13:
        //TODO- Replace with button handling code
        break;
      case setch14:
        //TODO- Replace with button handling code
        break;
      case setch15:
        //TODO- Replace with button handling code
        break;
      case setch16:
        //TODO- Replace with button handling code
        break;
      case setch17:
        //TODO- Replace with button handling code
        break;
      case setch18:
        //TODO- Replace with button handling code
        break;
      case setch19:
        //TODO- Replace with button handling code
        break;
      case setch20:
        //TODO- Replace with button handling code
        break;
      case setch21:
        //TODO- Replace with button handling code
        break;
      case setch22:
        //TODO- Replace with button handling code
        break;
      case setch23:
        //TODO- Replace with button handling code
        break;
      case setch24:
        //TODO- Replace with button handling code
        break;
      case backbtnchs:
        //TODO- Replace with button handling code
        break;
      case backbtnchsandsendstorx:
        //TODO- Replace with button handling code
        break;
      case reverse:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pReverse)) {
          ;
        }
        break;
      case centeredStick:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pCenteredstick)) {
          ;
        }
        break;
      case detectIO1:
        //TODO- Replace with button handling code
        break;
      case detectIO2:
        //TODO- Replace with button handling code
        break;
      case defaultval:
        // Clicked on edit field, so show popup box and associate with this text field
        gslc_ElemXKeyPadInputAsk(&m_gui, m_pElemKeyPadNum, E_POP_KEYPAD_NUM, m_pDefaultval);
        break;
      case savebtnchconf:
        //TODO- Replace with button handling code
        break;
      case backbtnchconf:
        //TODO- Replace with button handling code
        break;
      case E_ELEM_BTN279:
        //TODO- Replace with button handling code
        break;
      case pwmFreq:
        // Clicked on edit field, so show popup box and associate with this text field
        gslc_ElemXKeyPadInputAsk(&m_gui, m_pElemKeyPadNum, E_POP_KEYPAD_NUM, m_pPwmfreq);
        break;
      case backbtnsetupPWM:
        //TODO- Replace with button handling code
        break;
      case stepMinFreq:
        // Clicked on edit field, so show popup box and associate with this text field
        gslc_ElemXKeyPadInputAsk(&m_gui, m_pElemKeyPadNum, E_POP_KEYPAD_NUM, m_pStepminfreq);
        break;
      case stepMaxFreq:
        // Clicked on edit field, so show popup box and associate with this text field
        gslc_ElemXKeyPadInputAsk(&m_gui, m_pElemKeyPadNum, E_POP_KEYPAD_NUM, m_pStepmaxfreq);
        break;
      case backbtnsetupStepper:
        //TODO- Replace with button handling code
        break;
      case backbtnsetupNotNeeded:
        //TODO- Replace with button handling code
        break;
      case sm0:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pSm0)) {
          ;
        }
        break;
      case sm1:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pSm1)) {
          ;
        }
        break;
      case sm2:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pSm2)) {
          ;
        }
        break;
      case sm3:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pSm3)) {
          ;
        }
        break;
      case sm4:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pSm4)) {
          ;
        }
        break;
      case sm5:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pSm5)) {
          ;
        }
        break;
      case sm6:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pSm6)) {
          ;
        }
        break;
      case sm7:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pSm7)) {
          ;
        }
        break;
      case E_ELEM_BTN65:
        //TODO- Replace with button handling code
        break;
//<Button Enums !End!>
      default:
        break;
    }
  }
  return true;
}
//<Checkbox Callback !Start!>
//<Checkbox Callback !End!>
// KeyPad Input Ready callback
bool CbKeypad(void* pvGui, void *pvElemRef, int16_t nState, void* pvData)
{
  gslc_tsGui*     pGui     = (gslc_tsGui*)pvGui;
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem*    pElem    = gslc_GetElemFromRef(pGui,pElemRef);

  // From the pvData we can get the ID element that is ready.
  int16_t nTargetElemId = gslc_ElemXKeyPadDataTargetIdGet(pGui, pvData);
  if (nState == XKEYPAD_CB_STATE_DONE) {
    // User clicked on Enter to leave popup
    // - If we have a popup active, pass the return value directly to
    //   the corresponding value field
    switch (nTargetElemId) {
//<Keypad Enums !Start!>
      case defaultval:
        gslc_ElemXKeyPadInputGet(pGui, m_pDefaultval, pvData);
	    gslc_PopupHide(&m_gui);
        break;
      case pwmFreq:
        gslc_ElemXKeyPadInputGet(pGui, m_pPwmfreq, pvData);
	    gslc_PopupHide(&m_gui);
        break;
      case stepMinFreq:
        gslc_ElemXKeyPadInputGet(pGui, m_pStepminfreq, pvData);
	    gslc_PopupHide(&m_gui);
        break;
      case stepMaxFreq:
        gslc_ElemXKeyPadInputGet(pGui, m_pStepmaxfreq, pvData);
	    gslc_PopupHide(&m_gui);
        break;

//<Keypad Enums !End!>
      default:
        break;
    }
  } else if (nState == XKEYPAD_CB_STATE_CANCEL) {
    // User escaped from popup, so don't update values
    gslc_PopupHide(&m_gui);
  }
  return true;
}
//<Spinner Callback !Start!>
//<Spinner Callback !End!>
bool CbListbox(void* pvGui, void* pvElemRef, int16_t nSelId)
{
  gslc_tsGui*     pGui     = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem*    pElem    = gslc_GetElemFromRef(pGui, pElemRef);
  char            acTxt[MAX_STR + 1];
  
  if (pElemRef == NULL) {
    return false;
  }

  // From the element's ID we can determine which listbox was active.
  switch (pElem->nId) {
//<Listbox Enums !Start!>
    case lsbChannelOutputType:
      //TODO: Add your listbox selection code here
      if (nSelId != XLISTBOX_SEL_NONE) {
        gslc_ElemXListboxGetItem(&m_gui, pElemRef, nSelId, acTxt, MAX_STR);
      }
      break;

//<Listbox Enums !End!>
    default:
      break;
  }
  return true;
}
//<Draw Callback !Start!>
//<Draw Callback !End!>

// Callback function for when a slider's position has been updated
bool CbSlidePos(void* pvGui,void* pvElemRef,int16_t nPos)
{
  gslc_tsGui*     pGui      = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef  = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem*    pElem     = gslc_GetElemFromRef(pGui,pElemRef);
  int16_t         nVal;

  // From the element's ID we can determine which slider was updated.
  switch (pElem->nId) {
//<Slider Enums !Start!>
    case deadzone0:
      // Fetch the slider position
      nVal = gslc_ElemXSliderGetPos(pGui,m_pDeadzone0);
      //TODO- Replace with slider handling code
      break;

//<Slider Enums !End!>
    default:
      break;
  }

  return true;
}
//<Tick Callback !Start!>
//<Tick Callback !End!>

// ------------------------------------------------
// Create page elements
// - strPath: Path to executable passed in to locate resource files
// ------------------------------------------------
bool InitGUI(char *strPath)
{
  gslc_tsElemRef* pElemRef = NULL;

//<InitGUI !Start!>
  gslc_PageAdd(&m_gui,BasePage,m_asBasePage2Elem,MAX_ELEM_BasePage_RAM,m_asBasePage2ElemRef,MAX_ELEM_BasePage);
  gslc_PageSetHmiEvents(&m_gui,BasePage, false, false);
  gslc_PageAdd(&m_gui,E_PG_MAIN,m_asPage1Elem,MAX_ELEM_PG_MAIN_RAM,m_asPage1ElemRef,MAX_ELEM_PG_MAIN);
  gslc_PageSetHmiEvents(&m_gui,E_PG_MAIN, true, false);
  gslc_PageAdd(&m_gui,calibrations,m_asPage39Elem,MAX_ELEM_calibrations_RAM,m_asPage39ElemRef,MAX_ELEM_calibrations);
  gslc_PageSetHmiEvents(&m_gui,calibrations, true, false);
  gslc_PageAdd(&m_gui,DisplayRawValues,m_asPage40Elem,MAX_ELEM_DisplayRawValues_RAM,m_asPage40ElemRef,MAX_ELEM_DisplayRawValues);
  gslc_PageSetHmiEvents(&m_gui,DisplayRawValues, true, false);
  gslc_PageAdd(&m_gui,DisplayRcValues,m_asPage41Elem,MAX_ELEM_DisplayRcValues_RAM,m_asPage41ElemRef,MAX_ELEM_DisplayRcValues);
  gslc_PageSetHmiEvents(&m_gui,DisplayRcValues, true, false);
  gslc_PageAdd(&m_gui,channelSettings,m_asPage42Elem,MAX_ELEM_channelSettings_RAM,m_asPage42ElemRef,MAX_ELEM_channelSettings);
  gslc_PageSetHmiEvents(&m_gui,channelSettings, true, false);
  gslc_PageAdd(&m_gui,transmittingSettings,m_asPopup13Elem,MAX_ELEM_transmittingSettings_RAM,m_asPopup13ElemRef,MAX_ELEM_transmittingSettings);
  gslc_PageSetHmiEvents(&m_gui,transmittingSettings, false, false);
  gslc_PageAdd(&m_gui,setupChannel,m_asPage43Elem,MAX_ELEM_setupChannel_RAM,m_asPage43ElemRef,MAX_ELEM_setupChannel);
  gslc_PageSetHmiEvents(&m_gui,setupChannel, true, false);
  gslc_PageAdd(&m_gui,setupOutputPWM,m_asPage44Elem,MAX_ELEM_setupOutputPWM_RAM,m_asPage44ElemRef,MAX_ELEM_setupOutputPWM);
  gslc_PageSetHmiEvents(&m_gui,setupOutputPWM, false, false);
  gslc_PageAdd(&m_gui,setupOutputStepper,m_asPage45Elem,MAX_ELEM_setupOutputStepper_RAM,m_asPage45ElemRef,MAX_ELEM_setupOutputStepper);
  gslc_PageSetHmiEvents(&m_gui,setupOutputStepper, false, false);
  gslc_PageAdd(&m_gui,setupOutputNotNeeded,m_asPage46Elem,MAX_ELEM_setupOutputNotNeeded_RAM,m_asPage46ElemRef,MAX_ELEM_setupOutputNotNeeded);
  gslc_PageSetHmiEvents(&m_gui,setupOutputNotNeeded, false, false);
  gslc_PageAdd(&m_gui,setModel,m_asPage49Elem,MAX_ELEM_setModel_RAM,m_asPage49ElemRef,MAX_ELEM_setModel);
  gslc_PageSetHmiEvents(&m_gui,setModel, true, false);
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
  pElemRef = gslc_ElemCreateTxt(&m_gui,nBatPercent,BasePage,(gslc_tsRect){0,0,65,11},
    (char*)"Battery 100%",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // create BTN_Quit button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,BTN_Quit,BasePage,
    (gslc_tsRect){280,0,35,18},(char*)"Quit",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);

  // -----------------------------------
  // PAGE: E_PG_MAIN
  
  // create navRC button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,navRC,E_PG_MAIN,
    (gslc_tsRect){20,40,130,25},(char*)"Display RC Channels",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create navRAW button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,navRAW,E_PG_MAIN,
    (gslc_tsRect){20,80,130,25},(char*)"Display RAW Channels",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create navSETADC button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,navSETADC,E_PG_MAIN,
    (gslc_tsRect){20,120,130,25},(char*)"Setup ADC Params",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create navSETCH button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,navSETCH,E_PG_MAIN,
    (gslc_tsRect){20,160,130,25},(char*)"Setup channels",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create navMODEL button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,navMODEL,E_PG_MAIN,
    (gslc_tsRect){20,200,130,25},(char*)"Choose model",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);

  // -----------------------------------
  // PAGE: calibrations
  
  // Create E_ELEM_TEXT922 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT922,calibrations,(gslc_tsRect){40,20,18,11},
    (char*)"CH1",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT923 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT923,calibrations,(gslc_tsRect){40,60,18,11},
    (char*)"CH2",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT924 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT924,calibrations,(gslc_tsRect){40,100,18,11},
    (char*)"CH3",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT925 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT925,calibrations,(gslc_tsRect){40,140,18,11},
    (char*)"CH4",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT926 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT926,calibrations,(gslc_tsRect){40,180,18,11},
    (char*)"CH5",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT927 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT927,calibrations,(gslc_tsRect){190,20,19,11},
    (char*)"CH6",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT928 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT928,calibrations,(gslc_tsRect){190,60,18,11},
    (char*)"CH7",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT929 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT929,calibrations,(gslc_tsRect){190,100,18,11},
    (char*)"CH8",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT930 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT930,calibrations,(gslc_tsRect){190,140,19,11},
    (char*)"CH9",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT931 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT931,calibrations,(gslc_tsRect){190,180,24,11},
    (char*)"CH10",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create d1 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,d1,calibrations,(gslc_tsRect){70,20,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create c1 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,c1,calibrations,(gslc_tsRect){110,20,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // create l1 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,l1,calibrations,
    (gslc_tsRect){30,35,35,20},(char*)"min",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create m1 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,m1,calibrations,
    (gslc_tsRect){65,35,35,20},(char*)"mid",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create h1 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,h1,calibrations,
    (gslc_tsRect){100,35,35,20},(char*)"max",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create d2 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,d2,calibrations,(gslc_tsRect){70,60,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create c2 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,c2,calibrations,(gslc_tsRect){110,60,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // create l2 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,l2,calibrations,
    (gslc_tsRect){30,75,35,20},(char*)"min",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create m2 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,m2,calibrations,
    (gslc_tsRect){65,75,35,20},(char*)"mid",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create h2 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,h2,calibrations,
    (gslc_tsRect){100,75,35,20},(char*)"max",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create d3 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,d3,calibrations,(gslc_tsRect){70,100,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create c3 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,c3,calibrations,(gslc_tsRect){110,100,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // create l3 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,l3,calibrations,
    (gslc_tsRect){30,115,35,20},(char*)"min",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create m3 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,m3,calibrations,
    (gslc_tsRect){65,115,35,20},(char*)"mid",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create h3 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,h3,calibrations,
    (gslc_tsRect){100,115,35,20},(char*)"max",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create d4 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,d4,calibrations,(gslc_tsRect){70,140,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create c4 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,c4,calibrations,(gslc_tsRect){110,140,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // create l4 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,l4,calibrations,
    (gslc_tsRect){30,155,35,20},(char*)"min",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create m4 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,m4,calibrations,
    (gslc_tsRect){65,155,35,20},(char*)"mid",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create h4 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,h4,calibrations,
    (gslc_tsRect){100,155,35,20},(char*)"max",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create d5 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,d5,calibrations,(gslc_tsRect){70,180,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create c5 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,c5,calibrations,(gslc_tsRect){110,180,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // create l5 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,l5,calibrations,
    (gslc_tsRect){30,195,35,20},(char*)"min",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create m5 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,m5,calibrations,
    (gslc_tsRect){65,195,35,20},(char*)"mid",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create h5 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,h5,calibrations,
    (gslc_tsRect){100,195,35,20},(char*)"max",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create d6 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,d6,calibrations,(gslc_tsRect){220,20,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create c6 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,c6,calibrations,(gslc_tsRect){260,20,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // create l6 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,l6,calibrations,
    (gslc_tsRect){180,35,35,20},(char*)"min",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create m6 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,m6,calibrations,
    (gslc_tsRect){215,35,35,20},(char*)"mid",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create h6 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,h6,calibrations,
    (gslc_tsRect){250,35,35,20},(char*)"max",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create d7 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,d7,calibrations,(gslc_tsRect){220,60,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create c7 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,c7,calibrations,(gslc_tsRect){260,60,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // create l7 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,l7,calibrations,
    (gslc_tsRect){180,75,35,20},(char*)"min",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create m7 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,m7,calibrations,
    (gslc_tsRect){215,75,35,20},(char*)"mid",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create h7 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,h7,calibrations,
    (gslc_tsRect){250,75,35,20},(char*)"max",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create d8 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,d8,calibrations,(gslc_tsRect){220,100,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create c8 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,c8,calibrations,(gslc_tsRect){260,100,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // create l8 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,l8,calibrations,
    (gslc_tsRect){180,115,35,20},(char*)"min",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create m8 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,m8,calibrations,
    (gslc_tsRect){215,115,35,20},(char*)"mid",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create h8 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,h8,calibrations,
    (gslc_tsRect){250,115,35,20},(char*)"max",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create d9 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,d9,calibrations,(gslc_tsRect){220,140,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create c9 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,c9,calibrations,(gslc_tsRect){260,140,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // create l9 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,l9,calibrations,
    (gslc_tsRect){180,155,35,20},(char*)"min",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create m9 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,m9,calibrations,
    (gslc_tsRect){215,155,35,20},(char*)"mid",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create h9 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,h9,calibrations,
    (gslc_tsRect){250,155,35,20},(char*)"max",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create d10 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,d10,calibrations,(gslc_tsRect){220,180,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create c10 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,c10,calibrations,(gslc_tsRect){260,180,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // create l10 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,l10,calibrations,
    (gslc_tsRect){180,195,35,20},(char*)"min",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create m10 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,m10,calibrations,
    (gslc_tsRect){215,195,35,20},(char*)"mid",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create h10 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,h10,calibrations,
    (gslc_tsRect){250,195,35,20},(char*)"max",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create E_ELEM_TEXT952 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT952,calibrations,(gslc_tsRect){120,5,70,11},
    (char*)"deadzone: +/-",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create deadzonetxt text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,deadzonetxt,calibrations,(gslc_tsRect){150,15,13,11},
    (char*)"20",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);

  // Create slider deadzone0 
  pElemRef = gslc_ElemXSliderCreate(&m_gui,deadzone0,calibrations,&m_sXSlider6,
          (gslc_tsRect){150,30,20,200},0,100,0,5,false);
  gslc_ElemXSliderSetStyle(&m_gui,pElemRef,false,GSLC_COL_BLUE,10,5,GSLC_COL_BLUE);
  gslc_ElemXSliderSetPosFunc(&m_gui,pElemRef,&CbSlidePos);
  m_pDeadzone0 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create backbtncal button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,backbtncal,calibrations,
    (gslc_tsRect){0,20,20,20},(char*)"B",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create savebtncal button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,savebtncal,calibrations,
    (gslc_tsRect){143,215,30,20},(char*)"SAVE",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);

  // -----------------------------------
  // PAGE: DisplayRawValues
  
  // Create tr0 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,tr0,DisplayRawValues,(gslc_tsRect){5,25,24,11},
    (char*)"ADC1",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create nr0 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,nr0,DisplayRawValues,(gslc_tsRect){45,25,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create tr1 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,tr1,DisplayRawValues,(gslc_tsRect){5,45,24,11},
    (char*)"ADC2",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create nr1 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,nr1,DisplayRawValues,(gslc_tsRect){45,45,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create tr2 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,tr2,DisplayRawValues,(gslc_tsRect){5,65,24,11},
    (char*)"ADC3",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create nr2 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,nr2,DisplayRawValues,(gslc_tsRect){45,65,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create tr3 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,tr3,DisplayRawValues,(gslc_tsRect){5,85,24,11},
    (char*)"ADC4",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create nr3 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,nr3,DisplayRawValues,(gslc_tsRect){45,85,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create tr4 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,tr4,DisplayRawValues,(gslc_tsRect){5,105,24,11},
    (char*)"ADC5",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create nr4 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,nr4,DisplayRawValues,(gslc_tsRect){45,105,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create tr5 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,tr5,DisplayRawValues,(gslc_tsRect){5,125,24,11},
    (char*)"ADC6",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create nr5 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,nr5,DisplayRawValues,(gslc_tsRect){45,125,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create tr6 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,tr6,DisplayRawValues,(gslc_tsRect){5,145,24,11},
    (char*)"ADC7",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create nr6 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,nr6,DisplayRawValues,(gslc_tsRect){45,145,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create tr7 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,tr7,DisplayRawValues,(gslc_tsRect){5,165,24,11},
    (char*)"ADC8",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create nr7 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,nr7,DisplayRawValues,(gslc_tsRect){45,165,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create tr8 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,tr8,DisplayRawValues,(gslc_tsRect){5,185,24,11},
    (char*)"ADC9",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create nr8 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,nr8,DisplayRawValues,(gslc_tsRect){45,185,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create tr9 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,tr9,DisplayRawValues,(gslc_tsRect){5,205,30,11},
    (char*)"ADC10",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create nr9 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,nr9,DisplayRawValues,(gslc_tsRect){45,205,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT332 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT332,DisplayRawValues,(gslc_tsRect){170,20,35,11},
    (char*)"PrevIO",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create dprevio text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,dprevio,DisplayRawValues,(gslc_tsRect){100,35,163,11},
    (char*)"00000000000000000000000000000000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT330 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT330,DisplayRawValues,(gslc_tsRect){173,65,30,11},
    (char*)"CurIO",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create dcurio text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,dcurio,DisplayRawValues,(gslc_tsRect){100,50,163,11},
    (char*)"00000000000000000000000000000000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // create drbackbtn button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,drbackbtn,DisplayRawValues,
    (gslc_tsRect){140,180,80,40},(char*)"Back",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);

  // -----------------------------------
  // PAGE: DisplayRcValues
  
  // Create t0 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t0,DisplayRcValues,(gslc_tsRect){5,15,18,11},
    (char*)"ch1",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n0 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n0,DisplayRcValues,(gslc_tsRect){45,15,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t1 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t1,DisplayRcValues,(gslc_tsRect){5,35,18,11},
    (char*)"ch2",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n1 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n1,DisplayRcValues,(gslc_tsRect){45,35,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t2 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t2,DisplayRcValues,(gslc_tsRect){5,55,18,11},
    (char*)"ch3",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n2 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n2,DisplayRcValues,(gslc_tsRect){45,55,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t3 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t3,DisplayRcValues,(gslc_tsRect){5,75,18,11},
    (char*)"ch4",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n3 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n3,DisplayRcValues,(gslc_tsRect){45,75,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t4 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t4,DisplayRcValues,(gslc_tsRect){5,95,18,11},
    (char*)"ch5",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n4 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n4,DisplayRcValues,(gslc_tsRect){45,95,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t5 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t5,DisplayRcValues,(gslc_tsRect){5,115,18,11},
    (char*)"ch6",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n5 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n5,DisplayRcValues,(gslc_tsRect){45,115,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t6 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t6,DisplayRcValues,(gslc_tsRect){5,135,18,11},
    (char*)"ch7",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n6 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n6,DisplayRcValues,(gslc_tsRect){45,135,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t7 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t7,DisplayRcValues,(gslc_tsRect){5,155,18,11},
    (char*)"ch8",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n7 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n7,DisplayRcValues,(gslc_tsRect){45,155,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t8 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t8,DisplayRcValues,(gslc_tsRect){95,15,18,11},
    (char*)"ch9",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n8 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n8,DisplayRcValues,(gslc_tsRect){135,15,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t9 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t9,DisplayRcValues,(gslc_tsRect){95,35,24,11},
    (char*)"ch10",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n9 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n9,DisplayRcValues,(gslc_tsRect){135,35,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t10 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t10,DisplayRcValues,(gslc_tsRect){95,55,24,11},
    (char*)"ch11",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n10 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n10,DisplayRcValues,(gslc_tsRect){135,55,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t11 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t11,DisplayRcValues,(gslc_tsRect){95,75,24,11},
    (char*)"ch12",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n11 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n11,DisplayRcValues,(gslc_tsRect){135,75,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t12 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t12,DisplayRcValues,(gslc_tsRect){95,95,24,11},
    (char*)"ch13",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n12 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n12,DisplayRcValues,(gslc_tsRect){135,95,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t13 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t13,DisplayRcValues,(gslc_tsRect){95,115,24,11},
    (char*)"ch14",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n13 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n13,DisplayRcValues,(gslc_tsRect){135,115,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t14 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t14,DisplayRcValues,(gslc_tsRect){95,135,24,11},
    (char*)"ch15",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n14 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n14,DisplayRcValues,(gslc_tsRect){135,135,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t15 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t15,DisplayRcValues,(gslc_tsRect){95,155,24,11},
    (char*)"ch16",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n15 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n15,DisplayRcValues,(gslc_tsRect){135,155,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t16 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t16,DisplayRcValues,(gslc_tsRect){185,15,24,11},
    (char*)"ch17",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n16 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n16,DisplayRcValues,(gslc_tsRect){235,15,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t17 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t17,DisplayRcValues,(gslc_tsRect){185,35,24,11},
    (char*)"ch18",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n17 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n17,DisplayRcValues,(gslc_tsRect){235,35,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t18 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t18,DisplayRcValues,(gslc_tsRect){185,55,24,11},
    (char*)"ch19",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n18 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n18,DisplayRcValues,(gslc_tsRect){235,55,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t19 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t19,DisplayRcValues,(gslc_tsRect){185,75,23,11},
    (char*)"ch20",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n19 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n19,DisplayRcValues,(gslc_tsRect){235,75,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t20 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t20,DisplayRcValues,(gslc_tsRect){185,95,23,11},
    (char*)"ch21",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n20 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n20,DisplayRcValues,(gslc_tsRect){235,95,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t21 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t21,DisplayRcValues,(gslc_tsRect){185,115,23,11},
    (char*)"ch22",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n21 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n21,DisplayRcValues,(gslc_tsRect){235,115,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t22 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t22,DisplayRcValues,(gslc_tsRect){185,135,23,11},
    (char*)"ch23",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n22 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n22,DisplayRcValues,(gslc_tsRect){235,135,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create t23 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,t23,DisplayRcValues,(gslc_tsRect){185,155,23,11},
    (char*)"ch24",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create n23 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,n23,DisplayRcValues,(gslc_tsRect){235,155,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // create b5 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,b5,DisplayRcValues,
    (gslc_tsRect){0,180,80,40},(char*)"Back",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);

  // -----------------------------------
  // PAGE: channelSettings
  
  // create setch1 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch1,channelSettings,
    (gslc_tsRect){5,35,30,20},(char*)"ch1",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch2 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch2,channelSettings,
    (gslc_tsRect){45,35,30,20},(char*)"ch2",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch3 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch3,channelSettings,
    (gslc_tsRect){85,35,30,20},(char*)"ch3",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch4 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch4,channelSettings,
    (gslc_tsRect){125,35,30,20},(char*)"ch4",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch5 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch5,channelSettings,
    (gslc_tsRect){165,35,30,20},(char*)"ch5",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch6 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch6,channelSettings,
    (gslc_tsRect){205,35,30,20},(char*)"ch6",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch7 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch7,channelSettings,
    (gslc_tsRect){245,35,30,20},(char*)"ch7",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch8 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch8,channelSettings,
    (gslc_tsRect){285,35,30,20},(char*)"ch8",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch9 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch9,channelSettings,
    (gslc_tsRect){5,75,30,20},(char*)"ch9",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch10 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch10,channelSettings,
    (gslc_tsRect){45,75,30,20},(char*)"ch10",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch11 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch11,channelSettings,
    (gslc_tsRect){85,75,30,20},(char*)"ch11",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch12 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch12,channelSettings,
    (gslc_tsRect){125,75,30,20},(char*)"ch12",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch13 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch13,channelSettings,
    (gslc_tsRect){165,75,30,20},(char*)"ch13",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch14 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch14,channelSettings,
    (gslc_tsRect){205,75,30,20},(char*)"ch14",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch15 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch15,channelSettings,
    (gslc_tsRect){245,75,30,20},(char*)"ch15",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch16 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch16,channelSettings,
    (gslc_tsRect){285,75,30,20},(char*)"ch16",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch17 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch17,channelSettings,
    (gslc_tsRect){5,115,30,20},(char*)"ch17",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch18 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch18,channelSettings,
    (gslc_tsRect){45,115,30,20},(char*)"ch18",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch19 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch19,channelSettings,
    (gslc_tsRect){85,115,30,20},(char*)"ch19",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch20 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch20,channelSettings,
    (gslc_tsRect){125,115,30,20},(char*)"ch20",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch21 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch21,channelSettings,
    (gslc_tsRect){165,115,30,20},(char*)"ch21",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch22 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch22,channelSettings,
    (gslc_tsRect){205,115,30,20},(char*)"ch22",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch23 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch23,channelSettings,
    (gslc_tsRect){245,115,30,20},(char*)"ch23",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create setch24 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,setch24,channelSettings,
    (gslc_tsRect){285,115,30,20},(char*)"ch24",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create backbtnchs button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,backbtnchs,channelSettings,
    (gslc_tsRect){10,180,100,40},(char*)"Back",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create backbtnchsandsendstorx button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,backbtnchsandsendstorx,channelSettings,
    (gslc_tsRect){110,180,200,40},(char*)"Back and send settings",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);

  // -----------------------------------
  // PAGE: transmittingSettings
  
  // Create E_ELEM_TEXT745 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT745,transmittingSettings,(gslc_tsRect){90,70,111,11},
    (char*)"Transmitting settings",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT746 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT746,transmittingSettings,(gslc_tsRect){60,90,158,11},
    (char*)"Please wait for it to complete",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create settingstxtorxprogress text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,settingstxtorxprogress,transmittingSettings,(gslc_tsRect){60,110,154,11},
    (char*)"Currently at packet ??? of ???",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);

  // -----------------------------------
  // PAGE: setupChannel
  
  // Create channelname text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,channelname,setupChannel,(gslc_tsRect){140,20,28,11},
    (char*)"ch???",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT312 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT312,setupChannel,(gslc_tsRect){120,45,29,11},
    (char*)"RCval",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create channelval text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,channelval,setupChannel,(gslc_tsRect){160,45,23,11},
    (char*)"0000",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create reversetxt text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,reversetxt,setupChannel,(gslc_tsRect){197,170,38,11},
    (char*)"reverse",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button reverse
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,reverse,setupChannel,&m_asXToggle100,
    (gslc_tsRect){240,165,35,20},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pReverse = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, true);
  
  // Create E_ELEM_TEXT797 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT797,setupChannel,(gslc_tsRect){160,195,75,11},
    (char*)"Centered stick",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button centeredStick
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,centeredStick,setupChannel,&m_asXToggle101,
    (gslc_tsRect){240,190,35,20},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pCenteredstick = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, true);
  
  // create detectIO1 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,detectIO1,setupChannel,
    (gslc_tsRect){220,80,80,20},(char*)"Detect IO",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create detectIO2 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,detectIO2,setupChannel,
    (gslc_tsRect){220,110,80,20},(char*)"Detect IO",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create E_ELEM_TEXT305 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT305,setupChannel,(gslc_tsRect){160,85,19,11},
    (char*)"IO1",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create configuredIO1 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,configuredIO1,setupChannel,(gslc_tsRect){190,85,24,11},
    (char*)"NONE",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT307 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT307,setupChannel,(gslc_tsRect){160,115,19,11},
    (char*)"IO2",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create configuredIO2 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,configuredIO2,setupChannel,(gslc_tsRect){190,115,24,11},
    (char*)"NONE",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT309 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT309,setupChannel,(gslc_tsRect){140,143,71,11},
    (char*)"Default value",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create defaultval numeric input field
  static char m_sInputNumber25[7] = "";
  pElemRef = gslc_ElemCreateTxt(&m_gui,defaultval,setupChannel,(gslc_tsRect){230,138,40,20},
    (char*)m_sInputNumber25,7,E_FREEMONO9PT);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,0);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  m_pDefaultval = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, true);
  
  // create savebtnchconf button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,savebtnchconf,setupChannel,
    (gslc_tsRect){80,210,150,20},(char*)"Save channel config",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create backbtnchconf button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,backbtnchconf,setupChannel,
    (gslc_tsRect){10,210,40,20},(char*)"Back",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
   
  // Create listbox
  pElemRef = gslc_ElemXListboxCreate(&m_gui,lsbChannelOutputType,setupChannel,&m_sListbox3,
    (gslc_tsRect){0,70,130,100},E_FREEMONO9PT,
    (uint8_t*)&m_acListboxBuf3,sizeof(m_acListboxBuf3),0);
  gslc_ElemXListboxSetSize(&m_gui, pElemRef, 5, 1); // 5 rows, 1 columns
  gslc_ElemXListboxItemsSetSize(&m_gui, pElemRef, XLISTBOX_SIZE_AUTO, XLISTBOX_SIZE_AUTO);
  gslc_ElemSetTxtMarginXY(&m_gui, pElemRef, 5, 0);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE,GSLC_COL_BLACK,GSLC_COL_BLACK);
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
    (gslc_tsRect){10,180,120,20},(char*)"Setup output type",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);

  // -----------------------------------
  // PAGE: setupOutputPWM
  
  // Create E_ELEM_TEXT674 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT674,setupOutputPWM,(gslc_tsRect){100,20,98,11},
    (char*)"Setup PWM Paramters",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT667 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT667,setupOutputPWM,(gslc_tsRect){86,65,69,11},
    (char*)"PWM Frequency",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create pwmFreq numeric input field
  static char m_sInputNumber26[7] = "";
  pElemRef = gslc_ElemCreateTxt(&m_gui,pwmFreq,setupOutputPWM,(gslc_tsRect){160,60,40,20},
    (char*)m_sInputNumber26,7,E_FREEMONO9PT);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,0);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  m_pPwmfreq = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, true);
  
  // create backbtnsetupPWM button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,backbtnsetupPWM,setupOutputPWM,
    (gslc_tsRect){10,210,40,20},(char*)"Back",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);

  // -----------------------------------
  // PAGE: setupOutputStepper
  
  // Create E_ELEM_TEXT675 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT675,setupOutputStepper,(gslc_tsRect){100,20,118,11},
    (char*)"Setup Stepper Paramters",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create E_ELEM_TEXT669 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT669,setupOutputStepper,(gslc_tsRect){85,65,70,11},
    (char*)"Min frequency",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create stepMinFreq numeric input field
  static char m_sInputNumber27[7] = "";
  pElemRef = gslc_ElemCreateTxt(&m_gui,stepMinFreq,setupOutputStepper,(gslc_tsRect){160,60,40,20},
    (char*)m_sInputNumber27,7,E_FREEMONO9PT);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,0);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  m_pStepminfreq = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, true);
  
  // Create E_ELEM_TEXT670 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT670,setupOutputStepper,(gslc_tsRect){86,95,69,11},
    (char*)"Max frequency",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create stepMaxFreq numeric input field
  static char m_sInputNumber28[7] = "";
  pElemRef = gslc_ElemCreateTxt(&m_gui,stepMaxFreq,setupOutputStepper,(gslc_tsRect){160,90,40,20},
    (char*)m_sInputNumber28,7,E_FREEMONO9PT);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,0);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  m_pStepmaxfreq = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, true);
  
  // create backbtnsetupStepper button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,backbtnsetupStepper,setupOutputStepper,
    (gslc_tsRect){10,210,40,20},(char*)"Back",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);

  // -----------------------------------
  // PAGE: setupOutputNotNeeded
  
  // Create E_ELEM_TEXT676 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT676,setupOutputNotNeeded,(gslc_tsRect){100,110,84,11},
    (char*)"Setup not needed",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // create backbtnsetupNotNeeded button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,backbtnsetupNotNeeded,setupOutputNotNeeded,
    (gslc_tsRect){10,210,40,20},(char*)"Back",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);

  // -----------------------------------
  // PAGE: setModel
  
  // Create txt_ch1 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,txt_ch1,setModel,(gslc_tsRect){11,42,18,11},
    (char*)"ch1",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button sm0
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,sm0,setModel,&m_asXToggle118,
    (gslc_tsRect){5,10,30,30},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pSm0 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create txt_ch2 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,txt_ch2,setModel,(gslc_tsRect){41,42,18,11},
    (char*)"ch2",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button sm1
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,sm1,setModel,&m_asXToggle119,
    (gslc_tsRect){35,10,30,30},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pSm1 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create txt_ch3 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,txt_ch3,setModel,(gslc_tsRect){71,42,18,11},
    (char*)"ch3",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button sm2
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,sm2,setModel,&m_asXToggle120,
    (gslc_tsRect){65,10,30,30},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pSm2 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create txt_ch4 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,txt_ch4,setModel,(gslc_tsRect){101,42,18,11},
    (char*)"ch4",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button sm3
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,sm3,setModel,&m_asXToggle121,
    (gslc_tsRect){95,10,30,30},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pSm3 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create txt_ch5 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,txt_ch5,setModel,(gslc_tsRect){131,42,18,11},
    (char*)"ch5",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button sm4
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,sm4,setModel,&m_asXToggle122,
    (gslc_tsRect){125,10,30,30},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pSm4 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create txt_ch6 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,txt_ch6,setModel,(gslc_tsRect){161,42,18,11},
    (char*)"ch6",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button sm5
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,sm5,setModel,&m_asXToggle123,
    (gslc_tsRect){155,10,30,30},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pSm5 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create txt_ch7 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,txt_ch7,setModel,(gslc_tsRect){191,42,18,11},
    (char*)"ch7",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button sm6
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,sm6,setModel,&m_asXToggle124,
    (gslc_tsRect){185,10,30,30},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pSm6 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // Create txt_ch8 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,txt_ch8,setModel,(gslc_tsRect){221,42,18,11},
    (char*)"ch8",0,E_FREEMONO9PT);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, false, false, false, false);
  
  // Create toggle button sm7
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,sm7,setModel,&m_asXToggle125,
    (gslc_tsRect){215,10,30,30},GSLC_COL_GRAY,GSLC_COL_BLUE_DK1,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_pSm7 = pElemRef;
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);
  
  // create E_ELEM_BTN65 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN65,setModel,
    (gslc_tsRect){100,150,60,20},(char*)"Back",0,E_FREEMONO9PT,&CbBtnCommon);
  gslc_ElemSetHmiEvents(&m_gui,pElemRef, true, false, false, false);

  // -----------------------------------
  // PAGE: E_POP_KEYPAD_NUM
  static gslc_tsXKeyPadCfg_Num sCfg;
  sCfg = gslc_ElemXKeyPadCfgInit_Num();
  gslc_ElemXKeyPadCfgSetFloatEn_Num(&sCfg, true);
  gslc_ElemXKeyPadCfgSetSignEn_Num(&sCfg, true);
  m_pElemKeyPadNum = gslc_ElemXKeyPadCreate_Num(&m_gui, E_ELEM_KEYPAD_NUM, E_POP_KEYPAD_NUM,
    &m_sKeyPadNum, 65, 80, E_FREEMONO9PT, &sCfg);
  gslc_ElemXKeyPadValSetCb(&m_gui, m_pElemKeyPadNum, &CbKeypad);
//<InitGUI !End!>

  return true;
}

int main( int argc, char* args[] )
{
  bool              bOk = true;
  char              acTxt[MAX_STR];
  char serialPortname[20];
  if(argc == 1){
    printf("ERROR: Need at least 2 argument\n");
    exit(1);
  }
  else{
    strcpy(serialPortname, args[1]);
    printf("Using port %s\n", serialPortname);
  }
  // ------------------------------------------------
  // Initialize
  // ------------------------------------------------
  gslc_InitDebug(&DebugOut);
  HmiInit(serialPortname);
  gslc_InitHmi(&HmiOut, &HmiIn);
  UserInitEnv();
  
  if (!gslc_Init(&m_gui,&m_drv,m_asPage,MAX_PAGE,m_asFont,MAX_FONT)) { exit(1); }
  
  // ------------------------------------------------
  // Load Fonts
  // ------------------------------------------------
//<Load_Fonts !Start!>
  bOk = gslc_FontSet(&m_gui,E_FREEMONO9PT,GSLC_FONTREF_FNAME,FONT_FREE_MONO9,9);
  if (!bOk) { fprintf(stderr,"ERROR: FontAdd failed: %s\n",FONT_FREE_MONO9); exit(1); }
//<Load_Fonts !End!>

  // ------------------------------------------------
  // Create graphic elements
  // ------------------------------------------------
  InitGUI(dirname(args[0])); // Pass executable path to find resource files

  // ------------------------------------------------
  // Start up display on main page
  // ------------------------------------------------
//<Startup !Start!>
//<Startup !End!>

  // ------------------------------------------------
  // Main event loop
  // ------------------------------------------------

  m_bQuit = false;
  while (!m_bQuit) {

    // ----------------------------------------------
    // Update GUI Elements
    // ----------------------------------------------
    
    //TODO - Add update code for any text, gauges, or sliders
  
    // ----------------------------------------------
    // Periodically call GUIslice update function
    // ----------------------------------------------
    gslc_Update(&m_gui);

  } // bQuit

  // ------------------------------------------------
  // Close down display
  // ------------------------------------------------

  gslc_Quit(&m_gui);

  return 0;
}

