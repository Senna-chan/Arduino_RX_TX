#include <Arduino.h>
#include "ibus.h"

/*
 *  supports max 14 channels in this lib (with messagelength of 0x20 there is room for 14 channels)

  Example set of bytes coming over the iBUS line for setting servos:
    20 40 DB 5 DC 5 54 5 DC 5 E8 3 D0 7 D2 5 E8 3 DC 5 DC 5 DC 5 DC 5 DC 5 DC 5 DA F3
  Explanation
    Protocol length: 20
    Command code: 40
    Channel 0: DB 5  -> value 0x5DB
    Channel 1: DC 5  -> value 0x5Dc
    Channel 2: 54 5  -> value 0x554
    Channel 3: DC 5  -> value 0x5DC
    Channel 4: E8 3  -> value 0x3E8
    Channel 5: D0 7  -> value 0x7D0
    Channel 6: D2 5  -> value 0x5D2
    Channel 7: E8 3  -> value 0x3E8
    Channel 8: DC 5  -> value 0x5DC
    Channel 9: DC 5  -> value 0x5DC
    Channel 10: DC 5 -> value 0x5DC
    Channel 11: DC 5 -> value 0x5DC
    Channel 12: DC 5 -> value 0x5DC
    Channel 13: DC 5 -> value 0x5DC
    Checksum: DA F3 -> calculated by adding up all previous bytes, total must be FFFF
 */


void IBusBM::begin(HardwareSerial &serial) {
  serial.begin(115200, SERIAL_8N1);

  this->stream = &serial;
  this->state = DISCARD;
  this->last = millis();
  this->ptr = 0;
  this->len = 0;
  this->chksum = 0;
  this->lchksum = 0;
}

void IBusBM::end(void)
{
    stream->end();
}

// called from timer interrupt or mannually by user (if IBUSBM_NOTIMER set in begin())
void IBusBM::loop(void)
{
  // only process data already in our UART receive buffer
  while (stream->available() > 0) {
    // only consider a new data package if we have not heard anything for >3ms
    uint32_t now = millis();
    if (now - last >= PROTOCOL_TIMEGAP){
      state = GET_LENGTH;
    }
    last = now;

    uint8_t v = stream->read();
    switch (state) {
      case GET_LENGTH:
        if (v <= PROTOCOL_LENGTH && v > PROTOCOL_OVERHEAD) {
          ptr = 0;
          len = v - PROTOCOL_OVERHEAD;
          chksum = 0xFFFF - v;
          state = GET_DATA;
        } else {
          state = DISCARD;
        }
        break;

      case GET_DATA:
        buffer[ptr++] = v;
        chksum -= v;
        if (ptr == len) {
          state = GET_CHKSUML;
        }
        break;

      case GET_CHKSUML:
        lchksum = v;
        state = GET_CHKSUMH;
        break;

      case GET_CHKSUMH:
        // Validate checksum
        if (chksum == (v << 8) + lchksum) {
          // Checksum is all fine Execute command -
          uint8_t adr = buffer[0] & 0x0f;
          if (buffer[0] == PROTOCOL_COMMAND40) {
            // Valid servo command received - extract channel data
            for (uint8_t i = 1; i < PROTOCOL_CHANNELS * 2 + 1; i += 2) {
              channel[i / 2] = buffer[i] | (buffer[i + 1] << 8);
            }
            cnt_rec++;
          } else if (adr<=NumberSensors && adr>0 && len==1) {

            // all sensor data commands go here
            // we only process the len==1 commands (=message length is 4 bytes incl overhead) to prevent the case the
            // return messages from the UART TX port loop back to the RX port and are processed again. This is extra
            // precaution as it will also be prevented by the PROTOCOL_TIMEGAP required
           sensorinfo *s = &sensors[adr-1];
           delayMicroseconds(100);
            switch (buffer[0] & 0x0f0) {
              case PROTOCOL_COMMAND_DISCOVER: // 0x80, discover sensor
                cnt_poll++;
                // echo discover command: 0x04, 0x81, 0x7A, 0xFF
                stream->write(0x04);
                stream->write(PROTOCOL_COMMAND_DISCOVER + adr);
                chksum = 0xFFFF - (0x04 + PROTOCOL_COMMAND_DISCOVER + adr);
                break;
              case PROTOCOL_COMMAND_TYPE: // 0x90, send sensor type
                // echo sensortype command: 0x06 0x91 0x00 0x02 0x66 0xFF
                stream->write(0x06);
                stream->write(PROTOCOL_COMMAND_TYPE + adr);
                stream->write(s->sensorType);
                stream->write(s->sensorLength);
                chksum = 0xFFFF - (0x06 + PROTOCOL_COMMAND_TYPE + adr + s->sensorType + s->sensorLength);
                break;
              case PROTOCOL_COMMAND_VALUE: // 0xA0, send sensor data
                cnt_sensor++;
                uint8_t t;
                // echo sensor value command: 0x06 0x91 0x00 0x02 0x66 0xFF
                stream->write(t = 0x04 + s->sensorLength);
                chksum = 0xFFFF - t;
                stream->write(t = PROTOCOL_COMMAND_VALUE + adr);
                chksum -= t;
                stream->write(t = s->sensorValue & 0x0ff);
                chksum -= t;
                stream->write(t = (s->sensorValue >> 8) & 0x0ff);
                chksum -= t;
                if (s->sensorLength==4) {
                  stream->write(t = (s->sensorValue >> 16) & 0x0ff);
                  chksum -= t;
                  stream->write(t = (s->sensorValue >> 24) & 0x0ff);
                  chksum -= t;
                }
                break;
              default:
                adr=0; // unknown command, prevent sending chksum
                break;
            }
            if (adr>0) {
              stream->write(chksum & 0x0ff);
              stream->write(chksum >> 8);
            }
          }
        }
        state = DISCARD;
        break;

      case DISCARD:
      default:
        break;
    }
  }
}

uint16_t IBusBM::readChannel(uint8_t channelNr) {
  if (channelNr < PROTOCOL_CHANNELS) {
    return channel[channelNr];
  } else {
    return 0;
  }
}

uint8_t IBusBM::addSensor(uint8_t type, uint8_t len) {
  // add a sensor, return sensor number
  if (len!=2 && len!=4) len = 2;
  if (NumberSensors < SENSORMAX) {
    sensorinfo *s = &sensors[NumberSensors];
    s->sensorType = type;
    s->sensorLength = len;
    s->sensorValue = 0;
    NumberSensors++;
  }
  return NumberSensors;
}

void IBusBM::setSensorMeasurement(uint8_t adr, int32_t value) {
   if (adr<=NumberSensors && adr>0)
     sensors[adr-1].sensorValue = value;
}
