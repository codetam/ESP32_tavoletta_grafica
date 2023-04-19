#ifndef MANAGER_H
#define MANAGER_H

class Manager{
    private:
        bool showMenu;
        bool printTablet;
        bool bucketEnabled;
        bool printColorWheel;
    public:
        Manager();
        void switchToTablet();
        void switchToDrawingMode();
        void switchToColorWheel();
        void switchToBucket();
        bool shouldShowMenu(){ return showMenu; }
        bool shouldPrintTablet(){ return printTablet; }
        bool isBucketEnabled(){ return bucketEnabled; }
        bool shouldPrintColorWheel(){ return printColorWheel; }
        void toggleMenu(){ showMenu = !showMenu; }
};

#endif