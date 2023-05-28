#ifndef MENU_H
#define MENU_H

#include "Constants.h"

class TFT_eSPI;
class ConnectionHandler;

class Menu{
    private:
        TFT_eSPI* tft;
        menu_selection current_selection;
        ConnectionHandler* conn;
        void printIP();
    public:
        Menu(TFT_eSPI* tft_ready, ConnectionHandler* conn);
        void print();
        void switchSelection(direction current_direction);
        menu_selection getSelection();
        void printSelection();
};

#endif