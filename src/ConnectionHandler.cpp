#include "ConnectionHandler.h"


AsyncWebServer server(80);
const char* INDEX_HTML = "<html><body><form action='/login' method='post'><input type='text' name='uid' placeholder='Username'><input type='password' name='pwd' placeholder='Password'><br><button type='submit' name='submit'>LOGIN</button></form></body></html>";

ConnectionHandler::ConnectionHandler(char *ssid, char *password, char *serverName, DrawingTablet *tablet) : ssid(ssid), password(password), serverName(serverName), tablet(tablet) {}

void ConnectionHandler::setup()
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  { // Check for the connection
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void ConnectionHandler::send_to_server(String postData)
{
  HTTPClient http; // Declare object of class HTTPClient
  if (WiFi.status() == WL_CONNECTED)
  { // Check WiFi connection status
    // Send and get Data
    http.begin(serverName, 8056);                                        // Specify request destination
    http.addHeader("Content-Type", "application/x-www-form-urlencoded"); // Specify content-type header
    int httpCode = http.POST(postData);                                  // Send the request
    Serial.println(httpCode);                                            // Print HTTP return code
    http.end();                                                          // Close connection
    Serial.println("Immagine salvata con successo.");
  }
  else
  {
    Serial.println("Error in WiFi connection");
  }
}

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void ConnectionHandler::createWebServer()
{
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/html", INDEX_HTML);
    });

    // Send a POST request to <IP>/post with a form field message set to <message>
    server.on("/login", HTTP_POST, [](AsyncWebServerRequest *request){
        String message;
        message = "Username: ";
        if (request->hasParam("uid", true)) {
            message += request->getParam("uid", true)->value();
        } else {
            message += "No username sent ";
        }
        message += " Password: ";
        if (request->hasParam("pwd", true)) {
            message += request->getParam("pwd", true)->value();
        } else {
            message += "No password sent";
        }
        request->send(200, "text/plain", "Hello, POST: " + message);
    }); 
    server.onNotFound(notFound);
    server.begin();
}