#ifndef MATRIX_ROTATE
#define MATRIX_ROTATE

void swap_pixel(cLEDMatrixBase &matrix, byte x1, byte y1, byte x2, byte y2) {
  byte rTemp = matrix(x1, y1).r;
  byte gTemp = matrix(x1, y1).g;
  byte bTemp = matrix(x1, y1).b;
  matrix(x1, y1).r = matrix(x2, y2).r;
  matrix(x1, y1).g = matrix(x2, y2).g;
  matrix(x1, y1).b = matrix(x2, y2).b;
  matrix(x2, y2).r = rTemp;
  matrix(x2, y2).g = gTemp;
  matrix(x2, y2).b = bTemp;
}

void rotate(cLEDMatrixBase &matrix) {
  unsigned long cTime = millis();
  for (int n = 0; n < 2; n++) {
    for (int i = 0; i < MATRIX_WIDTH; i++) {
      for (int j = i + 1; j < MATRIX_HEIGHT; j++) {
        swap_pixel(matrix, i, j, j, i);
      }
    }
    for (int i = 0; i < MATRIX_WIDTH; i++) {
      for (int j = 0; j < MATRIX_HEIGHT / 2; j++) {
        swap_pixel(matrix, i, j, i, MATRIX_HEIGHT - j - 1);
      }
    }
  }
}
#endif
