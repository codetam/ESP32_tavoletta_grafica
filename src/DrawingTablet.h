#ifndef DRAWINGTABLET_H
#define DRAWINGTABLET_H

#include "Constants.h"
#include <stack>
#include <array>

class DrawingTablet{
  private:
    TFT_eSPI tft;
    char pixelMatrix[MAX_X][MAX_Y];
    int prevX;
    int prevY;
    char prevColor;
    char current_color;
    tablet_mode mode;
    bool checkCoordinates(int x, int y);
  public:
    DrawingTablet();
    void startDriver();
    void initialize();
    void drawPixel(int x, int y, char color);
    void print();
    void moveCursor(int x, int y);
    TFT_eSPI get_driver();
    void setMode(tablet_mode new_mode); //setter per mode
    void setMode(menu_selection new_selection); //cambia mode in base al menu
    tablet_mode getMode();
    void colorArea(int x, int y, char new_color);
    void setCurrentColor(char color){ current_color = color; }
    char getCurrentColor() { return current_color; }
    String stringify();
};

#endif