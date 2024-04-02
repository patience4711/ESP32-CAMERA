const char HTML_HEAD[] = R"=====(
<!DOCTYPE html><html><head><meta charset='utf-8'>
<title>ESP32-CAM</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="stylesheet" type="text/css" href="/STYLESHEET">

<script type='text/javascript'>

function showSubmit() {
document.getElementById("sub").style.display = "block";
}
function submitFunction(a) {
document.getElementById("bo").innerHTML="<br>wait...<br>processing<br>your<br>request"; 
document.getElementById("bo").style.display="block"; 
document.getElementById('formulier').submit();
setTimeout(function(){window.location.href=a;}, 3000 ); 
}
</script>
</head>

)=====";

const char STYLESHEET[] = R"=====(
body {
  background: linear-gradient(#e8f5f7, #caf5fb); 
  color:navy;
  font-family:'lato',Verdana,Sans-serif;
  font-size:16px;
  }
#divstijl { background: linear-gradient(#e8edc8, #c8eaed); padding:0px 0px 0px 0px; width: 96%; height: 55vh; }
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
input { font-size:16px; }
.inp1 {width:60px;}
.inp2 {width:80px;} 
.inp3 {width:100px;} 
.inp4 {width:205px;} 
.inp5 {width:200px;}
.inp6 {width:240px;} 
option {direction: ltr;}
 
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
#sub { float: left; background:green; display:none }

.close {
  width:20px; 
  padding: 0px 10px;
  color: red;
  float: right;
  font-size: 32px;
  font-weight: bold;
  cursor: pointer;
}
.close:hover {color: green;}
.sb1 {font-size:16px; height:24px; }
#bo {width:100%; height:100%; position: absolute; left:0; top:0; background-color:rgba(192,192,192,0.9); color:white; z-index:10; font-size: 70px;font-weight: bold; text-align: center; display: none;}
#fright {float:right;}
@media only screen and (max-width: 600px) { 
  li a { font-size:14px; 
    padding: 14px 26px 10px 12px; 
    width: 50px; 
   }
  .divstijl {width:98vw;}

  body { font-size:12px; }
}
)=====";

 

 const char HTML_CAPTURE[] = R"=====(
<!DOCTYPE html><html><head><meta charset='utf-8' name="viewport" content="width=device-width, initial-scale=1"><title>HANSIART ESP32 CAM</title>
<link rel="stylesheet" type="text/css" href="/STYLESHEET">  
<link rel="icon" type="image/x-icon" href="/favicon.ico" />
<body><center>

  <div id="container">
    <h2>ESP32-CAM Last Photo</h2>
    <p>It might take more than 5 seconds to capture a photo.</p>
    <p>
      <button onclick="rotatePhoto();">ROTATE</button>
      <button onclick="capturePhoto()">CAPTURE PHOTO</button>
      <button onclick="location.reload();">REFRESH PAGE</button>
    </p>
  </div>
  <div><img src="saved-photo" id="photo" width="70%"></div>
</body>
<script>
  var deg = 0;
  function capturePhoto() {
    var xhr = new XMLHttpRequest();
    xhr.open('GET', "/capture", true);
    xhr.send();
  }
  function rotatePhoto() {
    var img = document.getElementById("photo");
    deg += 90;
    if(isOdd(deg/90)){ document.getElementById("container").className = "vert"; }
    else{ document.getElementById("container").className = "hori"; }
    img.style.transform = "rotate(" + deg + "deg)";
  }
  function isOdd(n) { return Math.abs(n % 2) == 1; }
</script>
</html>
)=====";

const char CONFIRM[] = R"=====(
<!DOCTYPE html><html><head><meta charset='utf-8'><body style='font-size:16px;'>
<head></head><body>
<div id='msect'><center>
<h1> please wait..</h1><h3>When the requested action has been completed,<br><br>This page will close automatically.<br><br>
<script>
setTimeout(function(){ window.location.href='/'; }, 3000 );
</script>
</body></html> 
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
