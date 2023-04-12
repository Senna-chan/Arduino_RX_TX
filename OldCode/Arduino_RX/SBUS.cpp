// 
// 
// 

#include "SBUS.h"

void SBUS::init(HardwareSerial* serial)
{
	this->serial = serial;
	this->serial->begin(100000, SERIAL_8E2);
}

void SBUS::sbusPreparePacket(uint16_t channels[], bool isSignalLoss, bool isFailsafe)
{

	static int output[SBUS_CHANNEL_NUMBER] = { 0 };

	/*
	 * Map 1000-2000 with middle at 1500 chanel values to
	 * 173-1811 with middle at 992 S.BUS protocol requires
	 */
	for (uint8_t i = 0; i < SBUS_CHANNEL_NUMBER; i++) {
		output[i] = map(channels[i], RC_CHANNEL_MIN, RC_CHANNEL_MAX, SBUS_MIN_OFFSET, SBUS_MAX_OFFSET);
	}

	uint8_t stateByte = 0x00;
	if (isSignalLoss) {
		stateByte |= SBUS_STATE_SIGNALLOSS;
	}
	if (isFailsafe) {
		stateByte |= SBUS_STATE_FAILSAFE;
	}
	sbusOutPacket[0] = SBUS_FRAME_HEADER; //Header

	sbusOutPacket[1] = (uint8_t)(output[0] & 0x07FF);
	sbusOutPacket[2] = (uint8_t)((output[0] & 0x07FF) >> 8 | (output[1] & 0x07FF) << 3);
	sbusOutPacket[3] = (uint8_t)((output[1] & 0x07FF) >> 5 | (output[2] & 0x07FF) << 6);
	sbusOutPacket[4] = (uint8_t)((output[2] & 0x07FF) >> 2);
	sbusOutPacket[5] = (uint8_t)((output[2] & 0x07FF) >> 10 | (output[3] & 0x07FF) << 1);
	sbusOutPacket[6] = (uint8_t)((output[3] & 0x07FF) >> 7 | (output[4] & 0x07FF) << 4);
	sbusOutPacket[7] = (uint8_t)((output[4] & 0x07FF) >> 4 | (output[5] & 0x07FF) << 7);
	sbusOutPacket[8] = (uint8_t)((output[5] & 0x07FF) >> 1);
	sbusOutPacket[9] = (uint8_t)((output[5] & 0x07FF) >> 9 | (output[6] & 0x07FF) << 2);
	sbusOutPacket[10] = (uint8_t)((output[6] & 0x07FF) >> 6 | (output[7] & 0x07FF) << 5);
	sbusOutPacket[11] = (uint8_t)((output[7] & 0x07FF) >> 3);
	sbusOutPacket[12] = (uint8_t)((output[8] & 0x07FF));
	sbusOutPacket[13] = (uint8_t)((output[8] & 0x07FF) >> 8 | (output[9] & 0x07FF) << 3);
	sbusOutPacket[14] = (uint8_t)((output[9] & 0x07FF) >> 5 | (output[10] & 0x07FF) << 6);
	sbusOutPacket[15] = (uint8_t)((output[10] & 0x07FF) >> 2);
	sbusOutPacket[16] = (uint8_t)((output[10] & 0x07FF) >> 10 | (output[11] & 0x07FF) << 1);
	sbusOutPacket[17] = (uint8_t)((output[11] & 0x07FF) >> 7 | (output[12] & 0x07FF) << 4);
	sbusOutPacket[18] = (uint8_t)((output[12] & 0x07FF) >> 4 | (output[13] & 0x07FF) << 7);
	sbusOutPacket[19] = (uint8_t)((output[13] & 0x07FF) >> 1);
	sbusOutPacket[20] = (uint8_t)((output[13] & 0x07FF) >> 9 | (output[14] & 0x07FF) << 2);
	sbusOutPacket[21] = (uint8_t)((output[14] & 0x07FF) >> 6 | (output[15] & 0x07FF) << 5);
	sbusOutPacket[22] = (uint8_t)((output[15] & 0x07FF) >> 3);

	sbusOutPacket[23] = stateByte; //Flags byte
	sbusOutPacket[24] = SBUS_FRAME_FOOTER; //Footer
}

bool SBUS::loop()
{
	if (millis() > sbusTime) {
		serial->write(sbusOutPacket, SBUS_PACKET_LENGTH);
		sbusTime = millis() + SBUS_UPDATE_RATE;
	}
	return serial->available() > 0;
}

