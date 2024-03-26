// ************************************************************************************
// *                        START wifi and webserver
// ************************************************************************************
void start_wifi() {
 //Serial.println("start wifi 1");
 WiFi.softAPdisconnect(true);

 WiFi.mode(WIFI_STA); // geen ap op dit moment 
//Serial.println("start wifi 2");
 delay(1000);
//Serial.println("start wifi 3");
 if (swName[0] == '/') {
   WiFi.setHostname(getChipId().c_str()); 
 } else { 
   WiFi.setHostname(swName);
}
Serial.println("start wifi 4");
// we gaan 10 pogingen doen om te verbinden
// met de laatst gebruikte credentials
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print("*");
     WiFi.begin();
     event+=1;
     if (event==10) {break;}
  }
// als het verbinden is mislukt gaan we naar het configportal  
  if (event>9) {
     event=0;
     Serial.println("\nWARNING connection failed");
    
     start_portal(); // stel het portal in
     } else {
  Serial.println("\nconnection success, ip = ");
  Serial.println(WiFi.localIP());
     }

Serial.println("number of connection attempts " + String(event) );
event=0; // we kunnen door naar de rest
checkFixed();


  start_server();
}
// *************************************************************************
//                      SERVER STARTEN
//**************************************************************************
 void start_server() {

asyserver.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("homepage requested");    
    if (!request->authenticate("admin", pswd) && !request->authenticate("user", userpswd)) return request->requestAuthentication();
    
    toSend = FPSTR(HTML_HOMEPAGE);
    if(!camera_active) toSend.replace("<p>the camera has started","<p style='color:red;'>WARNING: camera not started!"); 
    toSend.replace( "HAIPS", String(swName) ); // we moeten {strm} vervangen door http://ip:81/stream
    // put local ip in a string
    IPAddress ip = WiFi.localIP();
    String adres = String(ip[0]) + "." + String(ip[1]) + "." + String(ip[2]) + "." + String(ip[3]);
    String streamlink = "http://" + adres + ":91/stream";
    toSend.replace("{strm}", streamlink);
    Serial.println("streamlink = " + streamlink);
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
  signalFlag=12;
  });

asyserver.on("/STARTAP", HTTP_GET, [](AsyncWebServerRequest *request) {
    loginAdmin(request);    
    DebugPrintln("We gaan de gegevens wissen");
    String teZenden = F("<!DOCTYPE html><html><head><script type='text/javascript'>setTimeout(function(){ window.location.href='/SW=BACK'; }, 3000 ); </script>");
    teZenden += F("</head><body><h2>OK het accesspoint wordt opgestart.</h2>Wacht tot de led brandt.<br><br>Ga dan naar wifi-instellingen op uw apparaat en verbind met ESP-");
    teZenden += getChipId() + " !";
    request->send(200, "text/html", teZenden);
     signalFlag=11;
  });
asyserver.on("/STYLESHEET", HTTP_GET, [](AsyncWebServerRequest *request) {
  //Serial.println("stylesheet requested");
   request->send_P(200, "text/css", STYLESHEET);
});

asyserver.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest *request) {
  Serial.println("favicon requested");
  AsyncWebServerResponse *response = request->beginResponse_P(200, "image/x-icon", FAVICON, FAVICON_len);
  request->send(response);
});

asyserver.on("/BASISCONFIG", HTTP_GET, [](AsyncWebServerRequest *request) {
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

//asyserver.on("/IPconfig", HTTP_GET, [](AsyncWebServerRequest *request) {
//    if (!request->authenticate("admin", pswd)) return request->requestAuthentication();
//    strcpy( static_ip2, request->getParam("ip")->value().c_str() );
//    handleIPconfig(*request); //argumenten ophalen en opslaan
//    request->send(200, "text/html", toSend);
//  });   

set_ipUtils(); // set the asyserver.on for ipconfiguration


  
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
  
  // ********************************************************************
//             controleer if er een static ip moet komen
// ********************************************************************
void checkFixed() {
  // we komen hier alleen als we zijn verbonden
    // we gaan GATE_WAY van een waarde voorzien, die is niet opgeslagen in SPIFFS
    char GATE_WAY[16]="";
    IPAddress gat=WiFi.gatewayIP();
    sprintf(GATE_WAY, "%d.%d.%d.%d", gat[0], gat[1], gat[2], gat[3]);
    DebugPrint("GATE_WAY in checkFixed = nu: "); DebugPrintln(String(GATE_WAY));
    DebugPrint("static_ip in checkFixed = nu: "); DebugPrintln(String(static_ip));

    if (static_ip[0] != '\0' && static_ip[0] != '0') {
      DebugPrintln("we need a static ip, Custom STA IP/GW/Subnet");
      IPAddress _ip,_gw,_sn(255,255,255,0); // declaratie 
      _ip.fromString(static_ip);
      _gw.fromString(GATE_WAY);//  if (ssid != "") {
      WiFi.config(_ip, _gw, _sn);
      DebugPrintln(WiFi.localIP());
  } 

}
