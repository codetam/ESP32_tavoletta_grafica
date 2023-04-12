#include "Controller.h"

void Controller::leggiInput(){
    analogX = analogRead(PIN_X);
    analogY = analogRead(PIN_Y);

    if(analogX > 2500){
        cursoreX++;
    }
    else if(analogX < 1500){
        cursoreX--;
    }
    if(analogY > 2500){
        cursoreY++;
    }
    else if(analogY < 1500){
        cursoreY--;
    }
}