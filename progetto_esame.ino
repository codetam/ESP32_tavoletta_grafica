#include "src/Constants.h"
#include "src/Manager.h"
#include "src/DrawingTablet.h"
#include "src/MqttHandler.h"
#include "src/ConnectionHandler.h"
#include "src/Controller.h"
#include "src/LCDDisplay.h"
#include "src/Menu.h"
#include "src/ColorWheel.h"

DrawingTablet* tablet;
Controller* controller;
Menu* menu;
ColorWheel* color_wheel;
Manager* manager;
LCDDisplay* display;
ConnectionHandler* connection_handler;
MqttHandler* mqtt_handler;

unsigned long last_millis_controller_btn = 0;
unsigned long last_millis_lone_btn = 0;
long debouncing_time = 1000;  //millisecondi

SemaphoreHandle_t mutex;

void run_display(void* ptr){
  int i = 0;
  char curr_color;
  lcd_state curr_state;
  char prev_color = '0';
  lcd_state prev_state = display->getState();
  display->print();
  while(true){
    xSemaphoreTake(mutex, portMAX_DELAY);
    curr_color = display->getColor();
    curr_state = display->getState();
    if(prev_state != curr_state || prev_color != curr_color){
      prev_color = curr_color;
      prev_state = curr_state;
      i++;
      if(i > 10){
        display->init();
        i = 0;
      }
      display->print();
    }
    xSemaphoreGive(mutex);
    delay(500);
  }
}

void loneButtonPressed()                                            // Se il button viene premuto, viene aperto/chiuso il menu
{
  if (millis() - last_millis_controller_btn > debouncing_time)      // Verifica il debouncing
  {
    manager->toggleMenu();
     
    if(manager->shouldShowMenu())
    {
      menu->print();
    }
    else
    {
      manager->switchToTablet();                                    // Non posso direttamente stampare la matrice perchè
    }                                                               // la callback prevede un tempo di esecuzione piccolo
    last_millis_controller_btn = millis();
  }
}

