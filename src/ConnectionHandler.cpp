#include "ConnectionHandler.h"


AsyncWebServer server(80);
const char* INDEX_HTML = "<html><body><form action='/login' method='post'><input type='text' name='uid' placeholder='Username'><input type='password' name='pwd' placeholder='Password'><br><button type='submit' name='submit'>LOGIN</button></form></body></html>";

ConnectionHandler::ConnectionHandler(char *ssid, char *password, DrawingTablet *tablet) : ssid(ssid), password(password), tablet(tablet) {
  isLoggedIn = false;
  dBusername = "";
  dBpassword = "";
}

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

int ConnectionHandler::send_to_server(String serverName, int port, String subfolder, String postData)
{
  HTTPClient http;
  if (WiFi.status() == WL_CONNECTED)
  {
    http.begin(serverName, 8056, subfolder);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpCode = http.POST(postData);
    Serial.println(httpCode);
    http.end();
    return httpCode;
  }
  else
  {
    Serial.println("Error in WiFi connection");
    return -1;
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
    server.on("/login", HTTP_POST, [this](AsyncWebServerRequest *request){
        String uid = "";
        String pwd = "";
        if (request->hasParam("uid", true)) {
            uid = request->getParam("uid", true)->value();
        }
        if (request->hasParam("pwd", true)) {
            pwd = request->getParam("pwd", true)->value();
        }
        if(uid != "" && pwd != ""){ //L'utente ha inserito le credenziali
          int status = this->send_to_server("iot.dayngine.com", 8056, "/esp_login/index.php", "uid=" + uid + "&pwd=" + pwd);
          if(status == 200){
            request->send(200, "text/plain", "Loggato con successo!");
            this->dBusername = uid;
            this->dBpassword = pwd;
            this->isLoggedIn = true;
            Serial.println("Username: " + this->dBusername);
            Serial.println("Password: " + this->dBpassword);
          }
          else{
            request->send(200, "text/plain", "Credenziali errate!");
          }
        }
        else{
          request->send(200, "text/plain", "Mancano delle credenziali!");
        }
    }); 
    server.onNotFound(notFound);
    server.begin();
}