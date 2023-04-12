#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Arduino.h"

#define PIN_X 13
#define PIN_Y 12

class Controller{
    private:
        int analogX;
        int analogY;
        int cursoreX;
        int cursoreY;
    public:
        void leggiInput();
};


#endif