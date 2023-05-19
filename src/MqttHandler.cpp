#include "MqttHandler.h"
#include <AsyncMQTT_ESP32.h>
#include <string>

#define MQTT_HOST "iot.dayngine.com"
#define MQTT_PORT 1883

static const char mqttUser[] = "gtab_user";
static const char mqttPassword[] = "SX54NipFEVZjwm";

MqttHandler::MqttHandler(Manager* manager) : manager(manager)
{
  mqttClient = new AsyncMqttClient();
  mqttClient->setServer(MQTT_HOST, MQTT_PORT);
  mqttClient->setCredentials(mqttUser, mqttPassword);

  mqttClient->onConnect([](bool sessionPresent) {
    Serial.println("Connected to MQTT.");
  });

  mqttClient->onSubscribe([](uint16_t packetId, uint8_t qos) {
    Serial.println("Subscribe acknowledged.");
  });

  mqttClient->onMessage([this](char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total){
    Serial.println("Publish received.");
    Serial.println(payload);
    strcpy(imageId, payload);
    this->manager->switchToLoadingMode();
  });

}

void MqttHandler::subscribe(char *topic)
{
  uint16_t packetIdSub = mqttClient->subscribe(topic, 0);
  Serial.print("Subscribing at QoS 0, packetId: ");
  Serial.println(packetIdSub);
  Serial.print("topic: ");
  Serial.println(topic);
}

void MqttHandler::connect()
{
  mqttClient->connect();
}
