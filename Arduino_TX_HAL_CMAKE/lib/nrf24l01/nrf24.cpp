// Functions to manage the nRF24L01+ transceiver

#include <stdarg.h>
#include <stdio.h>

#include "nrf24.hpp"


uint8_t nRF24::LL_RW(uint8_t data) {
    // Wait until TX buffer is empty
    uint8_t result;
    HAL_StatusTypeDef hal_result = HAL_SPI_TransmitReceive(_hspi, &data, &result, 1, 2000);
    int count = 0;
    while(hal_result != HAL_OK && ++count < 30) {
        HAL_Delay(50);
        hal_result = HAL_SPI_TransmitReceive(_hspi, &data, &result, 1, 2000);
    };
    return result;
}

void nRF24::debug_printf(const char* fmt, ...){
    if(_uart == nullptr) return;
    va_list args;
    va_start(args, fmt);
    char buf[255];
    vsnprintf(buf, 255, fmt, args);
    HAL_UART_Transmit(_uart, (uint8_t *)buf, 255, 50);
    va_end(args);
    HAL_Delay(100);
}

void nRF24::CE_L() {
    HAL_GPIO_WritePin(_cePort, _cePin, GPIO_PIN_RESET);
}

void nRF24::CE_H() {
    HAL_GPIO_WritePin(_cePort, _cePin, GPIO_PIN_SET);
}

void nRF24::CSN_L() {
    HAL_GPIO_WritePin(_csnPort, _csnPin, GPIO_PIN_RESET);
}

void nRF24::CSN_H() {
    HAL_GPIO_WritePin(_csnPort, _csnPin, GPIO_PIN_SET);
}


void nRF24::SetCEPin(GPIO_TypeDef *gpio, uint16_t pin){
    _cePort = gpio;
    _cePin = pin;
}
void nRF24::SetCSNPin(GPIO_TypeDef *gpio, uint16_t pin){
    _csnPort = gpio;
    _csnPin = pin;
}
void nRF24::SetSPI(SPI_HandleTypeDef *hspi){
    _hspi = hspi;
}

// Read a register
// input:
//   reg - number of register to read
// return: value of register
uint8_t nRF24::ReadReg(uint8_t reg) {
    uint8_t value;

    CSN_L();
    LL_RW(reg & RegisterMasks::REG_MAP);
    value = LL_RW(Instructions::NOP);
    CSN_H();

    return value;
}

// Write a new value to register
// input:
//   reg - number of register to write
//   value - value to write
void nRF24::WriteReg(uint8_t reg, uint8_t value) {
    CSN_L();
    if (reg < Instructions::W_REGISTER) {
        // This is a register access
        LL_RW(Instructions::W_REGISTER | (reg & RegisterMasks::REG_MAP));
        LL_RW(value);
    } else {
        // This is a single byte command or future command/register
        LL_RW(reg);
        if ((reg != Instructions::FLUSH_TX) && (reg != Instructions::FLUSH_RX) && \
                (reg != Instructions::REUSE_TX_PL) && (reg != Instructions::NOP)) {
            // Send register value
            LL_RW(value);
        }
    }
    CSN_H();
}

// Read a multi-byte register
// input:
//   reg - number of register to read
//   pBuf - pointer to the buffer for register data
//   count - number of bytes to read
void nRF24::ReadMBReg(uint8_t reg, uint8_t *pBuf, uint8_t count) {
    CSN_L();
    LL_RW(reg);
    while (count--) {
        *pBuf++ = LL_RW(Instructions::NOP);
    }
    CSN_H();
}

// Write a multi-byte register
// input:
//   reg - number of register to write
//   pBuf - pointer to the buffer with data to write
//   count - number of bytes to write
void nRF24::WriteMBReg(uint8_t reg, uint8_t *pBuf, uint8_t count) {
    CSN_L();
    LL_RW(reg);
    while (count--) {
        LL_RW(*pBuf++);
    }
    CSN_H();
}

