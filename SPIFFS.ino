
// ******************   spiffs r/w  *************************

void Files_Read() {
  DebugPrintln("mounting FS...");
 if (SPIFFS.begin()) {
    DebugPrintln("mounted file system");

       if( file_open_for_read("/wificonfig.json") ) {
                DebugPrintln("wificonfig read");
          } else {
             DebugPrintln("wificonfig.json not loaded");
          }
//       if( file_open_for_read("/timerconfig.json") ) {     
//             DebugPrintln("timerconfig gelezen");
//          } else {
//            DebugPrintln("timerconfig.json niet geladen");
//          }
//       if( file_open_for_read("/mqttconfig.json") ) {     
//             DebugPrintln("mqttconfig gelezen");
//          } else {
//          DebugPrintln("mqttconfig.json niet geladen");
//        }
       if( file_open_for_read("/basisconfig.json") ) {     
             DebugPrintln("basisconfig read");
          } else {
          DebugPrintln("basisconfig.json not loaded");
        }  
       // if we set the cameracontrols when no camera, the esp crashes
       if(camera_active) { //read cameraconfig and set the controls
           if( file_open_for_read("/cameraconfig.json") ) {     
                 DebugPrintln("cameraconfig read");
              } else {
              DebugPrintln("cameraconfig.json not loaded");
            }
        }

  } else {
        DebugPrintln("failed to mount FS, going to format");
            SPIFFS.format();
   }
 // einde spiffs lezen 4 bestanden
}
// als er geen swname of zomerTijd is gelezen dan zetten we deze op default
//      if (swname[0] == '\0') {
//    uint32_t chipId = 0;
//    for(int i=0; i<17; i=i+8) {
//    chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
//    }
//    String tmp =String(chipId);
//     //      String s = "ESP-" + String(ESP.getChipId());
//     tmp.toCharArray(swname, 21);
//  }      
// tijd_convert(); // omrekenen van tijdwaarden voor cdwn aso en switchtime
//}  


// **************************************************************************** 
//                      de gegevens opslaan in SPIFFS                         *  
// ****************************************************************************
void wifiConfigsave() {
   DebugPrintln("saving config");
    DynamicJsonDocument doc(1024);
    JsonObject json = doc.to<JsonObject>();
   
    json["ip"] = static_ip;
    json["pswd"] = pswd;
//    json["lengte"] = lengte;
//    json["breedte"] = breedte;
//    json["timezone"] = timezone;
//    json["gpBool"] = gpBool;         
//    json["zomerTijd"] = zomerTijd;
    File configFile = SPIFFS.open("/wificonfig.json", "w");
    if (!configFile) {
      DebugPrintln("failed to open config file for writing");
    }
    DebugPrintln("wrote wificonfig.json in SPIFFS");
    #ifdef DEBUG
    serializeJson(json, Serial);
    Serial.println("");
    #endif 
    serializeJson(json, configFile);
    configFile.close();
}

//void timerConfigsave() {   
//DebugPrintln("saving config");
//    DynamicJsonDocument doc(1024);
//    JsonObject json = doc.to<JsonObject>();
//
//    json["weekDag"] = weekDag;
//    json["relToSunOn"] = relToSunOn;
//    json["relToSunOff"] = relToSunOff;   
//    json["switchOn"] = switchOn;   
//    json["switchOff"] = switchOff;  
//
//    File configFile = SPIFFS.open("/timerconfig.json", "w");
//    if (!configFile) {
//      DebugPrintln("failed to open timerconfig file for writing");
//    }
//    DebugPrintln("timerconfig.json in SPIFFS geschreven");
//    #ifdef DEBUG
//    serializeJson(json, Serial);
//    Serial.println(""); 
//    #endif
//    serializeJson(json, configFile);
//    configFile.close();
//}

