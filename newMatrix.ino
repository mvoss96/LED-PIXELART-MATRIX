//global variables
String hours = "00";
String minutes = "00";
String seconds = "00";
byte temperature = 0;
byte humidity = 0;
bool button1Ps = false;
bool button2Ps = false;
bool button3Ps = false;

//external includes
#include <FastLED.h>
//#include <LEDMatrix.h>
#include <Wire.h>
#include "DHT.h"
#include "SD.h"
#include "SPI.h"

//other includes
#include "config.h"
#include "Matrix.h"
#include "BMPreader.h"
#include "fonts.h"
#include "animationLoader.h"
#include "stuff.h"
#include "Matrix.h"

//instances
//cLEDMatrix<MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> leds;
Matrix matrix = Matrix();
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
  //FastLED.addLeds<WS2812, LED_PIN, GRB> (leds[0], leds.Size()).setCorrection(TypicalSMD5050);
  if (!SD.begin(SD_PIN)) {
    Serial.println("Card Mount Failed");
    //error_state(leds);
  }
  dht.begin();
  print_status();
}

void loop() {
  load_all_animations(matrix,dht);
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



