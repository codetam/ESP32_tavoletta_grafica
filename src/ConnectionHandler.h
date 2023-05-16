#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include <WiFi.h>
#include <HTTPClient.h>
#include "ESPAsyncWebServer.h"
#include "DrawingTablet.h"

class ConnectionHandler{
    private:
        bool isLoggedIn;
        const char* ssid;
        const char* password;
        String dBusername;
        String dBpassword;
        DrawingTablet* tablet;
        String current_ip;
    public:
        ConnectionHandler(char* ssid, char* password, DrawingTablet* tablet);
        void setup();
        int post_to_server(String serverName, int port, String subfolder, String postData);
        void createWebServer();
        int upload();   // handle case 200
        String getIP();
};

#endif