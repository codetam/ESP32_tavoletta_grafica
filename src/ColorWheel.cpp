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
    shouldPrint = true;
}

void ColorWheel::print(){
    tft.fillScreen(TFT_WHITE);
    //header
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE, TFT_BLUE);
    tft.fillRect(0, 0, 480, 30, TFT_BLUE);
    tft.setTextDatum(TC_DATUM);
    tft.drawString("Colore", 239, 2, 4);

    for(int i=0; i<MAX_X*4; i++){
        for(int j=31; j<MAX_Y*4/2; j++){   
            //stampa i primi 4 colori
            tft.drawPixel(i,j,available_colors[i/MAX_X]);
        }
        for(int j=MAX_Y*4/2 + 1; j<MAX_Y*4 - 50; j++){
            tft.drawPixel(i,j,available_colors[i/MAX_X + 4]);
        }
    }
}

void ColorWheel::printSelection(){
  tft.setTextDatum(C_BASELINE);
  switch(current_selection){
    case 0:
      tft.drawString("[Nero]", 240, 300, GFXFF);
      break;
    case 1:
      tft.drawString("[Bianco]", 240, 300, GFXFF);
      break;
    case 2:
      tft.drawString("[Grigio]", 240, 300, GFXFF);
      break;
    case 3:
      tft.drawString("[Blu]", 240, 300, GFXFF);
      break;
    case 4:
      tft.drawString("[Verde]", 240, 300, GFXFF);
      break;
    case 5:
      tft.drawString("[Rosso]", 240, 300, GFXFF);
      break;
    case 6:
      tft.drawString("[Giallo]", 240, 300, GFXFF);
      break;
    case 7:
      tft.drawString("[Arancio]", 240, 300, GFXFF);
      break;
  }
}