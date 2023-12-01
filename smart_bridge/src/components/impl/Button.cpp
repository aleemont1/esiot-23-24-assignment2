#include "../api/Button.h"
#include "Arduino.h"

Button::Button(int pin)
{
    this->pin = pin;
    pinMode(pin, INPUT);
    sync();
}

bool Button::isPressed()
{
    return pressed;
}

void Button::sync()
{
    pressed = digitalRead(pin) == HIGH;
    updateSyncTime(millis());
}