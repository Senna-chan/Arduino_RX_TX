#ifndef __NRF24_H
#define __NRF24_H

#include <main.h>

class nRF24{
 public:
 	enum Instructions : uint8_t {
// nRF24L0 instruction definitions
		R_REGISTER =       		0x00,	// Register read
		W_REGISTER =       		0x20,	// Register write
		ACTIVATE =         		0x50,	// (De)Activates R_RX_PL_WID, W_ACK_PAYLOAD, W_TX_PAYLOAD_NOACK features
		R_RX_PL_WID =	   		0x60,	// Read RX-payload width for the top R_RX_PAYLOAD in the RX FIFO.
		R_RX_PAYLOAD =     		0x61,	// Read RX payload
		W_TX_PAYLOAD =     		0xA0,	// Write TX payload
		W_ACK_PAYLOAD =    		0xA8,	// Write ACK payload
		W_TX_PAYLOAD_NOACK = 	0xB0,	//Write TX payload and disable AUTOACK
		FLUSH_TX =         		0xE1,	// Flush TX FIFO
		FLUSH_RX =         		0xE2,	// Flush RX FIFO
		REUSE_TX_PL =      		0xE3,	// Reuse TX payload
		LOCK_UNLOCK =      		0x50,	// Lock/unlock exclusive features
		NOP =              		0xFF,	// No operation (used for reading status register)
 	};
	// nRF24L0 register definitions
	enum Registers : uint8_t {
		CONFIG          = 0x00, // Configuration register
		EN_AA           = 0x01, // Enable "Auto acknowledgment"
		EN_RXADDR       = 0x02, // Enable RX addresses
		SETUP_AW        = 0x03, // Setup of address widths
		SETUP_RETR      = 0x04, // Setup of automatic retransmit
		RF_CH           = 0x05, // RF channel
		RF_SETUP        = 0x06, // RF setup register
		STATUS          = 0x07, // Status register
		OBSERVE_TX      = 0x08, // Transmit observe register
		RPD             = 0x09, // Received power detector
		RX_ADDR_P0      = 0x0A, // Receive address data pipe 0
		RX_ADDR_P1      = 0x0B, // Receive address data pipe 1
		RX_ADDR_P2      = 0x0C, // Receive address data pipe 2
		RX_ADDR_P3      = 0x0D, // Receive address data pipe 3
		RX_ADDR_P4      = 0x0E, // Receive address data pipe 4
		RX_ADDR_P5      = 0x0F, // Receive address data pipe 5
		TX_ADDR         = 0x10, // Transmit address
		RX_PW_P0        = 0x11, // Number of bytes in RX payload in data pipe 0
		RX_PW_P1        = 0x12, // Number of bytes in RX payload in data pipe 1
		RX_PW_P2        = 0x13, // Number of bytes in RX payload in data pipe 2
		RX_PW_P3        = 0x14, // Number of bytes in RX payload in data pipe 3
		RX_PW_P4        = 0x15, // Number of bytes in RX payload in data pipe 4
		RX_PW_P5        = 0x16, // Number of bytes in RX payload in data pipe 5
		FIFO_STATUS     = 0x17, // FIFO status register
		DYNPD           = 0x1C, // Enable dynamic payload length
		FEATURE         = 0x1D, // Feature register
	};
	enum RegisterBits : uint8_t {
// Register bits definitions
		CONFIG_PRIM_RX      = (uint8_t)0x01, // PRIM_RX bit in CONFIG register
		CONFIG_PWR_UP       = (uint8_t)0x02, // PWR_UP bit in CONFIG register
		FEATURE_EN_DYN_ACK  = (uint8_t)0x01, // EN_DYN_ACK bit in FEATURE register
		FEATURE_EN_ACK_PAY  = (uint8_t)0x02, // EN_ACK_PAY bit in FEATURE register
		FEATURE_EN_DPL      = (uint8_t)0x04, // EN_DPL bit in FEATURE register
		FLAG_RX_DR          = (uint8_t)0x40, // RX_DR bit (data ready RX FIFO interrupt)
		FLAG_TX_DS          = (uint8_t)0x20, // TX_DS bit (data sent TX FIFO interrupt)
		FLAG_MAX_RT         = (uint8_t)0x10, // MAX_RT bit (maximum number of TX retransmits interrupt)
	};

