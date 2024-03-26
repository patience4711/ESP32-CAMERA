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

//<!--<div id="fake" style="display:block;" onclick='toggle_view()'><h3><br><br><br>&nbsp&nbspClick to toggle camera view !</h3></div>
//<object data="dummy" type="image/jpeg" id="stream-container" style="display:none;" onclick='toggle_view()' onload="contentLoaded(this)"><h3>&nbsp&nbspstream currently not available</h3></object>
//-->
