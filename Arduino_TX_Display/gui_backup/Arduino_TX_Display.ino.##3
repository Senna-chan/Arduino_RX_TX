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
      case BTN_START:
        gslc_SetPageCur(&m_gui, E_PG2);
        break;
      case BTN_SETUP_MINMAX:
        gslc_SetPageCur(&m_gui, E_PG2);
        break;
      case BTN_CH_MAPPING:
        break;
      case E_ELEM_BTN4:
        break;
      case E_ELEM_BTN5:
        break;
      case E_ELEM_BTN6:
        break;
      case E_ELEM_BTN7:
        break;
      case E_ELEM_BTN8:
        break;
      case E_ELEM_BTN9:
        break;
      case E_ELEM_BTN10:
        break;
      case E_ELEM_BTN11:
        break;
      case E_ELEM_BTN12:
        break;
      case E_ELEM_BTN13:
        break;
      case E_ELEM_BTN14:
        break;
      case E_ELEM_BTN15:
        break;
      case E_ELEM_BTN16:
        break;
      case E_ELEM_BTN17:
        break;
      case E_ELEM_BTN18:
        break;
      case E_ELEM_BTN19:
        break;
      case E_ELEM_BTN20:
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
//<Slider Callback !Start!>
//<Slider Callback !End!>
//<Tick Callback !Start!>
//<Tick Callback !End!>

void setup()
{
  // ------------------------------------------------
  // Initialize
  // ------------------------------------------------
  Serial.begin(9600);
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

