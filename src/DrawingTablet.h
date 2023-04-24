#ifndef DRAWINGTABLET_H
#define DRAWINGTABLET_H

#include <SPI.h>
#include <TFT_eSPI.h>
#include "Constants.h"
#include <stack>
#include <array>

class DrawingTablet{
  private:
    TFT_eSPI tft;
    uint16_t pixelMatrix[MAX_X][MAX_Y];
    int prevX;
    int prevY;
    uint16_t prevColor;
    uint16_t current_color;
    tablet_mode mode;
    bool checkCoordinates(int x, int y);
  public:
    DrawingTablet();
    void startDriver();
    void initialize();
    void drawPixel(int x, int y, uint16_t color);
    void print();
    void moveCursor(int x, int y);
    TFT_eSPI get_driver();
    void setMode(tablet_mode new_mode); //setter per mode
    void setMode(menu_selection new_selection); //cambia mode in base al menu
    tablet_mode getMode();
    void colorArea(int x, int y, uint16_t new_color);
    void setCurrentColor(int16_t color){ current_color = color; }
    uint16_t getCurrentColor() { return current_color; }
    String stringify();
};

#endif