/* read the SBUS data */
bool SBUS::read(uint16_t* channels, bool* failsafe, bool* lostFrame)
{
	// parse the SBUS packet
	if (parse()) {
		if (channels) {
			// 16 channels of 11 bit data

			channels[0] = map((uint16_t)((sbusInPacket[0] | sbusInPacket[1] << 8) & 0x07FF), SBUS_MIN_OFFSET, SBUS_MAX_OFFSET, 1000, 2000);
			channels[1] = map((uint16_t)((sbusInPacket[1] >> 3 | sbusInPacket[2] << 5) & 0x07FF), SBUS_MIN_OFFSET, SBUS_MAX_OFFSET, 1000, 2000);
			channels[2] = map((uint16_t)((sbusInPacket[2] >> 6 | sbusInPacket[3] << 2 | sbusInPacket[4] << 10) & 0x07FF), SBUS_MIN_OFFSET, SBUS_MAX_OFFSET, 1000, 2000);
			channels[3] = map((uint16_t)((sbusInPacket[4] >> 1 | sbusInPacket[5] << 7) & 0x07FF), SBUS_MIN_OFFSET, SBUS_MAX_OFFSET, 1000, 2000);
			channels[4] = map((uint16_t)((sbusInPacket[5] >> 4 | sbusInPacket[6] << 4) & 0x07FF), SBUS_MIN_OFFSET, SBUS_MAX_OFFSET, 1000, 2000);
			channels[5] = map((uint16_t)((sbusInPacket[6] >> 7 | sbusInPacket[7] << 1 | sbusInPacket[8] << 9) & 0x07FF), SBUS_MIN_OFFSET, SBUS_MAX_OFFSET, 1000, 2000);
			channels[6] = map((uint16_t)((sbusInPacket[8] >> 2 | sbusInPacket[9] << 6) & 0x07FF), SBUS_MIN_OFFSET, SBUS_MAX_OFFSET, 1000, 2000);
			channels[7] = map((uint16_t)((sbusInPacket[9] >> 5 | sbusInPacket[10] << 3) & 0x07FF), SBUS_MIN_OFFSET, SBUS_MAX_OFFSET, 1000, 2000);
			channels[8] = map((uint16_t)((sbusInPacket[11] | sbusInPacket[12] << 8) & 0x07FF), SBUS_MIN_OFFSET, SBUS_MAX_OFFSET, 1000, 2000);
			channels[9] = map((uint16_t)((sbusInPacket[12] >> 3 | sbusInPacket[13] << 5) & 0x07FF), SBUS_MIN_OFFSET, SBUS_MAX_OFFSET, 1000, 2000);
			channels[10] = map((uint16_t)((sbusInPacket[13] >> 6 | sbusInPacket[14] << 2 | sbusInPacket[15] << 10) & 0x07FF), SBUS_MIN_OFFSET, SBUS_MAX_OFFSET, 1000, 2000);
			channels[11] = map((uint16_t)((sbusInPacket[15] >> 1 | sbusInPacket[16] << 7) & 0x07FF), SBUS_MIN_OFFSET, SBUS_MAX_OFFSET, 1000, 2000);
			channels[12] = map((uint16_t)((sbusInPacket[16] >> 4 | sbusInPacket[17] << 4) & 0x07FF), SBUS_MIN_OFFSET, SBUS_MAX_OFFSET, 1000, 2000);
			channels[13] = map((uint16_t)((sbusInPacket[17] >> 7 | sbusInPacket[18] << 1 | sbusInPacket[19] << 9) & 0x07FF), SBUS_MIN_OFFSET, SBUS_MAX_OFFSET, 1000, 2000);
			channels[14] = map((uint16_t)((sbusInPacket[19] >> 2 | sbusInPacket[20] << 6) & 0x07FF), SBUS_MIN_OFFSET, SBUS_MAX_OFFSET, 1000, 2000);
			channels[15] = map((uint16_t)((sbusInPacket[20] >> 5 | sbusInPacket[21] << 3) & 0x07FF), SBUS_MIN_OFFSET, SBUS_MAX_OFFSET, 1000, 2000);
			// channels[16] = sbusInPacket[22] & 0b00000001 ? 1000 : 2000;
			// channels[17] = sbusInPacket[22] & 0b00000010 ? 1000 : 2000;
		}
		if (lostFrame) {
			// count lost frames
			if (sbusInPacket[22] & SBUS_STATE_SIGNALLOSS) {
				*lostFrame = true;
			}
			else {
				*lostFrame = false;
			}
		}
		if (failsafe) {
			// failsafe state
			if (sbusInPacket[22] & SBUS_STATE_FAILSAFE) {
				*failsafe = true;
			}
			else {
				*failsafe = false;
			}
		}
		// return true on receiving a full packet
		return true;
	}
	else {
		// return false if a full packet is not received
		return false;
	}
}

bool SBUS::parse()
{
	byte _curByte;
	byte _prevByte;
	byte _parserState = 0;
	if (serial->available() > 24) {
		Serial.println("Got some data on SBUS serial");
		while (serial->available() > 0) {
			_curByte = serial->read();
			// find the header
			if (_parserState == 0) {
				if ((_curByte == SBUS_FRAME_HEADER) && ((_prevByte == SBUS_FRAME_FOOTER) || ((_prevByte & SBUS_FRAME_MASK) == SBUS_FRAME_FOOTER_V2))) {
					_parserState++;
				}
				else {
					_parserState = 0;
				}
			}
			else {
				// strip off the data
				if ((_parserState - 1) < SBUS_PACKET_LENGTH) {
					sbusInPacket[_parserState - 1] = _curByte;
					_parserState++;
				}
				// check the end byte
				if ((_parserState - 1) == SBUS_PACKET_LENGTH) {
					if ((_curByte == SBUS_FRAME_FOOTER) || ((_curByte & SBUS_FRAME_MASK) == SBUS_FRAME_FOOTER_V2)) {
						return true;
					}
					return false;
				}
			}
			_prevByte = _curByte;
		}
	}
	// return false if a partial packet
	return false;
}
