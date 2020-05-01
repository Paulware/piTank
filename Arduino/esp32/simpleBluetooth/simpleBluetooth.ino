/*
 * On the raspberry pi, 
 /etc/rc.local should look like: 
   (With the proper BT address displayed by arduino code below)
#!/bin/sh -e
rfcomm bind 0 BT:AD:RE:SS:BE:LO 1
exit 0

Note: On the pi, you can use the command:
rfcomm release 0
to release rfcomm0

python test code on pi:
import serial
try:
   port = serial.Serial("/dev/rfcomm0", baudrate=9600, timeout=1)
   port.write (str.encode("Hello Yo")) 
finally:
   port.close() 

  
*/

#include "BluetoothSerial.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void printDeviceAddress() { 
  const uint8_t* point = esp_bt_dev_get_address(); 
  Serial.print ( "Blue tooth Address: " );
  for (int i = 0; i < 6; i++) { 
    char str[3]; 
    sprintf(str, "%02X", (int)point[i]);
    Serial.print(str);
 
    if (i < 5){
      Serial.print(":");
    } 
  }
}

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  printDeviceAddress();
}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }
  delay(20);
}
