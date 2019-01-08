
//external includes
#include <FastLED.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "SD.h"
#include "SPI.h"

//other includes
#include "config.h"
#include "Matrix.h"
#include "animationHandler.h"



//instances
Matrix matrix;
AnimationHandler* anim;


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
  anim = new AnimationHandler(matrix);
}

void loop() {
  anim->animate();
}

//-------------------------------------------------------------------------


