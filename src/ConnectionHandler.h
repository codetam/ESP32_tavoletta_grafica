#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include <WiFi.h>
#include <HTTPClient.h>
#include "DrawingTablet.h"

class ConnectionHandler{
    private:
        const char* ssid;
        const char* password;
        const char* serverName;
        DrawingTablet* tablet;
    public:
        ConnectionHandler(char* ssid, char* password, char* serverName, DrawingTablet* tablet);
        void setup();
        void send_to_server(String postData);
};

#endif