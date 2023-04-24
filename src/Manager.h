#ifndef MANAGER_H
#define MANAGER_H

class Manager{
    private:
        bool showMenu;
        bool printTablet;
        bool bucketEnabled;
        bool printColorWheel;
        bool save;
    public:
        Manager();
        void switchToTablet();
        void switchToDrawingMode();
        void switchToColorWheel();
        void switchToBucket();
        void switchToSavingMode();
        void switchToMenu();
        bool shouldShowMenu(){ return showMenu; }
        bool shouldPrintTablet(){ return printTablet; }
        bool isBucketEnabled(){ return bucketEnabled; }
        bool shouldPrintColorWheel(){ return printColorWheel; }
        bool shouldSave(){ return save; }
        void toggleMenu(){ showMenu = !showMenu; }
};

#endif