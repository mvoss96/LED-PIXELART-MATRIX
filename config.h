#ifndef CONFIG_H
#define CONFIG_H

//setup the dimensions of the LED matrix
#define MATRIX_WIDTH   16
#define MATRIX_HEIGHT  16 
#define MATRIX_ROTATION 180

//how long each animation should be played in animation mode (ms)
#define ANIMATION_DURATION 10000

//automatically cycle between clockmode and animationmode (seconds)
//set to 0 to disable
#define AUTO_CLOCK_DURATION 0

// the digital pin for controlling the WS2812 LED Matrix
#define LED_PIN  4

// the pin for connecting the SD card
#define SD_PIN  5

//activates automatic brightness control 
#define USE_LIGHT_SENSOR
#define LS_PIN 33
#define LS_GND 14
#define LS_VCC 32

//Button 1 changes animation/clock mode, Button 2 skips the current animation,
//Button 3 pauses the animation progression, so that the current aniamtion will be played in a loop.
//#define USE_BUTTONS
#define BUTTON_GND 33
#define BUTTON1_PIN 25
#define BUTTON2_PIN 26
#define BUTTON3_PIN 27

//activates clock mode
//#define USE_RTC_CLOCK
#define RTC_I2C_ADDRESS 0x68 // I2C adress of  RTC  DS3231

//display ambbient temperature in clock mode
//#define USE_TEMP_SENSOR
//#define TEMP_PIN 15

//print additional information to the serial monitor
#define DEBUG 1

#endif
