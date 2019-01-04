#ifndef STUFF_H
#define STUFF_H
#include "DHT.h"

const byte maxLsV = 100;
int lsVarr[maxLsV]={0};
byte lsVcount = 0;

void brightness_control()
{
  int lsV = analogRead(LS_PIN);
  lsVarr[lsVcount]=lsV;
  lsVcount++;
  if (lsVcount >= maxLsV)
  {
    lsVcount = 0;
  }
  lsV = 0;
  for(int i = 0;i<maxLsV;i++)
  {
    lsV+=lsVarr[i];
  }
  lsV /=maxLsV;
  float targetB;
  float bMin = 10;
  float bMax = 70;
  float minSense = 3000;
  float maxSense = 1000;
  //byte b1 = 5, b2 = 10, b3 = 20, b4 = 35, b5 = 50, b6 = 60, b7 = 70;
  //int lv1 = 3000, lv2 = 2000, lv3 = 1000, lv4 = 600, lv5 = 400, lv6 = 200, lv7 = 150;
  targetB = ((lsV - maxSense) / (minSense - maxSense)) * (bMin - bMax) + bMax;
  if (lsV > minSense) {
    targetB = 5;
  }
  if (lsV < maxSense) {
    targetB = bMax;
  }
  FastLED.setBrightness(targetB);
}

void read_sensors(DHT &dht)
{
  EVERY_N_SECONDS(5) { //DHT-Sensors can't be read too fast
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();
  }
}

void button_pressed(int button)
{
  Serial.print("Button pressed: ");
  Serial.println(button);
}

byte read_buttons()
{
  if (digitalRead(BUTTON1_PIN) == HIGH)
  {
    button1Ps = false;
  }
  else if (button1Ps == false) {
    button_pressed(1);
    button1Ps = true;
    return 1;
  }
  if (digitalRead(BUTTON2_PIN) == HIGH)
  {
    button2Ps = false;
  }
  else if (button2Ps == false) {
    button_pressed(2);
    button2Ps = true;
    return 2;
  }
  if (digitalRead(BUTTON3_PIN) == HIGH)
  {
    button3Ps = false;
  }
  else if (button3Ps == false) {
    button_pressed(3);
    button3Ps = true;
    return 3;
  }
}



#endif
