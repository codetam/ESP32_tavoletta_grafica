#include "src/DrawingTablet.h"

DrawingTablet tav;

void setup(void) {
  Serial.begin(115200);
  tav.init();
  for (int i = 0; i < 10; i++) {
    tav.drawPixel(i, 40);
  }
}

void loop() {
}