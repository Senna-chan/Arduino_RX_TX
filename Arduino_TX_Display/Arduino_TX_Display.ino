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
gslc_tsElemRef* m_pElemSlider2    = NULL;
gslc_tsElemRef* m_pElemToggle1    = NULL;
gslc_tsElemRef* m_pElemToggle10   = NULL;
gslc_tsElemRef* m_pElemToggle11   = NULL;
gslc_tsElemRef* m_pElemToggle12   = NULL;
gslc_tsElemRef* m_pElemToggle13   = NULL;
gslc_tsElemRef* m_pElemToggle14   = NULL;
gslc_tsElemRef* m_pElemToggle15   = NULL;
gslc_tsElemRef* m_pElemToggle16   = NULL;
gslc_tsElemRef* m_pElemToggle17   = NULL;
gslc_tsElemRef* m_pElemToggle18   = NULL;
gslc_tsElemRef* m_pElemToggle19   = NULL;
gslc_tsElemRef* m_pElemToggle2    = NULL;
gslc_tsElemRef* m_pElemToggle20   = NULL;
gslc_tsElemRef* m_pElemToggle21   = NULL;
gslc_tsElemRef* m_pElemToggle22   = NULL;
gslc_tsElemRef* m_pElemToggle23   = NULL;
gslc_tsElemRef* m_pElemToggle24   = NULL;
gslc_tsElemRef* m_pElemToggle3    = NULL;
gslc_tsElemRef* m_pElemToggle33   = NULL;
gslc_tsElemRef* m_pElemToggle34   = NULL;
gslc_tsElemRef* m_pElemToggle35   = NULL;
gslc_tsElemRef* m_pElemToggle36   = NULL;
gslc_tsElemRef* m_pElemToggle37   = NULL;
gslc_tsElemRef* m_pElemToggle38   = NULL;
gslc_tsElemRef* m_pElemToggle39   = NULL;
gslc_tsElemRef* m_pElemToggle4    = NULL;
gslc_tsElemRef* m_pElemToggle40   = NULL;
gslc_tsElemRef* m_pElemToggle5    = NULL;
gslc_tsElemRef* m_pElemToggle6    = NULL;
gslc_tsElemRef* m_pElemToggle7    = NULL;
gslc_tsElemRef* m_pElemToggle8    = NULL;
gslc_tsElemRef* m_pElemToggle9    = NULL;
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
      case b5:
        break;
      case b4:
        break;
      case rev0:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pElemToggle1)) {
          ;
        }
        break;
      case rev1:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pElemToggle2)) {
          ;
        }
        break;
      case rev2:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pElemToggle3)) {
          ;
        }
        break;
      case rev3:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pElemToggle4)) {
          ;
        }
        break;
      case rev4:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pElemToggle5)) {
          ;
        }
        break;
      case rev5:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pElemToggle6)) {
          ;
        }
        break;
      case rev6:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pElemToggle7)) {
          ;
        }
        break;
      case rev7:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pElemToggle8)) {
          ;
        }
        break;
      case rev8:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pElemToggle9)) {
          ;
        }
        break;
      case rev9:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pElemToggle10)) {
          ;
        }
        break;
      case rev10:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pElemToggle11)) {
          ;
        }
        break;
      case rev11:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pElemToggle12)) {
          ;
        }
        break;
      case rev12:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pElemToggle13)) {
          ;
        }
        break;
      case rev13:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pElemToggle14)) {
          ;
        }
        break;
      case rev14:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pElemToggle15)) {
          ;
        }
        break;
      case rev15:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pElemToggle16)) {
          ;
        }
        break;
      case rev16:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pElemToggle17)) {
          ;
        }
        break;
      case rev17:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pElemToggle18)) {
          ;
        }
        break;
      case rev18:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pElemToggle19)) {
          ;
        }
        break;
      case rev19:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pElemToggle20)) {
          ;
        }
        break;
      case rev20:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pElemToggle21)) {
          ;
        }
        break;
      case rev21:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pElemToggle22)) {
          ;
        }
        break;
      case rev22:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pElemToggle23)) {
          ;
        }
        break;
      case rev23:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pElemToggle24)) {
          ;
        }
        break;
      case saveButton1:
        break;
      case b6:
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
      case saveButton0:
        break;
      case m0:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pElemToggle33)) {
          ;
        }
        break;
      case m11:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pElemToggle34)) {
          ;
        }
        break;
      case m12:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pElemToggle35)) {
          ;
        }
        break;
      case m13:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pElemToggle36)) {
          ;
        }
        break;
      case m14:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pElemToggle37)) {
          ;
        }
        break;
      case m15:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pElemToggle38)) {
          ;
        }
        break;
      case m16:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pElemToggle39)) {
          ;
        }
        break;
      case m17:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pElemToggle40)) {
          ;
        }
        break;
      case E_ELEM_BTN65:
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
//<Keypad Callback !Start!>
//<Keypad Callback !End!>
//<Spinner Callback !Start!>
//<Spinner Callback !End!>
//<Listbox Callback !Start!>
//<Listbox Callback !End!>
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
      nVal = gslc_ElemXSliderGetPos(pGui,m_pElemSlider2);
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

