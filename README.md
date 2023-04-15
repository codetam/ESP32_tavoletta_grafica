# Idea di progetto

La *Tavoletta Grafica* è un **dispositivo IOT** che permette ad un utente di disegnare su uno schermo tramite un joystick.

## Requisiti funzionali: 
<ul>
    <li>l’utente potrà scegliere uno dei colori disponibili, scrivere o cancellare sullo schermo; 
    <li>una volta terminato il proprio disegno, l’utente potrà salvarlo e visualizzarlo in un secondo momento.
</ul>

Al dispositivo è associato un **portale web** dove l’utente potrà registrarsi e, con le corrette credenziali, potrà accedere alla sua area personale e visualizzare i disegni salvati. 
La *Tavoletta Grafica* è un dispositivo divertente e facile da utilizzare soprattutto per gli amanti del disegno, per dare spazio alla loro creatività.

## Errore SPI
```
C:\Users\dayne\Desktop\ESP32_projects\progetto_esame\src\TavolaDisegno.cpp: In constructor 'TavolaDisegno::TavolaDisegno()':
C:\Users\dayne\Desktop\ESP32_projects\progetto_esame\src\TavolaDisegno.cpp:6:9: error: use of deleted function 'TFT_eSPI& TFT_eSPI::operator=(TFT_eSPI&&)'
     tft = TFT_eSPI();
         ^
In file included from C:\Users\dayne\Desktop\ESP32_projects\progetto_esame\src\TavolaDisegno.h:6:0,
                 from C:\Users\dayne\Desktop\ESP32_projects\progetto_esame\src\TavolaDisegno.cpp:1:
C:\Users\dayne\Documents\Arduino\libraries\TFT_eSPI-master/TFT_eSPI.h:426:7: note: 'TFT_eSPI& TFT_eSPI::operator=(TFT_eSPI&&)' is implicitly deleted because the default definition would be ill-formed:
 class TFT_eSPI : public Print { friend class TFT_eSprite; // Sprite class has access to protected members
       ^
C:\Users\dayne\Documents\Arduino\libraries\TFT_eSPI-master/TFT_eSPI.h:426:7: error: non-static reference member 'fs::FS& TFT_eSPI::fontFS', can't use default assignment operator

exit status 1

Compilation error: use of deleted function 'TFT_eSPI& TFT_eSPI::operator=(TFT_eSPI&&)'
```