	enum RegisterMasks : uint8_t {
// Register masks definitions
		REG_MAP        = (uint8_t)0x1F, // Mask bits[4:0] for CMD_RREG and CMD_WREG commands
		CONFIG_CRC     = (uint8_t)0x0C, // Mask for CRC bits [3:2] in CONFIG register
		STATUS_IRQ     = (uint8_t)0x70, // Mask for all IRQ bits in STATUS register
		RF_PWR         = (uint8_t)0x06, // Mask RF_PWR[2:1] bits in RF_SETUP register
		RX_P_NO        = (uint8_t)0x0E, // Mask RX_P_NO[3:1] bits in STATUS register
		DATARATE       = (uint8_t)0x28, // Mask RD_DR_[5,3] bits in RF_SETUP register
		EN_RX          = (uint8_t)0x3F, // Mask ERX_P[5:0] bits in EN_RXADDR register
		RX_PW          = (uint8_t)0x3F, // Mask [5:0] bits in RX_PW_Px register
		RETR_ARD       = (uint8_t)0xF0, // Mask for ARD[7:4] bits in SETUP_RETR register
		RETR_ARC       = (uint8_t)0x0F, // Mask for ARC[3:0] bits in SETUP_RETR register
		RXFIFO         = (uint8_t)0x03, // Mask for RX FIFO status bits [1:0] in FIFO_STATUS register
		TXFIFO         = (uint8_t)0x30, // Mask for TX FIFO status bits [5:4] in FIFO_STATUS register
		PLOS_CNT       = (uint8_t)0xF0, // Mask for PLOS_CNT[7:4] bits in OBSERVE_TX register
		ARC_CNT        = (uint8_t)0x0F, // Mask for ARC_CNT[3:0] bits in OBSERVE_TX register
	};

// Fake address to test transceiver presence (5 bytes long)
	const char* TEST_ADDR  = "nRF24";


// Retransmit delay
enum RetransmitDelay : uint8_t {
	ARD_NONE   = (uint8_t)0x00, // Dummy value for case when retransmission is not used
	ARD_250us  = (uint8_t)0x00,
	ARD_500us  = (uint8_t)0x01,
	ARD_750us  = (uint8_t)0x02,
	ARD_1000us = (uint8_t)0x03,
	ARD_1250us = (uint8_t)0x04,
	ARD_1500us = (uint8_t)0x05,
	ARD_1750us = (uint8_t)0x06,
	ARD_2000us = (uint8_t)0x07,
	ARD_2250us = (uint8_t)0x08,
	ARD_2500us = (uint8_t)0x09,
	ARD_2750us = (uint8_t)0x0A,
	ARD_3000us = (uint8_t)0x0B,
	ARD_3250us = (uint8_t)0x0C,
	ARD_3500us = (uint8_t)0x0D,
	ARD_3750us = (uint8_t)0x0E,
	ARD_4000us = (uint8_t)0x0F
};

// Data rate
enum DataRate : uint8_t {
	DR_250kbps = (uint8_t)0x20, // 250kbps data rate
	DR_1Mbps   = (uint8_t)0x00, // 1Mbps data rate
	DR_2Mbps   = (uint8_t)0x08  // 2Mbps data rate
};

// RF output power in TX mode
enum TXPower : uint8_t {
	TXPWR_18dBm = (uint8_t)0x00, // -18dBm
	TXPWR_12dBm = (uint8_t)0x02, // -12dBm
	TXPWR_6dBm  = (uint8_t)0x04, //  -6dBm
	TXPWR_0dBm  = (uint8_t)0x06  //   0dBm
};

// CRC encoding scheme
enum CRCScheme : uint8_t {
	CRC_off   = (uint8_t)0x00, // CRC disabled
	CRC_1byte = (uint8_t)0x08, // 1-byte CRC
	CRC_2byte = (uint8_t)0x0c  // 2-byte CRC
};

// nRF24L01 power control
enum PowerControl : uint8_t {
	PWR_UP   = (uint8_t)0x02, // Power up
	PWR_DOWN = (uint8_t)0x00  // Power down
};

// Transceiver mode
enum TranceiverMode : uint8_t {
	RX = (uint8_t)0x01, // PRX
	TX = (uint8_t)0x00  // PTX
};

enum DynamicPayload : uint8_t {
	ON = (uint8_t)0x01, // PRX
	OFF = (uint8_t)0x00  // PTX
} ;

// Enumeration of RX pipe addresses and TX address
enum Addresses : uint8_t {
	PIPE0  = (uint8_t)0x00, // pipe0
	PIPE1  = (uint8_t)0x01, // pipe1
	PIPE2  = (uint8_t)0x02, // pipe2
	PIPE3  = (uint8_t)0x03, // pipe3
	PIPE4  = (uint8_t)0x04, // pipe4
	PIPE5  = (uint8_t)0x05, // pipe5
	PIPETX = (uint8_t)0x06, // TX address (not a pipe in fact)
	NONE   = (uint8_t)0xff  // No pipe
};

// State of auto acknowledgment for specified pipe
enum AutoAck : uint8_t {
	AA_OFF = (uint8_t)0x00,
	AA_ON  = (uint8_t)0x01
};

// Status of the RX FIFO
enum FifoStatus : uint8_t {
	FIFO_DATA  = (uint8_t)0x00, // The RX FIFO contains data and available locations
	FIFO_EMPTY = (uint8_t)0x01, // The RX FIFO is empty
	FIFO_FULL  = (uint8_t)0x02, // The RX FIFO is full
	FIFO_ERROR = (uint8_t)0x03  // Impossible state: RX FIFO cannot be empty and full at the same time
};

// Addresses of the RX_PW_P# registers
static constexpr uint8_t RX_PW_PIPE[6] = {
	RX_PW_P0,
	RX_PW_P1,
	RX_PW_P2,
	RX_PW_P3,
	RX_PW_P4,
	RX_PW_P5
};

// Addresses of the address registers
static constexpr uint8_t ADDR_REGS[7] = {
	RX_ADDR_P0,
	RX_ADDR_P1,
	RX_ADDR_P2,
	RX_ADDR_P3,
	RX_ADDR_P4,
	RX_ADDR_P5,
	TX_ADDR
};

