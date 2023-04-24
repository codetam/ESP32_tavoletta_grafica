#include "ConnectionHandler.h"

ConnectionHandler::ConnectionHandler(char* ssid, char* password, char* serverName, DrawingTablet* tablet) : ssid(ssid), password(password), serverName(serverName), tablet(tablet){}

void ConnectionHandler::setup(){
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) { //Check for the connection
        delay(1000);
        Serial.println("Connecting to WiFi..");
    }
    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
}

void ConnectionHandler::send_to_server(String postData) {
  HTTPClient http;    //Declare object of class HTTPClient
  if (WiFi.status() == WL_CONNECTED) 
  { //Check WiFi connection status
    // Send and get Data
    http.begin(serverName);              //Specify request destination
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
    int httpCode = http.POST(postData);   //Send the request
    Serial.println(httpCode);   //Print HTTP return code
    http.end();  //Close connection
    Serial.println("Immagine salvata con successo.");
  }
  else 
  {
    Serial.println("Error in WiFi connection");
  }
}