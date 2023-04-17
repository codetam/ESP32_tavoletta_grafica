#include "src/DrawingTablet.h"
#include "src/Controller.h"
#include "src/Menu.h"

DrawingTablet* tablet;
Controller* controller;
Menu* menu;

unsigned long last_millis_controller_btn = 0;
unsigned long last_millis_lone_btn = 0;
long debouncing_time = 1000;  //millisecondi

boolean showMenu = false;
boolean shouldPrintTablet = false;
boolean shouldColor = false;

//se il button viene premuto, viene aperto/chiuso il menu
void loneButtonPressed() {
  //verifica il debouncing
  if (millis() - last_millis_controller_btn > debouncing_time) {
    showMenu = !showMenu;
    if (!showMenu) {
      //non posso usare tablet->print() qui perchè l'interrupt deve durare poco
      shouldPrintTablet = true;
    } else {
      menu->print();
    }
    last_millis_controller_btn = millis();
  }
}

//se il controller viene premuto, viene cambiata modalità o colorata un'area
void controllerButtonPressed() {
  if (millis() - last_millis_lone_btn > debouncing_time) {
    if (!showMenu) {
      switch (tablet->getMode()) {
        case drawing:
          tablet->setMode(cursor);
          break;
        case cursor:
          tablet->setMode(drawing);
          break;
        case coloring:
          shouldColor = true;
          break;
      }
    }
    last_millis_lone_btn = millis();
  }
}

void setup(void) {
  controller = new Controller();
  tablet = new DrawingTablet();
  tablet->startDriver();

  menu = new Menu(tablet->get_driver());

  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(PIN_PUSHBTN), controllerButtonPressed, RISING);
  attachInterrupt(digitalPinToInterrupt(PIN_LONEBTN), loneButtonPressed, RISING);
}

void loop() {
  while (!showMenu) {
    if (shouldPrintTablet) {
      //Viene svuotato il menu e viene ricaricato il disegno precedente
      tablet->print();
      shouldPrintTablet = false;
    }
    controller->readInput();
    if(!shouldColor){
      updateTablet();
    }
    else{
      tablet->colorArea(controller->getCursorX(), controller->getCursorY(), TFT_BLACK);
      shouldColor = false;
    }
    delay(50);
  }
  while (showMenu) {
    controller->readInput();
    menu_selection current_selection = menu->getSelection();
    menu->switchSelection(controller->getDirection());
    //se la selezione cambia, si ri-stampa il menù
    if(menu->getSelection() != current_selection){
      tablet->setMode(menu->getSelection());
      menu->print();
      delay(500);
    }  
    delay(50);
  }
}

void updateTablet() {
  switch (tablet->getMode()) {
    case drawing:
      tablet->drawPixel(controller->getCursorX(), controller->getCursorY(), TFT_BLACK);
      break;
    case cursor:
      tablet->moveCursor(controller->getCursorX(), controller->getCursorY());
      break;
    case coloring:
      tablet->moveCursor(controller->getCursorX(), controller->getCursorY());
      break;
  }
}
