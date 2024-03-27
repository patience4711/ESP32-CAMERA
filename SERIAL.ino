void handle_Serial () {
Serial.println("we are in handle serial");  
int SerialInByteCounter = 0;
char InputBuffer_Serial[100] = "";
byte SerialInByte;  

if(Serial.available() < 13 ) return; //buffer must be at least 13
delay(100); //we wait a little for more data
// Serial.println("incoming bytes available, number = " + String(Serial.available()) );

 while(Serial.available()) {
             SerialInByte=Serial.read(); 
             //Serial.print("+");
            
            if(isprint(SerialInByte)) {
              if(SerialInByteCounter<100) InputBuffer_Serial[SerialInByteCounter++]=SerialInByte;
            }    
            if(SerialInByte=='\n') {                                              // new line character
              InputBuffer_Serial[SerialInByteCounter]=0;
  //            Serial.println(F("found new line"));
             break; // serieel data is complete
            }
       }   
Serial.println("InputBuffer_Serial = " + String(InputBuffer_Serial) );
// evaluate the incomming data

        // -------------------------------------------------------
        // Handle Device Management Commands
        // -------------------------------------------------------
        
        if (strcasecmp(InputBuffer_Serial, "PRINTOUT-SPIFFS") == 0) {
          File root = SPIFFS.open("/");
          File file = root.openNextFile();
          int total = 0;
          while(file){
             //Serial.print("FILE: ");
             //Serial.println(file.name());
             //Serial.println(file.size());
             total += file.size();
             Serial.println("File: " + String(file.name()) + " size: " + String(file.size()) ); 
             
             file = root.openNextFile();
          }
          Serial.println("total SPIFFS = " + String(total));
          return;
        
        
        } else
        if (strcasecmp(InputBuffer_Serial,"DEVICE-REBOOT")==0) {
          Serial.println("\ngoing to reboot ! \n");
           delay(1000);
           ESP.restart();
            
        } else
        if (strncasecmp(InputBuffer_Serial, "WIFI",4)==0) {
           //sprintf(InputBuffer_Serial,"20;RESET OK;");
           //Serial.println(InputBuffer_Serial);
           
           String credent = InputBuffer_Serial;
           //Serial.println("string credent = " + credent);
           credent = credent.substring(5); // WIFI;
           Serial.println("string credentials cleaned = " + credent);
           int pos1 = credent.indexOf(';');
           int pos2 = credent.lastIndexOf(';');
           String sid = credent.substring(0,pos1);
           Serial.println("string sid = " + sid);
           String pw = credent.substring(pos1+1,pos2);
           Serial.println("string pw = " + pw);                     
           int sid_len = sid.length() + 1;
           char APID[sid_len];
           sid.toCharArray(APID, sid_len);
           int pw_len = pw.length() + 1;
           char PASS[pw_len];
           pw.toCharArray(PASS, pw_len);                     
           WiFi.begin(APID, PASS);
          
           while (WiFi.status() != WL_CONNECTED) {
              delay(500);
              Serial.print("* ");
              WiFi.begin();
              event += 1;
              if(event>10) break;
            }
            event=0;  //reset event
            if(WiFi.status() == WL_CONNECTED) {
            Serial.print("WiFi connected, ip = ");
            Serial.println(WiFi.localIP());
            Serial.println("\ntype DEVICE-REBOOT; to reboot");  
            } else {
            Serial.println("connection failed, try again\n");
            }
            return;
        } else

     // **************   admin password   *****************************
     if (strncasecmp(InputBuffer_Serial,"SET-ADMINPW", 11 ) == 0 ) {
         Serial.println("found SET-ADMINPW");
         String passwd = InputBuffer_Serial;
         passwd = passwd.substring(12); // SET-ADMINPW;
         passwd.toCharArray(pswd, passwd.length()+1);
         Serial.printf("\npasswd = \"%s\", is saved! " , String(pswd));
         
         //Serial.println("\nsaving the password");
         wifiConfigsave(); //  save it in SPIFFS
         return;
      } else
        
        if (strcasecmp(InputBuffer_Serial,"LIST-COMMANDS") == 0) {
            Serial.println("*** AVAILABLE COMMANDS ***"); 
            Serial.println("WIFI;SSID;PASSWORD; (connect to wifi)");
            Serial.println("SET-ADMINPW;PASSWORD (set admin password)");
            Serial.println("DEVICE-REBOOT; (restart the device)");
            Serial.println("PRINTOUT-SPIFFS; (show filesystem)");
            return;
        } else {
             sprintf(InputBuffer_Serial, "CMD UNKNOWN;"); // 
             Serial.println( InputBuffer_Serial );
        }

}

String readSerial() {
    while(Serial.available() == 0) { } 
    String rec = Serial.readString();
    //Serial.println("\nyou entered " + rec);
    Serial.println("\nentered " + rec + " len=" + String(rec.length()) );
    return rec;
}               
