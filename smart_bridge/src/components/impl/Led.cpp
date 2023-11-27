#include "../api/Led.h"
#include "Arduino.h"

Led::Led(int pin)
{
  this->pin = pin;
  pinMode(pin, OUTPUT);
}

void Led::switchOn()
{
  digitalWrite(pin, HIGH);
}

void Led::switchOff()
{
  digitalWrite(pin, LOW);
};

void Led::blink()
{
  // Grab the current time
  unsigned long currentMillis = millis();

  if (currentMillis - lastBlinkTime >= BLINK_INTERVAL)
  {
    lastBlinkTime = currentMillis;
    blinkState = (blinkState == LOW) ? HIGH : LOW;
    digitalWrite(pin, blinkState);
  }
}