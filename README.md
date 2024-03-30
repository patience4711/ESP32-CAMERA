# ESP32-CAMERA
With this cheap little board we can have a very nice camera to view on our phone. <br> 
The example software has many shortcomings that i improved. This was not an easy job as the original software is difficult to understand and not documented.<br>The result is a complete websverver with very nice features. visi the [wiki](https://github.com/patience4711/ESP32-CAMERA/wiki) for more info on this project.
![camhouse](https://github.com/patience4711/ESP32-CAMERA/assets/12282915/22a264fe-db46-47ee-ad5b-8151959807ca)

## some of the features
- Easy to connect to your wifi via a config portal or serial console
- Can save settings for 5 different video formats
- camera can be viewed on homepage, optimized for mobile devices
- the flashlight can be controlled via the homepage
- works well when viewed from outside your network
- very compact, small enough to fit in a bird's nestbox
- the stream can be opened in any browser, easy to embed in website
- we can set a doorbell functionality (led on and send mqtt message)

frontpage<br>
![frontpage](https://github.com/patience4711/ESP32-CAMERA/assets/12282915/c96e1cb3-6924-4acb-8fa0-94ae172bee7d)
   
## downloads
you can find the latest binary here [ESP32-CAM-v1_3](https://github.com/patience4711/ESP32-CAMERA/blob/main/ESP32-CAM_v1_3.ino.esp32.bin)<br>
if you own a 3d-printer you can use [camhouse.stl](https://github.com/patience4711/ESP32-CAMERA/blob/main/camhouse.stl) end [camhouse_top.stl](https://github.com/patience4711/ESP32-CAMERA/blob/main/camhouse_TOP.stl) to print a nice housing.

## compile this sketch
You can use the provided binary but if you must compile it yourself: read the legende tab for instructions on settings in Arduino IDE
<br>Please note: by popular demand I have published the code here but i do not feel responsible for problems as to compiling. Impossible for me to know why it doesn't compile in your situation.

## other challenges
view orientation
The esp32cam boards can gav a different image orientation, i have 2 boards, one is portrait and the other landscape. So there should be an option to rotate the image in the software. I have already found a way to do this.
I tried to make this sketch work with bluetooth and skip the wifi config portal. Unfortunately this didn't work as the available programspace is too small.
So other things i had in mind (like a touch button that sends an MQTT message to make it a doorbell) are not feasible at this point. Still one thing to research is to make a custom partition scheme so that we have more program space.
