#include "../api/Temp.h"
#include "config/config.h"
#include "Arduino.h"

Temp::Temp(int pin)
{
    this->tempPin = TMP_PIN;
    pinMode(tempPin, INPUT);
}

int Temp::getTemp()
{
    int temp = analogRead(tempPin);
    return temp;
}