	/**
	 * @brief Initialize nRF
	 * 
	 */
	void Init(void);
	/**
	 * @brief Check if nRF is connected
	 * 
	 * @retval 1 - nRF24L01 is online and responding
	 * @retval 0 - received sequence differs from original
	 */
	uint8_t Check(void);

void SetPowerMode(PowerControl mode);
void SetOperationalMode(TranceiverMode mode);
void SetRFChannel(uint8_t channel);
void SetAutoRetr(RetransmitDelay ard, uint8_t retryCount);
void SetAddrWidth(uint8_t addr_width);
void SetAddr(Addresses pipe, const uint8_t *addr);
void SetTXPower(TXPower tx_pwr);
void SetDataRate(DataRate data_rate);
void SetCRCScheme(CRCScheme scheme);
void SetRXPipe(Addresses pipe, AutoAck aa_state, uint8_t payload_len);
void ClosePipe(Addresses pipe);
void EnableAA(Addresses pipe);
void DisableAA(Addresses pipe);
void SetDynamicPayloadLength(DynamicPayload mode);
void SetPayloadWithAck(AutoAck mode);

uint8_t GetStatus(void);
uint8_t GetIRQFlags(void);
uint8_t GetStatus_RXFIFO(void);
uint8_t GetStatus_TXFIFO(void);
uint8_t GetRXSource(void);
uint8_t GetRetransmitCounters(void);
uint8_t GetFeatures(void);

void ResetPLOS(void);
void FlushTX(void);
void FlushRX(void);
void ClearIRQFlags(void);
void ActivateFeatures(void);
void WritePayload(uint8_t *pBuf, uint8_t length);
void WriteAckPayload(Addresses pipe, uint8_t *payload, uint8_t length);
Addresses ReadPayload(uint8_t *pBuf, uint8_t *length);
Addresses ReadPayloadDpl(uint8_t *pBuf, uint8_t *length);

void DumpConfig(void);


uint8_t LL_RW(uint8_t data);
void debug_printf(const char* fmt, ...);

void SetCEPin(GPIO_TypeDef *gpio, uint16_t pin);
void SetCSNPin(GPIO_TypeDef *gpio, uint16_t pin);
void SetSPI(SPI_HandleTypeDef *hspi);

void CE_L();
void CE_H();
void CSN_L();
void CSN_H();

void RX_ON() {
	CE_H();
}
void RX_OFF(){
	CE_L();
}
private:
	SPI_HandleTypeDef *_hspi;
	UART_HandleTypeDef *_uart;	

	GPIO_TypeDef *_cePort;
	GPIO_TypeDef *_csnPort;
	uint16_t      _cePin;
	uint16_t      _csnPin;
	
	uint8_t GetRxDplPayloadWidth();
	Addresses ReadPayloadGeneric(uint8_t *pBuf, uint8_t *length, uint8_t dpl);
	void WriteReg(uint8_t reg, uint8_t value);
	uint8_t ReadReg(uint8_t reg);
	void WriteMBReg(uint8_t reg, uint8_t *pBuf, uint8_t count);
	void ReadMBReg(uint8_t reg, uint8_t *pBuf, uint8_t count);
};
#endif // __NRF24_H