void basisConfigsave() {
   DebugPrintln("saving basis config");
    DynamicJsonDocument doc(1024);
    JsonObject json = doc.to<JsonObject>();
// 
    json["swName"] = swName;
    json["userpswd"] = userpswd;
    File configFile = SPIFFS.open("/basisconfig.json", "w");
    if (!configFile) {
      DebugPrintln("failed to open config file for writing");
    }
    DebugPrintln("wrote basisconfig.json in SPIFFS");
    #ifdef DEBUG
    serializeJson(json, Serial);
    Serial.println("");
    #endif 
    serializeJson(json, configFile);
    configFile.close();
}
//

void cameraConfigsave() {
    sensor_t * s = esp_camera_sensor_get();
    Serial.println("survived esp_camera_sensor_get()");
//char * p ;
//    *p++ = '{';
//
//    p+=sprintf(p, "\"framesize\":%u,", s->status.framesize);
//    p+=sprintf(p, "\"quality\":%u,", s->status.quality);
//    p+=sprintf(p, "\"brightness\":%d,", s->status.brightness);
//    p+=sprintf(p, "\"contrast\":%d,", s->status.contrast);
//    p+=sprintf(p, "\"saturation\":%d,", s->status.saturation);
//    p+=sprintf(p, "\"sharpness\":%d,", s->status.sharpness);
//    p+=sprintf(p, "\"special_effect\":%u,", s->status.special_effect);
//    p+=sprintf(p, "\"wb_mode\":%u,", s->status.wb_mode);
//    p+=sprintf(p, "\"awb\":%u,", s->status.awb);
//    p+=sprintf(p, "\"awb_gain\":%u,", s->status.awb_gain);
//    p+=sprintf(p, "\"aec\":%u,", s->status.aec);
//    p+=sprintf(p, "\"aec2\":%u,", s->status.aec2);
//    p+=sprintf(p, "\"ae_level\":%d,", s->status.ae_level);
//    p+=sprintf(p, "\"aec_value\":%u,", s->status.aec_value);
//    p+=sprintf(p, "\"agc\":%u,", s->status.agc);
//    p+=sprintf(p, "\"agc_gain\":%u,", s->status.agc_gain);
//    p+=sprintf(p, "\"gainceiling\":%u,", s->status.gainceiling);
//    p+=sprintf(p, "\"bpc\":%u,", s->status.bpc);
//    p+=sprintf(p, "\"wpc\":%u,", s->status.wpc);
//    p+=sprintf(p, "\"raw_gma\":%u,", s->status.raw_gma);
//    p+=sprintf(p, "\"lenc\":%u,", s->status.lenc);
//    p+=sprintf(p, "\"vflip\":%u,", s->status.vflip);
//    p+=sprintf(p, "\"hmirror\":%u,", s->status.hmirror);
//    p+=sprintf(p, "\"dcw\":%u,", s->status.dcw);
//    p+=sprintf(p, "\"colorbar\":%u,", s->status.colorbar);
//    p+=sprintf(p, "\"face_detect\":%u,", detection_enabled);
//    p+=sprintf(p, "\"face_enroll\":%u,", is_enrolling);
//    p+=sprintf(p, "\"face_recognize\":%u", recognition_enabled);
//    *p++ = '}';
//    *p++ = 0;
   
   Serial.println("saving camera config");
   DynamicJsonDocument doc(1024);
   JsonObject json = doc.to<JsonObject>();
   json["framesize"] = s->status.framesize;
   json["quality"] = s->status.quality;
   json["brightness"] = s->status.brightness;
   json["contrast"] = s->status.contrast;
   json["saturation"] = s->status.saturation;
   json["sharpness"] = s->status.sharpness;  
   json["vflip"] = s->status.vflip;
   json["hmirror"] = s->status.hmirror; 
   json["agc_gain"] = s->status.agc_gain;
   json["gainceiling"] = s->status.gainceiling; 
   File configFile = SPIFFS.open("/cameraconfig.json", "w");
    //#ifdef DEBUG
    serializeJson(json, Serial);
    Serial.println("");
    //#endif 
    serializeJson(json, configFile);
    configFile.close();
}


// ********************************************************************
//                 read files
// *********************************************************************

