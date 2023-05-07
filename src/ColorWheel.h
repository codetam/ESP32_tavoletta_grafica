#ifndef COLORWHEEL_H
#define COLORWHEEL_H

#include <Arduino.h>
#include "Constants.h"

#define NUM_COLORS 8

class ColorWheel{
    private:
        TFT_eSPI tft;
        char available_colors[NUM_COLORS];                     
        int current_selection;
        void printSelection();
        bool shouldPrint;
        void draw16pixels(int x, int y, uint16_t color);
    public:
        ColorWheel(TFT_eSPI tft_ready);
        void setShouldPrint();
        void print();
        void switchSelection(direction current_direction);
        char getColor(){ return available_colors[current_selection]; } // Ritorna il colore associato alla selezione
};

#endif