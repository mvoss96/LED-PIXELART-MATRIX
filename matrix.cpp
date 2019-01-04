#include "matrix.h"


Matrix::Matrix() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, MATRIX_WIDTH * MATRIX_HEIGHT).setCorrection(TypicalSMD5050);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 1000);
  FastLED.setBrightness(64);

}

void Matrix::setPixel(byte x, byte y, CRGB color) {
  int pos;
  if (y % 2) {
    pos = (y - 1) * MATRIX_WIDTH + x - 1;
  }
  else {
    pos = (y - 1) * MATRIX_WIDTH + MATRIX_WIDTH - x;
  }
  leds[pos] = color;
}

CRGB Matrix::getPixel(byte x, byte y) {
  int pos;
  if (y % 2) {
    pos = (y - 1) * MATRIX_WIDTH + x - 1;
  }
  else {
    pos = (y - 1) * MATRIX_WIDTH + MATRIX_WIDTH - x;
  }
  //CRGB color = CRGB(leds[pos].r,)
  return leds[pos];
}

void Matrix::swapPixel(byte x1, byte y1, byte x2, byte y2) {
  CRGB tempColor = getPixel(x1, y1);
  setPixel(x1, y1, getPixel(x2, y2));
  setPixel(x2, y2, tempColor);
}

void Matrix::update() {
  for (int n = 0; n < rotation / 90; n++) {
    for (int i = 1; i <= MATRIX_WIDTH; i++) {
      for (int j = i + 1; j <= MATRIX_HEIGHT; j++) {
        swapPixel(i, j, j, i);
      }
    }
    for (int i = 1; i <= MATRIX_WIDTH; i++) {
      for (int j = 1; j <= MATRIX_HEIGHT / 2; j++) {
        swapPixel(i, j, i, MATRIX_HEIGHT - j + 1);
      }
    }
  }
  FastLED.show();
}

void Matrix::loadPgmImage(const long *image) {
  for (byte column = 1, counter = 0; column <=  MATRIX_HEIGHT; column++) //Set the right pixels in the led matrix based on the array chosen above.
  {
    for (byte row = 1; row <= MATRIX_WIDTH; row++, counter++)
    {
      setPixel(row, column, image[counter]);
    }
  }
}

