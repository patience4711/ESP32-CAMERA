#include "esp_camera.h"
#include <WiFi.h>
#include <DNSServer.h> // for portal 
#include <WebServer.h>
#include "soc/soc.h" // ha for brownout
#include "soc/rtc_cntl_reg.h" // ha for brownout
#include "HTML.H"
#include "PORTAL_HTML.H"
#include <FS.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <esp_task_wdt.h> // ha
#include <AsyncTCP.h>

#include "soc/rtc_wdt.h"
#include <ESPAsyncWebServer.h>
AsyncWebServer asyserver(80);//
#include "cam_index.h"
//#include "index_cam.h"
//WebServer portalserver(80);  // Replace with WebServer for ESP32
const byte DNS_PORT = 53;
DNSServer dnsServer;
//#include "headerbestand.h"

#define DEBUG
#ifdef  DEBUG
#define DebugPrint(x)     Serial.print (x)
#define DebugPrintDec(x)  Serial.print (x, DEC)
#define DebugPrintln(x)   Serial.println (x)
#else
#define DebugPrint(x)
#define DebugPrintDec(x)
#define DebugPrintln(x)
#endif

 
  char static_ip[16] = "000.000.000.000";
  char lengte[8] = "5.123";
  char breedte[8] = "51.345"; 
  char timezone[5] = "+120";  //+5.30 GMT
  bool zomerTijd = false;
  int value = 0;
  int event = 0;  
  int signalFlag = 0;
  static unsigned long laatsteMeting = 0;  
  char swName[21] = "ESP32CAM";
  char pswd[11] = "0000";
  char userpswd[11] = "1111";
  String toSend = ""; 
  int networksFound = 0;
  bool camera_active = true;
  bool tryConnectFlag = false;
  char ssid[33] = ""; // was 33 
  char pass[40] = ""; // was 40 
    
  #define LED_AAN     LOW
  #define LED_UIT     HIGH
  #define led_onb     33
  #define led_buildin 4
  #define knop        16
//
// WARNING!!! Make sure that you have either selected ESP32 Wrover Module,
//            or another board which has PSRAM enabled

// Select camera model
//#define CAMERA_MODEL_WROVER_KIT
//#define CAMERA_MODEL_ESP_EYE
//#define CAMERA_MODEL_M5STACK_PSRAM
//#define CAMERA_MODEL_M5STACK_WIDE
#define CAMERA_MODEL_AI_THINKER // this is an OV2640

#include "camera_pins.h"
//CONFIG_ESP_INT_WDT_TIMEOUT_MS 500;
void startCameraServer(); //predeclare

void setup() {

 WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable brownout detector 

  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();
  pinMode(led_onb, OUTPUT);
  pinMode(knop, INPUT_PULLUP);
  //attachInterrupt(digitalPinToInterrupt(knop), isr, FALLING);

#define CAMERA_PRESENT
#ifdef CAMERA_PRESENT

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
    Serial.println("psram found, initial framesize UXGA");
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    Serial.println("psram not found initial framesize SVGA");
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
    camera_active = false;
    //yyyreturn false;
  } else {
  // if esp_ok then do the settings
  Serial.print("Camera init success\n");
  sensor_t * s = esp_camera_sensor_get();
  //initial sensors are flipped vertically and colors are a bit saturated

  if (s->id.PID == OV3660_PID) {
    s->set_vflip(s, 1);//flip it back
    s->set_brightness(s, 1);//up the blightness just a bit
    s->set_saturation(s, -2);//lower the saturation
  }
  //drop down frame size for higher initial frame rate
  s->set_framesize(s, FRAMESIZE_VGA);

#if defined(CAMERA_MODEL_M5STACK_WIDE)
  s->set_vflip(s, 1);
  s->set_hmirror(s, 1);
#endif
//return true;
} 

#endif // CAMERAPRESENT

  Files_Read(); // we cannot read cameraconfig as camera_active == false

  start_wifi();

  startCameraServer();

  Serial.print("Camera Ready! Use 'http://");
  Serial.print(WiFi.localIP());
  Serial.println("' to connect");
  ledblink(3,500);
}


// ************************************************************************************************
// ************************************************************************************************
//                                   L O O P
// ************************************************************************************************
// ************************************************************************************************


void loop() {

//  if ( millis() > heartbeat + 10*1000UL ) {
//    heartbeat = millis(); // elke 10 sec een heartbeat
//    DebugPrint("l ");
//  }
  
  if (signalFlag == 11) { // de knop is langdurig ingedrukt geweest, opstarten in AP
    DebugPrintln("We are wiping the wificredentials");
    WiFi.disconnect(true);
    WiFi.begin("0","0");
    delay(8000); // ruim de tijd om de knop los te laten anders komt ie in programmeermode
    ESP.restart();
  }
    if (signalFlag == 12) { // de knop is langdurig ingedrukt geweest, opstarten in AP
    DebugPrintln("We are going to reboot");
    ESP.restart();
  }



//  portalserver.handleClient(); //
    if(Serial.available()) {
        handle_Serial();
    }  
  delay(1000);
}
// ****************************************************************************
//                         E N D  L O O P 
// ***************************************************************************

void ledblink(int i, int wait) {
  for (int x = 0; x < i; x++) {
    digitalWrite(led_onb, LED_AAN);
    delay(wait);
    digitalWrite(led_onb, LED_UIT);
    delay(wait);
  }
}

String getChipId() {
    uint32_t chipId = 0;
    for(int i=0; i<17; i=i+8) {
    chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
  }
  return "ESPCAM-" + String(chipId);
}



//bool camera_init() {
//  // camera init
////  esp_err_t err = esp_camera_init(&config);
//
//  if (err != ESP_OK) {
//      Serial.printf("Camera init failed with error 0x%x", err);
//      camera_active = false;
//      return false;
//  } else {
//      // if esp_ok then do the settings
//      Serial.print("Camera init success");
//      sensor_t * s = esp_camera_sensor_get();
//      //initial sensors are flipped vertically and colors are a bit saturated
//    
//      if (s->id.PID == OV3660_PID) {
//        s->set_vflip(s, 1);//flip it back
//        s->set_brightness(s, 1);//up the blightness just a bit
//        s->set_saturation(s, -2);//lower the saturation
//      }
//      //drop down frame size for higher initial frame rate
//      s->set_framesize(s, FRAMESIZE_QVGA);
//    
//    #if defined(CAMERA_MODEL_M5STACK_WIDE)
//      s->set_vflip(s, 1);
//      s->set_hmirror(s, 1);
//    #endif
//    return true;
//  }
//}    
