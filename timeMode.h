#ifndef TIMEMODE_H
#define TIMEMODE_H
#include "fonts.h"
#include "stuff.h"
#include "matrixRotate.h"
#include <FastLED.h>

//fonts
font5x3 font5x3;
font7x3 font7x3;
CRGB timeColor = CRGB::White;

void draw_time_and_temp(cLEDMatrixBase &matrix)
{
  byte mx;
  byte hx;
  font7x3.drawNumber(matrix, 0, 8, hours, timeColor);
  font7x3.drawNumber(matrix, 9, 8, minutes, timeColor);
  matrix(10, 5) = timeColor;
  font5x3.drawNumber(matrix, 2, 1, String(temperature), timeColor);
  font5x3.drawNumber(matrix, 12, 1, "c", timeColor);
}

void draw_time_and_humid(cLEDMatrixBase &matrix)
{
  byte mx;
  byte hx;
  font7x3.drawNumber(matrix, 0, 8, hours, timeColor);
  font7x3.drawNumber(matrix, 9, 8, minutes, timeColor);
  font5x3.drawNumber(matrix, 0, 1, String(humidity), timeColor);
  matrix.DrawLine(10, 1, 14, 5, timeColor);
  matrix(10, 5) = timeColor;
  matrix(14, 1) = timeColor;
}

byte bcdToDec(byte val) {
  return ( (val / 16 * 10) + (val % 16) );
}

void readTimeRTC()
{
  Wire.beginTransmission(RTC_I2C_ADDRESS); //Aufbau der Verbindung
  Wire.write(0);
  Wire.endTransmission();
  Wire.requestFrom(RTC_I2C_ADDRESS, 7);
  seconds    = String(bcdToDec(Wire.read()));
  minutes     = String(bcdToDec(Wire.read()));
  hours     = String(bcdToDec(Wire.read()));
  if (seconds.length() == 1)
  {
    seconds += seconds[0];
    seconds[0] = '0';
  }
  if (minutes.length() == 1)
  {
    minutes += minutes[0];
    minutes[0] = '0';
  }
  if (hours.length() == 1)
  {
    hours += hours[0];
    hours[0] = '0';
  }
  bcdToDec(Wire.read());
  bcdToDec(Wire.read());
  bcdToDec(Wire.read());
  bcdToDec(Wire.read());
}

void timemode(cLEDMatrixBase &matrix, DHT &dht)
{
  byte modi = 0;
  CRGB colors[5] = {CRGB::White, CRGB::Red, CRGB::Blue, CRGB::Green, CRGB::Yellow};
  byte curColor = 0;
  while (true)
  {
    FastLED.clear();
    brightness_control();
    byte i = read_buttons();
    switch (i)
    {
      case 1:
        return;
      case 2:
        modi++;
        Serial.print("modi: ");
        Serial.println(modi);
        if (modi > 1) {
          modi = 0;
        }
        Serial.print("modi: ");
        Serial.println(modi);
        break;
      case 3:
        curColor++;
        if (curColor >= 5) {
          curColor = 0;
        }
        timeColor = colors[curColor];
        break;
    }
    read_sensors(dht);
    readTimeRTC();
    switch (modi)
    {
      case 0:
        draw_time_and_temp(matrix);
        break;
      case 1:
        draw_time_and_humid(matrix);
        break;
    }
    rotate(matrix);
    FastLED.show();
  }
}


#endif
