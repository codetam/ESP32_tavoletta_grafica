#ifndef DRAWINGTABLET_H
#define DRAWINGTABLET_H

#include <SPI.h>
#include <TFT_eSPI.h>

#define MAX_X 120  //480
#define MAX_Y 80   //320

enum color{
  white,
  black,
  dark_grey,
  light_grey,
  red
};

class DrawingTablet{
  private:
    TFT_eSPI tft;
    color pixelMatrix[MAX_X][MAX_Y];
    int prevX;
    int prevY;
    color prevColor;
  public:
    DrawingTablet();
    void startDriver();
    void initialize();
    void drawPixel(int x, int y, color col);
    void print();
    void moveCursor(int x, int y);
    int getColor(color col);
};

#endif