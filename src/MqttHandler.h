#ifndef MQTTHANDLER_H
#define MQTTHANDLER_H

#include <Arduino.h>
#include "Constants.h"
#include "Manager.h"

class AsyncMqttClient; // Forward declaration
class LCDDisplay;
class ConnectionHandler;

class MqttHandler{
    private:
        AsyncMqttClient* mqttClient;
    public:
        Manager* manager;
        MqttHandler(Manager* manager);
        void subscribe(char* topic);
        void connect();
};

#endif