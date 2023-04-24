#include "Manager.h"

Manager::Manager(){
    showMenu = false;
    printTablet = false;
    bucketEnabled = false;
    printColorWheel = false;
    save =  false;
}

void Manager::switchToTablet(){
    showMenu = false;
    printColorWheel = false;
    printTablet = true;
    bucketEnabled = false;
    save =  false;
}

void Manager::switchToMenu(){
    showMenu = true;
    printColorWheel = false;
    printTablet = true;
    bucketEnabled = false;
    save =  false;
}

void Manager::switchToColorWheel(){
    showMenu = true;
    printColorWheel = true;
    printTablet = false;
    bucketEnabled = false;
    save =  false;
}

void Manager::switchToBucket(){
    showMenu = false;
    printColorWheel = false;
    printTablet = false;
    bucketEnabled = true;
    save =  false;
}

void Manager::switchToDrawingMode(){
    showMenu = false;
    printColorWheel = false;
    printTablet = false;
    bucketEnabled = false;
    save =  false;
}

void Manager::switchToSavingMode(){
    showMenu = true;
    printColorWheel = false;
    printTablet = false;
    bucketEnabled = false;
    save =  true;
}