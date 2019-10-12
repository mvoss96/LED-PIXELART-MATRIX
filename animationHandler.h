#ifndef ANIMATION_HANDLER_H
#define ANIMATION_HANDLER_H

#include "sensorHandler.h"
#include "fonts.h"

font5x3 font5x3;
font7x3 font7x3;

int countFrames(String param, String path);

//helper functions
int32_t readNbytes32(File& p_file, int pos = -1, byte nBytes = 4)
{
  if (pos == -1)
    pos = p_file.position();
  if (nBytes > 4)
    return 0;
  if (p_file.position() != pos)
    p_file.seek(pos);

  int32_t weight = 1;
  int32_t result = 0;
  for (; nBytes; nBytes--)
  {
    result += weight * p_file.read();
    weight <<= 8;
  }
  return result;
}

int16_t readNbytes16(File& p_file, int pos = -1, byte nBytes = 2)
{
  if (pos == -1)
    pos = p_file.position();
  if (nBytes > 4)
    return 0;
  if (p_file.position() != pos)
    p_file.seek(pos);

  int16_t weight = 1;
  int16_t result = 0;
  for (; nBytes; nBytes--)
  {
    result += weight * p_file.read();
    weight <<= 8;
  }
  return result;
}


class AnimationHandler {
  private:
    Matrix* matrix;
    SensorHandler* sensors;
    String currentAnimamtion;
    String animationRootPath = "/animations";
    String configPath = "/config.ini";
    File file;
    File animationDir;
    File dir;
    int animationDuration = ANIMATION_DURATION;
    CRGB timeColor;


  public:
    AnimationHandler(Matrix &matrix)
    {
      this->matrix = &matrix;
      this->sensors = new SensorHandler();
      timeColor = CRGB::White;
      if (!SD.begin(SD_PIN)) {
        Serial.println("Card Mount Failed");
        matrix.showError();
        return;
      }
      animationDir = SD.open(animationRootPath);
      if (!animationDir) {
        Serial.println(animationRootPath + " does not exist");
      }
      dir = animationDir.openNextFile();
      if (!dir) {
        Serial.println("File Error!");
      }
      Serial.println("AnimationHandler setup completed");
    }

    byte animate()
    {
      if (dir)
      {
        if (dir.isDirectory()) {
          if (drawAnimation() == 1) {
            return 1;
          }
        }
        dir = animationDir.openNextFile();
      }
      else {
        Serial.println("restarting animation sequence");
        animationDir = SD.open(animationRootPath);
        dir = animationDir.openNextFile();
      }
    }

    byte drawAnimation()
    {
      matrix->update();
      byte nFrames = 0;
      byte curFrame = 0;
      int hold;
      int frames;
      bool pausemode = false;
      Serial.print("Loading animation:");
      Serial.println(dir.name());
      if (!dir)
      {
        Serial.println("Error: Path doesn't exist!");
        return -1;
      }
      if (!dir.isDirectory())
      {
        Serial.println("Error: Not a directory");
        return -1;
      }
      File file = dir.openNextFile();
      if (!SD.exists(dir.name() + configPath))
      {
        Serial.print(dir.name() + configPath);
        Serial.println(" not found: Skipping directory!");
        return -1;
      }
      else
      {
        hold = readFromConfig("hold");
        if (hold == 0) // if 0 is returned, there was an error
        {
          hold = 100;
          Serial.println("Error! Missing value hold in config.ini. Default value is used!");
        }
        frames = readFromConfig("frames");
        if (frames <= 0)
        {
          Serial.println("Error! Missing value frames in config.ini! -> creating...");
          frames = countFrames("frames", dir.name());
        }
      }
      if (DEBUG) Serial.println("Number of Frames:" + String(frames));
      long animationStartTime = millis();
      while (millis() < (animationStartTime + animationDuration) || pausemode)
      {
        int i = 0;
        long autoClockTimer = millis();
        unsigned long frameTimer = millis();
        while (i < frames)
        {
          String filename = String(dir.name()) + "/" + String(i) + ".bmp";
          i++;
          do
          {
            sensors->controllBrightness();
            int i = sensors->readButtons();
            switch (i)
            {
#ifdef USE_RTC_CLOCK
              case 1:
                timemode(false);
                break;
#endif
              case 2:
                Serial.println("Skipping...");
                return 0;
              case 3:
                if (pausemode == true) {
                  pausemode = false;
                  Serial.println("pausemode off");
                }
                else {
                  pausemode = true;
                  Serial.println("pausemode on");
                }
                break;
            }
            if  (AUTO_CLOCK_DURATION != 0) {
              if (millis() - autoClockTimer > AUTO_CLOCK_DURATION * 1000) {
                timemode(true);
              }
            }
            autoClockTimer = millis();
          }
          while (millis() < (frameTimer + hold));
          matrix->update();
          frameTimer = millis();
          if (readBMP(filename) != 0) {
            Serial.println("Error: reading .bmp file was unsuccessful");
            return -1;
          }
        }
      }
    }

