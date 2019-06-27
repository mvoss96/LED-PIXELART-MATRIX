# LED-PIXELART-MATRIX
WIP firmware for an esp32 based LED Matrix

This is the firmware for my DIY LED Pixelart aniamtion matrix. 
You can find the stl files and more inforamtion about this project here:
https://www.thingiverse.com/thing:3349738

I got the inspiration from the gameframe by ledseq however this firmware was written completly from scratch.
the firmware supports loading 16x16 .bmp files as animations from an SD-card and is also compatible to the original gameframe animations,
that you can buy from ledseq.

Other features that are supportet:

-clock mode-
in clock mode the matrix can show the time and the ambient temperature
(requires a rtc3231 real time clock and a digital temperature sensor)

-automatic Brightness-
if you connect a light sensor to measure the ambient light level, the brightness of the matrix can automatically be adjusted.

-three different buttons-
for switching between different modes, skipping an animation or enabling loop mode.


-To-Do-
-detailed assembly instructions
-optional wifi functionality for esp32 and other microcontrolles with onbaord wifi
![image](/01.JPG)
