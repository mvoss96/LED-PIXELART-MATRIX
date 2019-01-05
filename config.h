#ifndef CONFIG_H
#define CONFIG_H

#define LS_PIN 39
#define LS_GND 14
#define LS_VCC 32
#define BUTTON_GND 33
#define BUTTON1_PIN 25
#define BUTTON2_PIN 26
#define BUTTON3_PIN 27
#define SD_PIN  5
#define LED_PIN  13
#define TEMP_PIN 15
#define MATRIX_WIDTH   16
#define MATRIX_HEIGHT  16
#define NUM_LEDS    MATRIX_WIDTH*MATRIX_HEIGHT
#define MATRIX_TYPE    HORIZONTAL_ZIGZAG_MATRIX
#define DHTTYPE DHT11   
#define RTC_I2C_ADDRESS 0x68 // I2C Adresse des RTC  DS3231
#define DEBUG 0
#endif
