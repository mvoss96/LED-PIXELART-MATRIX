//Global variables
String hours = "00";
String minutes = "00";
String seconds = "00";
byte temperature = 0;
byte humidity = 0;
bool button1Ps = false;
bool button2Ps = false;
bool button3Ps = false;
bool lastSave = false;
String tempAnimation = "";
int tempImage = 0;

#define LS_PIN 39
#define LS_GND 14
#define LS_VCC 32
#define BUTTON_GND 33
#define BUTTON1_PIN 25
#define BUTTON2_PIN 26
#define BUTTON3_PIN 27
#define SD_PIN  5
#define LED_PIN  13
#define DHT_PIN 15
#define MATRIX_WIDTH   16
#define MATRIX_HEIGHT  16
#define NUM_LEDS    MATRIX_WIDTH*MATRIX_HEIGHT
#define MATRIX_TYPE    HORIZONTAL_ZIGZAG_MATRIX
#define DHTTYPE DHT11   
#define RTC_I2C_ADDRESS 0x68 // I2C Adresse des RTC  DS3231
#define DEBUG 0


//includes
#include <FastLED.h>
#include <LEDMatrix.h>
#include <Wire.h>
#include "DHT.h"
#include "SD.h"
#include "SPI.h"
#include "BMPreader.h"
#include "fonts.h"
#include "storedImages.h"
#include "animationLoader.h"
#include "matrixRotate.h"
#include "stuff.h"

//instances
cLEDMatrix<MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> leds;
DHT dht(DHT_PIN, DHTTYPE);





//-------------------------------------------------------------------------

void setup() {
  pinMode(LS_PIN, INPUT);
  pinMode(LS_VCC, OUTPUT);
  pinMode(LS_GND, OUTPUT);
  pinMode(BUTTON_GND, OUTPUT);
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  pinMode(BUTTON3_PIN, INPUT_PULLUP);
  digitalWrite(LS_VCC, HIGH);
  digitalWrite(LS_GND, LOW);
  digitalWrite(BUTTON_GND, LOW);
  Serial.begin(115200);
  Wire.begin();
  FastLED.addLeds<WS2812, LED_PIN, GRB> (leds[0], leds.Size()).setCorrection(TypicalSMD5050);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 1000);
  FastLED.setBrightness(64);
  if (!SD.begin(SD_PIN)) {
    Serial.println("Card Mount Failed");
    error_state(leds);
  }
  dht.begin();
  print_status();
}

void loop() {
  load_all_animations(leds,dht);
}

//-------------------------------------------------------------------------



void print_status()
{
  int cTime = millis();
  Serial.println();
  String output = "Statusreport: ";
  String divider = "/";
  String divider2 = ":";
  output = (output + divider + hours + divider2 + minutes + divider2 + seconds);
  Serial.println(output);
  Serial.println("Temperature: " + String(temperature));
  Serial.println("Humidity: " + String(humidity));
  Serial.print("Brightness: ");
  Serial.println(FastLED.getBrightness());
  Serial.print("time taken: ");
  Serial.println(millis() - cTime);
  Serial.println();

}



