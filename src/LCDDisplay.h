#ifndef LCDDISPLAY_H
#define LCDDISPLAY_H

#include "Constants.h"
#include <LiquidCrystal_I2C.h>

class LCDDisplay{
    private:
        LiquidCrystal_I2C lcd;
        lcd_state current_state;
        char current_color;
        String ip;
        void print_drawing();
        void print_coloring();
        void print_connecting();
        void print_loading();
    public:
        LCDDisplay();
        void setState(lcd_state state){
            current_state = state;
        }
        void setColor(char color){
            current_color = color;
        }
        void setIP(String new_ip){
            ip = new_ip;
        }
        lcd_state getState(){
            return current_state;
        }
        char getColor(){
            return current_color;
        }
        void init();
        void print();
};  

#endif