void controllerButtonPressed()                                      // Se il controller viene premuto
{
  if (millis() - last_millis_lone_btn > debouncing_time)            // Verifica il debouncing
  {
    if(manager->shouldShowMenu())                                   // Può selezionare un nuovo colore, salvare 
    { 
      switch(menu->getSelection()){
        case change_color:
          if(manager->shouldPrintColorWheel())                        // se mostra la color wheel
          {
            manager->switchToMenu();                                  // passa a modalità menu  
            menu->print();                                            // stampa il menu
          }
          else                                                        // se è in modalità menu
          {
            color_wheel->setShouldPrint();                            // stampa la color wheel                
            manager->switchToColorWheel();                            // passa in modalità color wheel
          }
          break;
        case save_drawing:
          manager->switchToSavingMode();
          break;
        case load_drawing:
          manager->switchToLoadingMode();
          break;
        case connect:
          manager->switchToConnectingMode();
          break;
        default:
          manager->switchToTablet();
          break;
      }
    }
    else                                                            // Può passare da cursore a pennello
    {                                                               // oppure colorare un'area
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
  mutex = xSemaphoreCreateMutex();
  Serial.begin(115200);
  display = new LCDDisplay();
  display->init();

  manager = new Manager();
  mqtt_handler = new MqttHandler();
  connection_handler = new ConnectionHandler("Mi Note 10 Lite","gerardoMau",tablet, mqtt_handler);

  controller = new Controller();
  tablet = new DrawingTablet();
  tablet->startDriver();
  menu = new Menu(tablet->get_driver(), connection_handler);
  color_wheel = new ColorWheel(tablet->get_driver());

  attachInterrupt(digitalPinToInterrupt(PIN_PUSHBTN), controllerButtonPressed, RISING);
  attachInterrupt(digitalPinToInterrupt(PIN_LONEBTN), loneButtonPressed, RISING);

  display->setState(lcd_drawing);
  
  xTaskCreatePinnedToCore(
      run_display, /* Function to implement the task */
      "runDisplay", /* Name of the task */
      20000,  /* Stack size in words */
      NULL,  /* Task input parameter */
      0,  /* Priority of the task */
     NULL,  /* Task handle. */
     0); /* Core where the task should run */
}

void loop()
{
  controller->readInput();                                                    // Aggiorna le variabili dell'oggetto controller
  
  if (manager->shouldShowMenu())
  {
    if (manager->shouldPrintColorWheel())                                     // Modalità color wheel
    {
      char current_color = color_wheel->getColor();
      color_wheel->switchSelection(controller->getDirection());

      if (color_wheel->getColor() != current_color)                           // Il colore è stato cambiato
      {
        tablet->setCurrentColor(color_wheel->getColor());
        display->setColor(color_wheel->getColor());
        color_wheel->setShouldPrint();
      }
      xSemaphoreTake(mutex, portMAX_DELAY);
      color_wheel->print();                                                   // Ri-stampa solo se setShouldPrint() è chiamata
      xSemaphoreGive(mutex);
    }
    else if(manager->shouldSave())
    {
      display->setState(lcd_loading);
      tablet->stringify();                                                    // Ricava la stringa dall'immagine e la pone in pixelString
      strcpy(post_data, "uid=");
      strcat(post_data, connection_handler->getUid().c_str());
      strcat(post_data, "&pwd=");
      strcat(post_data, connection_handler->getPwd().c_str());
      strcat(post_data, "&sent_image=");
      strcat(post_data, pixelString);
      int status = connection_handler->post_to_server("iot.dayngine.com", 8056, "/remote/upload_image.php", post_data, false);    //  L'immagine viene caricata sul database
      if(status == 200){
        display->setString("Immagine salvata", "con successo.");
      }
      else{
        display->setString("Errore durante", "il salvataggio.");
      }
      display->setState(lcd_print_string);
      delay(550);                                                             // Viene dato il tempo allo schermo LCD di stampare la stringa
      xSemaphoreTake(mutex, portMAX_DELAY);
      manager->switchToMenu();
      menu->print();                                                          // Viene stampato il menu
      xSemaphoreGive(mutex);
    }
    else if(manager->shouldLoad()){
      display->setState(lcd_loading);
      int status = connection_handler->post_to_server("iot.dayngine.com", 8056, "/remote/load_image.php", "uid=" + connection_handler->getUid() + "&pwd=" + connection_handler->getPwd() + "&imageId=" + imageId, true);
      if(status == 200){
        display->setString("Immagine", "caricata");
      }
      else{
        display->setString("Errore durante", "il caricamento");
      }
      display->setState(lcd_print_string);
      delay(500);                                                             // Viene dato il tempo allo schermo LCD di stampare la stringa
      xSemaphoreTake(mutex, portMAX_DELAY);
      tablet->replaceTablet();
      xSemaphoreGive(mutex);
      manager->switchToTablet();
    }
    else if(manager->shouldConnect()){
      display->setState(lcd_connecting);
      connection_handler->setup();
      display->setIP(connection_handler->getIP());
      connection_handler->createWebServer();  
      display->setState(lcd_drawing);
      delay(500);                                     
      manager->switchToMenu();                                                  
      xSemaphoreTake(mutex, portMAX_DELAY);
      menu->print();                                                          // Viene stampato il menu
      xSemaphoreGive(mutex);
    }
    else 
    {
      menu_selection current_selection = menu->getSelection();                // Modalità menù
      menu->switchSelection(controller->getDirection());

      if (menu->getSelection() != current_selection) 
      {
        tablet->setMode(menu->getSelection());                                // Aggiorna la modalità della tavoletta 
        xSemaphoreTake(mutex, portMAX_DELAY);
        menu->printSelection();                                               // Ri-stampa solo se la selezione è cambiata
        xSemaphoreGive(mutex);
      }
    }
    delay(100);
  }
  else                                                                        // Modalità tablet
  {
    if (manager->shouldPrintTablet())                                         // Appena switchato a modalità tablet
    {
      if(tablet->getMode() == cursor){
        display->setState(lcd_drawing);
      }
      else if(tablet->getMode() == coloring){
        display->setState(lcd_coloring);
      }
      xSemaphoreTake(mutex, portMAX_DELAY);
      tablet->print();                                                        // Viene svuotato il menu e ricaricato il disegno precedente
      manager->switchToCursor();
      xSemaphoreGive(mutex);
    }

    if (manager->isBucketEnabled())                                           //modalità bucket
    {
      tablet->colorArea(controller->getCursorX(), controller->getCursorY(), tablet->getCurrentColor());
      manager->switchToCursor();
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
      tablet->drawPixel(controller->getCursorX(), controller->getCursorY(), tablet->getCurrentColor()); // Disegna
      break;
    case cursor:
      tablet->moveCursor(controller->getCursorX(), controller->getCursorY());                           // Muove il cursore
      break;
    case coloring:
      tablet->moveCursor(controller->getCursorX(), controller->getCursorY());                           // Muove il cursore
      break;
  }
}
