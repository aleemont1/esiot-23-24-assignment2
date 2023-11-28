#include "../api/LCD.h"
#include "Arduino.h"

LCD::LCD(int address, int columns, int rows) : lcd(address, columns, rows) {
    lcd.init();
    lcd.backlight();
}

void LCD::write(const char* string, int start_col, int start_rows) {
    Serial.println("LCD::Sto scrivendo sul display" + String(string));
    lcd.clear();      
    lcd.setCursor(start_col, start_rows);
    lcd.print(string);
}