# GSMCam
A Python program to determine the Grams per Square Meter of a Fabric using hardware accelerated Image Processing
(Also contains source code, design files and PCB schematics for cartesian slider system used to move the camera across fabrics.)

![cover1_97ebsi5cop](https://user-images.githubusercontent.com/20635670/120110813-c33bf200-c18c-11eb-8a1f-5e5f48039571.jpg)

Conventional method of fabric GSM measurement involves cutting a small round piece of fabric with an area of 0.01 square centimeters and measuring its weight using a precision balance.This project was aimed to replace this conventional method with an optical based one. Currently the scope of the project is limited to single light color (white) fabrics with a plain, twill weave. (Algorithm can also be applied to knit fabrics with a considerable accuracy as well)

For anyone looking to implement a hardware accelerated application with minimal development and debugging time, PYNQ is a great option. Currently PYNQ supports several boards including the Ultra96. The computer vision library for PYNQ provides several overlays for accelerating OpenCV functions in hardware. Currently Filter2D and dilation operations are supported. 


The following flow diagram depicts the stages in the GSM Determination process.

![sssddd](https://user-images.githubusercontent.com/20635670/51759809-10a48200-20ef-11e9-84cc-d46a29176133.jpg)


The GUI is made using Flask, and can be used to calibrate and view results.

![33333](https://user-images.githubusercontent.com/20635670/51759866-36ca2200-20ef-11e9-8d12-da7225b2df38.jpg)


### Complete Instructions : 
https://www.hackster.io/yasaspeiris/fabric-gsm-determination-using-ultra96-pynq-6c5499


### Contributors : 

Pasindu Liyanage

