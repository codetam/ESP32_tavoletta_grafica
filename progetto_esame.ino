#include "src/DrawingTablet.h"
#include "src/Controller.h"

DrawingTablet tablet;
Controller controller;

void setup(void) {
  Serial.begin(115200);
  //needed to start the driver
  tablet.startDriver();
}

void loop() {
  controller.readInput();
  tablet.drawPixel(controller.getCursorX(), controller.getCursorY(), light_grey);
  delay(100);
}

