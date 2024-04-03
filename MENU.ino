 const char MENU[] = R"=====(
<body> 
<script> function cl() { window.location.href='/'; } </script>
<div id='msect'><center><div id='bo'></div><h2>HAIPS</h2>
<ul>
<li id='fright'><span class='close' onclick='cl();'>&times;</span>
<li><a href='{ctrl}' '>camera</a></li>
<li><a href='/PHOTO' '>photo</a></li>
<li><a href='/MQTT'>mqtt</a></li>
</ul>
<div id='divstijl'><center>
<br><br>
<form id='formulier' method='get' action='basisconfig' oninput='showSubmit();'><table>

<tr><td style='width:120px;'>name<td><input class='inp6' name='swname' placeholder='naam camera' value='{nm}'></input><td></tr>
<tr><td>user passwd<td><input  class='inp5' name='pw1' placeholder='max. 10 tekens' value='{pw1}' pattern='.{4,10}' title='tussen 4 en 10 karakters'></input> 
<tr><td>doorbell ?<td><input type='checkbox' style='width:30px; height:30px;' name='dBell' #sjaak></input></td></tr>
<tr><td>view rotate ?<td><input type='checkbox' style='width:30px; height:30px;' name='rot' #sjook></input></td></tr>
</td></tr>
</table></form>
<br><br>
</div><br>
<ul>
<li id='sub'><a href='#' onclick='submitFunction("/")'>save</a></li>
<li><a href='/IPCONFIG'>ip conf</a></li>
<li><a onclick="return confirm('are you sure to start AP?')" href='/STARTAP'>start ap</a></li>
<li><a onclick="return confirm('are you sure to reboot?')"href='/REBOOT'>reboot</a></li>
<br></div></body></html>
)=====";

void zendPageBasis() {
    toSend = FPSTR(HTML_HEAD);
    toSend += FPSTR(MENU);
    toSend.replace("HAIPS" , String(swName));
    IPAddress ip = WiFi.localIP();
    String adres = String(ip[0]) + "." + String(ip[1]) + "." + String(ip[2]) + "." + String(ip[3]);
    String controllink = "http://" + adres + ":90";
    toSend.replace("{ctrl}", controllink); // for the camerea settings page  

    // replace form data
    toSend.replace("'{nm}'" , "'" + String(swName) + "'") ;
    toSend.replace( "'{pw1}'" , "'" + String(userpswd) + "'") ;
     if (doorBell) { 
      toSend.replace("#sjaak", "checked");
    }
     if (rotate) { 
      toSend.replace("#sjook", "checked");
    }
}   


void handleBasisconfig(AsyncWebServerRequest *request) { // form action = handleConfigsave
// verzamelen van de serverargumenten   
   strcpy(swName, request->getParam("swname")->value().c_str());
   strcpy(userpswd, request->getParam("pw1")->value().c_str());

   if (swName[0] == '\0') {
     String s = "ESP01 " + String(getChipId());
     s.toCharArray(swName, 21);
   }
  //BEWARE CHECKBOX
  // the problem is that there is no param when not checked
  // so whe there is a param the box is checked
  if(request->hasParam("dBell") ) { doorBell = true; } else { doorBell = false;};
  if(request->hasParam("rot") ) { rotate = true; } else { rotate = false;};
   
  basisConfigsave();  // alles opslaan
  //request->send_P(200, "text/html", CONFIRM); //send the html code to the client
 
  //DebugPrintln("basisconfig saved");
  //actionFlag=12; // causes reboot, needed?
}
