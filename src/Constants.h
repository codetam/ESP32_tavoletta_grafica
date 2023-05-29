#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "Arduino.h"

#define MAX_X 120  //480
#define MAX_Y 80   //320
#define LCD_ROWS 2
#define LCD_COLUMNS 16

// I pin sono invertiti
#define PIN_Y 35      //devo usare ADC_1 altrimenti il controller + wifi non funziona
#define PIN_X 34      //devo usare ADC_1 altrimenti il controller + wifi non funziona
#define PIN_PUSHBTN 25
#define PIN_LONEBTN 2
#define PIN_SCL 22
#define PIN_SDA 21
#define NUM_SELECTIONS 3
#define NUM_MENU_SELECTIONS 5

#define BLACK 0
#define WHITE 1
#define LIGHTGREY 2
#define BLUE 3
#define GREEN 4
#define RED 5
#define YELLOW 6
#define ORANGE 7

extern char post_data[10000];
extern char pixelString[9601];
extern char imageId[10];

enum direction{
  left,
  right,
  center
};

enum menu_selection{
    change_color,
    draw,
    color,
    connect,
    load_drawing,
    save_drawing
};

enum tablet_mode{
  drawing,
  coloring,
  cursor
};

enum lcd_state{
  lcd_drawing,
  lcd_coloring,
  lcd_connecting,
  lcd_loading,
  lcd_print_string,
};

uint16_t getColorFromChar(char num);
String getColorStringFromChar(char num);

#endif