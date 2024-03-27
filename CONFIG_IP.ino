
const char IPCONFIG[] PROGMEM = R"=====(
<!DOCTYPE html><html><head><meta charset='utf-8' name="viewport" content="width=device-width, initial-scale=1"><title>HANSIART ESP32 CAM</title>
<link rel="stylesheet" type="text/css" href="/STYLESHEET">  
<link rel="icon" type="image/x-icon" href="/favicon.ico"  />
</head>
<body><div id='msect'><center>
<div id='helpdiv' style='background-color: #ffffff; border: solid 2px; display:none;'>
<span class='close' onclick='sluiten();'>&times;</span><h3>IP ADRES HELP</h3>
<b>STATIC IP:</b><br>You can configure a static ip. 
This is usually not required because the router always hands out the same ip address to a certain device.
<br><br>
<b>DHCP IP:</b><br> the router determines the IP address.<br><br>
<b>IP address:</b><br>
This must be derived from the router's IP address. The last digits are a number from 2 to 255.<br>
For instance ip address router is 192.168.2.1, <br>a correct static ip is <br>192.168.2.<span style='color:red;'>2 t/m 254</span>
<br><br>
If you set a DHCP IP address, a correct IP must be entered, or leave this field empty.<br>
The data cannot be saved if the IP address is incorrect.
<br><br>
</div>
<script type="text/javascript">
function helpfunctie() {
document.getElementById("helpdiv").style.display = "block";
}
function sluiten() {  
document.getElementById("helpdiv").style.display = "none";
}
function showSubmit() {
document.getElementById("submitknop").style.display = "block";
}
function submitFunction() {
document.getElementById("formulier").submit(); 
}
</script>
<h2>IP ADDRESS SETTINGS</h2>

<div class='divstijl'><center>
<form id='formulier' method='get' action='IPconfig' oninput='showSubmit();'>
<table><tr><td style='width:140px;'>IP configuration<td>
<select name='keuze' class='sb1'>
<option value="DHCP" option1>DHCP IP</option>
<option value="STAT" option2>STATIC IP</option>
</select>
</td></table>

<div><table>
<tr><td style='width:145px;'>IP address<td>
<input class='inp5' name='ip' placeholder='leeg = DHCP' value='{ip}' pattern = '^\b({patroon})([0-9]{1,2}|1[0-9]{2}|2[0-4][0-9]|25[0-5])$' title='must be derived from ip router'>
</input></tr>
<tr><td>IP address router<td>
<input class='inp5' name='gw' value='{gw}' readonly></input></tr>
<tr><td>subnet mask<td>
<input class='inp5' name='sn' value='{sn}' readonly></input></tr>
</table>

<p>NOTE: a fixed IP has to be correct, or empty.</p>
</div>
</div><br><ul style='width:420px;'><div id="submitknop" style='display:none;'>
<li style='background:red;'><a href='#' onclick='submitFunction()'>save data</a></li></div></form>
<li><a href='#' onclick='helpfunctie()'>help</a>
<li><a href='/'>close (no save)</a></ul>
<br></div></body></html>
)=====";

void zendPageIPconfig() {
   DebugPrintln("we zijn nu op zendPageIPconfig");

toSend = FPSTR(IPCONFIG);  

// we gaan kijken of we een static hebben, zoja zetten we de select goed en lezen de ip argumenten
if ( static_ip[0] == '\0' || static_ip[0] == '0' ) {
  DebugPrint("static_ip = "); DebugPrintln(String(static_ip));
  DebugPrintln("no static ip");
  toSend.replace("option}" , "selected" );
  //als we de pagina verstoppen worden er geen gegevens teruggezet, deze worden dus als leeg opgeslagen 
  } else {
// we hebben een static ip dus 
  DebugPrint("static_ip = "); DebugPrintln(String(static_ip));
  DebugPrintln("there is a static ip");   
  toSend.replace("option2" , "selected" );

  }
  //altijd de ip gegevens terugzetten
    toSend.replace("{ip}" , String(static_ip) );
    toSend.replace("{gw}" , WiFi.gatewayIP().toString().c_str() );
    toSend.replace("{sn}" , WiFi.subnetMask().toString().c_str() );
 
    // we gaan de regex voor static ip samenstellen en aanpassen
//     String GateWay=WiFi.gatewayIP().toString().c_str();
     //String GateWay = 'GATE_WAY' + "";
     String GateWay = WiFi.gatewayIP().toString();
     DebugPrint("gateway in ipconfig = "); DebugPrintln(GateWay);
     int punt1 = GateWay.indexOf('.');
     int punt2 = GateWay.indexOf('.', punt1+1);
     int punt3 = GateWay.indexOf('.', punt2+1);
     String deel_a=GateWay.substring(0, punt3+1);
    //Serial.print("deel_a = "); Serial.println(deel_a);
    //st3l de regex samen als afgeleid van gateway 
    String patroon="(";
    patroon += deel_a;
    patroon += ")([0-9]{1,2}|1[0-9]{2}|2[0-4][0-9]|25[0-5])";
    //Serial.print("patroon = "); Serial.print(patroon);
    toSend.replace("{patroon}" , patroon);
    // de melding bij verkeerd invullen
    deel_a += "x";
    toSend.replace("{title}" , deel_a);  
  
//server.send(200, "text/html", toSend); //send the html code to the client
//delay(500);  //wait half a second after sending the data 
}


