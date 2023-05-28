#include "MqttHandler.h"
#include <AsyncMQTT_ESP32.h>
#include <string>

#define MQTT_HOST "iot.dayngine.com"
#define MQTT_PORT 1883

static const char mqttUser[] = "gtab_user";
static const char mqttPassword[] = "SX54NipFEVZjwm";

MqttHandler::MqttHandler()
{
  mqttClient = new AsyncMqttClient();
  mqttClient->setServer(MQTT_HOST, MQTT_PORT);
  mqttClient->setCredentials(mqttUser, mqttPassword);

  mqttClient->onConnect([](bool sessionPresent) {
  });

  mqttClient->onSubscribe([](uint16_t packetId, uint8_t qos) {
  });

  mqttClient->onMessage([this](char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total){
    for(int i = 0; i < total; i++){
      imageId[i] = payload[i];
    }
    imageId[total] = '\0';
    Serial.print("New image saved. Payload: ");
    Serial.print(payload);
    Serial.print(", imageid: ");
    Serial.println(imageId);
  });

}

void MqttHandler::subscribe(char *topic)
{
  uint16_t packetIdSub = mqttClient->subscribe(topic, 0);
  Serial.print("Subscribed at topic: ");
  Serial.println(topic);
}

void MqttHandler::connect()
{
  mqttClient->connect();
  Serial.println("MQTT connected");
}
