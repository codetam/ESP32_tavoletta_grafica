#include "Menu.h"

Menu::Menu(TFT_eSPI tft_ready): tft(tft_ready){
  current_selection = draw;
}

void Menu::print(){
    tft.fillScreen(TFT_LIGHTGREY);
    //header
    tft.setTextSize(1);
    tft.setTextColor(TFT_MAGENTA, TFT_BLUE);
    tft.fillRect(0, 0, 480, 30, TFT_BLUE);
    tft.setTextDatum(TC_DATUM);
    tft.drawString("Menu Principale", 239, 2, 4);
    tft.setTextColor(TFT_BLACK, TFT_LIGHTGREY);
    tft.setFreeFont(FSS9);

    //Middle left
    tft.setTextDatum(ML_DATUM);
    tft.drawString("Disegna", 20, 140, GFXFF);

    //Middle Center
    tft.setTextDatum(MC_DATUM);
    tft.drawString("Cambia colore", 240, 140, GFXFF);

    //Middle right
    tft.setTextDatum(MR_DATUM);
    tft.drawString("Colora", 460, 140, GFXFF);

    printSelection();
}

void Menu::switchSelection(direction current_direction){
  if (current_direction == right){
    switch(current_selection){
      case change_color:
        current_selection = color;
        break;
      case draw:
        current_selection = change_color;
        break;
      case color:
        current_selection = draw;
        break;
    }
  }
  else if(current_direction == left){
    switch(current_selection){
      case change_color:
        current_selection = draw;
        break;
      case draw:
        current_selection = color;
        break;
      case color:
        current_selection = change_color;
        break;
    }
  }
}

menu_selection Menu::getSelection(){
  return current_selection;
}

void Menu::printSelection(){
  tft.setTextDatum(C_BASELINE);
  switch(current_selection){
    case change_color:
      tft.drawString("[Cambia Colore]", 240, 300, GFXFF);
      break;
    case draw:
      tft.drawString("[Disegna]", 240, 300, GFXFF);
      break;
    case color:
      tft.drawString("[Colora]", 240, 300, GFXFF);
      break;
  }
}