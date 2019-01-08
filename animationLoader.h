#ifndef ANIMATION_LOADER_H
#define ANIMATION_LOADER_H

void error_state(Matrix &matrix)
{
  while (true) {
    FastLED.clear();
    //load_stored_image(matrix, IMG_warning);
    FastLED.show();
  }
}

byte doBackgroundStuff(Matrix &matrix, DHT &dht)
{

  brightness_control();
}

int count_frames(String param, String path)
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

int readFromConfig(String param, String path)
{
  unsigned long cTime = millis();
  File configfile = SD.open(path);
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
      Serial.print("config read time: ");
      Serial.println(millis() - cTime);
      return (output);
    }
  }
  Serial.print("config read time error : ");
  Serial.println(millis() - cTime);
  return -1;
}

int drawAnimation(Matrix &matrix, String animationPath, int duration, DHT &dht)
{
  unsigned long debugTime = millis();
  byte nFrames = 0;
  byte curFrame = 0;
  int hold;
  int frames;
  bool pausemode = false;
  String configpath = "/config.ini";
  Serial.print("Loading animation:");
  Serial.println(animationPath);
  File dir = SD.open(animationPath);
  if (!dir)
  {
    Serial.println("Error: Animation doesn't exist!");
    error_state(matrix);
    return -1;
  }
  if (!dir.isDirectory())
  {
    Serial.println("Error: Not a directory");
    return -1;
  }
  File file = dir.openNextFile();
  if (!SD.exists(animationPath + configpath))
  {
    Serial.println("No config.ini found: Skipping directory!");
    return -1;
  }
  else
  {
    hold = readFromConfig("hold", animationPath + configpath);
    if (hold == 0) // if 0 is returned, there was an error
    {
      hold = 100;
      Serial.println("Error! There is something wrong with the config file!");
    }
    frames = readFromConfig("frames", animationPath + configpath);
    if (frames <= 0)
    {
      Serial.println("Error! no Frame count in config.ini -> creating...");
      frames = count_frames("frames", animationPath);
    }
  }
  if (DEBUG) Serial.println("Number of Frames:" + String(frames));
  long curTime = millis();
  while (millis() < (curTime + duration * 1000) || pausemode)
  {
    int i = 0;
    unsigned long timer = millis();
    while (i < frames)
    {
      String filename = animationPath + "/" + String(i) + ".bmp";
      i++;
      nFrames++;
      unsigned long cTime = millis();
      do
      {
        doBackgroundStuff(matrix, dht);
        int i = read_buttons();
        switch (i)
        {
          case 1:
            timemode(matrix, dht);
            break;
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
      }
      while (millis() < (timer + hold));
      if (DEBUG)
      {
        Serial.print("stuff:");
        Serial.print(millis() - cTime);
        Serial.print("frametime:");
        Serial.print(millis() - timer);
      }
      //rotate(matrix);
      matrix.update();
      timer = millis();
      if (readBMP(matrix, filename) != 0) {
        Serial.println("Error: Something went wrong");
        error_state(matrix);
        return -1;
      }
    }
  }
}

int load_all_animations(Matrix &matrix, DHT &dht)
{
  int start = 0;
  int nAnimations = 0;
  File root = SD.open("/");
  File dir = root.openNextFile();
  dir.openNextFile();
  while (dir)
  {
    if (dir.isDirectory()) {
      if (drawAnimation(matrix, dir.name(), 5, dht) == 1) {
        return 1;
      }
      nAnimations++;
      start = 0;
    }
    dir = root.openNextFile();
  }
  return 0;
}


#endif