bool file_open_for_read(String bestand) {
      DebugPrint("we are in file_open_for_read, bestand = "); DebugPrintln(bestand); 
      if (!SPIFFS.exists(bestand)) { 
      DebugPrintln("file does not exist");
      return false;
      } else {
      //file exists, reading and loading
      DebugPrintln("file exists");
        File configFile = SPIFFS.open(bestand, "r");
        if (configFile) {
           DebugPrint("opened config file"); DebugPrintln(bestand);
           size_t size = configFile.size();
          // Allocate a buffer to store contents of the file.
           std::unique_ptr<char[]> buf(new char[size]);
           configFile.readBytes(buf.get(), size);
//           DynamicJsonBuffer jsonBuffer;
//           JsonObject& json = jsonBuffer.parseObject(buf.get());
           DynamicJsonDocument doc(1024);
           auto error = deserializeJson(doc, buf.get());

           //#ifdef DEBUG 
           serializeJson(doc, Serial); Serial.println("");
           //#endif
           if (!error) {
              DebugPrintln("parsed json\n");
              String jsonStr = ""; // we printen het json object naar een string
            // nu kunnen we eerst controleren of een bepaalde entry bestaat
            // zoniet slaan we die over anders crasht de ESP
//              json.printTo(jsonStr); // zet het opbject in een string
            serializeJson(doc, jsonStr);
            if (bestand == "/wificonfig.json") {
                      if(jsonStr.indexOf("ip") > 0){ strcpy(static_ip, doc["ip"]);}
                      if(jsonStr.indexOf("pswd") > 0){ strcpy(pswd, doc["pswd"]);}
                      if(jsonStr.indexOf("lengte") > 0){ strcpy(lengte, doc["lengte"]);}
                      if(jsonStr.indexOf("breedte") > 0){ strcpy(breedte, doc["breedte"]);}
                      if(jsonStr.indexOf("timezone") > 0){ strcpy(timezone, doc["timezone"]);}
                      //if(jsonStr.indexOf("gpBool") > 0){ strcpy(gpBool, doc["gpBool"]);}
                      if(jsonStr.indexOf("zomerTijd") > 0) { zomerTijd =  doc["zomerTijd"].as<bool>();}
            }

            if (bestand == "/basisconfig.json"){
                     if(jsonStr.indexOf("swName") > 0){strcpy(swName, doc["swName"]);}
                     if(jsonStr.indexOf("userpswd") > 0){ strcpy(userpswd, doc["userpswd"]);}
            }

            if (bestand == "/cameraconfig.json") {
              sensor_t * s = esp_camera_sensor_get();
              int res = 0;
              Serial.println("pointer retrieved");
              
                     if(jsonStr.indexOf("framesize") > 0) {
                     framesize_t temp = doc["framesize"].as<framesize_t>();
                     Serial.println("temp set value = " + String(temp));
                     switch (temp) {
 /*                     
                                <option value="8">8 UXGA(1600x1200)</option>
                                <option value="7">7 SXGA(1280x1024)</option>
                                <option value="6">6 XGA(1024x768)</option>
                                <option value="5">5 SVGA(800x600)</option>
                                <option value="4">4 VGA(640x480)</option>
                                <option value="3">3 CIF(400x296)</option>
                                <option value="2">2 QVGA(320x240)</option>
                                <option value="1">1 HQVGA(240x176)</option>
                                <option value="0">0 QQVGA(160x120)</option> 

there is some conversion between the save and restore
4 ---> 5 cif 
5 ---> 6 xga
6 ---> 8 xga
7 geeft 9 sxga
8 geeft 10 uxga
9 geeft niets
// valid for OV2640 FRAMESIZE_ + QVGA|CIF|VGA|SVGA|XGA|SXGA|UXGA 
 */                  
// translate this to the right input for setFsize()
// wi ==> serial
//3  --> 1
//5  --> 2
//6  --> 3
//8  --> 4
//12 --> 7
//10 --> 6
                      case 5:
                         setFsize(0);
                         break;
                      case 6:
                         setFsize(1) ;
                         break;  
                      case 8:
                         setFsize(2) ;
                         break;
                      case 9:                         
                         setFsize(3) ;
                         break;                      
                      case 10:                         
                         setFsize(5) ;
                         break;  
                      
//                      case 4: 
//                        s->set_framesize(s, FRAMESIZE_QVGA);
//                        break;
//                      case 3:
//                        s->set_framesize(s, FRAMESIZE_HQVGA);
//                        break;
//                       case 6:
//                        s->set_framesize(s, FRAMESIZE_VGA);
//                        break;   
                     } 
                     
                  }   

            if(jsonStr.indexOf("quality") > 0) {
             int8_t temp = doc["quality"].as<int8_t>();
             s->set_quality(s, temp); 
            }
           if(jsonStr.indexOf("brightness") > 0) {
             int8_t temp = doc["brightness"].as<int8_t>();
             s->set_brightness(s, temp); 
            }
           if(jsonStr.indexOf("contrast") > 0) {
             int8_t temp = doc["contrast"].as<int8_t>();
             s->set_contrast(s, temp); 
            }
           if(jsonStr.indexOf("saturation") > 0) {
             int8_t temp = doc["saturation"].as<int8_t>();
             s->set_saturation(s, temp); 
            }
           if(jsonStr.indexOf("sharpness") > 0) {
             int8_t temp = doc["sharpness"].as<int8_t>();
             s->set_sharpness(s, temp); 
            }            
           if(jsonStr.indexOf("vflip") > 0) {
             int8_t temp = doc["vflip"].as<int8_t>();
             s->set_vflip(s, temp); 
            } 
           if(jsonStr.indexOf("hmirror") > 0) {
             s->set_hmirror(s, doc["hmirror"].as<int8_t>() );  
            }           
           if(jsonStr.indexOf("agc_gain") > 0) {
             s->set_agc_gain(s, doc["agc_gain"].as<int8_t>() ); 
            } 
           if(jsonStr.indexOf("gainceiling") > 0) {
             s->set_gainceiling(s, doc["gainceiling"].as<gainceiling_t>() );  
            }           
      
       }
            return true;
           } else {
              Serial.print(F("deserializeJson() failed with code "));
              Serial.println(error.c_str());
            return false;
           }
     }
  }  
}

