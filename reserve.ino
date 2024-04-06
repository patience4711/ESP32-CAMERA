//function toggle_view() {
//var hihaho = document.getElementById("stream-container").data; 
//if(hihaho.indexOf("dummy") == -1) {
//window.location.reload();  
//} else {
//var currentUrl = window.location.href.slice(0, -1); // remove the slash
//console.log("currentUrl = " + currentUrl);
////the regex checks if there is a colon with at least 1 digit behind it (and no other characters slashes)
//var regex = /^.+:\d+$/;
//var newUrl ="";
//console.log("test = " + regex.test(currentUrl));
//if(regex.test(currentUrl))  {
//  // we have a port so we replace the last 2 characters wiht 91/stream
////alert("we have a port in the url");
//newUrl = currentUrl.slice(0, -2) + '91/stream';
//
//} else {
////we just add :91/stream
//newUrl = currentUrl + ':91/stream';
//}
//console.log("newUrl = " + newUrl);
//// now when from inside yhere i no port so the link gets wrong;
//// so if we have a : we replace the last 2 else we replace ony the /
//
////go to the new url
////window.location.href=newUrl;
////document.getElementById("stream").data = "192.168.0.203:91/stream";
////document.getElementById("stream").style.display="block";
//document.getElementById("stream-container").data = newUrl;
////document.getElementById("stream-container").data = "{strm}";
//document.getElementById("fake").style.display = "none";
//document.getElementById("stream-container").style.display = "block";
////document.getElementById("toggle").innerHTML = "close";
//}
//}
/*
<!DOCTYPE html><html><head><meta charset='utf-8' name="viewport" content="width=device-width, initial-scale=1"><title>HANSIART ESP32 CAM</title>
<link rel="stylesheet" type="text/css" href="/STYLESHEET">  
<link rel="icon" type="image/x-icon" href="/favicon.ico" />

const char HTML_STREAMPAGE[] = R"=====(

<style>
* {
  box-sizing: border-box;
}

img {
  max-width:100%;
  max-height:100%;
  object-fit: cover;
}
.img_rot {
transform:rotate(90deg);
}

@media only screen and (max-width: 600px) { 
.fake, .overlay {
  width:90%; 
  height:250px;
  }

.flex-portrait {
  object-fit: cover;
  overflow: auto; 
}


}

</style>
</head> 
  <body><center>
  <div id='shouldRotate' style='display: none;'>0123</div>

<script>
const orientation = document.getElementById("shouldRotate");
var STRM = document.getElementById("strm");

function cl() { window.location.href='/'; }
function contentLoaded() {
        console.log("data loaded");
        document.getElementById("overlay").style.display = "none";
    }

function toggle_view() {
var STRM = document.getElementById("strm");

var hihaho = document.getElementById("strm").src; 

// if  not dummy 
if(hihaho.indexOf("dummy") == -1 ) {
window.location.reload();  

} else {

// show a preload
var OVERLAY = document.getElementById("overlay");
document.getElementById("fake").style.display = "none";
console.log("hide fake");
OVERLAY.style.display="block";

//if (location.href.indexOf("#") != -1) {
//console.log("found hash");  
//var currentUrl = window.location.href.slice(0, -2); // remove the /#
//} else {
// the url ends with stream so we slice that. -1 is the M so it should be -6 STREAM
var currentUrl = window.location.href.slice(0, -7); // remove the slash/STREAM
//}

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
newUrl = "http://192.168.0.208:91/stream";  //for test
console.log("newUrl = " + newUrl);

STRM.src = newUrl;

if(orientation.innerHTML == "3210") {
STRM.classList. add("img_rot");
STRM.style.display="block";

  } else {
  console.log("show landscape ");
  STRM.style.display="block";
  }
}
}

</script>
<span id='fright' class='close' style="font-size:52px;" onclick='cl();'>&times;</span>
<br>
<div id="fake" class="im_cont fake" style="display:block;" onclick="toggle_view()"><h3><br><br><br><br>&nbsp&nbspClick here to toggle camera view !</h3></div>

<div id="overlay" class="im_cont overlay" style="display:none;" onclick="toggle_view()">
<h3><br><br><br><br><marquee id='marq' class='mar' direction='left' scrollamount='12' >Waiting for data ! If this takes too long, click help</marquee></h3>
</div>

<img id="strm" src="dummy" onclick="toggle_view()" onload="contentLoaded(this)" style="display: none;"></image>

<br>
<p>ESP32-CAM-v1_4 Powered by hansiart</p>

</div>
<body></html>
)====="; 

*/
//<!--<div id="fake" style="display:block;" onclick='toggle_view()'><h3><br><br><br>&nbsp&nbspClick to toggle camera view !</h3></div>
//<object data="dummy" type="image/jpeg" id="stream-container" style="display:none;" onclick='toggle_view()' onload="contentLoaded(this)"><h3>&nbsp&nbspstream currently not available</h3></object>
//-->

// from camindex logo <label for="nav-toggle-cb" id="nav-toggle">&#9776;&nbsp;&nbsp;Toggle hansiart espcamera view</label>
