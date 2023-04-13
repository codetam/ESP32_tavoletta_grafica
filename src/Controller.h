#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Arduino.h"

#define MAX_X 120  //480
#define MAX_Y 80   //320

//in realtà sono invertiti
#define PIN_Y 13
#define PIN_X 12 

class Controller {
private:
  int analogX;
  int analogY;
  int cursorX;
  int cursorY;
  int prevCursorX;
  int prevCursorY;
public:
  Controller();
  void readInput();
  int getCursorX(){
    return cursorX;
  }
  int getCursorY(){
    return cursorY;
  }
  int getPrevCursorX(){
    return prevCursorX;
  }
  int getPrevCursorY(){
    return prevCursorY;
  }
};


#endif