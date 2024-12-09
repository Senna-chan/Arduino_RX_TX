//<App !Start!>
// FILE: [Arduino_TX_Display.ino]
// Created by GUIslice Builder version: [0.16.b006]
//
// GUIslice Builder Generated File
//
// For the latest guides, updates and support view:
// https://github.com/ImpulseAdventure/GUIslice
//
//<App !End!>

// ------------------------------------------------
// Headers to include
// ------------------------------------------------
#include "Arduino_TX_Display_GSLC.h"


//<HMI ReadWrite Functions !Start!>
HardwareSerial HMI_SERIAL(PC11, PC10);
static int16_t HmiOut(char ch)
{
  HMI_SERIAL.write(ch);
  return 0;
}
static int16_t HmiIn()
{
  return HMI_SERIAL.read();
}
//<HMI ReadWrite Functions !End!>

// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Save some element references for direct access
//<Save_References !Start!>
gslc_tsElemRef* m_pElemSlider4    = NULL;
gslc_tsElemRef* m_pElemToggle52   = NULL;
gslc_tsElemRef* m_pElemToggle53   = NULL;
gslc_tsElemRef* m_pElemToggle54   = NULL;
gslc_tsElemRef* m_pElemToggle55   = NULL;
gslc_tsElemRef* m_pElemToggle56   = NULL;
gslc_tsElemRef* m_pElemToggle57   = NULL;
gslc_tsElemRef* m_pElemToggle58   = NULL;
gslc_tsElemRef* m_pElemToggle59   = NULL;
gslc_tsElemRef* m_pElemToggle60   = NULL;
gslc_tsElemRef* m_pElemVal4       = NULL;
gslc_tsElemRef* m_pElemKeyPadNum  = NULL;
//<Save_References !End!>

// Define debug message function
static int16_t DebugOut(char ch) { if (ch == (char)'\n') Serial.println(""); else Serial.write(ch); return 0; }

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
      case b0:
        break;
      case b1:
        break;
      case b2:
        break;
      case b3:
        break;
      case b4:
        break;
      case l1:
        break;
      case m1:
        break;
      case h1:
        break;
      case l2:
        break;
      case m2:
        break;
      case h2:
        break;
      case l3:
        break;
      case m3:
        break;
      case h3:
        break;
      case l4:
        break;
      case m4:
        break;
      case h4:
        break;
      case l5:
        break;
      case m5:
        break;
      case h5:
        break;
      case l6:
        break;
      case m6:
        break;
      case h6:
        break;
      case l7:
        break;
      case m7:
        break;
      case h7:
        break;
      case l8:
        break;
      case m8:
        break;
      case h8:
        break;
      case l9:
        break;
      case m9:
        break;
      case h9:
        break;
      case l10:
        break;
      case m10:
        break;
      case h10:
        break;
      case backbtncal:
        break;
      case savebtncal:
        break;
      case drbackbtn:
        break;
      case b5:
        break;
      case setch1:
        break;
      case setch2:
        break;
      case setch3:
        break;
      case setch4:
        break;
      case setch5:
        break;
      case setch6:
        break;
      case setch7:
        break;
      case setch8:
        break;
      case setch9:
        break;
      case setch10:
        break;
      case setch11:
        break;
      case setch12:
        break;
      case setch13:
        break;
      case setch14:
        break;
      case setch15:
        break;
      case setch16:
        break;
      case setch17:
        break;
      case setch18:
        break;
      case setch19:
        break;
      case setch20:
        break;
      case setch21:
        break;
      case setch22:
        break;
      case setch23:
        break;
      case setch24:
        break;
      case backbtnchs:
        break;
      case reverse:
        // TODO Add code for Toggle button ON/OFF state
        break;
      case detectIO1:
        break;
      case detectIO2:
        break;
      case defaultval:
        // Clicked on edit field, so show popup box and associate with this text field
        gslc_ElemXKeyPadInputAsk(&m_gui, m_pElemKeyPadNum, E_POP_KEYPAD_NUM, m_pElemVal4);
        break;
      case savebtnchconf:
        break;
      case backbtnchconf:
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
        gslc_ElemXKeyPadInputGet(pGui, m_pElemVal4, pvData);
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
  gslc_tsGui*     pGui     = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem*    pElem    = gslc_GetElemFromRef(pGui,pElemRef);
  int16_t         nVal;

  // From the element's ID we can determine which slider was updated.
  switch (pElem->nId) {
//<Slider Enums !Start!>
    case deadzone0:
      // Fetch the slider position
      nVal = gslc_ElemXSliderGetPos(pGui,m_pElemSlider4);
      break;

//<Slider Enums !End!>
    default:
      break;
  }

  return true;
}
//<Tick Callback !Start!>
//<Tick Callback !End!>

void setup()
{
  // ------------------------------------------------
  // Initialize
  // ------------------------------------------------
  Serial.begin(115200);
  // Wait for USB Serial 
  //delay(1000);  // NOTE: Some devices require a delay after Serial.begin() before serial port can be used

  gslc_InitDebug(&DebugOut);


//<HMI Setup Functions !Start!>
  HMI_SERIAL.begin(115200);
  gslc_InitHmi(&HmiOut, &HmiIn);
//<HMI Setup Functions !End!>
  // ------------------------------------------------
  // Create graphic elements
  // ------------------------------------------------
  InitGUIslice_gen();

}

// -----------------------------------
// Main event loop
// -----------------------------------
void loop()
{

  // ------------------------------------------------
  // Update GUI Elements
  // ------------------------------------------------
  
  //TODO - Add update code for any text, gauges, or sliders
  
  // ------------------------------------------------
  // Periodically call GUIslice update function
  // ------------------------------------------------
  gslc_Update(&m_gui);
    
}