// Set transceiver to it's initial state
// note: RX/TX pipe addresses remains untouched
void nRF24::Init(void) {
    // Write to registers their initial values
    WriteReg(Registers::CONFIG, 0x08);
    WriteReg(Registers::EN_AA, 0x3F);
    WriteReg(Registers::EN_RXADDR, 0x03);
    WriteReg(Registers::SETUP_AW, 0x03);
    WriteReg(Registers::SETUP_RETR, 0x03);
    WriteReg(Registers::RF_CH, 0x02);
    WriteReg(Registers::RF_SETUP, 0x0E);
    WriteReg(Registers::STATUS, 0x00);
    WriteReg(Registers::RX_PW_P0, 0x00);
    WriteReg(Registers::RX_PW_P1, 0x00);
    WriteReg(Registers::RX_PW_P2, 0x00);
    WriteReg(Registers::RX_PW_P3, 0x00);
    WriteReg(Registers::RX_PW_P4, 0x00);
    WriteReg(Registers::RX_PW_P5, 0x00);
    WriteReg(Registers::DYNPD, 0x00);
    WriteReg(Registers::FEATURE, 0x00);

    // Clear the FIFO's
    FlushRX();
    FlushTX();

    // Clear any pending interrupt flags
    ClearIRQFlags();

    // Deassert CSN pin (chip release)
    CSN_H();
}

// Check if the nRF24L01 present
// return:
//   1 - nRF24L01 is online and responding
//   0 - received sequence differs from original
uint8_t nRF24::Check(void) {
    uint8_t rxbuf[5];
    uint8_t i;
    uint8_t *ptr = (uint8_t *)TEST_ADDR;

    // Write test TX address and read TX_ADDR register
    WriteMBReg(Instructions::W_REGISTER | Registers::TX_ADDR, ptr, 5);
    ReadMBReg(Instructions::R_REGISTER | Registers::TX_ADDR, rxbuf, 5);

    // Compare buffers, return error on first mismatch
    for (i = 0; i < 5; i++) {
        if (rxbuf[i] != *ptr++) {
            return 0;
        }
    }

    return 1;
}

// Control transceiver power mode
// input:
//   mode - new state of power mode, one of PWR_xx values
void nRF24::SetPowerMode(PowerControl mode) {
    uint8_t reg;

    reg = ReadReg(Registers::CONFIG);
    if (mode == PowerControl::PWR_UP) {
        // Set the PWR_UP bit of CONFIG register to wake the transceiver
        // It goes into Stanby-I mode with consumption about 26uA
        reg |= RegisterBits::CONFIG_PWR_UP;
    } else {
        // Clear the PWR_UP bit of CONFIG register to put the transceiver
        // into power down mode with consumption about 900nA
        reg &= ~RegisterBits::CONFIG_PWR_UP;
    }
    WriteReg(Registers::CONFIG, reg);
}

// Set transceiver operational mode
// input:
//   mode - operational mode, one of MODE_xx values
void nRF24::SetOperationalMode(TranceiverMode mode) {
    uint8_t reg;

    // Configure PRIM_RX bit of the CONFIG register
    reg  = ReadReg(Registers::CONFIG);
    reg &= ~CONFIG_PRIM_RX;
    reg |= (mode & CONFIG_PRIM_RX);
    WriteReg(Registers::CONFIG, reg);
}

// Set transceiver DynamicPayloadLength feature for all the pipes
// input:
//   mode - status, one of DPL_xx values
void nRF24::SetDynamicPayloadLength(DynamicPayload mode) {
    uint8_t reg;
    reg  = ReadReg(FEATURE);
    if(mode) {
        WriteReg(FEATURE, reg | FEATURE_EN_DPL);
        WriteReg(DYNPD, 0x1F);
    } else {
        WriteReg(FEATURE, reg &~ FEATURE_EN_DPL);
        WriteReg(DYNPD, 0x0);
    }
}

