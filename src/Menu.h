#ifndef MENU_H
#define MENU_H

#include "TFT_eSPI.h"
#include <SPI.h>
#include "Free_Fonts.h" // Include the header file attached to this sketch
#include "Constants.h"

class Menu{
    private:
        TFT_eSPI tft;
        menu_selection current_selection;
    public:
        Menu(TFT_eSPI tft_ready);
        void print();
        void switchSelection(direction current_direction);
        menu_selection getSelection();
        void printSelection();
};

#endif