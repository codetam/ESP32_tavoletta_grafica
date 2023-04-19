#ifndef CONSTANTS_H
#define CONSTANTS_H

#define MAX_X 120  //480
#define MAX_Y 80   //320

#define PIN_Y 12
#define PIN_X 13 
#define PIN_PUSHBTN 25
#define PIN_LONEBTN 2
#define NUM_SELECTIONS 3

enum direction{
  left,
  right,
  center
};

enum menu_selection{
    change_color,
    draw,
    color,
    change_brush_size
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
}

#endif