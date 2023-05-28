#ifndef MQTTHANDLER_H
#define MQTTHANDLER_H

#include "Constants.h"

class AsyncMqttClient; // Forward declaration
class ConnectionHandler;
class Manager;

class MqttHandler{
    private:
        AsyncMqttClient* mqttClient;
    public:
        MqttHandler();
        void subscribe(char* topic);
        void connect();
};

#endif