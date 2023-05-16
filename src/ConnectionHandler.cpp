#include "ConnectionHandler.h"

AsyncWebServer server(80);

const char* INDEX_HTML="<!DOCTYPE html> <html> <head> <meta name='viewport' content='width=device-width, initial-scale=1'> <style> * { box-sizing: border-box; } body { margin: 0; font-family: 'Roboto', sans-serif; background-color: #f5f5f5; } .logo { margin-right: auto; margin-left: auto; display: block; } .navbar { background-color: #f5f5f5; padding: 16px; display: flex; justify-content: space-between; align-items: center; } .navbar img { height: 75px; } .container { padding: 40px; background-color: #F7F7F7; box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); border-radius: 4px; max-width: 400px; margin: 5px auto; } input[type=text], input[type=password] { width: 100%; padding: 12px; margin: 8px 0; display: inline-block; border: 1px solid #d2d8dd; border-radius: 4px; background-color: transparent; font-size: 16px; font-weight: 400; color: #2d3748; } input[type=text]:focus, input[type=password]:focus { outline: none; border-color: #1a73e8; } .login { background-color: #1a73e8; color: white; padding: 12px; margin: 16px 0 8px; border: none; border-radius: 4px; cursor: pointer; font-size: 16px; font-weight: 500; letter-spacing: 0.03em; transition: background-color 0.2s ease; width: 100%; } .login:hover { background-color: #0c5dd1; } .signup { background-color: #BD161C; color: white; padding: 12px; margin: 16px 0 8px; border: none; border-radius: 4px; cursor: pointer; font-size: 16px; font-weight: 500; letter-spacing: 0.03em; transition: background-color 0.2s ease; width: 100%; } .signup:hover { background-color: #99181e; } .container { padding: 16px; } .divider { display: flex; align-items: center; text-align: center; margin: 20px 0; } .divider hr { flex-grow: 1; height: 1px; margin: 0; border: none; background-color: #ccc; } .divider .left { margin-right: 10px; } .divider .right { margin-left: 10px; } .divider span { font-size: 14px; font-weight: bold; color: #666; text-transform: uppercase; letter-spacing: 1px; font-style: italic; /* add italic style */ } @media screen and (max-width: 600px) { .container { padding: 20px; } } </style> </head> <body> <div class='navbar'> <img class='logo' src='https://i.ibb.co/yPBvMrD/logo-min.png'> </div> <div class='container'> <form action='/login' method='post'> <h2>Login</h2> <p>Accedere al portale per autenticarsi nella tavoletta.</p> <input type='text' name='uid' placeholder='Username'> <input type='password' name='pwd' placeholder='Password'> <button type='submit' name='action' value='login' class='login'>Login</button> <div class='divider'> <hr class='left'> <span>OR</span> <hr class='right'> </div> <button type='submit' name='action' value='signup' class='signup'>Registrati</button> </form> </div> </body> </html>";
const char* LOGGED_IN_HTML="<!DOCTYPE html> <html> <head> <meta name='viewport' content='width=device-width, initial-scale=1'> <style> * { box-sizing: border-box; } body { margin: 0; font-family: 'Roboto', sans-serif; background-color: #f5f5f5; } .logo { margin-right: auto; margin-left: auto; display: block; } .navbar { background-color: #f5f5f5; padding: 16px; display: flex; justify-content: space-between; align-items: center; } .navbar img { height: 75px; } .container { padding: 40px; background-color: #F7F7F7; box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); border-radius: 4px; max-width: 400px; margin: 5px auto; text-align: center; } h2 { font-size: 24px; font-weight: 500; margin-bottom: 20px; } p { font-size: 16px; margin-bottom: 20px; } .message { font-size: 15px; font-weight: 500; margin-bottom: 20px; } .button { display: block; background-color: #1a73e8; color: white; padding: 12px; margin: 16px 0 8px; border: none; border-radius: 4px; cursor: pointer; font-size: 16px; font-weight: 500; letter-spacing: 0.03em; transition: background-color 0.2s ease; width: 100%; } .button:hover { background-color: #0c5dd1; } .divider { display: flex; align-items: center; text-align: center; margin: 20px 0; } .divider hr { flex-grow: 1; height: 1px; margin: 0; border: none; background-color: #ccc; } .divider .left { margin-right: 10px; } .divider .right { margin-left: 10px; } .divider span { font-size: 14px; font-weight: bold; color: #666; text-transform: uppercase; letter-spacing: 1px; font-style: italic; /* add italic style */ } a { text-decoration: none; } </style> </head> <body> <div class='navbar'> <img class='logo' src='https://i.ibb.co/yPBvMrD/logo-min.png'></div> <div class='container'> <h2>Benvenuto nel portale</h2> <p>Utente autenticato con successo!</p> <p class='message'>Per visualizzare i disegni salvati vai su Area Personale. Se vuoi cambiare account vai su Cambia Account.</p> <a href='/profile' class='button'>Area Personale</a> <div class='divider'> <hr class='left'> <span>OR</span> <hr class='right'> </div> <a href='/' class='button'>Cambia Account</a> </div> </body> </html>";
const char* SIGNEG_UP_HTML="<!DOCTYPE html> <html> <head> <meta name='viewport' content='width=device-width, initial-scale=1'> <style> * { box-sizing: border-box; } body { margin: 0; font-family: 'Roboto', sans-serif; background-color: #f5f5f5; } .logo { margin-right: auto; margin-left: auto; display: block; } .navbar { background-color: #f5f5f5; padding: 16px; display: flex; justify-content: space-between; align-items: center; } .navbar img { height: 75px; } .container { padding: 40px; background-color: #F7F7F7; box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); border-radius: 4px; max-width: 400px; margin: 5px auto; text-align: center; } h2 { font-size: 24px; font-weight: 500; margin-bottom: 20px; } p { font-size: 16px; margin-bottom: 20px; } .message { font-size: 15px; font-weight: 500; margin-bottom: 20px; } .button { display: block; background-color: #1a73e8; color: white; padding: 12px; margin: 16px 0 8px; border: none; border-radius: 4px; cursor: pointer; font-size: 16px; font-weight: 500; letter-spacing: 0.03em; transition: background-color 0.2s ease; width: 100%; } .button:hover { background-color: #0c5dd1; } .divider { display: flex; align-items: center; text-align: center; margin: 20px 0; } .divider hr { flex-grow: 1; height: 1px; margin: 0; border: none; background-color: #ccc; } .divider .left { margin-right: 10px; } .divider .right { margin-left: 10px; } .divider span { font-size: 14px; font-weight: bold; color: #666; text-transform: uppercase; letter-spacing: 1px; font-style: italic; /* add italic style */ } a { text-decoration: none; } </style> </head> <body> <div class='navbar'> <img class='logo' src='https://i.ibb.co/yPBvMrD/logo-min.png'></div> <div class='container'> <h2>Benvenuto nel portale</h2> <p>Utente registrato con successo!</p> <p class='message'>Per visualizzare i disegni salvati vai su Area Personale. Se vuoi cambiare account vai su Cambia Account.</p> <a href='/profile' class='button'>Area Personale</a> <div class='divider'> <hr class='left'> <span>OR</span> <hr class='right'> </div> <a href='/' class='button'>Cambia Account</a> </div> </body> </html>";
const char* WRONG_CREDS="<!DOCTYPE html> <html> <head> <meta name='viewport' content='width=device-width, initial-scale=1'> <style> * { box-sizing: border-box; } body { margin: 0; font-family: 'Roboto', sans-serif; background-color: #f5f5f5; } .logo { margin-right: auto; margin-left: auto; display: block; } .navbar { background-color: #f5f5f5; padding: 16px; display: flex; justify-content: space-between; align-items: center; } .navbar img { height: 75px; } .container { padding: 40px; background-color: #F7F7F7; box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); border-radius: 4px; max-width: 400px; margin: 5px auto; } input[type=text], input[type=password] { width: 100%; padding: 12px; margin: 8px 0; display: inline-block; border: 1px solid #d2d8dd; border-radius: 4px; background-color: transparent; font-size: 16px; font-weight: 400; color: #2d3748; } input[type=text]:focus, input[type=password]:focus { outline: none; border-color: #1a73e8; } .login { background-color: #1a73e8; color: white; padding: 12px; margin: 16px 0 8px; border: none; border-radius: 4px; cursor: pointer; font-size: 16px; font-weight: 500; letter-spacing: 0.03em; transition: background-color 0.2s ease; width: 100%; } .login:hover { background-color: #0c5dd1; } .signup { background-color: #BD161C; color: white; padding: 12px; margin: 16px 0 8px; border: none; border-radius: 4px; cursor: pointer; font-size: 16px; font-weight: 500; letter-spacing: 0.03em; transition: background-color 0.2s ease; width: 100%; } .signup:hover { background-color: #99181e; } .container { padding: 16px; } .divider { display: flex; align-items: center; text-align: center; margin: 20px 0; } .divider hr { flex-grow: 1; height: 1px; margin: 0; border: none; background-color: #ccc; } .divider .left { margin-right: 10px; } .divider .right { margin-left: 10px; } .divider span { font-size: 14px; font-weight: bold; color: #666; text-transform: uppercase; letter-spacing: 1px; font-style: italic; /* add italic style */ } .error { color: red; text-align: center; } @media screen and (max-width: 600px) { .container { padding: 20px; } } </style> </head> <body> <div class='navbar'> <img class='logo' src='https://i.ibb.co/yPBvMrD/logo-min.png'> </div> <div class='container'> <p class='error'>Credenziali non corrette!</p> <form action='/login' method='post'> <h2>Login</h2> <p>Accedere al portale per autenticarsi nella tavoletta.</p> <input type='text' name='uid' placeholder='Username'> <input type='password' name='pwd' placeholder='Password'> <button type='submit' name='action' value='login' class='login'>Login</button> <div class='divider'> <hr class='left'> <span>OR</span> <hr class='right'> </div> <button type='submit' name='action' value='signup' class='signup'>Registrati</button> </form> </div> </body> </html>";
const char* INVALID_UID="<!DOCTYPE html> <html> <head> <meta name='viewport' content='width=device-width, initial-scale=1'> <style> * { box-sizing: border-box; } body { margin: 0; font-family: 'Roboto', sans-serif; background-color: #f5f5f5; } .logo { margin-right: auto; margin-left: auto; display: block; } .navbar { background-color: #f5f5f5; padding: 16px; display: flex; justify-content: space-between; align-items: center; } .navbar img { height: 75px; } .container { padding: 40px; background-color: #F7F7F7; box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); border-radius: 4px; max-width: 400px; margin: 5px auto; } input[type=text], input[type=password] { width: 100%; padding: 12px; margin: 8px 0; display: inline-block; border: 1px solid #d2d8dd; border-radius: 4px; background-color: transparent; font-size: 16px; font-weight: 400; color: #2d3748; } input[type=text]:focus, input[type=password]:focus { outline: none; border-color: #1a73e8; } .login { background-color: #1a73e8; color: white; padding: 12px; margin: 16px 0 8px; border: none; border-radius: 4px; cursor: pointer; font-size: 16px; font-weight: 500; letter-spacing: 0.03em; transition: background-color 0.2s ease; width: 100%; } .login:hover { background-color: #0c5dd1; } .signup { background-color: #BD161C; color: white; padding: 12px; margin: 16px 0 8px; border: none; border-radius: 4px; cursor: pointer; font-size: 16px; font-weight: 500; letter-spacing: 0.03em; transition: background-color 0.2s ease; width: 100%; } .signup:hover { background-color: #99181e; } .container { padding: 16px; } .divider { display: flex; align-items: center; text-align: center; margin: 20px 0; } .divider hr { flex-grow: 1; height: 1px; margin: 0; border: none; background-color: #ccc; } .divider .left { margin-right: 10px; } .divider .right { margin-left: 10px; } .divider span { font-size: 14px; font-weight: bold; color: #666; text-transform: uppercase; letter-spacing: 1px; font-style: italic; /* add italic style */ } .error { color: red; text-align: center; } @media screen and (max-width: 600px) { .container { padding: 20px; } } </style> </head> <body> <div class='navbar'> <img class='logo' src='https://i.ibb.co/yPBvMrD/logo-min.png'> </div> <div class='container'> <p class='error'>Username non valido!</p> <form action='/login' method='post'> <h2>Login</h2> <p>Accedere al portale per autenticarsi nella tavoletta.</p> <input type='text' name='uid' placeholder='Username'> <input type='password' name='pwd' placeholder='Password'> <button type='submit' name='action' value='login' class='login'>Login</button> <div class='divider'> <hr class='left'> <span>OR</span> <hr class='right'> </div> <button type='submit' name='action' value='signup' class='signup'>Registrati</button> </form> </div> </body> </html>";
const char* USER_ALREADY_REGISTERED="<!DOCTYPE html> <html> <head> <meta name='viewport' content='width=device-width, initial-scale=1'> <style> * { box-sizing: border-box; } body { margin: 0; font-family: 'Roboto', sans-serif; background-color: #f5f5f5; } .logo { margin-right: auto; margin-left: auto; display: block; } .navbar { background-color: #f5f5f5; padding: 16px; display: flex; justify-content: space-between; align-items: center; } .navbar img { height: 75px; } .container { padding: 40px; background-color: #F7F7F7; box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); border-radius: 4px; max-width: 400px; margin: 5px auto; } input[type=text], input[type=password] { width: 100%; padding: 12px; margin: 8px 0; display: inline-block; border: 1px solid #d2d8dd; border-radius: 4px; background-color: transparent; font-size: 16px; font-weight: 400; color: #2d3748; } input[type=text]:focus, input[type=password]:focus { outline: none; border-color: #1a73e8; } .login { background-color: #1a73e8; color: white; padding: 12px; margin: 16px 0 8px; border: none; border-radius: 4px; cursor: pointer; font-size: 16px; font-weight: 500; letter-spacing: 0.03em; transition: background-color 0.2s ease; width: 100%; } .login:hover { background-color: #0c5dd1; } .signup { background-color: #BD161C; color: white; padding: 12px; margin: 16px 0 8px; border: none; border-radius: 4px; cursor: pointer; font-size: 16px; font-weight: 500; letter-spacing: 0.03em; transition: background-color 0.2s ease; width: 100%; } .signup:hover { background-color: #99181e; } .container { padding: 16px; } .divider { display: flex; align-items: center; text-align: center; margin: 20px 0; } .divider hr { flex-grow: 1; height: 1px; margin: 0; border: none; background-color: #ccc; } .divider .left { margin-right: 10px; } .divider .right { margin-left: 10px; } .divider span { font-size: 14px; font-weight: bold; color: #666; text-transform: uppercase; letter-spacing: 1px; font-style: italic; /* add italic style */ } .error { color: red; text-align: center; } @media screen and (max-width: 600px) { .container { padding: 20px; } } </style> </head> <body> <div class='navbar'> <img class='logo' src='https://i.ibb.co/yPBvMrD/logo-min.png'> </div> <div class='container'> <p class='error'>Username già registrato!</p> <form action='/login' method='post'> <h2>Login</h2> <p>Accedere al portale per autenticarsi nella tavoletta.</p> <input type='text' name='uid' placeholder='Username'> <input type='password' name='pwd' placeholder='Password'> <button type='submit' name='action' value='login' class='login'>Login</button> <div class='divider'> <hr class='left'> <span>OR</span> <hr class='right'> </div> <button type='submit' name='action' value='signup' class='signup'>Registrati</button> </form> </div> </body> </html>";


