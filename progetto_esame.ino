#include "src/DrawingTablet.h"
#include "src/Controller.h"
#include "src/Menu.h"
#include "src/ColorWheel.h"

TaskHandle_t TaskController;
xTaskCreatePinnedToCore(
      ControllerCode, /* Function to implement the task */
      "TaskController", /* Name of the task */
      10000,  /* Stack size in words */
      NULL,  /* Task input parameter */
      0,  /* Priority of the task */
      &TaskController,  /* Task handle. */
      0); /* Core where the task should run */

DrawingTablet* tablet;
Controller* controller;
Menu* menu;
ColorWheel* color_wheel;

unsigned long last_millis_controller_btn = 0;
unsigned long last_millis_lone_btn = 0;
long debouncing_time = 1000;  //millisecondi

boolean showMenu = false;
boolean shouldPrintTablet = false;
boolean shouldColor = false;
boolean shouldPrintColorWheel = false;

//se il button viene premuto, viene aperto/chiuso il menu
void loneButtonPressed() {
  //verifica il debouncing
  if (millis() - last_millis_controller_btn > debouncing_time) {
    showMenu = !showMenu;
    if (!showMenu) {
      //non posso usare tablet->print() qui perchè l'interrupt deve durare poco
      shouldPrintTablet = true;
      shouldPrintColorWheel = false;
    } 
    else {
      menu->print();
    }
    last_millis_controller_btn = millis();
  }
}

//se il controller viene premuto, viene cambiata modalità o colorata un'area
void controllerButtonPressed() {
  if (millis() - last_millis_lone_btn > debouncing_time) {
    //se non sono nel menù, cliccare il controller button switcha tra drawing e cursor, oppure colora
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
    //Se sono nel menù (click del button prevede la stampa della color wheel solo se ho selezionato "cambia colore")
    //altrimenti prevede il ritorno alla modalità tablet
    else{
      if(menu->getSelection() == change_color){
          color_wheel->setShouldPrint();
          shouldPrintColorWheel = true; 
      }
      else{
        showMenu = false;
        shouldPrintTablet = true;
        shouldPrintColorWheel = false;
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
  color_wheel = new ColorWheel(tablet->get_driver());
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
    //se non mi trovo in modalità color, muoverò il cursore o disegnerò
    if(!shouldColor){
      updateTablet();
    }
    //se sono in modalità color e premo il button, verrà colorata la zona
    else{
      tablet->colorArea(controller->getCursorX(), controller->getCursorY(), tablet->getCurrentColor());
      shouldColor = false;
    }
    delay(50);
  }
  while (showMenu) {
    if(shouldPrintColorWheel){
      controller->readInput();
      uint16_t current_color = color_wheel->getColor();
      color_wheel->switchSelection(controller->getDirection());
      if(color_wheel->getColor() != current_color){
        tablet->setCurrentColor(color_wheel->getColor());
        color_wheel->setShouldPrint();
        delay(100);
      }
      //stampa solo se setShouldPrint() è chiamata
      color_wheel->print();
      delay(50);  
    }
    else{
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
}

void updateTablet() {
  switch (tablet->getMode()) {
    case drawing:
      tablet->drawPixel(controller->getCursorX(), controller->getCursorY(), tablet->getCurrentColor());
      break;
    case cursor:
      tablet->moveCursor(controller->getCursorX(), controller->getCursorY());
      break;
    case coloring:
      tablet->moveCursor(controller->getCursorX(), controller->getCursorY());
      break;
  }
}
