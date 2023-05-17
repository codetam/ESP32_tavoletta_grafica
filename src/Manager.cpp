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
    load = false;
    connect = false;
}

void Manager::switchToColorWheel(){
    showMenu = true;
    printColorWheel = true;
    printTablet = false;
    bucketEnabled = false;
    save =  false;
    load = false;
    connect = false;
}

void Manager::switchToSavingMode(){
    showMenu = true;
    printColorWheel = false;
    printTablet = false;
    bucketEnabled = false;
    save =  true;
    load = false;
    connect = false;
}

void Manager::switchToLoadingMode(){
    showMenu = true;
    printColorWheel = false;
    printTablet = false;
    bucketEnabled = false;
    save =  false;
    load = true;
    connect = false;
}

void Manager::switchToConnectingMode(){
    showMenu = true;
    printColorWheel = false;
    printTablet = false;
    bucketEnabled = false;
    save =  false;
    load = false;
    connect = true;
}

void Manager::switchToTablet(){
    showMenu = false;
    printColorWheel = false;
    printTablet = true;
    bucketEnabled = false;
    save =  false;
    load = false;
    connect = false;
}

void Manager::switchToCursor(){
    showMenu = false;
    printColorWheel = false;
    printTablet = false;
    bucketEnabled = false;
    save =  false;
    load = false;
    connect = false;
}

void Manager::switchToBucket(){
    showMenu = false;
    printColorWheel = false;
    printTablet = false;
    bucketEnabled = true;
    save =  false;
    load = false;
    connect = false;
}