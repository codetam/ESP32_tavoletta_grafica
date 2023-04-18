#ifndef COLORWHEEL_H
#define COLORWHEEL_H

#include "TFT_eSPI.h"
#include <SPI.h>
#include "Free_Fonts.h" // Include the header file attached to this sketch
#include "Constants.h"

class ColorWheel{
    private:
        TFT_eSPI tft;
        uint16_t available_colors[8];
        int current_selection;
        void printSelection();
        bool shouldPrint;
    public:
        ColorWheel(TFT_eSPI tft_ready);
        void print();
};

#endif