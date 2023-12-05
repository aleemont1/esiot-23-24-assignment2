#include "../api/LCD.h"
#include "Arduino.h"

LCD::LCD(int address, int columns, int rows) : lcd(address, columns, rows)
{
    lcd.init();
    lcd.backlight();
    lcd.clear();
}

void LCD::clear()
{
    lcd.clear();
}

void LCD::write(const char *string, int start_col, int start_rows)
{
    Serial.print(F("LCD::Sto scrivendo sul display "));
    Serial.println(String(string));
    lcd.setCursor(start_col, start_rows);
    lcd.print(string);
}