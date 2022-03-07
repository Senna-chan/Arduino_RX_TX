/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 
 Update 2014 - TMRh20
 */

/**
 * Example of using interrupts
 *
 * This is an example of how to user interrupts to interact with the radio, and a demonstration
 * of how to use them to sleep when receiving, and not miss any payloads. 
 * The pingpair_sleepy example expands on sleep functionality with a timed sleep option for the transmitter.
 * Sleep functionality is built directly into my fork of the RF24Network library
 */

#include <SPI.h>
#include "config.h"
                                        
const short role_pin = 5;                 // sets the role of this unit in hardware.  Connect to GND to be the 'pong' receiver
                                          // Leave open to be the 'ping' transmitter


// Role management

// Set up role.  This sketch uses the same software for all the nodes in this
// system.  Doing so greatly simplifies testing.  The hardware itself specifies
// which node it is.
// This is done through the role_pin
typedef enum { role_sender = 1, role_receiver } role_e;                 // The various roles supported by this sketch
const char* role_friendly_name[] = { "invalid", "Sender", "Receiver"};  // The debug-friendly names of those roles
role_e role = role_sender;                                                            // The role of the current running sketch

static uint32_t message_count = 0;

/********************** Setup *********************/

void setup(){

  Serial.begin(115200);
  Serial.print(F("\n\rRF24/examples/pingpair_irq\n\rROLE: "));
  Serial.println(role_friendly_name[role]);
  SPI.setMISO(RF24MISO);
  SPI.setMOSI(RF24MOSI);
  SPI.setSCLK(RF24SCK);
  SPI.setSSEL(RF24CS);
  Serial.printf("NRFPinConfig: MOSI 0x%02X, MISO 0x%02X, SCLK 0x%02X, CSN 0x%02X, CE 0x%02X, IRQ 0x%02X\n", digitalPinToPinName(RF24MOSI), digitalPinToPinName(RF24MISO), digitalPinToPinName(RF24SCK), digitalPinToPinName(RF24CS), digitalPinToPinName(RF24CE), digitalPinToPinName(RF24INT));

  // Setup and configure rf radio
  common_nRFInit();
                                                    // Open pipes to other node for communication
  if ( role == role_sender ) {                      // This simple sketch opens a pipe on a single address for these two nodes to 
     radio.openWritingPipe(nrfAddress[0]);             // communicate back and forth.  One listens on it, the other talks to it.
     radio.openReadingPipe(1, nrfAddress[1]);
  }else{
    radio.openWritingPipe(nrfAddress[1]);
    radio.openReadingPipe(1, nrfAddress[0]);
    radio.startListening();
    radio.writeAckPayload( 1, &message_count, sizeof(message_count) );  // Add an ack packet for the next time around.  This is a simple
    ++message_count;        
  }
  radio.printDetails();                             // Dump the configuration of the rf unit for debugging
  delay(20);
  uint8_t channel = radio.getChannel();
  Serial.printf("Read channel %d\n", channel);
  delay(50);
  attachInterrupt(RF24INT, check_radio, LOW);             // Attach interrupt handler to interrupt #0 (using pin 2) on BOTH the sender and receiver
}



/********************** Main Loop *********************/
void loop() {


  if (role == role_sender)  {                        // Sender role.  Repeatedly send the current time 
    unsigned long time = millis();                   // Take the time, and send it.
      Serial.print(F("Now sending "));
      Serial.println(time);
    radio.startWrite( &time, sizeof(unsigned long) ,0);
    delay(2000);                                     // Try again soon
  }


  if(role == role_receiver){                        // Receiver does nothing except in IRQ
  }  
}


/********************** Interrupt *********************/

void check_radio(void)                                // Receiver role: Does nothing!  All the work is in IRQ
{
  
  bool tx,fail,rx;
  radio.whatHappened(tx,fail,rx);                     // What happened?
  
  if ( tx ) {                                         // Have we successfully transmitted?
      if ( role == role_sender ){   Serial.println(F("Send:OK")); }
      if ( role == role_receiver ){ Serial.println(F("Ack Payload:Sent")); }
  }
  
  if ( fail ) {                                       // Have we failed to transmit?
      if ( role == role_sender ){   Serial.println(F("Send:Failed"));  }
      if ( role == role_receiver ){ Serial.println(F("Ack Payload:Failed"));  }
  }
  
  if ( rx || radio.available()){                      // Did we receive a message?
    
    if ( role == role_sender ) {                      // If we're the sender, we've received an ack payload
        radio.read(&message_count,sizeof(message_count));
        Serial.print(F("Ack: "));
        Serial.println(message_count);
    }
    
    if ( role == role_receiver ) {                    // If we're the receiver, we've received a time message
      static unsigned long got_time;                  // Get this payload and dump it
      radio.read( &got_time, sizeof(got_time) );
      Serial.print(F("Got payload "));
      Serial.println(got_time);
      radio.writeAckPayload( 1, &message_count, sizeof(message_count) );  // Add an ack packet for the next time around.  This is a simple
      ++message_count;                                // packet counter
    }
  }
}