ConnectionHandler::ConnectionHandler(char *ssid, char *password, DrawingTablet *tablet) : ssid(ssid), password(password), tablet(tablet)
{
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
  }
  current_ip = WiFi.localIP().toString();
}

int ConnectionHandler::post_to_server(String serverName, int port, String subfolder, String postData)
{
  HTTPClient http;
  if (WiFi.status() == WL_CONNECTED)
  {
    http.begin(serverName, port, subfolder);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpCode = http.POST(postData);
    http.end();
    return httpCode;
  }
  else
  {
    return -1;
  }
}

void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Not found");
}

void ConnectionHandler::createWebServer()
{
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", INDEX_HTML); });

  // Send a POST request to <IP>/post with a form field message set to <message>
  server.on("/login", HTTP_POST, [this](AsyncWebServerRequest *request){
        String uid = "";
        String pwd = "";
        String action = "";
        if (request->hasParam("uid", true)) {
            uid = request->getParam("uid", true)->value();
        }
        if (request->hasParam("pwd", true)) {
            pwd = request->getParam("pwd", true)->value();
        }
        if (request->hasParam("action", true)) {
            action = request->getParam("action", true)->value();
        }
        if(uid != "" && pwd != "" && action != ""){
          int status = this->post_to_server("iot.dayngine.com", 8056, "/remote/login.php", "uid=" + uid + "&pwd=" + pwd + "&action=" + action);
          if(action == "login"){
            if(status == 200){
              request->send(200, "text/html", LOGGED_IN_HTML);
              this->dBusername = uid;
              this->dBpassword = pwd;
              this->isLoggedIn = true;
            }
            else{
              request->send(200, "text/html", WRONG_CREDS);
            }
          }
          else if(action == "signup"){
            switch(status){
              case 200:
                request->send(200, "text/html", SIGNEG_UP_HTML);
                this->dBusername = uid;
                this->dBpassword = pwd;
                this->isLoggedIn = true;
                break;
              case 401:
                request->send(200, "text/html", INVALID_UID);
                break;
              case 400:
                request->send(200, "text/html", USER_ALREADY_REGISTERED);
                break;
              default:
                request->send(200, "text/html", WRONG_CREDS);
                break;
            }
          }
        }
        else{
          request->send(200, "text/html", WRONG_CREDS);
        } });

      
  server.on("/profile", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", "mogu mogu!"); });

  server.onNotFound(notFound);
  server.begin();
}

int ConnectionHandler::upload()
{
  int status = post_to_server("http://iot.dayngine.com", 8056, "/remote/upload_image.php", "uid=" + dBusername + "&pwd=" + dBpassword + "&sent_image=" + "tablet->stringify()");
  return status;
}

String ConnectionHandler::getIP(){
  return current_ip;
}