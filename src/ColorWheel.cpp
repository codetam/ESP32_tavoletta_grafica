#include "ColorWheel.h"

ColorWheel::ColorWheel(TFT_eSPI tft_ready): tft(tft_ready){
    current_selection = 0;
    available_colors[0] = TFT_BLACK;
    available_colors[1] = TFT_WHITE;
    available_colors[2] = TFT_LIGHTGREY;
    available_colors[3] = TFT_BLUE;
    available_colors[4] = TFT_GREEN;
    available_colors[5] = TFT_RED;
    available_colors[6] = TFT_YELLOW;
    available_colors[7] = TFT_ORANGE;
}

void ColorWheel::print(){
  if(shouldPrint){
    tft.fillScreen(TFT_WHITE);
    //header
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE, TFT_BLUE);
    tft.fillRect(0, 0, 480, 30, TFT_BLUE);
    tft.setTextDatum(TC_DATUM);
    tft.drawString("Colore", 239, 2, 4);

    for(int i=0; i<MAX_X*4; i++){
        for(int j=30; j<MAX_Y*4/4; j++){   
            //stampa gli 8 colori in una line
            tft.drawPixel(i,j,available_colors[i/(MAX_X/2)]);
        }
    }
    printSelection();
    shouldPrint = false;
  } 
}

void ColorWheel::printSelection(){
  for(int i=MAX_X * current_selection / 8; i < MAX_X * (current_selection + 1) / 8; i++){
    draw4pixels(i,30/4, TFT_RED);
    draw4pixels(i,MAX_Y/4, TFT_RED);
  }
  for(int j=30/4; j<MAX_Y/4; j++){
    draw4pixels(MAX_X * current_selection / 8,j, TFT_RED);
    draw4pixels(MAX_X * (current_selection + 1) / 8,j, TFT_RED);
  }
}

void ColorWheel::switchSelection(direction current_direction){
  if (current_direction == right){
    current_selection = (current_selection + 1) % NUM_COLORS;
  }
  else if(current_direction == left){
    if(current_selection == 0){
      current_selection = 7;
    }
    else{
      current_selection = (current_selection - 1) % NUM_COLORS;
    }
  }
}

void ColorWheel::setShouldPrint(){
  shouldPrint = true;
}

void ColorWheel::draw4pixels(int x, int y, uint16_t color){
  //Disegna su schermo mappando le coordinate a quelle dello schermo
  for(int i = x*4; i < x*4 + 4; i++){
    for(int j = y*4; j < y*4 + 4; j++){
      tft.drawPixel(i,j,color);
    }
  }
}