#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include "Constants.h"

class DrawingTablet;
class MqttHandler;

class ConnectionHandler{
    private:
        bool isLoggedIn;
        const char* ssid;
        const char* password;
        String dBusername;
        String dBpassword;
        DrawingTablet* tablet;
        MqttHandler* mqtt_handler;
        String current_ip;
        String imageId;
    public:
        ConnectionHandler(char* ssid, char* password, DrawingTablet* tablet, MqttHandler* mqtt_handler);
        void setup();
        int post_to_server(String serverName, int port, String subfolder, String postData, bool savePayload);
        void createWebServer();
        String getIP();
        String getUid(){ return dBusername; }
        String getPwd(){ return dBpassword; }
};

#endif