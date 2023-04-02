//additional comment
//Second comment
#include <SPI.h>

#include <TFT_eSPI.h> // Hardware-specific library

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

#define MAX_X 120 //480
#define MAX_Y 80 //320
#define PIN_X 13
#define PIN_Y 12
//Il secondo argomento è sempre la y, il primo è la x
bool dataArray[MAX_X][MAX_Y];
int cursore[2];
int valuex, valuey;

void inizializeData(){
  for(int i=0; i<MAX_X; i++){
    for(int j=0; j<MAX_Y; j++){
      dataArray[i][j] = false;
    }
  }
}

void printData(){
  for(int i=0; i<MAX_X; i++){
    for(int j=0; j<MAX_Y; j++){
      if(dataArray[i][j]==true){
        drawPixelSquare(i,j);
      }
    }
  }
}

void drawPixelSquare(int x, int y){
  dataArray[x][y] = true;
  for(int i = x*4; i < x*4 + 4; i++){
    for(int j = y*4; j < y*4 + 4; j++){ 
      tft.drawPixel(i,j,TFT_BLACK);
      Serial.printf("Pixel disegnato, i: %d, j: %d\n", i,j);
    }
  }
}

void drawRectangle(uint8_t fromX, uint8_t fromY, uint8_t toX, uint8_t toY){
  for(int i = fromX; i < toX; i++){
    for(int j = fromY; j < toY; j++){
      drawPixelSquare(i,j);
    }
  }
}


void setup(void) {
  tft.init();
  tft.fillScreen(TFT_WHITE);
  inizializeData();
  Serial.begin(115200);
  tft.setRotation(1);
  pinMode(PIN_X,INPUT_PULLUP);
  pinMode(PIN_Y,INPUT_PULLUP);  
  cursore[0] = MAX_X/2;
  cursore[1] = MAX_Y/2;
}


void loop() {
  valuex = analogRead(PIN_X);
  valuey = analogRead(PIN_Y);
  Serial.println("Analogici letti\n");
  if(valuex > 2500){
    cursore[0]++;
  }
  else if(valuex < 1500){
    cursore[0]--;
  }
  if(valuey > 2500){
    cursore[1]++;
  }
  else if(valuey < 1500){
    cursore[1]--;
  }
  Serial.println("Condizioni viste\n");
  drawPixelSquare(cursore[0],cursore[1]);
  Serial.println("Cursore stampato\n");
  Serial.printf( "Cursore: X: %d \t Y: %d, Count: %d\n", cursore[0],cursore[1]);  
  Serial.println("Ciclo terminato\n");
  delay(100);
}
