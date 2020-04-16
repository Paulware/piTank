// This module gets loaded on the nrf/arduino component
// The NrfSerial class is used by the master device to drive
// this nrf component.
#include <EEPROM.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

//nRF24 pins
// Cables are:
//     SS       -> 10
//     MOSI     -> 11
//     MISO     -> 12
//     SCK      -> 13
#define CEPIN 8
#define CSNPIN 17
RF24 radio(CEPIN, CSNPIN);
const byte thisSlaveAddress[] = [0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xc2, 0xc2, 0xc2, 0xc2, 0xc2];

char payload[1];
byte channel; // Read from EEPROM
unsigned long channelTimeout = 0;

void setup() {
  Serial.begin (9600);
  Serial.println ("nrf Module ready");

  //channel = EEPROM.read(0);
  //if (channel == 255) {
  //  channel = 1;
  //}
  channel = 0x60;
  Serial.print ( "Current channel:" );
  Serial.println ( channel );

  radio.begin();
  radio.setChannel (channel);
  radio.setPALevel (RF24_PA_HIGH);
  radio.setDataRate( RF24_250KBPS );
  radio.openReadingPipe(1, thisSlaveAddress);
  radio.startListening();

  Serial.println ( "Enter a channel you prefer in the first 10 seconds." );
  channelTimeout = millis() + 10000;
  channel = 0;
}

void loop() {
  char ch;
  char oneCh[] = " ";
  unsigned char length;

  if (Serial.available()) {
    ch = Serial.read();
    // Check if 10 second timer has expired
    if (millis() < channelTimeout) {
      if (ch == 13) {
        Serial.print ( "New Channel (Restart to take effect):" );
        Serial.println ( channel );
        EEPROM.write (0, channel);
        channel = 0;
      } else if (ch == 10) { // ignore it
      } else if ((ch >= '0') && (ch <= '9')) {
        if (channel <= 25) {
          channel = (channel * 10) + ch - 48;
        } else {
          Serial.println ( "channel (0..255) too large" );
        }
      } else {
        channelTimeout = 0; // Got non-number (done)
      }
      channelTimeout = millis() + 10000; // Increment timer
    }
  }

  if (radio.available()) {
    // length = radio.getDynamicPayloadSize();
    radio.read(payload, 1);
    oneCh[0] = payload[0];
    Serial.print (oneCh);
  }
}