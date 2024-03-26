void handle_Serial () {
Serial.println("we are in handle serial");  
int SerialInByteCounter = 0;
char InputBuffer_Serial[100] = "";
byte SerialInByte;  
 Serial.println("incoming bytes available, number = " + String(Serial.available()) );

 while(Serial.available()) {
             SerialInByte=Serial.read(); 
             //Serial.print("+");
            
            if(isprint(SerialInByte)) {
              if(SerialInByteCounter<100) InputBuffer_Serial[SerialInByteCounter++]=SerialInByte;
            }    
            if(SerialInByte=='\n') {                                              // new line character
              InputBuffer_Serial[SerialInByteCounter]=0;
              Serial.println(F("found new line"));
             break; // serieel data is complete
            }
       }   
Serial.println("InputBuffer_Serial = " + String(InputBuffer_Serial) );
// evaluate the incomming data
          if (strlen(InputBuffer_Serial) > 3){                                // need to see minimal 8 characters on the serial port
                               // Command from Master to RFLink

                  // -------------------------------------------------------
                  // Handle Device Management Commands
                  // -------------------------------------------------------
                  
                  if (strcasecmp(InputBuffer_Serial, "CAMSET") == 0) {
                     Serial.println("\provide a number 1 - 10");
                       int x = readSerial().toInt();
                       setFsize(x);
                   return;
                  
                  } else
                  if (strcasecmp(InputBuffer_Serial,"REBOOT")==0) {
                    Serial.println("\ngoing to reboot ! \n");
                     delay(1000);
                     ESP.restart();
                      
                  } else
                  if (strcasecmp(InputBuffer_Serial+3, "WIFI")==0) {
                     //sprintf(InputBuffer_Serial,"20;RESET OK;");
                     //Serial.println(InputBuffer_Serial);
                     
                     String credent = InputBuffer_Serial;
                     //Serial.println("string credent = " + credent);
                     credent = credent.substring(8);
                     //Serial.println("string credentials cleaned = " + credent);
                     int pos1 = credent.indexOf(';');
                     int pos2 = credent.lastIndexOf(';');
                     String sid = credent.substring(0,pos1);
                     //Serial.println("string sid = " + sid);
                     String pw = credent.substring(pos1+1,pos2);
                     //Serial.println("string pw = " + pw);                     
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
                      Serial.println("\ntype 10;REBOOT; to reboot");  
                      } else {
                      Serial.println("connection failed, try again\n");
                      }
                      return;
                  } else
                  if (strcasecmp(InputBuffer_Serial,"LIST") == 0) {
                      Serial.println("*** AVAILABLE COMMANDS ***"); 
                      Serial.println("10;WIFIRESET; (wipe wifi credentials)");
                      Serial.println("10;WIFI;SSID;PASSWORD; (connect  to wifi)");
                      Serial.println("10;IPCONFIG;ipadres (eg 192.168.3.123)");
                      Serial.println("10;REBOOT; (restart the device)");
                      return;
                  } else {
                       sprintf(InputBuffer_Serial, "20;CMD UNKNOWN;"); // Node and packet number 
                       Serial.println( InputBuffer_Serial );
                  }
           
       }// end if strlen 
}
String readSerial() {
    while(Serial.available() == 0) { } 
    String rec = Serial.readString();
    //Serial.println("\nyou entered " + rec);
    Serial.println("\nentered " + rec + " len=" + String(rec.length()) );
    return rec;
}               
