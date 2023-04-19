#ifndef COLORWHEEL_H
#define COLORWHEEL_H

#include <Arduino.h>
#include "TFT_eSPI.h"
#include <SPI.h>
#include "Free_Fonts.h" // Include the header file attached to this sketch
#include "Constants.h"

#define NUM_COLORS 8

class ColorWheel{
    private:
        TFT_eSPI tft;
        uint16_t available_colors[NUM_COLORS];
        int current_selection;
        void printSelection();
        bool shouldPrint;
        void draw4pixels(int x, int y, uint16_t color);
    public:
        ColorWheel(TFT_eSPI tft_ready);
        void print();
        void switchSelection(direction current_direction);
        uint16_t getColor(){ return available_colors[current_selection]; }
        void setShouldPrint();
};

#endif