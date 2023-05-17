#include "DrawingTablet.h"

//inizializza la costante TFT
DrawingTablet::DrawingTablet(): tft(TFT_eSPI()){
  current_color = '0';
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

//ritorna il driver TFT_eSPI
TFT_eSPI DrawingTablet::get_driver(){
  return tft;
}

//inizializza la matrice di pixel e i valori prev
void DrawingTablet::initialize(){
  for(int i = 0; i < MAX_X; i++){
    for(int j = 0; j < MAX_Y; j++){
      pixelMatrix[i][j] = '1';
    }
  }
  prevColor = '1';
  prevX = MAX_X/2;
  prevY = MAX_Y/2;
}

void DrawingTablet::drawPixel(int x, int y, char color){
  //salva il valore del colore nella matrice
  pixelMatrix[x][y] = color;
  //Disegna su schermo mappando le coordinate della matrice a quelle dello schermo
  for(int i = x*4; i < x*4 + 4; i++){
    for(int j = y*4; j < y*4 + 4; j++){
      tft.drawPixel(i,j,getColorFromChar(color));
    }
  }
}

//stampa la matrice corrente
void DrawingTablet::print(){
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
    if(pixelMatrix[prevX][prevY] == 'D'){
      drawPixel(prevX, prevY, prevColor);
    }   
    prevX = x;
    prevY = y;
    prevColor = pixelMatrix[prevX][prevY];
    drawPixel(x, y, 'D');
  }
}

void DrawingTablet::setMode(tablet_mode new_mode){
  mode = new_mode;
}
void DrawingTablet::setMode(menu_selection new_selection){
  switch(new_selection){
    case change_color:
      mode = cursor;
      break;
    case draw:
      mode = cursor;
      break;
    case color:
      mode = coloring;
      break;
  }
}

tablet_mode DrawingTablet::getMode(){
  return mode;
}

void DrawingTablet::colorArea(int x, int y, char new_color){
  if(prevColor==new_color){
    return;
  } 
  // cambio il valore della matrice a quello precedente al pixel selezionato
  // se non lo facessi, avrei il dark_gray dato dal cursore
  // prevColor è il colore attuale del pixel sul quale si trova il cursore
  drawPixel(x, y, prevColor);
  std::stack<std::array<int, 2>> stack_int;
  stack_int.push({x, y});
  while(stack_int.size() > 0){
    std::array<int, 2> coords;
    coords = stack_int.top();
    stack_int.pop();
    if(!checkCoordinates(coords.at(0), coords.at(1))) continue;
    if(pixelMatrix[coords.at(0)][coords.at(1)] != prevColor) continue;
    if(pixelMatrix[coords.at(0)][coords.at(1)] == new_color) continue;
    drawPixel(coords.at(0), coords.at(1), new_color);
    stack_int.push({coords.at(0) + 1, coords.at(1)});
    stack_int.push({coords.at(0) - 1, coords.at(1)});
    stack_int.push({coords.at(0), coords.at(1) + 1});
    stack_int.push({coords.at(0), coords.at(1) - 1});
  }
  //aggiorno prevColor
  prevColor = new_color;
}

bool DrawingTablet::checkCoordinates(int x, int y){
  return(x >= 0 && x < MAX_X && y >= 0 && y < MAX_Y);
}

void DrawingTablet::stringify(){
  int k = 0;
  for(int i=0; i<MAX_X; i++){
    for(int j=0; j<MAX_Y; j++){
      pixelString[k] = pixelMatrix[i][j];
      k++;
    }
  }
  pixelString[k] = '\0';
}
