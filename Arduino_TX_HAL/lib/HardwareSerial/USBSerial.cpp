//
// Created by senyaa on 4/22/25.
//

#include "USBSerial.h"

void USBSerial::create(uint8_t cdc_num){

}

void USBSerial::init(){

}
void USBSerial::waitForNewData(){

}
USBSerial* USBSerial::getInstance(uint8_t cdc_num){
    if(cdc_num > NUMBER_OF_CDC){
        Error_Handler();
    }
    return &usbSerial[cdc_num];
}
// These functions are not for user use
void USBSerial::handleISR(EventType eventType, uint16_t pos){

}