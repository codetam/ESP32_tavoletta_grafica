#include "DrawingTablet.h"

//initializing the constant tft
DrawingTablet::DrawingTablet(): tft(TFT_eSPI()){
  initialize();
}
//Needed to set up order between tft declaration and utilization
void DrawingTablet::startDriver(){
  tft.init();
  tft.fillScreen(TFT_WHITE);
}

void DrawingTablet::initialize(){
  for(int i = 0; i < MAX_X; i++){
    for(int j = 0; j < MAX_Y; j++){
      pixelMatrix[i][j] = white;
    }
  }
  prevColor = white;
  prevX = MAX_X/2;
  prevY = MAX_Y/2;
}

void DrawingTablet::drawPixel(int x, int y, color col){
  //Salva il valore nella matrice
  pixelMatrix[x][y] = col;
  //Disegna su schermo mappando le coordinate a quelle dello schermo
  for(int i = x*4; i < x*4 + 4; i++){
    for(int j = y*4; j < y*4 + 4; j++){ 
      tft.drawPixel(i,j,getColor(col));
      Serial.printf("Pixel disegnato, i: %d, j: %d\n", i,j);
    }
  }
}
void DrawingTablet::print(){
  for(int i=0; i<MAX_X; i++){
    for(int j=0; j<MAX_Y; j++){
        drawPixel(i,j,pixelMatrix[i][j]);
    }
  }
}

void DrawingTablet::moveCursor(int x, int y){
  drawPixel(prevX, prevY, prevColor);
  prevX = x;
  prevY = y;
  prevColor = pixelMatrix[currX][currY];
  drawPixel(x, y, light_grey);
}

int DrawingTablet::getColor(color col) {
  int tft_col;
  switch (col) {
    case white:
      tft_col = TFT_WHITE;
      break;
    case black:
      tft_col = TFT_BLACK;
      break;
    case dark_grey:
      tft_col = TFT_DARKGREY;
      break;
    case light_grey:
      tft_col = TFT_LIGHTGREY;
      break;
    case red:
      tft_col = TFT_RED;
      break;
  }
  return tft_col;
}