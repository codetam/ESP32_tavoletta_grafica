#ifndef TAVOLADISEGNO_H
#define TAVOLADISEGNO_H

#include "Arduino.h"
#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library

#define MAX_X 120 //480
#define MAX_Y 80 //320

        
class TavolaDisegno{
    private:
        bool pixelArray[MAX_X][MAX_Y];
        TFT_eSPI tft = TFT_eSPI();
    public:
        TavolaDisegno();
        void inizializzaTavola();
        void stampaDati();
        void disegnaPixel(int x, int y);
};

#endif
