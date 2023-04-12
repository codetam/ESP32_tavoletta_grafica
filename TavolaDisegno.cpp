#include "TavolaDisegno.h"

TFT_eSPI tft = TFT_eSPI();

TavolaDisegno::TavolaDisegno(){ 
    tft.init();
    tft.fillScreen(TFT_WHITE);
    Serial.begin(115200);
    inizializzaTavola();
}

void TavolaDisegno::inizializzaTavola(){
    for(int i = 0; i < MAX_X; i++){
        for(int j = 0; j < MAX_Y; j++){
            pixelArray[i][j] = false;
            Serial.printf("Pixel bianco!\n");
        }
    }
}

void TavolaDisegno::disegnaPixel(int x, int y){
    //Salva il valore nella matrice
    pixelArray[x][y] = true;
    //Disegna su schermo mappando le coordinate a quelle dello schermo
    for(int i = x*4; i < x*4 + 4; i++){
        for(int j = y*4; j < y*4 + 4; j++){ 
            tft.drawPixel(i,j,TFT_BLACK);
            Serial.printf("Pixel disegnato, i: %d, j: %d\n", i,j);
        }
    }
}

void TavolaDisegno::stampaDati(){
    for(int i=0; i<MAX_X; i++){
        for(int j=0; j<MAX_Y; j++){
            if(pixelArray[i][j] == true){
                disegnaPixel(i,j);
            }
        }
    }
}