#include "Manager.h"

Manager::Manager(){
    showMenu = false;
    printTablet = false;
    bucketEnabled = false;
    printColorWheel = false;
}

void Manager::switchToTablet(){
    showMenu = false;
    printColorWheel = false;
    printTablet = true;
    bucketEnabled = false;
}

void Manager::switchToColorWheel(){
    showMenu = true;
    printColorWheel = true;
    printTablet = false;
    bucketEnabled = false;
}

void Manager::switchToBucket(){
    showMenu = false;
    printColorWheel = false;
    printTablet = false;
    bucketEnabled = true;
}

void Manager::switchToDrawingMode(){
    showMenu = false;
    printColorWheel = false;
    printTablet = false;
    bucketEnabled = false;
}