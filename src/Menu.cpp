#include "Menu.h"

Menu::Menu(TFT_eSPI tft_ready): tft(tft_ready){
  current_selection = draw;
}

void Menu::print(){
    tft.fillScreen(TFT_WHITE);
    //header
    tft.setTextSize(1);
    tft.setTextColor(TFT_MAGENTA, TFT_BLUE);
    tft.fillRect(0, 0, 480, 30, TFT_BLUE);
    tft.setTextDatum(TC_DATUM);
    tft.drawString("Menu Principale", 239, 2, 4);
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.setFreeFont(FSS9);

    printSelection();
}

void Menu::switchSelection(direction current_direction){
  if (current_direction == right){
    switch(current_selection){
      case draw:
        current_selection = change_color;
        break;
      case change_color:
        current_selection = color;
        break;
      case color:
        current_selection = change_brush_size;
        break;
      case change_brush_size:
        current_selection = save_drawing;
        break;
      case save_drawing:
        current_selection = draw;
        break;
    }
  }
  else if(current_direction == left){
    switch(current_selection){
      case draw:
        current_selection = save_drawing;
        break;
      case change_color:
        current_selection = draw;
        break;
      case color:
        current_selection = change_color;
        break;
      case change_brush_size:
        current_selection = color;
        break;
      case save_drawing:
        current_selection = change_brush_size;
        break;
    }
  }
}

menu_selection Menu::getSelection(){
  return current_selection;
}

void Menu::printSelection(){
  //Middle left
    tft.setTextDatum(ML_DATUM);
    if(current_selection == draw)
      tft.setTextColor(TFT_BLACK, TFT_YELLOW);
    else 
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.drawString("Disegna", 20, 140, GFXFF);

    //Middle Center
    tft.setTextDatum(MC_DATUM);
    if(current_selection == change_color)
      tft.setTextColor(TFT_BLACK, TFT_YELLOW);
    else 
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.drawString("Cambia colore", 240, 140, GFXFF);

    //Middle right
    tft.setTextDatum(MR_DATUM);
    if(current_selection == color)
      tft.setTextColor(TFT_BLACK, TFT_YELLOW);
    else 
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.drawString("Colora", 460, 140, GFXFF);

    //Bottom left
    tft.setTextDatum(BL_DATUM);
    if(current_selection == change_brush_size)
      tft.setTextColor(TFT_BLACK, TFT_YELLOW);
    else 
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.drawString("Cambia pennello", 20, 220, GFXFF);

    //Bottom right
    tft.setTextDatum(BR_DATUM);
    if(current_selection == save_drawing)
      tft.setTextColor(TFT_BLACK, TFT_YELLOW);
    else 
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.drawString("Salva immagine", 460, 220, GFXFF);
}