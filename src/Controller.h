#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Constants.h"

class Controller{
private:
  int analogX;
  int analogY;
  int cursorX;
  int cursorY;
  direction current_direction;
public:
  Controller();
  void readInput();
  int getCursorX(){ return cursorX; }
  int getCursorY(){ return cursorY; }
  direction getDirection(){ return current_direction; }
};


#endif