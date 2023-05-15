#include "LCDDisplay.h"

LCDDisplay::LCDDisplay(): lcd(0x27, LCD_COLUMNS, LCD_ROWS){}

void LCDDisplay::init(){
  lcd.init();                     
  lcd.backlight();
  current_state = lcd_loading;
  current_color = '0';
}

void LCDDisplay::print(){
    switch(current_state){
        case lcd_drawing:
            print_drawing();
            break;
        case lcd_coloring:
            print_coloring();
            break;
        case lcd_connecting:
            print_connecting();
            break;
        case lcd_loading:
            print_loading();
            break;
    }
}

void LCDDisplay::print_drawing(){
    lcd.clear(); 
    lcd.setCursor(0, 0);
    lcd.print("Disegno");
    lcd.setCursor(0, 1);
    lcd.print(getColorStringFromChar(current_color));
}

void LCDDisplay::print_coloring(){
    lcd.clear(); 
    lcd.setCursor(0, 0);
    lcd.print("Bucket");
    lcd.setCursor(0, 1);
    lcd.print(getColorStringFromChar(current_color));
}

void LCDDisplay::print_connecting(){
    lcd.setCursor(0, 0);
    while(current_state == lcd_connecting){
        if(current_state == lcd_connecting){
            lcd.clear(); 
            lcd.setCursor(0, 0);
            lcd.print("Connettendo");
            delay(500);
        }
        if(current_state == lcd_connecting){
            lcd.clear(); 
            lcd.setCursor(0, 0);
            lcd.print("Connettendo .");
            delay(500);
        }
        if(current_state == lcd_connecting){
            lcd.clear(); 
            lcd.setCursor(0, 0);
            lcd.print("Connettendo ..");
            delay(500);
        }
        if(current_state == lcd_connecting){
            lcd.clear(); 
            lcd.setCursor(0, 0);
            lcd.print("Connettendo ...");
            delay(500);
        }
    }
    lcd.clear(); 
    delay(250);
    lcd.print("Connesso");
    lcd.setCursor(0, 1);
    lcd.print(ip);
    delay(3000);
}

void LCDDisplay::print_loading(){
    lcd.setCursor(0, 0);
    while(current_state == lcd_loading){
        if(current_state == lcd_loading){
            lcd.clear(); 
            lcd.setCursor(0, 0);
            lcd.print("Caricamento");
            delay(500);
        }
        if(current_state == lcd_loading){
            lcd.clear(); 
            lcd.setCursor(0, 0);
            lcd.print("Caricamento .");
            delay(500);
        }
        if(current_state == lcd_loading){
            lcd.clear(); 
            lcd.setCursor(0, 0);
            lcd.print("Caricamento ..");
            delay(500);
        }
        if(current_state == lcd_loading){
            lcd.clear(); 
            lcd.setCursor(0, 0);
            lcd.print("Caricamento ...");
            delay(500);
        }
    }
}
