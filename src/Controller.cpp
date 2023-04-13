#include "Controller.h"

Controller::Controller(){
  pinMode(PIN_X,INPUT_PULLUP);
  pinMode(PIN_Y,INPUT_PULLUP);  
  cursorX = MAX_X/2;
  cursorY = MAX_Y/2;
}

void Controller::readInput() {
  analogX = analogRead(PIN_X);
  analogY = analogRead(PIN_Y);

  //invertiti
  if (analogX > 2500) {
    cursorX--;
  } else if (analogX < 1500) {
    cursorX++;
  }
  if (analogY > 2500) {
    cursorY++;
  } else if (analogY < 1500) {
    cursorY--;
  }
}

