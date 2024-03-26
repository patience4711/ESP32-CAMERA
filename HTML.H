const char STYLESHEET[] = R"=====(

body {
  background: linear-gradient(#e8f5f7, #caf5fb); 
  color:navy;
  font-family:'lato',Verdana,Sans-serif;
  font-size:16px;
  }
#divstijl { background: linear-gradient(#e8edc8, #c8eaed); padding:0px 0px 0px 0px; width: 96%; height: 99%; }
#msect { display: flex; flex-basis: 100%; align-items: center; margin: 0px 0px; width:96vw;}
#msect:before, #msect:after { content: ""; flex-grow: 1;  margin: 0px 0px;}
p {
  color: #006600;
  font-family: 'lato',Verdana,Sans-serif;
  font-size:14px;
  }
.bt{
  display:block;
  width:150px;
  height:60px;
  padding:6px;
  margin:6px;
  text-align:center;
  border-radius:6px;
  color:white;
  background:red;
  font-weight:bold;
  font-size:40px;
  text-decoration:none;
  }
.sb1 {font-size:22px; height:30px; }
.red{
  background:#db97b9;
  color:white;
  border:6px solid #db97b9;
  }
.rad {
    background:green;
    color:white;
    border:6px solid black;
    }
.knop {
  font-size: 22px; 
  background-color:#330066; 
  color:#99ffff; 
  padding: 5px 8px; 
  border-radius:8px;
  }
.knop1 {
    font-size: 18px; 
    background-color:#2d6b1a; 
    color:#ffffff; 
    padding: 2px 2px; 
    border-radius:8px; 
    width:100px; height:38px;
    }
input { font-size:24px; }
.inp1 {width:60px;}
.inp2 {width:80px;} 
.inp3 {width:100px;} 
.inp4 {width:205px;} 
.inp5 {width:200px;}
.inp6 {width:300px;} 
option {direction: ltr;}
.sb1 {
   font-size:30px;
   height:40px;
  } 
 
tr {height:45px;} 
input[type=checkbox] 
  {
    width:30px; 
    height:30px;
    }
ul {
  list-style-type: none;
  margin: 0;
  padding: 0;
  overflow: hidden;
  background-color: #333;
  border-radius:6px;
  width:96vw;
  height: 48px;
  }
li {
  float: left;
}
li a {
  display: inline-block;
  color: white;
  text-align: center;
  padding: 14px 16px 10px;
  text-decoration: none;
  width:70px; 
  height:48px;
  font-size:20px;}
  }
li a:hover { background-color: #ff0808 !important;} 
a:focus {background-color: red;}   
.sub {
    display: inline-block;
    background:red;
    border:none;
    margin:0;
    padding:10;
    cursor: pointer;
    color:black;
    font-weight: bold;
    font-size:16px; 
    height: 48px; }   
.close {
  color: red;
  float: right;
  font-size: 48px;
  font-weight: bold;
  cursor: pointer;
}
.close:hover {color: green;}

@media only screen and (max-width: 600px) { 
  li a { font-size:14px; 
    padding: 14px 26px 10px 12px; 
    width: 50px; 
   }
}
)=====";

 const char HTML_HOMEPAGE[] = R"=====(
<!DOCTYPE html><html><head><meta charset='utf-8' name="viewport" content="width=device-width, initial-scale=1"><title>HANSIART ESP32 CAM</title>
<link rel="stylesheet" type="text/css" href="/STYLESHEET">  
<link rel="icon" type="image/x-icon" href="/favicon.ico" />

<style>
#strm, #overlay, #fake {
  width:370px; 
  height:250px;
}
#strm {object-fit: scale-down;}

#fake, #overlay{
  text-align:center;
  background: lightgrey;
  border: solid 2px black;
  }
.mar {
width:300px; 
height:30px;
font-size:26px;
}


@media only screen and (max-width: 600px) { 
#strm, #fake, #overlay {
  width:100%; 
  height:250px;
  }
}
</style>
</head> 
  <body><div id='msect'><center><h3>HAIPS</h3>
  <p>the camera has started</p>
<script>

function contentLoaded() {
        console.log("data loaded");
        // now we hide the overlay and show the cameraview
        document.getElementById("overlay").style.display = "none";
        document.getElementById("strm").style.display = "block";
    }

function toggle_view() {
var hihaho = document.getElementById("strm").src; 
if(hihaho.indexOf("dummy") == -1) {
window.location.reload();  
} else {

// show a preload
document.getElementById("fake").style.display = "none";
document.getElementById("overlay").style.display="block";

var currentUrl = window.location.href.slice(0, -1); // remove the slash
console.log("currentUrl = " + currentUrl);
//the regex checks if there is a colon with at least 1 digit behind it (and no other characters slashes)
var regex = /^.+:\d+$/;
var newUrl ="";
console.log("test = " + regex.test(currentUrl));
if(regex.test(currentUrl))  {
// we have a port so we replace the last 2 characters with 91/stream
newUrl = currentUrl.slice(0, -2) + '91/stream';
} else {
//we just add :91/stream
newUrl = currentUrl + ':91/stream';
}
console.log("newUrl = " + newUrl);
document.getElementById("strm").src = newUrl;

}
}

