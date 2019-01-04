#ifndef BMPREADER_H
#define BMPREADER_H
//read up to 4 Bytes form the File p_file and store it as  int32_t
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

//read up to 2 Bytes form the File p_file and store it as  int16_t
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


int readBMP(Matrix &matrix, String path)
{
  unsigned long start_time = millis();
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
      CRGB color = CRGB(r,g,b);
      matrix.setPixel(row, column, color);
    }
  }
  unsigned long current_time = millis();
  if (DEBUG)Serial.println("Time taken: " + String(current_time - start_time) + "ms");
  return 0;
}


#endif
