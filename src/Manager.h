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
        void switchToMenu();            // Modalità menu
        void switchToColorWheel();      // Modalità menu
        void switchToSavingMode();      // Modalità menu
        void switchToTablet();          // Modalità tablet
        void switchToCursor();          // Modalità tablet
        void switchToBucket();          // Modalità tablet

        void toggleMenu(){ showMenu = !showMenu; }

        bool shouldShowMenu(){ return showMenu; }
        bool shouldPrintTablet(){ return printTablet; }

        bool shouldPrintColorWheel(){ return printColorWheel; }
        bool shouldSave(){ return save; }
        bool isBucketEnabled(){ return bucketEnabled; }
};

#endif