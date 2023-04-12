#include "DrawingTablet.h"

TFT_eSPI tft = TFT_eSPI();

DrawingTablet::DrawingTablet(){
  initialize();
}
//Needed to set up order between tft declaration and utilization
void DrawingTablet::init(){
  tft.init();
  tft.fillScreen(TFT_WHITE);
}

void DrawingTablet::initialize(){
  for(int i = 0; i < MAX_X; i++){
    for(int j = 0; j < MAX_Y; j++){
      pixelMatrix[i][j] = false;
    }
  }
}

void DrawingTablet::drawPixel(int x, int y){
  //Salva il valore nella matrice
  pixelMatrix[x][y] = true;
  //Disegna su schermo mappando le coordinate a quelle dello schermo
  for(int i = x*4; i < x*4 + 4; i++){
    for(int j = y*4; j < y*4 + 4; j++){ 
      tft.drawPixel(i,j,TFT_BLACK);
      Serial.printf("Pixel disegnato, i: %d, j: %d\n", i,j);
    }
  }
}
void DrawingTablet::print(){
  for(int i=0; i<MAX_X; i++){
    for(int j=0; j<MAX_Y; j++){
      if(pixelMatrix[i][j] == true){
        drawPixel(i,j);
      }
    }
  }
}