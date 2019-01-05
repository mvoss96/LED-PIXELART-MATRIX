#ifndef SENSOR_HANDLER_H
#define SENSOR_HANDLER_H

OneWire oneWire(TEMP_PIN);
DallasTemperature sensors(&oneWire);

byte bcdToDec(byte val) {
  return ( (val / 16 * 10) + (val % 16) );
}

class SensorHandler {
  private:
    bool button1, button2, button3;
    int temperature;
    String hours;
    String minutes;
    int lsVarr[100] = {0};;
    byte lsVcount = 0;
    long buttonPollTime;
    long buttonPollDuration;

  public:
    SensorHandler() {
      hours = "00";
      minutes = "00";
      temperature = 0;
      button1 = button2 = button3 = false;
      buttonPollTime = millis();
      buttonPollDuration = 300;
    };

    byte readButtons()
    {
      if (buttonPollTime + buttonPollDuration < millis()) {
        if (digitalRead(BUTTON1_PIN) == LOW)
        {
          Serial.println("Button1 pressed");
          buttonPollTime = millis();
          return 1;
        }
        else if (digitalRead(BUTTON2_PIN) == LOW)
        {
          Serial.println("Button2 pressed");
          buttonPollTime = millis();
          return 2;
        }
        else if (digitalRead(BUTTON3_PIN) == LOW)
        {
          Serial.println("Button3 pressed");
          buttonPollTime = millis();
          return 3;
        }
      }
      return 0;
    }

    int readTemp() {
      EVERY_N_SECONDS(5) {
        sensors.requestTemperatures(); // Send the command to get temperatures
        temperature = round(sensors.getTempCByIndex(0));
      }
      return temperature;
    }

    void controllBrightness() {
      int lsV = analogRead(LS_PIN);
      lsVarr[lsVcount] = lsV;
      lsVcount++;
      if (lsVcount >= 100)
      {
        lsVcount = 0;
      }
      lsV = 0;
      for (int i = 0; i < 100; i++)
      {
        lsV += lsVarr[i];
      }
      lsV /= 100;
      float targetB;
      float bMin = 5;
      float bMax = 70;
      float minSense = 3000;
      float maxSense = 1000;
      targetB = ((lsV - maxSense) / (minSense - maxSense)) * (bMin - bMax) + bMax;
      if (lsV > minSense) {
        targetB = 5;
      }
      if (lsV < maxSense) {
        targetB = bMax;
      }
      FastLED.setBrightness(targetB);
    }

    void getTime(String &outMinutes, String &outHours) {
      readTimeRTC();
      outMinutes = minutes;
      outHours = hours;
    }

    void readTimeRTC()
    {
      Wire.beginTransmission(RTC_I2C_ADDRESS); //Aufbau der Verbindung
      Wire.write(0);
      Wire.endTransmission();
      Wire.requestFrom(RTC_I2C_ADDRESS, 7);
      bcdToDec(Wire.read());
      minutes     = String(bcdToDec(Wire.read()));
      hours     = String(bcdToDec(Wire.read()));
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

};

#endif
