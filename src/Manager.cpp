#include "Manager.h"

Manager::Manager(){
    switchToCursor();
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

void Manager::switchToSavingMode(){
    showMenu = true;
    printColorWheel = false;
    printTablet = false;
    bucketEnabled = false;
    save =  true;
}

void Manager::switchToTablet(){
    showMenu = false;
    printColorWheel = false;
    printTablet = true;
    bucketEnabled = false;
    save =  false;
}

void Manager::switchToCursor(){
    showMenu = false;
    printColorWheel = false;
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