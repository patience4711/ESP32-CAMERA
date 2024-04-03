// let op. define camera present 121 en start cameraserver 198
// on esp32 devkit v4 the touch works

#include "esp_camera.h"
#include <WiFi.h>
#include <DNSServer.h> // for portal 
#include <WebServer.h>
#include "soc/soc.h" // ha for brownout
#include "soc/rtc_cntl_reg.h" // ha for brownout
#include "HTML.H"
#include "HOMEPAGE.H"
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

#include <PubSubClient.h>

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
  //int signalFlag = 0;
  static unsigned long laatsteMeting = 0;  

  char swName[21] = "ESP32CAM";
  char pswd[11] = "0000";
  bool doorBell = false;
  int touch_th = 40;
  int ledon_time = 20;
  char userpswd[11] = "1111";
  String toSend = ""; 
  int networksFound = 0;
  bool camera_active = true;
  bool tryConnectFlag = false;
  char ssid[33] = ""; // was 33 
  char pass[40] = ""; // was 40 
  int actionFlag = 0;   
  #define LED_AAN     LOW
  #define LED_UIT     HIGH
  #define led_onb     33
  #define flashLed 4
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
char requestUrl[12] = {""}; // to remember from which webpage we came
// variables mqtt ********************************************
  char  Mqtt_Broker[30]=    {"192.168.0.100"};
  char  Mqtt_outTopic[26] = {"domoticz/in"}; // was 26
  int   Mqtt_idx = 0; 
  char  Mqtt_Username[26] = {""};
  char  Mqtt_Password[26] = {""};
  char  Mqtt_Clientid[26] = {""};
  char  Mqtt_Port[5] =  {"1883"};
  int   Mqtt_Format = 0; 
  long  mqtt_lastConnect = 0;

WiFiClient espClient ;
PubSubClient MQTT_Client ( espClient ) ;

int touch_sensor_value=0;

#define TOUCHPIN  T6  // this is the only one working
bool takeNewPhoto = false;
#define FILE_PHOTO "/photo.jpg"
bool rotate = false;
// ************************************************************************************
//       S E T U P       S E T U P        S E T U P       S E T U P
//*************************************************************************************
void setup() {

 WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable brownout detector 

  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();
  pinMode(led_onb, OUTPUT);
  pinMode(knop, INPUT_PULLUP);
  pinMode(flashLed, OUTPUT);
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

  // ****************** mqtt init *********************
  MQTT_Client.setKeepAlive(150);
  MQTT_Client.setServer(Mqtt_Broker, atoi(Mqtt_Port));
  MQTT_Client.setCallback ( MQTT_Receive_Callback ) ;

}


// ************************************************************************************************
// ************************************************************************************************
//                                   L O O P
// ************************************************************************************************
// ************************************************************************************************


void loop() {

  // read the touch sensor
  // touch0=gp4 1=gp00 2=gp2 3=gp15 4=gp13 5=gp12 6=gp14
  if(doorBell){
  if(touchRead(TOUCHPIN) < touch_th ) handleTouch();
  if ( millis() > laatsteMeting + ledon_time*1000UL ) { //20 sec
    digitalWrite(flashLed, LOW);
  }
  }  
    if(Serial.available()) {
        handle_Serial();
    }  
// ***************************************************************************
//                       m q t t
// ***************************************************************************
       // before each transmission the connection is tested
       // so we don't do this in the loop
       if(Mqtt_Format != 0 ) MQTT_Client.loop(); //looks for incoming messages

 if(actionFlag != 0)  test_actionFlag();

  if (takeNewPhoto) {
    capturePhotoSaveSpiffs();
    takeNewPhoto = false;
  }

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
void test_actionFlag() {
// commit actions that cannot run within the servers infrastructure

  if (actionFlag == 11) { // de knop is langdurig ingedrukt geweest, opstarten in AP
    DebugPrintln("We are wiping the wificredentials");
    WiFi.disconnect(true);
    WiFi.begin("0","0");
    delay(8000); // ruim de tijd om de knop los te laten anders komt ie in programmeermode
    ESP.restart();
  }
    if (actionFlag == 12) { // de knop is langdurig ingedrukt geweest, opstarten in AP
    DebugPrintln("We are going to reboot");
    ESP.restart();
  }

// ************  mosquitto reconnect  ********************* 
   
    if (actionFlag == 24) { // set by the mqtt config page
        actionFlag = 0; //reset the actionflag
        MQTT_Client.disconnect();
       //reset the mqttserver
        MQTT_Client.setServer(Mqtt_Broker, atoi(Mqtt_Port) );
        MQTT_Client.setCallback ( MQTT_Receive_Callback ) ;
        if (Mqtt_Format != 0) mqttConnect(); // reconnect mqtt after change of settings
    } 
//    if (actionFlag == 49) { //triggered by console testmqtt
//        actionFlag = 0; //reset the actionflag
//        ledblink(1,100);
//        // always first drop the existing connection
//        MQTT_Client.disconnect();
//        Serial.println("dropped connection");
//        delay(100);
//       
//        if(mqttConnect() ) {
//        String toMQTT=""; // if we are connected we do this
//        
//        
//        toMQTT = "{\"test\":\"hello from esp32-cam\"}";
//                
//        if( MQTT_Client.publish (Mqtt_outTopic, toMQTT.c_str() ) ) {
//            Serial.println("sent mqtt message : " + toMQTT);
//        } else {
//            Serial.println("sending mqtt message failed : " + toMQTT);    
//        }
//      } 
//     // the not connected message is displayed by mqttConnect()
//    }  
}
String getChipId() {
    uint32_t chipId = 0;
    for(int i=0; i<17; i=i+8) {
    chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
  }
  return "ESPCAM-" + String(chipId);
}


void handleTouch() {
  //Serial.println("touch button pressed");
  //if the led is on, the touch doesn't react
   if (doorBell && digitalRead(flashLed) != HIGH) {
      char toMQTT[100]={0};
      digitalWrite(flashLed, HIGH);
      ledblink(5,150);
      laatsteMeting = millis(); // mark the on-time
      // now send an mqttmessage like {"command": "switchlight", "idx": 2450, "switchcmd": "On" }
      switch (Mqtt_Format) {
      case 1: 
        snprintf(toMQTT, sizeof(toMQTT), "{\"command\":\"switchlight\",\"idx\":%d,\"switchcmd\":\"On\"}" , Mqtt_idx);
        break;
      case 2:
        snprintf(toMQTT, sizeof(toMQTT), "{\"family\":\"switchupdate\",\"idx\":%d,\"Action\":\"On\"}" , Mqtt_idx);
        break;
      }
      if(mqttConnect() ) MQTT_Client.publish ( Mqtt_outTopic, toMQTT, false);
  }
}