    int readFromConfig(String param)
    {
      File configfile = SD.open(dir.name() + configPath);
      String line;
      while (configfile.available()) {
        line = configfile.readStringUntil('\n');
        if (line.indexOf(param) != -1 && line.indexOf('=') != -1 && line.indexOf('#') == -1)
        {
          if (DEBUG) Serial.println(line);
          line = line.substring(line.indexOf("=") + 1); //search for "="
          line.trim(); //remove possible whitespace
          if (DEBUG) Serial.println(line);
          int output = line.toInt(); //convert to int (returns 0 if not possible)
          if (DEBUG) Serial.println(output);
          return (output);
        }
      }
      Serial.print("config read error!");
      return -1;
    }

    int readBMP(String path)
    {
      //see http://www.ece.ualberta.ca/~elliott/ee552/studentAppNotes/2003_w/misc/bmp_file_format/bmp_file_format.htm for reference
      struct bmp_file_header {
        uint16_t signature;
        uint32_t file_size;
        uint32_t reserved[4];
        uint32_t image_offset;
      };
      struct bmp_info_header {
        uint32_t header_size;
        uint32_t image_width;
        uint32_t image_height;
        uint16_t color_planes;
        uint16_t bits_per_pixel;
        uint32_t compression_method;
        uint32_t image_size;
        uint32_t horizontal_resolution;
        uint32_t vertical_resolution;
        uint32_t colors_in_palette;
        uint32_t important_colors;
      };
      if (DEBUG) {
        Serial.print("loading File:  ");
        Serial.println(path);
      }
      File bmpFile = SD.open(path);
      if (!bmpFile) {
        Serial.println("Error: Failed to open");
        return -1;
      }
      bmp_file_header file_header;
      bmp_info_header info_header;
      file_header.signature = readNbytes16(bmpFile);
      bmpFile.seek(bmpFile.position() + 8);
      file_header.image_offset = readNbytes32(bmpFile);
      bmpFile.seek(bmpFile.position() + 4);
      info_header.image_width = readNbytes32(bmpFile);
      info_header.image_height = readNbytes32(bmpFile);
      bmpFile.seek(bmpFile.position() + 2);
      info_header.bits_per_pixel = readNbytes16(bmpFile);
      info_header.compression_method = readNbytes32(bmpFile);

      if (file_header.signature != 0x4D42) //BMP signature check
      {
        Serial.print("Error: Invalid file signature!");
        Serial.println(file_header.signature);
        return -1;
      }
      if (info_header.compression_method != 0) //check for no compression
      {
        Serial.print("Error: Invalid compression!");
        Serial.println(info_header.compression_method);
        return -1;
      }
      if (info_header.image_width != 16 || info_header.image_height != 16 ) //check that image is 16x16
      {
        Serial.print("Error: Invalid resolution!");
        Serial.println(info_header.image_width + "x" + info_header.image_height);
        return -1;
      }
      if (info_header.bits_per_pixel != 24) //check for 24 bit BMP
      {
        Serial.println("Error: Only 24 bit files are supported!");
        return -1;
      }
      bmpFile.seek(file_header.image_offset);   //skip the whole header
      byte r, g, b;
      for (byte column = 1; column <=  16; column++)
      {
        for (byte row = 1; row <= 16; row++)
        {
          b = bmpFile.read();
          g = bmpFile.read();
          r = bmpFile.read();
          CRGB color = CRGB(r, g, b);
          matrix->setPixel(row, column, color);
        }
      }
      return 0;
    }

    void drawTimeAndTemp()
    {
      String hours, minutes;
      sensors->getTime(minutes, hours);
      font7x3.drawNumber(*matrix, 1, 9, hours, timeColor);
      font7x3.drawNumber(*matrix, 10, 9, minutes, timeColor);
#ifdef USE_TEMP_SENSOR
      matrix->setPixel(11, 6, timeColor);
      font5x3.drawNumber(*matrix, 3, 2, String(sensors->readTemp()), timeColor);
      font5x3.drawNumber(*matrix, 13, 2, "c", timeColor);
#endif
    }

    void timemode(bool autocycle)
    {
      CRGB colors[5] = {CRGB::White, CRGB::Red, CRGB::Blue, CRGB::Green, CRGB::Yellow};
      byte curColor = 0;
      long autoClockTimer = millis();
      while (true)
      {
        FastLED.clear();
        sensors->controllBrightness();
        byte i = sensors->readButtons();
        switch (i)
        {
          case 1:
            return;
          case 2:
            break;
          case 3:
            curColor++;
            if (curColor >= 5) {
              curColor = 0;
            }
            timeColor = colors[curColor];
            break;
        }
        if (autocycle && AUTO_CLOCK_DURATION != 0) {
          if (millis() - autoClockTimer > AUTO_CLOCK_DURATION * 1000)
            break;
          }
        drawTimeAndTemp();
        matrix->update();
      }
    }
};

int countFrames(String param, String path)
{
  unsigned long cTime = millis();
  int counter = 0;
  File folder = SD.open(path);
  File file = folder.openNextFile();
  while (file)
  {
    String filename = file.name();
    Serial.println(filename);
    if (filename.indexOf(".bmp") != -1 || filename.indexOf(".BMP") != -1)
      counter++;
    file = folder.openNextFile();
  }
  File configfile = SD.open(path + "/config.ini", FILE_APPEND);
  Serial.println(configfile.name());
  configfile.println(param + " = " + String(counter));
  configfile.close();
  return counter;
}

#endif
