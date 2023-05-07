#ifndef MENU_H
#define MENU_H

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