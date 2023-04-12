#ifndef DRAWINGTABLET_H
#define DRAWINGTABLET_H

#include <SPI.h>
#include <TFT_eSPI.h>

#define MAX_X 120  //480
#define MAX_Y 80   //320

class DrawingTablet{
  private:
    bool pixelMatrix[MAX_X][MAX_Y];
  public:
    DrawingTablet();
    void init();
    void initialize();
    void drawPixel(int x, int y);
    void print();
};

#endif