// Enables Payload With Ack. NB Refer to the datasheet for proper retransmit timing.
// input:
//   mode - status, 1 or 0
void nRF24::SetPayloadWithAck(AutoAck mode) {
    uint8_t reg;
    reg  = ReadReg(Registers::FEATURE);
    if(mode) {
        WriteReg(Registers::FEATURE, reg | FEATURE_EN_ACK_PAY);
    } else {
        WriteReg(Registers::FEATURE, reg &~ FEATURE_EN_ACK_PAY);
    }
}

// Configure transceiver CRC scheme
// input:
//   scheme - CRC scheme, one of CRC_xx values
// note: transceiver will forcibly turn on the CRC in case if auto acknowledgment
//       enabled for at least one RX pipe
void nRF24::SetCRCScheme(CRCScheme scheme) {
    uint8_t reg;

    // Configure EN_CRC[3] and CRCO[2] bits of the CONFIG register
    reg  = ReadReg(Registers::CONFIG);
    reg &= ~RegisterMasks::CONFIG_CRC;
    reg |= (scheme & CONFIG_CRC);
    WriteReg(Registers::CONFIG, reg);
}

// Set frequency channel
// input:
//   channel - radio frequency channel, value from 0 to 127
// note: frequency will be (2400 + channel)MHz
// note: PLOS_CNT[7:4] bits of the OBSERVER_TX register will be reset
void nRF24::SetRFChannel(uint8_t channel) {
    WriteReg(Registers::RF_CH, channel);
}

// Set automatic retransmission parameters
// input:
//   ard - auto retransmit delay, one of ARD_xx values
//   arc - count of auto retransmits, value form 0 to 15
// note: zero arc value means that the automatic retransmission disabled
void nRF24::SetAutoRetr(RetransmitDelay ard, uint8_t retryCount) {
    // Set auto retransmit settings (SETUP_RETR register)
    WriteReg(Registers::SETUP_RETR, (uint8_t)((ard << 4) | (retryCount & RegisterMasks::RETR_ARC)));
}

// Set of address widths
// input:
//   addr_width - RX/TX address field width, value from 3 to 5
// note: this setting is common for all pipes
void nRF24::SetAddrWidth(uint8_t addr_width) {
    WriteReg(Registers::SETUP_AW, addr_width - 2);
}

// Set static RX address for a specified pipe
// input:
//   pipe - pipe to configure address, one of PIPEx values
//   addr - pointer to the buffer with address
// note: pipe can be a number from 0 to 5 (RX pipes) and 6 (TX pipe)
// note: buffer length must be equal to current address width of transceiver
// note: for pipes[2..5] only first byte of address will be written because
//       other bytes of address equals to pipe1
// note: for pipes[2..5] only first byte of address will be written because
//       pipes 1-5 share the four most significant address bytes
void nRF24::SetAddr(Addresses pipe, const uint8_t *addr) {
    uint8_t addr_width;

    // RX_ADDR_Px register
    switch (pipe) {
        case PIPETX:
        case PIPE0:
        case PIPE1:
            // Get address width
            addr_width = ReadReg(Registers::SETUP_AW) + 1;
            // Write address in reverse order (LSByte first)
            addr += addr_width;
            CSN_L();
            LL_RW(Instructions::W_REGISTER | ADDR_REGS[pipe]);
            do {
                LL_RW(*addr--);
            } while (addr_width--);
            CSN_H();
            break;
        case PIPE2:
        case PIPE3:
        case PIPE4:
        case PIPE5:
            // Write address LSBbyte (only first byte from the addr buffer)
            WriteReg(ADDR_REGS[pipe], *addr);
            break;
        default:
            // Incorrect pipe number -> do nothing
            break;
    }
}

// Configure RF output power in TX mode
// input:
//   tx_pwr - RF output power, one of TXPWR_xx values
void nRF24::SetTXPower(TXPower tx_pwr) {
    uint8_t reg;

    // Configure RF_PWR[2:1] bits of the RF_SETUP register
    reg  = ReadReg(Registers::RF_SETUP);
    reg &= ~RegisterMasks::RF_PWR;
    reg |= tx_pwr;
    WriteReg(Registers::RF_SETUP, reg);
}

