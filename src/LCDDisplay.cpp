#include "LCDDisplay.h"
#include <LiquidCrystal_I2C.h>

LCDDisplay::LCDDisplay() {
    lcd = new LiquidCrystal_I2C(0x27, LCD_COLUMNS, LCD_ROWS);
    current_color = '0';
}

void LCDDisplay::init() {
    lcd->init();
    lcd->backlight();
}

void LCDDisplay::print() {
    lcd->clear();
    switch (current_state)
    {
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
    case lcd_print_string:
        print_string();
        break;
    }
}

void LCDDisplay::print_drawing() {
    lcd->print("Disegno");
    lcd->setCursor(0, 1);
    lcd->print(getColorStringFromChar(current_color));
}

void LCDDisplay::print_coloring() {
    lcd->print("Bucket");
    lcd->setCursor(0, 1);
    lcd->print(getColorStringFromChar(current_color));
}

void LCDDisplay::print_connecting() {
    while (current_state == lcd_connecting)
    {
        if (current_state == lcd_connecting)
        {
            lcd->print("Connettendo");
            delay(500);
        }
        if (current_state == lcd_connecting)
        {
            lcd->print(".");
            delay(500);
        }
        if (current_state == lcd_connecting)
        {
            lcd->print(".");
            delay(500);
        }
        if (current_state == lcd_connecting)
        {
            lcd->print(".");
            delay(500);
        }
        lcd->clear();
    }
    lcd->print("Connesso");
    lcd->setCursor(0, 1);
    lcd->print(ip);
    delay(3000);
}

void LCDDisplay::print_loading() {
    while (current_state == lcd_loading)
    {
        if (current_state == lcd_loading)
        {
            lcd->print("Caricamento");
            delay(500);
        }
        if (current_state == lcd_loading)
        {
            lcd->print(".");
            delay(500);
        }
        if (current_state == lcd_loading)
        {
            lcd->print(".");
            delay(500);
        }
        if (current_state == lcd_loading)
        {
            lcd->print(".");
            delay(500);
        }
        lcd->clear();
    }
}

void LCDDisplay::print_string() {
    lcd->print(s1);
    lcd->setCursor(0, 1);
    lcd->print(s2);
    delay(3000);
    setState(lcd_drawing);
}
