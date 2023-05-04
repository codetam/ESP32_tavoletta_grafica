#include "ConnectionHandler.h"


AsyncWebServer server(80);
const char* INDEX_HTML = "<html><head><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Login ESP32</title><style>body{background-color:#F5F5F5;font-family:Arial,sans-serif}form{background-color:#FFFFFF;border-radius:10px;box-shadow:0px 0px 10px #CCCCCC;margin:100px auto;padding:20px;max-width:400px;text-align:center}input[type=text],input[type=password]{border-radius:5px;border:none;box-shadow:0px 0px 5px #CCCCCC;font-size:16px;margin-bottom:10px;padding:10px;width:100%}button[type=submit]{background-color:#4D71FF;border:none;border-radius:5px;color:#FFFFFF;cursor:pointer;font-size:16px;margin-top:10px;padding:10px;width:100%}button[type=submit]:hover{background-color:#3C58C7} @media only screen and (max-width: 600px){form{margin:50px auto;padding:10px}input[type=text],input[type=password]{font-size:14px;padding:8px}button[type=submit]{font-size:14px;padding:8px}} </style></head><body><form action='/login' method='post'><h2>Login</h2><p>Accedere al portale per autenticarsi nella tavoletta.</p><input type='text' name='uid' placeholder='Username'><input type='password' name='pwd' placeholder='Password'><button type='submit' name='submit'>LOGIN</button></form></body></html>";
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

int ConnectionHandler::post_to_server(String serverName, int port, String subfolder, String postData)
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
          int status = this->post_to_server("iot.dayngine.com", 8056, "/esp_login/index.php", "uid=" + uid + "&pwd=" + pwd);
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

void ConnectionHandler::upload(){
  int status = post_to_server("iot.dayngine.com", 8056, "/esp_login/upload_image.php", "uid=" + dBusername + "&pwd=" + dBpassword + "&sent_image=" + tablet->stringify());
  if(status == 200){
    Serial.println("Immagine salvata con successo.");
  }
  else{
    Serial.println("Errore durante il salvataggio dell'immagine.");
  }
}