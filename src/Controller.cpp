#include "Controller.h"

Controller::Controller(){
  //inizializzazione dei PIN
  pinMode(PIN_X,INPUT_PULLUP);
  pinMode(PIN_Y,INPUT_PULLUP); 
  pinMode(PIN_PUSHBTN,INPUT_PULLUP);   
  pinMode(PIN_LONEBTN, INPUT);
  //cursore posto al centro dello schermo
  cursorX = MAX_X/2;
  cursorY = MAX_Y/2;
}

void Controller::readInput() {
  analogX = analogRead(PIN_X);
  analogY = analogRead(PIN_Y);

  //muove il cursore sullo schermo in base al valore dell'analogico
  if (analogX > 2500 && cursorX < MAX_X) {
    cursorX--;
    current_direction = left; // invertito
  } 
  else if (analogX < 1500 && cursorX > 0 ) {
    cursorX++;
    current_direction = right; // invertito
  }
  else{
    current_direction = center;
  }
  if (analogY > 2500 && cursorY < MAX_Y) {
    cursorY++;
  } 
  else if (analogY < 1500 && cursorY > 0 ) {
    cursorY--;
  }
}
