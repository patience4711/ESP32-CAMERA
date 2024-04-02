bool mqttConnect() {   // 
/* this function checks if we are connected to the broker, if not connect anyway */  
    if( MQTT_Client.connected() ) {
    DebugPrintln("mqtt was connected");
    return true;
    }
    // we are here because w'r not connected. Signal with the LED
    ledblink(2,70);

    if (Mqtt_Port[0] == '\0' ) strcpy(Mqtt_Port, "1883");   // just in case ....
    uint8_t retry = 3;
    
    //char Mqtt_inTopic[11]={"ESP-ECU/in"};

    while (!MQTT_Client.connected()) {

      if ( MQTT_Client.connect( Mqtt_Clientid, Mqtt_Username, Mqtt_Password) )
      {
         //connected, so subscribe to inTopic (not for thingspeak)
        if(Mqtt_Format != 5 ) {
        if(  MQTT_Client.subscribe ( "ESP32-CAM/in" ) ) {
               DebugPrintln("subscribed to ESP32-CAM/in");
           }
        }
         Serial.println(F("mqtt connected"));
         
      
       return true;

    } else {
        if (!--retry) break; // stop when tried 3 times
        delay(500);
    }
  }
  // if we are here , no connection was made.

  Serial.println(F("mqtt connection failed"));
  return false;
}

// *************************************************************************
//                   process received mqtt
// *************************************************************************

void MQTT_Receive_Callback(char *topic, byte *payload, unsigned int length)
{
   
//    String Payload = "";     // convert the payload to a String...
//    for (int i = 0; i < length; i++)
//    {
//        Payload += (char)payload[i]; // convert to char, needed???
//    }
    
   // ws.textAll("mqtt received " + Payload);

    StaticJsonDocument<1024> doc;       // We use json library to parse the payload                         
   //  The function deserializeJson() parses a JSON input and puts the result in a JsonDocument.
   // DeserializationError error = deserializeJson(doc, Payload); // Deserialize the JSON document
    DeserializationError error = deserializeJson(doc, payload); // Deserialize the JSON document
    if (error)            // Test if parsing succeeds.
    {
       Serial.println("mqtt no valid json ");
        return;
    } 
    
    // We check the kind of command format received with MQTT
    //now we have a payload like {"poll",1}    

    if( doc.containsKey("poll") )
    {
        int inv = doc["poll"].as<int>(); 
        Serial.println( "got message {\"poll\":" + String(inv) + "}" );

    }
}