function helpfunctie() {
alert("In case of malfunction: \nOnly one client at a time is possible. Check if the stream is opened in another browser or window.\nIf you see the warning \"camera not started\", please reboot. \n\nTo view the stream in a browser, the url is\"camera-ip:91/stream");
}

</script>

<ul>
<li><a href='#' onclick='helpfunctie()'>help</a></li>
<li style='float: right'><a href='/BASISCONFIG'>menu</a></li>
</ul>
<br><br>
<div id='divstijl'><center><br>

<div id="fake" style="display:block;" onclick="toggle_view()"><h3><br><br><br><br>&nbsp&nbspClick here to toggle camera view !</h3></div>

<div id="overlay" style="display:none;" onclick="toggle_view()"><h3><br><br><br>
<marquee class="mar" direction="left" scrollamount="12" >Waiting for data ! If this takes too long, click help</marquee>
</div>

<image id="strm" src="dummy" onclick="toggle_view()" onload="contentLoaded(this)" onloadstart="stalled()" style="display:none"></image>

<br>
<p>version ESP32CameraWebserver-v1_3<br>Powered by hansiart</p>
</div>
</html>
)====="; 

const char CONFIRM[] = R"=====(
<!DOCTYPE html><html><head><meta charset='utf-8'><body style='font-size:16px;'>
<head></head><body><div id='msect><center><script type='text/javascript'>
setTimeout(function(){window.location.href='/';}, 3000 );</script>
<h1> please wait..</h1><h3>When the requested action has been completed,<br><br>This page will close automatically.<br><br></body></html>
)=====";

const char CONFIRM_IP[] = R"=====(
<!DOCTYPE html><html><head><meta charset='utf-8'><body style='font-size:16px;'>
<head></head>
<body style='font-size:16px;'>
<script type='text/javascript'>setTimeout(function(){ window.location.href='http://{adres0}/'; }, 6000 ); </script>
<h1> SAVE SETTINGS</h1><br><br><div class='divstijl' style='width: 800px;'>
The ip settings are saved.<br><br>
The device is going to reboot now! <strong>Wait until the LED has flashed 3x!</strong><br><br>
{zin}
</body></html>
)=====";

#define FAVICON_len 318
const uint8_t FAVICON[] PROGMEM = {
0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x10, 0x10, 0x10, 0x00, 0x01, 0x00, 0x04, 0x00, 0x28, 0x01,
0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x20, 0x00,
0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2E, 0xDB,
0xD6, 0x00, 0xD1, 0x0F, 0x18, 0x00, 0xB4, 0xDD, 0xDE, 0x00, 0x66, 0xE1, 0xE3, 0x00, 0xD3, 0xE6,
0xE5, 0x00, 0x81, 0xE1, 0xE3, 0x00, 0x9A, 0xDA, 0xDB, 0x00, 0x75, 0xDF, 0xE0, 0x00, 0xB5, 0x14,
0x9D, 0x00, 0xB6, 0xE3, 0xE2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x44, 0x44,
0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x49, 0x91, 0x99, 0x91, 0x19, 0x99, 0x19, 0x94, 0x49, 0x21,
0x22, 0x12, 0x21, 0x22, 0x12, 0x94, 0x49, 0x21, 0x66, 0x16, 0x61, 0x66, 0x12, 0x94, 0x49, 0x21,
0x55, 0x15, 0x51, 0x55, 0x12, 0x94, 0x49, 0x21, 0x57, 0x71, 0x17, 0x71, 0x11, 0x94, 0x49, 0x26,
0x50, 0x00, 0x00, 0x75, 0x62, 0x94, 0x49, 0x26, 0x57, 0x33, 0x30, 0x75, 0x62, 0x94, 0x48, 0x86,
0x58, 0x83, 0x80, 0x75, 0x62, 0x84, 0x48, 0x86, 0x58, 0x80, 0x88, 0x75, 0x68, 0x84, 0x48, 0x86,
0x58, 0x87, 0x88, 0x88, 0x88, 0x84, 0x48, 0x88, 0x88, 0x85, 0x58, 0x85, 0x88, 0x94, 0x48, 0x86,
0x68, 0x86, 0x66, 0x82, 0x82, 0x94, 0x48, 0x82, 0x28, 0x82, 0x22, 0x88, 0x82, 0x94, 0x48, 0x89,
0x98, 0x89, 0x99, 0x98, 0x99, 0x94, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};   