void setFsize(int x) 
{
 
 // valid    FRAMESIZE_ + QVGA|CIF|VGA|SVGA|XGA|SXGA|UXGA
     sensor_t * s = esp_camera_sensor_get();
     int res = 0;
     Serial.println("pointer retrieved");
           switch (x) {
                     case 0: 
                        s->set_framesize(s, FRAMESIZE_QVGA); // CIF
                        Serial.println("set to QVGA");
                        break;
                      case 1:
                        s->set_framesize(s, FRAMESIZE_CIF); // VGA
                        Serial.println("set to CIF"); // saved 8
                        break;
                      case 2:
                        s->set_framesize(s, FRAMESIZE_VGA); // XGA
                         Serial.println("set to VGA"); // saved 8
                        break; 
                      case 3: 
                        s->set_framesize(s, FRAMESIZE_SVGA); // sxga
                         Serial.println("set to SVGA"); // saved 9
                        break;
                      case 4:
                        s->set_framesize(s, FRAMESIZE_XGA); // uxga 
                         Serial.println("set to XGA"); // saved 10
                        break;
//                       case 5:
//                        s->set_framesize(s, FRAMESIZE_SXGA); 
//                         Serial.println("set to SXGA");
//                        break;   
//                      case 6: 
//                        s->set_framesize(s, FRAMESIZE_UXGA);
//                         Serial.println("set to UXGA");
//                        break;
//                      case 7:
//                        s->set_framesize(s, FRAMESIZE_SXGA);
//                         Serial.println("set to SXGA");
//                        break;
//                       case 8:
//                        s->set_framesize(s, FRAMESIZE_UXGA);
//                         Serial.println("set to UXGA");
//                        break; 
                     }
                        res = s->status.framesize;
                        Serial.println("res = " + String(res)); //8
}                    
