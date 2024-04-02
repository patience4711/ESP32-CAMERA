// *************************************************************************
//                      SERVER STARTEN
//**************************************************************************
 void start_server() {

asyserver.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("homepage requested");    
    if (!request->authenticate("admin", pswd) && !request->authenticate("user", userpswd)) return request->requestAuthentication();
    
    toSend = FPSTR(HTML_HOMEPAGE);
    if(!camera_active) toSend.replace("camera started","camera not started ! !"); 

    
    toSend.replace( "HAIPS", String(swName) ); // we must replace {strm} by http://ip:81/stream
    // put local ip in a string
    IPAddress ip = WiFi.localIP();
    String adres = String(ip[0]) + "." + String(ip[1]) + "." + String(ip[2]) + "." + String(ip[3]);
    String streamlink = "http://" + adres + ":91/stream";
    toSend.replace("{strm}", streamlink);
    Serial.println("streamlink = " + streamlink);
    if(rotate) toSend.replace("0123", "3210");
    
    request->send(200, "text/html", toSend);
});

asyserver.on("STREAM", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("stream requested");    
    if (!request->authenticate("admin", pswd) && !request->authenticate("user", userpswd)) return request->requestAuthentication();
    // put local ip in a string
    IPAddress ip = WiFi.localIP();
    String adres = String(ip[0]) + "." + String(ip[1]) + "." + String(ip[2]) + "." + String(ip[3]);
    String streamlink = "http://" + adres + ":91/stream";
    request->redirect(streamlink);
});


asyserver.on("/saveCS", HTTP_GET, [](AsyncWebServerRequest *request) {
Serial.println("settings save requested");    
cameraConfigsave();
String toSend=FPSTR(CONFIRM);
request->send(200, "text/html", toSend);
  });

asyserver.on("/REBOOT", HTTP_GET, [](AsyncWebServerRequest *request) {
Serial.println("reboot requested");    
  loginAdmin(request);
  request->send_P(200, "text/html", CONFIRM);
  actionFlag=12;
  });

asyserver.on("/STARTAP", HTTP_GET, [](AsyncWebServerRequest *request) {
    loginAdmin(request);    
    DebugPrintln("We are going to wipe the wifi settings");
    String teZenden = F("<!DOCTYPE html><html><head><script type='text/javascript'>setTimeout(function(){ window.location.href='/SW=BACK'; }, 3000 ); </script>");
    teZenden += F("</head><body><center><h2>OK the accesspoint is started.</h2>Wait until the led is on.<br><br>Then go to the wifisettings on your device and connect to ESP-");
    teZenden += getChipId() + " !";
    request->send(200, "text/html", teZenden);
     actionFlag=11;
  });
asyserver.on("/STYLESHEET", HTTP_GET, [](AsyncWebServerRequest *request) {
  //Serial.println("stylesheet requested");
   request->send_P(200, "text/css", STYLESHEET);
});

asyserver.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest *request) {
  //Serial.println("favicon requested");
  AsyncWebServerResponse *response = request->beginResponse_P(200, "image/x-icon", FAVICON, FAVICON_len);
  request->send(response);
});

asyserver.on("/MENU", HTTP_GET, [](AsyncWebServerRequest *request) {
    loginAdmin(request);
    zendPageBasis();
    request->send(200, "text/html", toSend);
});

asyserver.on("/basisconfig", HTTP_GET, [](AsyncWebServerRequest *request) {
handleBasisconfig(request);
// no response needed. reboot
});

asyserver.on("/IPCONFIG", HTTP_GET, [](AsyncWebServerRequest *request) {
    loginAdmin(request);
    zendPageIPconfig();
    request->send(200, "text/html", toSend);
  });

set_ipUtils(); // set the asyserver.on for ipconfiguration

asyserver.on("/MQTT", HTTP_GET, [](AsyncWebServerRequest *request) {
  //if(checkRemote( request->client()->remoteIP().toString()) ) request->redirect( "/DENIED" );
  loginAdmin(request);
  //requestUrl = request->url();
  strcpy( requestUrl, request->url().c_str() );
  zendPageMQTTconfig(request);
  //request->send(200, "text/html", toSend);
});

asyserver.on("/MQTTconfig", HTTP_GET, [](AsyncWebServerRequest *request) {
  handleMQTTconfig(request);
  request->redirect( String(requestUrl) );
});
asyserver.on("/MQTT_TEST", HTTP_GET, [](AsyncWebServerRequest *request) {
loginAdmin(request);

String toMQTT = "{\"test\":\"hello from ESP32-CAM\"}";
MQTT_Client.publish ( Mqtt_outTopic, toMQTT.c_str(), true );
toSend = "sent mqtt message : " + toMQTT;
request->send( 200, "text/plain", toSend  );
});  

asyserver.on("/PHOTO", HTTP_GET, [](AsyncWebServerRequest *request) {
   // Serial.println("stream requested");    
    if (!request->authenticate("admin", pswd) && !request->authenticate("user", userpswd)) return request->requestAuthentication();
    request->send_P(200, "text/html", HTML_CAPTURE);
});
asyserver.on("/capture", HTTP_GET, [](AsyncWebServerRequest * request) {
  takeNewPhoto = true;
  request->send_P(200, "text/plain", "Taking Photo");
});  
asyserver.on("/saved-photo", HTTP_GET, [](AsyncWebServerRequest * request) {
  request->send(SPIFFS, FILE_PHOTO, "image/jpg", false);
});  

  DebugPrintln("async HTTP server started");
   asyserver.begin(); 
   //portalserver.begin();
}

////  *******************************************************************
////               M A I N  S E R V E R  H A N D L E S
//// ********************************************************************
void loginAdmin(AsyncWebServerRequest *request) {
  String authFailResponse = "<h2>login failed <a href='/'>click here</a></h2>";
  const char* www_realm = "login as administrator."; 
    if (!request->authenticate("admin", pswd)) return request->requestAuthentication();
}  
 
