const char HTML_HOMEPAGE[] = R"=====(
<!DOCTYPE html><html><head><meta charset='utf-8' name="viewport" content="width=device-width, initial-scale=1"><title>HANSIART ESP32 CAM</title>
<link rel="stylesheet" type="text/css" href="/STYLESHEET">  
<link rel="icon" type="image/x-icon" href="/favicon.ico" />

<style>
* {
  box-sizing: border-box;
}

.flex-landscape {
  display: flex;
  width : 340px;
  height : 270px;
}

.flex-portrait {
  display: flex;
  width : 370px;
  height : 270px;
  padding-bottom: 0px;
  transform: rotate(90deg);
}

.fake, .overlay{
  width:370px; 
  height:250px;
  text-align:center;
  background: lightgrey;
  border: solid 2px black;
  }
.mar {width:260px; height:30px; font-size:26px;}
img {
  max-width:100%;
  max-height:100%;
  object-fit: cover;
}


@media only screen and (max-width: 600px) { 
.fake, .overlay {
  width:90%; 
  height:250px;
  }

.flex-portrait {
  width : 340px;
  height : 220px;
  padding-left:0px;
  padding-top:0px;
  object-fit: cover;
  overflow: auto; 
}

#divstijl {height: 60vh;}
}

</style>
</head> 
  <body><div id='msect'><center><h3>HAIPS</h3>
  <div id='shouldRotate' style='display: none;'>0123</div>

<script>
const orientation = document.getElementById("shouldRotate");
function contentLoaded() {
        console.log("data loaded");
        // now we hide the overlay and show the cameraview
        document.getElementById("overlay").style.display = "none";
        //document.getElementById("strm").style.display = "block";
    }

function toggle_view() {
var hihaho = document.getElementById("strmpo").src; 
var hohahi = document.getElementById("strmls").src;
// if both not dummy 
if(hihaho.indexOf("dummy") == -1 || hohahi.indexOf("dummy")  == -1)  {
window.location.reload();  

} else {

// show a preload
var OVERLAY = document.getElementById("overlay");
//var MARQUEE = document.getElementById("marq");
document.getElementById("fake").style.display = "none";
console.log("hide fake");
OVERLAY.style.display="block";

if (location.href.indexOf("#") != -1) {
console.log("found hash");  
var currentUrl = window.location.href.slice(0, -2); // remove the /#
} else {
var currentUrl = window.location.href.slice(0, -1); // remove the slash
}
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
//newUrl = "http://192.168.0.208:91/stream";  //for test
console.log("newUrl = " + newUrl);
var STRM = document.getElementById("strm");


if(orientation.innerHTML == "3210") {
  document.getElementById("strmpo").src=newUrl;
  document.getElementById("pobox").style.display="block";
  document.getElementById("space").innerHTML="<br><br>";
  } else {
  console.log("show landscape ");
  document.getElementById("strmls").src=newUrl;
  document.getElementById("lsbox").style.display="block";
  }
}
}


function helpfunctie() {
alert("In case of malfunction: \nOnly one client at a time is possible. Check if the stream is opened in another browser or window.\nIf you see the warning \"camera not started\", please reboot.\nWhen there is a hash (#) in your url it won't work! \n\nTo view the stream in a browser, the url is\"camera-ip:91/stream\n\nstatus: camera started");
}

</script>

<ul>
<li><a href='#' onclick='helpfunctie()'>help</a></li>
<li style='float: right'><a href='/MENU'>menu</a></li>
</ul>
<br>
<div id='divstijl' style='height: 65vh'><center><br>
<div id='space'><br></div>
<div id="fake" class="im_cont fake" style="display:block;" onclick="toggle_view()"><h3><br><br><br><br>&nbsp&nbspClick here to toggle camera view !</h3></div>

<div id="overlay" class="im_cont overlay" style="display:none;" onclick="toggle_view()">
<h3><br><br><br><br><marquee id='marq' class='mar' direction='left' scrollamount='12' >Waiting for data ! If this takes too long, click help</marquee></h3>
</div>

<div class="flex-landscape" id="lsbox" style="display:none;">
<img id="strmls" src="dummy" onclick="toggle_view()" onload="contentLoaded(this)"></image>
</div>

<div class="flex-portrait" id="pobox" style="display:none;" >
<img id="strmpo" src="dummy" onclick="toggle_view()" onload="contentLoaded(this)"></image>
</div>


<br></div>
<p>ESP32-CAM-v1_4 Powered by hansiart</p>
</div>

<body></html>
)====="; 