// Configure transceiver data rate
// input:
//   data_rate - data rate, one of DR_xx values
void nRF24::SetDataRate(DataRate data_rate) {
    uint8_t reg;

    // Configure RF_DR_LOW[5] and RF_DR_HIGH[3] bits of the RF_SETUP register
    reg  = ReadReg(Registers::RF_SETUP);
    reg &= ~RegisterMasks::DATARATE;
    reg |= data_rate;
    WriteReg(Registers::RF_SETUP, reg);
}

// Configure a specified RX pipe
// input:
//   pipe - number of the RX pipe, value from 0 to 5
//   aa_state - state of auto acknowledgment, one of AA_xx values
//   payload_len - payload length in bytes
void nRF24::SetRXPipe(Addresses pipe, AutoAck aa_state, uint8_t payload_len) {
    uint8_t reg;

    // Enable the specified pipe (EN_RXADDR register)
    reg = (ReadReg(Registers::EN_RXADDR) | (1 << pipe)) & RegisterMasks::EN_RX;
    WriteReg(Registers::EN_RXADDR, reg);

    // Set RX payload length (RX_PW_Px register)
    WriteReg(RX_PW_PIPE[pipe], payload_len & RegisterMasks::RX_PW);

    // Set auto acknowledgment for a specified pipe (EN_AA register)
    reg = ReadReg(Registers::EN_AA);
    if (aa_state == AA_ON) {
        reg |=  (1 << pipe);
    } else {
        reg &= ~(1 << pipe);
    }
    WriteReg(Registers::EN_AA, reg);
}

// Disable specified RX pipe
// input:
//   PIPE - number of RX pipe, value from 0 to 5
void nRF24::ClosePipe(Addresses pipe) {
    uint8_t reg;

    reg  = ReadReg(Registers::EN_RXADDR);
    reg &= ~(1 << pipe);
    reg &= RegisterMasks::EN_RX;
    WriteReg(Registers::EN_RXADDR, reg);
}

// Enable the auto retransmit (a.k.a. enhanced ShockBurst) for the specified RX pipe
// input:
//   pipe - number of the RX pipe, value from 0 to 5
void nRF24::EnableAA(Addresses pipe) {
    uint8_t reg;

    // Set bit in EN_AA register
    reg  = ReadReg(Registers::EN_AA);
    reg |= (1 << pipe);
    WriteReg(Registers::EN_AA, reg);
}

// Disable the auto retransmit (a.k.a. enhanced ShockBurst) for one or all RX pipes
// input:
//   pipe - number of the RX pipe, value from 0 to 5, any other value will disable AA for all RX pipes
void nRF24::DisableAA(Addresses pipe) {
    uint8_t reg;

    if (pipe > 5) {
        // Disable Auto-ACK for ALL pipes
        WriteReg(Registers::EN_AA, 0x00);
    } else {
        // Clear bit in the EN_AA register
        reg  = ReadReg(Registers::EN_AA);
        reg &= ~(1 << pipe);
        WriteReg(Registers::EN_AA, reg);
    }
}

// Get value of the STATUS register
// return: value of STATUS register
uint8_t nRF24::GetStatus(void) {
    return ReadReg(Registers::STATUS);
}

// Get pending IRQ flags
// return: current status of RX_DR, TX_DS and MAX_RT bits of the STATUS register
uint8_t nRF24::GetIRQFlags(void) {
    return (ReadReg(Registers::STATUS) & RegisterMasks::STATUS_IRQ);
}

// Get status of the RX FIFO
// return: one of the STATUS_RXFIFO_xx values
uint8_t nRF24::GetStatus_RXFIFO(void) {
    return (ReadReg(Registers::FIFO_STATUS) & RegisterMasks::RXFIFO);
}

