// This class is used by the master arduino to receive
// nrf data.  Tx is not required because does not need pin 10.
#ifndef NRF_RX_SERIAL_h
#define NRF_RX_SERIAL_h
#include <SoftwareSerial.h>

class NrfRxSerial {
public:
  #define NOT_CONNECTED_PIN 20
  // pin specifies the pin that the master arduino will receive data on.
  NrfRxSerial (uint8_t pin) : nrfSerial (pin,NOT_CONNECTED_PIN) {
    nrfSerial.begin (9600);
  }; 
  
  bool available () {
     return nrfSerial.available();
  }
  
  char read () {
     return nrfSerial.read();
  }
  
private:  
  SoftwareSerial nrfSerial;
};
#endif