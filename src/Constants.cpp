#include "Constants.h"

char post_data[10000];
char pixelString[9600];

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

String getColorStringFromChar(char num){
  String color;
  switch(num){
    case '0':
      color = "Nero";
      break;
    case '1':
      color = "Bianco";
      break;
    case 'L':
      color = "Grigio chiaro";
      break;
    case 'D':
      color = "Grigio scuro";
      break;
    case 'B':
      color = "Blu";
      break;
    case 'G':
      color = "Verde";
      break;
    case 'R':
      color = "Rosso";
      break;
    case 'Y':
      color = "Giallo";
      break;
    case 'O':
      color = "Arancione";
      break;
  }
  return color;
}