// Get status of the TX FIFO
// return: one of the STATUS_TXFIFO_xx values
// note: the TX_REUSE bit ignored
uint8_t nRF24::GetStatus_TXFIFO(void) {
    return ((ReadReg(Registers::FIFO_STATUS) & RegisterMasks::TXFIFO) >> 4);
}

// Get pipe number for the payload available for reading from RX FIFO
// return: pipe number or 0x07 if the RX FIFO is empty
uint8_t nRF24::GetRXSource(void) {
    return ((ReadReg(Registers::STATUS) & RegisterMasks::RX_P_NO) >> 1);
}

// Get auto retransmit statistic
// return: value of OBSERVE_TX register which contains two counters encoded in nibbles:
//   high - lost packets count (max value 15, can be reseted by write to RF_CH register)
//   low  - retransmitted packets LL_RW
// Flush the TX FIFO
void nRF24::FlushTX(void) {
    WriteReg(Instructions::FLUSH_TX, Instructions::NOP);
}

// Flush the RX FIFO
void nRF24::FlushRX(void) {
    WriteReg(Instructions::FLUSH_RX, Instructions::NOP);
}

// Clear any pending IRQ flags
void nRF24::ClearIRQFlags(void) {
    uint8_t reg;

    // Clear RX_DR, TX_DS and MAX_RT bits of the STATUS register
    reg  = ReadReg(Registers::STATUS);
    reg |= RegisterMasks::STATUS_IRQ;
    WriteReg(Registers::STATUS, reg);
}

// Write TX payload
// input:
//   pBuf - pointer to the buffer with payload data
//   length - payload length in bytes
void nRF24::WritePayload(uint8_t *pBuf, uint8_t length) {
    WriteMBReg(Instructions::W_TX_PAYLOAD, pBuf, length);
}

uint8_t nRF24::GetRxDplPayloadWidth() {
    uint8_t value;

    CSN_L();
    LL_RW(Instructions::R_RX_PL_WID);
    value = LL_RW(Instructions::NOP);
    CSN_H();

    return value;

}

nRF24::Addresses nRF24::ReadPayloadGeneric(uint8_t *pBuf, uint8_t *length, uint8_t dpl) {
    uint8_t pipe;

    // Extract a payload pipe number from the STATUS register
    pipe = (ReadReg(STATUS) & RegisterMasks::RX_P_NO) >> 1;

    // RX FIFO empty?
    if (pipe < 6) {
        // Get payload length
        if(dpl) {
            *length = GetRxDplPayloadWidth();
            if(*length>32) { //broken packet
                *length = 0;
                FlushRX();
            }
        } else {
            *length = ReadReg(RX_PW_PIPE[pipe]);
        }

        // Read a payload from the RX FIFO
        if (*length) {
            ReadMBReg(Instructions::R_RX_PAYLOAD, pBuf, *length);
        }

        return ((Addresses)pipe);
    }

    // The RX FIFO is empty
    *length = 0;

    return NONE;
}

// Read top level payload available in the RX FIFO
// input:
//   pBuf - pointer to the buffer to store a payload data
//   length - pointer to variable to store a payload length
// return: one of RX_xx values
//   RX_PIPEX - packet has been received from the pipe number X
//   RX_EMPTY - the RX FIFO is empty
nRF24::Addresses nRF24::ReadPayload(uint8_t *pBuf, uint8_t *length) {
    return ReadPayloadGeneric(pBuf, length,0);
}

nRF24::Addresses nRF24::ReadPayloadDpl(uint8_t *pBuf, uint8_t *length) {
    return ReadPayloadGeneric(pBuf, length,1);
}

uint8_t nRF24::GetFeatures() {
    return ReadReg(Registers::FEATURE);
}
void nRF24::ActivateFeatures() {
    CSN_L();
    LL_RW(Instructions::ACTIVATE);
    LL_RW(0x73);
    CSN_H();
}

void nRF24::WriteAckPayload(Addresses pipe, uint8_t *payload, uint8_t length) {
    CSN_L();
    LL_RW(Instructions::W_ACK_PAYLOAD | pipe);
    while (length--) {
        LL_RW(*payload++);
    }
    CSN_H();

}


