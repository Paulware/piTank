#include "esp_camera.h"
#include <WiFi.h>


// Tools
//   Board => ESP32 Wrover Module
//   Partition Scheme => Huge App
//   Reset power with io0 grounded to put in program mode 
//

// Select camera model
//#define CAMERA_MODEL_WROVER_KIT
//#define CAMERA_MODEL_ESP_EYE
//#define CAMERA_MODEL_M5STACK_PSRAM
//#define CAMERA_MODEL_M5STACK_WIDE
#define CAMERA_MODEL_AI_THINKER

#include "camera_pins.h"

// Connect to an existing wifi network
const char* ssid = "SBG6700AC-958C3"; //"canDebugger"; // "SBG6700AC-958C3"; // piPair"; //"PiRx062"; // "RichardsWiFi";
const char* password = "Star123!?";  //"ABCD1234"; // "Star123!?";  // "ABCD1234"; // "heartland62"; // "Star123!";

void startCameraServer();

// Arduino like analogWrite
// value has to be between 0 and valueMax
void ledcAnalogWrite(uint8_t channel, uint32_t value, uint32_t valueMax = 180) {

  // calculate duty, 8191 from 2 ^ 13 - 1
  uint32_t duty = (8191 / valueMax) * min(value, valueMax);
  ledcWrite(channel, duty);
}

/*
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
*/

void setup() {

  ledcSetup(2, 50, 16); //channel, freq, resolution
  ledcAttachPin(2, 2); // pin, channel
  ledcSetup(4, 50, 16);
  ledcAttachPin(12, 4);
  
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();

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

#if defined(CAMERA_MODEL_ESP_EYE)
  pinMode(13, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
#endif

  // camera init
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

#if defined(CAMERA_MODEL_M5STACK_WIDE)
  s->set_vflip(s, 1);
  s->set_hmirror(s, 1);
#endif

  WiFi.begin(ssid, password);

  Serial.println ( "Attempt to login yo" );
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

  /* 
   *  Enabling bluetooth interferes with the camera
   *  
   
  SerialBT.begin("ESP32test"); //Bluetooth device name    
  Serial.println("The device started, now you can pair it with bluetooth!");
  printDeviceAddress();  
  */
}

void loop() {
  char ch;
  static unsigned long timeout = 0; 

  static int leftValue = 0;
  static int rightValue = 0;

  if (Serial.available()) {
     ch = Serial.read();
     Serial.print (ch);    
     if (ch == 'L') {
        if (leftValue < 180) {
           leftValue = leftValue + 10;          
        }
     } else if (ch == 'l') {
        if (leftValue > 0) {
           leftValue = leftValue - 10; 
        }
     }
     ledcAnalogWrite(2, leftValue); // channel, value

     if (ch == 'R') {
        if (rightValue < 180) {
           rightValue = rightValue + 10;          
        }
     } else if (ch == 'r') {
        if (rightValue > 0) {
           rightValue = rightValue - 10; 
        }
     }
     ledcAnalogWrite(4, rightValue);      
  }
}
