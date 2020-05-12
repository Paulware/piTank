
#include "esp_camera.h"
#include <WiFi.h>
/* 
 // Enabling bluetooth interferes with the camera
#include "BluetoothSerial.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
*/

// Tools
//   Board => ESP32 Wrover Module
//   Partition Scheme => Huge App
//   Reset power with io0 grounded to put in program mode 
//

// Select camera model
#define CAMERA_MODEL_AI_THINKER

#include "camera_pins.h"

// Connect to an existing wifi network
const char* ssid = "piPair"; //"PiRx062"; // "RichardsWiFi";
const char* password = "ABCD1234"; // "heartland62"; // "Star123!";

void startCameraServer();

// Arduino like analogWrite
// value has to be between 0 and valueMax
void ledcAnalogWrite(uint8_t channel, uint32_t value, uint32_t valueMax = 180) {
  // value = map(value, -90, 90, 0, 180); // 0-180
  // calculate duty, 8191 from 2 ^ 13 - 1
  uint32_t duty = (8191 / valueMax) * min(value, valueMax);
  ledcWrite(channel, duty);
}

// Arm should be run when the ESC is powering up
void arm() {
   // Arm the ESC
   ledcAnalogWrite(2, 180); // channel, value
   ledcAnalogWrite(4, 180); // channel, value
   delay (2000); // 2 seconds
   ledcAnalogWrite(2, 90); // channel, value
   ledcAnalogWrite(4, 90); // channel, value
   delay (2000); // 2 seconds
}

void setup() {
  Serial.begin(9600);
  Serial.setDebugOutput(true);
  
  ledcSetup(2, 50, 16); //channel, freq, resolution
  ledcAttachPin(2, 2); // pin, channel
  ledcSetup(4, 50, 16);
  ledcAttachPin(12, 4);
  // arm();
  
  Serial.println ( "Configure camera" );
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  //init with high specs to pre-allocate larger buffers
  if(psramFound()){
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

// TODO: Use pin 13 and 14 for something? 
pinMode (13,OUTPUT);
pinMode (14,OUTPUT);
/*
#if defined(CAMERA_MODEL_ESP_EYE)
  pinMode(13, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
#endif
*/

  // camera init
  Serial.println ( "Camera init" );
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  sensor_t * s = esp_camera_sensor_get();
  //initial sensors are flipped vertically and colors are a bit saturated
  if (s->id.PID == OV3660_PID) {
    s->set_vflip(s, 1);//flip it back
    s->set_brightness(s, 1);//up the blightness just a bit
    s->set_saturation(s, -2);//lower the saturation
  }
  //drop down frame size for higher initial frame rate
  s->set_framesize(s, FRAMESIZE_QVGA);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  startCameraServer();

  Serial.print("Camera Ready! Use 'http://");
  Serial.print(WiFi.localIP());
  Serial.println("' to connect");

  //arm();

  /* 
   *  Enabling bluetooth interferes with the camera
   *  
   
  SerialBT.begin("ESP32test"); //Bluetooth device name    
  Serial.println("The device started, now you can pair it with bluetooth!");
  printDeviceAddress();  
  */
}

void loop() {
  static unsigned long count = 0;
  char ch;
  static unsigned long timeout = 0; 

  static int leftValue = 90;
  static int rightValue = 90;

  if (Serial.available()) {
     ch = Serial.read();
     Serial.print (ch);    
     if (ch == 'L') {
        if (leftValue < 120) { 
          leftValue = leftValue + 5;
        }
        digitalWrite (13,1);
        Serial.print ( "Left +" );
     } else if (ch == 'l') {
        if (leftValue > 90) { 
          leftValue = leftValue - 5;
        }
        digitalWrite (13,0);
        Serial.print ( "Left -" );  
     } else if (ch == 'S') { 
        if (leftValue > 105) { 
          leftValue = leftValue - 5;
        } else if (leftValue < 105) {
          leftValue = leftValue + 5;
        }
     }
     ledcAnalogWrite(2, leftValue); // channel, value

     if (ch == 'R') {
        if (rightValue < 120) { 
          rightValue = rightValue + 5;
        }
        digitalWrite (14,1);
     } else if (ch == 'r') {
        if (rightValue > 90) { 
          rightValue = rightValue - 5;
        }
        digitalWrite (14,0);
     } else if (ch == 's') {
        if (rightValue < 105) { 
           rightValue = rightValue + 5; 
        } else if (rightValue > 105) { 
           rightValue = rightValue - 5;
        }
     }
     ledcAnalogWrite(4, rightValue);      
  }

  if (millis() > timeout) {
    Serial.print ( "Count: " );
    Serial.println ( count );
    count = count + 1;
    timeout = millis() + 1000;    
  }
  
}