// Print nRF24L01+ current configuration (for debug purposes)
void nRF24::DumpConfig(void) {
    uint8_t i,j;
    uint8_t aw;
    uint8_t buf[5];

    // Dump nRF24L01+ configuration
    // CONFIG
    i = ReadReg(Registers::CONFIG);
    debug_printf("[0x%02X] 0x%02X MASK:%03b CRC:%02b PWR:%s MODE:P%s\r\n",
        Registers::CONFIG,
            i,
            i >> 4,
            (i & 0x0c) >> 2,
            (i & 0x02) ? "ON" : "OFF",
            (i & 0x01) ? "RX" : "TX"
        );
    // EN_AA
    i = ReadReg(Registers::EN_AA);
    debug_printf("[0x%02X] 0x%02X ENAA: ",Registers::EN_AA,i);
    for (j = 0; j < 6; j++) {
        debug_printf("[P%1u%s]%s",j,
                (i & (1 << j)) ? "+" : "-",
                (j == 5) ? "\r\n" : " "
            );
    }
    // EN_RXADDR
    i = ReadReg(Registers::EN_RXADDR);
    debug_printf("[0x%02X] 0x%02X EN_RXADDR: ",Registers::EN_RXADDR,i);
    for (j = 0; j < 6; j++) {
        debug_printf("[P%1u%s]%s",j,
                (i & (1 << j)) ? "+" : "-",
                (j == 5) ? "\r\n" : " "
            );
    }
    // SETUP_AW
    i = ReadReg(Registers::SETUP_AW);
    aw = (i & 0x03) + 2;
    debug_printf("[0x%02X] 0x%02X EN_RXADDR=%06b (address width = %u)\r\n",Registers::SETUP_AW,i,i & 0x03,aw);
    // SETUP_RETR
    i = ReadReg(Registers::SETUP_RETR);
    debug_printf("[0x%02X] 0x%02X ARD=%04b ARC=%04b (retr.delay=%uus, count=%u)\r\n",
        Registers::SETUP_RETR,
            i,
            i >> 4,
            i & 0x0F,
            ((i >> 4) * 250) + 250,
            i & 0x0F
        );
    // RF_CH
    i = ReadReg(Registers::RF_CH);
    debug_printf("[0x%02X] 0x%02X (%.3uGHz)\r\n",Registers::RF_CH,i,2400 + i);
    // RF_SETUP
    i = ReadReg(Registers::RF_SETUP);
    debug_printf("[0x%02X] 0x%02X CONT_WAVE:%s PLL_LOCK:%s DataRate=",
        Registers::RF_SETUP,
            i,
            (i & 0x80) ? "ON" : "OFF",
            (i & 0x80) ? "ON" : "OFF"
        );
    switch ((i & 0x28) >> 3) {
        case 0x00:
            debug_printf("1M");
            break;
        case 0x01:
            debug_printf("2M");
            break;
        case 0x04:
            debug_printf("250k");
            break;
        default:
            debug_printf("???");
            break;
    }
    debug_printf("pbs RF_PWR=");
    switch ((i & 0x06) >> 1) {
        case 0x00:
            debug_printf("-18");
            break;
        case 0x01:
            debug_printf("-12");
            break;
        case 0x02:
            debug_printf("-6");
            break;
        case 0x03:
            debug_printf("0");
            break;
        default:
            debug_printf("???");
            break;
    }
    debug_printf("dBm\r\n");
    // STATUS
    i = ReadReg(Registers::STATUS);
    debug_printf("[0x%02X] 0x%02X IRQ:%03b RX_PIPE:%u TX_FULL:%s\r\n",
        Registers::STATUS,
            i,
            (i & 0x70) >> 4,
            (i & 0x0E) >> 1,
            (i & 0x01) ? "YES" : "NO"
        );
    // OBSERVE_TX
    i = ReadReg(Registers::OBSERVE_TX);
    debug_printf("[0x%02X] 0x%02X PLOS_CNT=%u ARC_CNT=%u\r\n",Registers::OBSERVE_TX,i,i >> 4,i & 0x0F);
    // RPD
    i = ReadReg(Registers::RPD);
    debug_printf("[0x%02X] 0x%02X RPD=%s\r\n",Registers::RPD,i,(i & 0x01) ? "YES" : "NO");
    // RX_ADDR_P0
    ReadMBReg(Registers::RX_ADDR_P0,buf,aw);
    debug_printf("[0x%02X] RX_ADDR_P0 \"",Registers::RX_ADDR_P0);
    for (i = 0; i < aw; i++) debug_printf("0x%02X ",buf[i]);
    debug_printf("\"\r\n");
    // RX_ADDR_P1
    ReadMBReg(Registers::RX_ADDR_P1,buf,aw);
    debug_printf("[0x%02X] RX_ADDR_P1 \"",Registers::RX_ADDR_P1);
    for (i = 0; i < aw; i++) debug_printf("0x%02X ",buf[i]);
    debug_printf("\"\r\n");
    // RX_ADDR_P2
    debug_printf("[0x%02X] RX_ADDR_P2 \"",Registers::RX_ADDR_P2);
    for (i = 0; i < aw - 1; i++) debug_printf("0x%02X ",buf[i]);
    i = ReadReg(Registers::RX_ADDR_P2);
    debug_printf("%c\"\r\n",i);
    // RX_ADDR_P3
    debug_printf("[0x%02X] RX_ADDR_P3 \"",Registers::RX_ADDR_P3);
    for (i = 0; i < aw - 1; i++) debug_printf("0x%02X ",buf[i]);
    i = ReadReg(Registers::RX_ADDR_P3);
    debug_printf("%c\"\r\n",i);
    // RX_ADDR_P4
    debug_printf("[0x%02X] RX_ADDR_P4 \"",Registers::RX_ADDR_P4);
    for (i = 0; i < aw - 1; i++) debug_printf("0x%02X ",buf[i]);
    i = ReadReg(Registers::RX_ADDR_P4);
    debug_printf("%c\"\r\n",i);
    // RX_ADDR_P5
    debug_printf("[0x%02X] RX_ADDR_P5 \"",Registers::RX_ADDR_P5);
    for (i = 0; i < aw - 1; i++) debug_printf("0x%02X ",buf[i]);
    i = ReadReg(Registers::RX_ADDR_P5);
    debug_printf("%c\"\r\n",i);
    // TX_ADDR
    ReadMBReg(Registers::TX_ADDR,buf,aw);
    debug_printf("[0x%02X] TX_ADDR \"",Registers::TX_ADDR);
    for (i = 0; i < aw; i++) debug_printf("0x%02X ",buf[i]);
    debug_printf("\"\r\n");
    // RX_PW_P0
    i = ReadReg(Registers::RX_PW_P0);
    debug_printf("[0x%02X] RX_PW_P0=%u\r\n",Registers::RX_PW_P0,i);
    // RX_PW_P1
    i = ReadReg(Registers::RX_PW_P1);
    debug_printf("[0x%02X] RX_PW_P1=%u\r\n",Registers::RX_PW_P1,i);
    // RX_PW_P2
    i = ReadReg(Registers::RX_PW_P2);
    debug_printf("[0x%02X] RX_PW_P2=%u\r\n",Registers::RX_PW_P2,i);
    // RX_PW_P3
    i = ReadReg(Registers::RX_PW_P3);
    debug_printf("[0x%02X] RX_PW_P3=%u\r\n",Registers::RX_PW_P3,i);
    // RX_PW_P4
    i = ReadReg(Registers::RX_PW_P4);
    debug_printf("[0x%02X] RX_PW_P4=%u\r\n",Registers::RX_PW_P4,i);
    // RX_PW_P5
    i = ReadReg(Registers::RX_PW_P5);
    debug_printf("[0x%02X] RX_PW_P5=%u\r\n",Registers::RX_PW_P5,i);
}