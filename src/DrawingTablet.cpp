#include "DrawingTablet.h"

//inizializza la costante TFT
DrawingTablet::DrawingTablet(): tft(TFT_eSPI()){
  initialize();
  //starts with the cursor mode
  setMode(cursor);
}
//fa partire il driver SPI
void DrawingTablet::startDriver(){
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_WHITE);
}
//inizializza la matrice di pixel e i valori prev
void DrawingTablet::initialize(){
  for(int i = 0; i < MAX_X; i++){
    for(int j = 0; j < MAX_Y; j++){
      pixelMatrix[i][j] = TFT_WHITE;
    }
  }
  prevColor = TFT_WHITE;
  prevX = MAX_X/2;
  prevY = MAX_Y/2;
}

void DrawingTablet::drawPixel(int x, int y, uint16_t color){
  //salva il valore del colore nella matrice
  pixelMatrix[x][y] = color;
  //Disegna su schermo mappando le coordinate a quelle dello schermo
  for(int i = x*4; i < x*4 + 4; i++){
    for(int j = y*4; j < y*4 + 4; j++){
      tft.drawPixel(i,j,color);
    }
  }
}
//stampa la matrice corrente
void DrawingTablet::print(){
  tft.fillScreen(TFT_WHITE);
  for(int i = 0; i < MAX_X; i++){
    for(int j = 0; j < MAX_Y; j++){
        drawPixel(i,j,pixelMatrix[i][j]);
    }
  }
}
//muove il cursore senza disegnare
void DrawingTablet::moveCursor(int x, int y){
  if(x != prevX || y != prevY){
    //Cambia il colore riportando quello vecchio, solo se il colore corrente è dark_gray,
    //ovvero solo se il cursore NON sta disegnando
    if(pixelMatrix[prevX][prevY] == TFT_DARKGREY){
      drawPixel(prevX, prevY, prevColor);
    }   
    prevX = x;
    prevY = y;
    prevColor = pixelMatrix[prevX][prevY];
    drawPixel(x, y, TFT_DARKGREY);
  }
}

TFT_eSPI DrawingTablet::get_driver(){
  return tft;
}

void DrawingTablet::setMode(tablet_mode new_mode){
  mode = new_mode;
}
void DrawingTablet::setMode(menu_selection new_selection){
  switch(new_selection){
    case change_color:
      break;
    case draw:
      mode = drawing;
      break;
    case color:
      mode = coloring;
      break;
  }
}
tablet_mode DrawingTablet::getMode(){
  return mode;
}