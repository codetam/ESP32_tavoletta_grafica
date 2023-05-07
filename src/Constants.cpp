#include "Constants.h"

uint16_t getColorFromChar(char num){
  uint16_t color;
  switch(num){
    case '0':
      color = TFT_BLACK;
      break;
    case '1':
      color = TFT_WHITE;
      break;
    case 'L':
      color = TFT_LIGHTGREY;
      break;
    case 'D':
      color = TFT_DARKGREY;
      break;
    case 'B':
      color = TFT_BLUE;
      break;
    case 'G':
      color = TFT_GREEN;
      break;
    case 'R':
      color = TFT_RED;
      break;
    case 'Y':
      color = TFT_YELLOW;
      break;
    case 'O':
      color = TFT_ORANGE;
      break;
  }
  return color;
}