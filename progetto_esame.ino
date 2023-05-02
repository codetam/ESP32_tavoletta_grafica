/*
#include "src/DrawingTablet.h"
#include "src/Controller.h"
#include "src/Menu.h"
#include "src/ColorWheel.h"
#include "src/Manager.h"
#include "src/ConnectionHandler.h"

DrawingTablet* tablet;
Controller* controller;
Menu* menu;
ColorWheel* color_wheel;
Manager* manager;
ConnectionHandler* connection_handler;

unsigned long last_millis_controller_btn = 0;
unsigned long last_millis_lone_btn = 0;
long debouncing_time = 1000;  //millisecondi


void loneButtonPressed()                                                                        //se il button viene premuto, viene aperto/chiuso il menu
{
  if (millis() - last_millis_controller_btn > debouncing_time)                                  //verifica il debouncing
  {
    manager->toggleMenu();
     
    if(manager->shouldShowMenu())
    {
      menu->print();
    }
    else
    {
      manager->switchToTablet();
    }

    last_millis_controller_btn = millis();
  }
}

//se il controller viene premuto, viene cambiata modalità o colorata un'area
void controllerButtonPressed()
{
  if (millis() - last_millis_lone_btn > debouncing_time)                                          //verifica il debouncing
  {
    if(manager->shouldShowMenu())
    {
      if (menu->getSelection() == change_color)
      {
        if(manager->shouldPrintColorWheel())
        {
          manager->switchToMenu();
        }
        else
        {
          color_wheel->setShouldPrint();
          manager->switchToColorWheel();
        }  
      }
      else if(menu->getSelection() == save_drawing)
      {
        manager->switchToSavingMode();
      }
      else
      {
        manager->switchToTablet();
      }
    }
    else
    {
      switch (tablet->getMode())
      {
        case drawing:
          tablet->setMode(cursor);
          break;
        case cursor:
          tablet->setMode(drawing);
          break;
        case coloring:
          manager->switchToBucket();
          break;
      }
    }
    last_millis_lone_btn = millis();
  }
}

void setup(void)
{
  manager = new Manager();
  controller = new Controller();
  tablet = new DrawingTablet();
  tablet->startDriver();

  menu = new Menu(tablet->get_driver());
  color_wheel = new ColorWheel(tablet->get_driver());

  Serial.begin(115200);

  connection_handler = new ConnectionHandler("TP-Link_093A","85345010","192.168.1.11",tablet);
  connection_handler->setup();

  attachInterrupt(digitalPinToInterrupt(PIN_PUSHBTN), controllerButtonPressed, RISING);
  attachInterrupt(digitalPinToInterrupt(PIN_LONEBTN), loneButtonPressed, RISING);
}

void loop()
{
  controller->readInput();                                                    //Aggiorna le variabili dell'oggetto controller
  
  if (manager->shouldShowMenu())
  {
    if (manager->shouldPrintColorWheel())                                     //modalità color wheel
    {
      uint16_t current_color = color_wheel->getColor();
      color_wheel->switchSelection(controller->getDirection());

      if (color_wheel->getColor() != current_color)                           //Il colore è stato cambiato
      {
        tablet->setCurrentColor(color_wheel->getColor());                     
        color_wheel->setShouldPrint();
      }

      color_wheel->print();                                                   //ri-stampa solo se setShouldPrint() è chiamata
    }
    else if(manager->shouldSave())
    {
      connection_handler->send_to_server("sent_string=" + tablet->stringify());
      manager->switchToMenu();
      menu->print();
    }
    else 
    {
      menu_selection current_selection = menu->getSelection();                //modalità menù
      menu->switchSelection(controller->getDirection());

      if (menu->getSelection() != current_selection) 
      {
        tablet->setMode(menu->getSelection());
        menu->printSelection();                                                         //ri-stampa solo se la selezione è cambiata
      }
    }
    delay(100);
  }
  else                                                                         //modalità tablet
  {
    if (manager->shouldPrintTablet())                                          //appena switchato a modalità tablet
    {
      tablet->print();                                                         //Viene svuotato il menu e viene ricaricato il disegno precedente
      manager->switchToDrawingMode();
    }
    if (manager->isBucketEnabled())                                            //modalità bucket
    {
      tablet->colorArea(controller->getCursorX(), controller->getCursorY(), tablet->getCurrentColor());
      manager->switchToDrawingMode();
    }
    else
    {
      updateTablet();  
    }
  }
  delay(50);
}

void updateTablet()
{
  switch (tablet->getMode())
  {
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
*/

#include "src/DrawingTablet.h"
#include "src/ConnectionHandler.h"

ConnectionHandler* connection_handler;

void setup(void)
{
  DrawingTablet* tablet;
  Serial.begin(115200);
  connection_handler = new ConnectionHandler("TP-Link_093A","85345010","192.168.1.11",tablet);
  connection_handler->setup();
  connection_handler->createWebServer();
}

void loop(){}


