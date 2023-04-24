#ifndef CONSTANTS_H
#define CONSTANTS_H

#define MAX_X 120  //480
#define MAX_Y 80   //320

#define PIN_Y 34      //devo usare ADC_1 altrimenti il controller + wifi non funziona
#define PIN_X 35      //devo usare ADC_1 altrimenti il controller + wifi non funziona
#define PIN_PUSHBTN 25
#define PIN_LONEBTN 2
#define NUM_SELECTIONS 3
#define NUM_MENU_SELECTIONS 5

enum direction{
  left,
  right,
  center
};

enum menu_selection{
    change_color,
    draw,
    color,
    change_brush_size,
    save_drawing
};

enum tablet_mode{
  drawing,
  coloring,
  cursor
};

enum brush_size{
  small,
  medium,
  large
};

#endif