#ifndef FONTS_H
#define FONTS_H

class font5x3
{
  private:
    byte fontwidth = 3;
    byte fontheight = 5;
    bool n1[15] PROGMEM = {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1};
    bool n2[15] PROGMEM = {1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1};
    bool n3[15] PROGMEM = {1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1};
    bool n4[15] PROGMEM = {0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1};
    bool n5[15] PROGMEM = {1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1};
    bool n6[15] PROGMEM = {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1};
    bool n7[15] PROGMEM = {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1};
    bool n8[15] PROGMEM = {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1};
    bool n9[15] PROGMEM = {1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1};
    bool n0[15] PROGMEM = {1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1};
    bool nc[15] PROGMEM = {1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0};

  public:
    font5x3() {}
    ~font5x3() {}
    //This Method gets as input an string of numbers (s) and a starting position s_x and s_y. c1 is the foreground color and c2 the background color.
    //The Method then goes through the input string and chooses the right array containing boolean pixeldata (1 = foreground color, 0 = background color)
    void drawNumber(Matrix &matrix, byte s_x, byte s_y, String s, CRGB c1 = CRGB::White, CRGB c2 = CRGB::Black) //Draw a  Number at x,y
    {
      bool * number;
      for (byte i = 0; i < s.length(); i++) //go through the input string s f.e. "10"
      {
        byte x = s_x + (fontwidth + 1) * i; //x,y drawing position  for the current number
        byte y = s_y;
        switch (s[i]) //chose the right array for the current nuber
        {
          case '1': number = n1;
            break;
          case '2': number = n2;
            break;
          case '3': number = n3;
            break;
          case '4': number = n4;
            break;
          case '5': number = n5;
            break;
          case '6': number = n6;
            break;
          case '7': number = n7;
            break;
          case '8': number = n8;
            break;
          case '9': number = n9;
            break;
          case 'c': number = nc;
            break;
          default: number = n0;
            break;
        }
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
    bool n1[21] PROGMEM = {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1};
    bool n2[21] PROGMEM = {1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1};
    bool n3[21] PROGMEM = {1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1};
    bool n4[21] PROGMEM = {0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1};
    bool n5[21] PROGMEM = {1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1};
    bool n6[21] PROGMEM = {1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1};
    bool n7[21] PROGMEM = {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1};
    bool n8[21] PROGMEM = {1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1};
    bool n9[21] PROGMEM = {1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1};
    bool n0[21] PROGMEM = {1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1};
    bool nc[21] PROGMEM = {1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0};

  public:
    font7x3() {}
    ~font7x3() {}
    void drawNumber(Matrix &matrix, byte s_x, byte s_y, String s, CRGB c1 = CRGB::White, CRGB c2 = CRGB::Black) //Draw a  Number at x,y
    {
      bool * number;
      for (byte i = 0; i < s.length(); i++) //go through the input string s f.e. "10"
      {
        byte x = s_x + (fontwidth + 1) * i; //x,y drawing position  for the current number
        byte y = s_y;
        switch (s[i]) //chose the right array for the current nuber
        {
          case '1': number = n1;
            break;
          case '2': number = n2;
            break;
          case '3': number = n3;
            break;
          case '4': number = n4;
            break;
          case '5': number = n5;
            break;
          case '6': number = n6;
            break;
          case '7': number = n7;
            break;
          case '8': number = n8;
            break;
          case '9': number = n9;
            break;
          case 'c': number = nc;
            break;
          default: number = n0;
            break;
        }
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