void set_ipUtils() {
asyserver.on("/IPconfig", HTTP_GET, [](AsyncWebServerRequest *request) {

char static_ip2[16] = "";

IPAddress ipc = WiFi.gatewayIP();
String gwcheck = String(ipc[0]) + "." + String(ipc[1]) + "." + String(ipc[2]);
Serial.println("\ngwcheck = " + gwcheck );
  // almost impossible to enter an invalid ip.
  // collect the server args
strcpy( static_ip2, request->getParam("ip")->value().c_str() );
String ipcheck = String(static_ip2[0]) + "." + String(static_ip2[1]) + "." + String(static_ip2[2]);   
Serial.println("\ipcheck = " + ipcheck );
  
  String adres="";
  String zin="";
  bool reBoot = false;
  bool leegmaken = false;

// we gaan nu kijken of dhcp is gekozen. zo ja, static_ip2 leegmaken
String optie = request->getParam("keuze")->value();
//String optie = server.arg("keuze");
if ( optie == "DHCP") {
    DebugPrint("dhcp set, get rid of static_ip, optie = ");
    DebugPrintln(optie);
    static_ip2[0] = '\0';
  }

  // we now need to check if the IP has changed, this will affect the confirm page
  // with dhcp static_ip is cleared so this is always true.
  // how do we do this ?
  // We have the variable static_ip, which we compare with the specified value
  // we may have made this null with the selectbox
  // If not equal then the value has changed 
     String test1=String(static_ip);  
     String test2=String(static_ip2);
        DebugPrint("de teststrings zijn: ");
        DebugPrintln(test1);
        DebugPrintln(test2);        

     if (String(static_ip) != String(static_ip2) ) {
       DebugPrintln("het IP is veranderd");
      //static_ip=static_ip2;
      strcpy(static_ip, static_ip2);

        // als er een ip is opgegeven dan zetten we de ip gevens in de confirmpage
      if (static_ip[0] != '\0' && static_ip[0] != '0') {
           signalFlag = 12; // make it reboot in the loop
           adres = String(static_ip);
           DebugPrint("the specified ip = "); DebugPrintln(adres);
           zin = F("The specified IP is <strong><a href='http://{adres1}'>http://{adres2}</a></strong>");
           zin += F("<br>Type the new IP adres in de addressbar of your browser or click the link.<br>");
           zin += F("<br>This page closes automatically after a few seconds..<br><br><br></div><br><br> <a class='bt rad' href='/'>OK</a>");
           zin.replace("{adres1}" , adres);
           zin.replace("{adres2}" , adres);
           
          } else {
          // if no ip is specified we try to connect at once 
           zin="IP not specified, this is unknown now !!<br><br>NOTE: the configuration modus (AP) is started<br>The led is lighted up. Connect to the AP<br>so you can find out the DHCP ip address.<br><br>You can close this page.<br><br></div>";
           adres ="/";   
           signalFlag = 11; // reboot to AP
          }
    
      // now we show the confirm page confirmpage tonen

      toSend = FPSTR(CONFIRM_IP);
      toSend.replace("{adres0}" , adres);
      toSend.replace("{zin}" , zin);
      DebugPrintln("IPconfig saved");
      wifiConfigsave();
  
     }
     Serial.println("set signalFlag to " + String(signalFlag) );
     request->send(200, "text/html", toSend);
  });
}
