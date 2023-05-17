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
        String imageId;
    public:
        ConnectionHandler(char* ssid, char* password, DrawingTablet* tablet);
        void setup();
        int post_to_server(String serverName, int port, String subfolder, String postData, bool savePayload);
        void createWebServer();
        int upload();   // handle case 200
        String getIP();
        String getUid(){ return dBusername; }
        String getPwd(){ return dBpassword; }
};

#endif