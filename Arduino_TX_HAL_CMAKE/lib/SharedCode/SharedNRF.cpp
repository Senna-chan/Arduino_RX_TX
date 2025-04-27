#include "Config.h"

#include <nrf24.hpp>
#include <stdio.h>

#include "SharedNRF.h"

nRF24 Main_nRF;

void common_nRFInit(bool isTransmitter) {
    Main_nRF.CE_L();
    HAL_Delay(5);
    if (!Main_nRF.Check()) {
        printf("NRF Module not found");
        Error_Handler();
    }

    Main_nRF.Init();

    // Set RF channel
    Main_nRF.SetRFChannel(40);

    // Set data rate
    Main_nRF.SetDataRate(nRF24::DataRate::DR_1Mbps);

    // Set CRC scheme
    Main_nRF.SetCRCScheme(nRF24::CRCScheme::CRC_2byte);

    // Set address width, its common for all pipes (RX and TX)
    Main_nRF.SetAddrWidth(3);

    // Configure RX PIPE
    if (!isTransmitter) {
        Main_nRF.SetAddr(nRF24::Addresses::PIPE0, nrfAddress); 	// Set RX Pipe
    }
    else {
        Main_nRF.SetAddr(nRF24::Addresses::PIPE0, nrfAddress); 	// Set RX Pipe
        Main_nRF.SetAddr(nRF24::Addresses::PIPETX, nrfAddress);   // Set TX Pipe
        Main_nRF.SetAutoRetr(nRF24::RetransmitDelay::ARD_250us, 10);
    }
    Main_nRF.SetRXPipe(nRF24::Addresses::PIPE0, Main_nRF.AA_ON, 32); // Auto-ACK: enabled, payload length: 32 bytes

    // Set TX power
    Main_nRF.SetTXPower(nRF24::TXPower::TXPWR_0dBm);

    // Enable DPL
    Main_nRF.SetDynamicPayloadLength(nRF24::DynamicPayload::ON);

    Main_nRF.SetPayloadWithAck(nRF24::AutoAck::AA_ON);


    // Enable Auto-ACK for pipe#0 (for ACK packets)
    Main_nRF.EnableAA(nRF24::Addresses::PIPE0);

    if (!isTransmitter) {
        // Set operational mode (PRX == receiver)
        Main_nRF.SetOperationalMode(nRF24::TranceiverMode::RX);
    }
    else {
        Main_nRF.SetAutoRetr(nRF24::RetransmitDelay::ARD_250us, 3);


        Main_nRF.SetOperationalMode(nRF24::TranceiverMode::RX);
    }
    // Clear any pending IRQ flags
    Main_nRF.ClearIRQFlags();

    // Wake the transceiver
    Main_nRF.SetPowerMode(nRF24::PowerControl::PWR_UP);


    //Main_nRF.DumpConfig();
    if (!isTransmitter) {
        // Put the transceiver to the RX mode
        Main_nRF.CE_H();
    }
}
