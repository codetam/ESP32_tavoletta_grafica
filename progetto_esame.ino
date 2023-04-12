#include "TavolaDisegno.h"
#include "Controller.h"


#define MAX_X 120 //480
#define MAX_Y 80 //320

void setup(void) {
    Serial.begin(115200);
    TavolaDisegno tav;
    for(int i=0; i<10; i++){ 
      tav.disegnaPixel(i, 40);
    }
}


void loop() {
}
