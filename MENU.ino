 const char BASISCONFIG[] = R"=====(
<!DOCTYPE html><html><head><meta charset='utf-8' name="viewport" content="width=device-width, initial-scale=1"><title>ESP32 CAM</title>
<link rel="stylesheet" type="text/css" href="/STYLESHEET">  
<link rel="icon" type="image/x-icon" href="/favicon.ico"  />
</head><body> 
<script type='text/javascript'>
function showSubmit() {
document.getElementById("submitknop").style.display = "block";
}
</script>
<div id='msect'><center><h2>HAIPS</h2>
<ul>
<li><a href='/'>home</a></li>
<li><a href='{ctrl}' '>camera</a></li>
<li><a href='/IPCONFIG'>ip conf</a></li>

</ul>
<div class='divstijl'><center>
<br><br>
<form method='get' action='basisconfig' oninput='showSubmit();'><table>

<tr><td style='width:120px;'>name<td><input class='inp6' name='swname' length='21' placeholder='naam schakelaar' value='{nm}'></input><td></tr>
<tr><td>user passwd<td><input  class='inp5' name='pw1' length='11' placeholder='max. 10 tekens' value='{pw1}' pattern='.{4,10}' title='tussen 4 en 10 karakters'></input> 
</td></tr>
</table>
<br><br>
</div><br>
<ul ><div id="submitknop" style='display:none;'>
<li><button class='sub' type='submit'>save settings</button></li></div></form>
<li><a onclick="return confirm('are you sure to start AP?')" href='/STARTAP'>start ap</a></li>
<li><a onclick="return confirm('are you sure to reboot?')"href='/REBOOT'>reboot</a></li>
<br></div></body></html>
)=====";

void zendPageBasis() {

    toSend = FPSTR(BASISCONFIG);
    toSend.replace("HAIPS" , String(swName));
    IPAddress ip = WiFi.localIP();
    String adres = String(ip[0]) + "." + String(ip[1]) + "." + String(ip[2]) + "." + String(ip[3]);
    String controllink = "http://" + adres + ":90";
    toSend.replace("{ctrl}", controllink);   

    // replace form data
    toSend.replace("'{nm}'" , "'" + String(swName) + "'") ;
    toSend.replace( "'{pw1}'" , "'" + String(userpswd) + "'") ;
    
}

void handleBasisconfig(AsyncWebServerRequest *request) { // form action = handleConfigsave
// verzamelen van de serverargumenten   
   strcpy(swName, request->getParam("swname")->value().c_str());
   strcpy(userpswd, request->getParam("pw1")->value().c_str());

   if (swName[0] == '\0') {
     String s = "ESP01 " + String(getChipId());
     s.toCharArray(swName, 21);
   }

   
  DebugPrintln("we gaan een nieuwe webpage inlezen in toSend");

  //toSend = FPSTR(CONFIRM);
  basisConfigsave();  // alles opslaan
  request->send_P(200, "text/html", CONFIRM); //send the html code to the client
 
  DebugPrintln("basisconfig saved");
  signalFlag=12; // zorgt voor de reboot 
}
