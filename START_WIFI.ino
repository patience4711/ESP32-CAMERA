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
