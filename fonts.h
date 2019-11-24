#ifndef FONTS_H
#define FONTS_H

//currently PROGMEM in class members doesnt work on ESP8266
#ifdef ESP8266
#define PROG_MEM
#else
#define PROG_MEM PROGMEM
#endif

class font5x3
{
  private:
    byte fontwidth = 3;
    byte fontheight = 5;
    const bool n1[15] PROG_MEM = {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1};
    const bool n2[15] PROG_MEM = {1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1};
    const bool n3[15] PROG_MEM = {1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1};
    const bool n4[15] PROG_MEM = {0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1};
    const bool n5[15] PROG_MEM = {1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1};
    const bool n6[15] PROG_MEM = {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1};
    const bool n7[15] PROG_MEM = {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1};
    const bool n8[15] PROG_MEM = {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1};
    const bool n9[15] PROG_MEM = {1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1};
    const bool n0[15] PROG_MEM = {1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1};
    const bool nc[15] PROG_MEM = {1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0};

  public:
    font5x3() {}
    ~font5x3() {}
    //This Method gets as input an string of numbers (s) and a starting position s_x and s_y. c1 is the foreground color and c2 the background color.
    //The Method then goes through the input string and chooses the right array containing boolean pixeldata (1 = foreground color, 0 = background color)
    void drawNumber(Matrix &matrix, byte s_x, byte s_y, String s, CRGB c1 = CRGB::White, CRGB c2 = CRGB::Black) //Draw a  Number at x,y
    {
      bool * numberTemp; //temporary non const pointer to store the right address
      for (byte i = 0; i < s.length(); i++) //go through the input string s f.e. "10"
      {
        byte x = s_x + (fontwidth + 1) * i; //x,y drawing position  for the current number
        byte y = s_y;
        switch (s[i]) //chose the right array for the current nuber
        {
          case '1': numberTemp = (bool*)n1;
            break;
          case '2': numberTemp = (bool*)n2;
            break;
          case '3': numberTemp = (bool*)n3;
            break;
          case '4': numberTemp = (bool*)n4;
            break;
          case '5': numberTemp = (bool*)n5;
            break;
          case '6': numberTemp = (bool*)n6;
            break;
          case '7': numberTemp = (bool*)n7;
            break;
          case '8': numberTemp = (bool*)n8;
            break;
          case '9': numberTemp = (bool*)n9;
            break;
          case 'c': numberTemp = (bool*)nc;
            break;
          default: numberTemp = (bool*)n0;
            break;
        }
        const bool* number = numberTemp; //make it const again
        for (byte column = 1, counter = 0; column <=  fontheight; column++) //Set the right pixels in the led matrix based on the array chosen above.
        {
          for (byte row = 1; row <= fontwidth; row++, counter++)
          {
            if (number[counter] == true)
              matrix.setPixel(x + row - 1, y + column - 1, c1);
            else
              matrix.setPixel(x + row - 1, y + column - 1, c2);
          }
        }
      }
    }
};

class font7x3
{
  private:
    byte fontwidth = 3;
    byte fontheight = 7;
    const bool n1[21] PROG_MEM = {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1};
    const bool n2[21] PROG_MEM = {1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1};
    const bool n3[21] PROG_MEM = {1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1};
    const bool n4[21] PROG_MEM = {0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1};
    const bool n5[21] PROG_MEM = {1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1};
    const bool n6[21] PROG_MEM = {1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1};
    const bool n7[21] PROG_MEM = {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1};
    const bool n8[21] PROG_MEM = {1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1};
    const bool n9[21] PROG_MEM = {1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1};
    const bool n0[21] PROG_MEM = {1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1};
    const bool nc[21] PROG_MEM = {1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0};

  public:
    font7x3() {}
    ~font7x3() {}
    void drawNumber(Matrix &matrix, byte s_x, byte s_y, String s, CRGB c1 = CRGB::White, CRGB c2 = CRGB::Black) //Draw a  Number at x,y
    {
      bool * numberTemp; //temporary non const pointer to store the right address
      for (byte i = 0; i < s.length(); i++) //go through the input string s f.e. "10"
      {
        byte x = s_x + (fontwidth + 1) * i; //x,y drawing position  for the current number
        byte y = s_y;
        switch (s[i]) //chose the right array for the current nuber
        {
          case '1': numberTemp = (bool*)n1;
            break;
          case '2': numberTemp = (bool*)n2;
            break;
          case '3': numberTemp = (bool*)n3;
            break;
          case '4': numberTemp = (bool*)n4;
            break;
          case '5': numberTemp = (bool*)n5;
            break;
          case '6': numberTemp = (bool*)n6;
            break;
          case '7': numberTemp = (bool*)n7;
            break;
          case '8': numberTemp = (bool*)n8;
            break;
          case '9': numberTemp = (bool*)n9;
            break;
          case 'c': numberTemp = (bool*)nc;
            break;
          default: numberTemp = (bool*)n0;
            break;
        }
        const bool* number = numberTemp; //make it const again
        for (byte column = 1, counter = 0; column <=  fontheight; column++) //Set the right pixels in the led matrix based on the array chosen above.
        {
          for (byte row = 1; row <= fontwidth; row++, counter++)
          {
            if (number[counter] == true)
              matrix.setPixel(x + row - 1, y + column - 1, c1);
            else
              matrix.setPixel(x + row - 1, y + column - 1, c2);
          }
        }
      }
    }
};

#endif //fonts_matrix_h
