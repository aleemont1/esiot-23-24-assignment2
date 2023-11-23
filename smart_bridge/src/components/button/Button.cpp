#include "Button.h"
#include "config/config.h"
#include "Arduino.h"

Button::Button(int pin) : buttonState(BUTTON_RELEASED)
{
    this->buttonPin = BUTTON_PIN;
    lastTimeButtonWasInSync = 0;
    pinMode(pin, INPUT);
    updateButtonState();
}

bool Button::checkButtonPressStatus()
{
    return buttonState == BUTTON_PRESSED;
}

bool Button::checkButtonReleaseStatus()
{
    return buttonState == BUTTON_RELEASED;
}

void Button::updateButtonState()
{
    // If the button is pressed, the pin will be HIGH.
    buttonState = digitalRead(buttonPin) == HIGH ? BUTTON_PRESSED : BUTTON_RELEASED;
    // Update the last time the button state was synchronized.
    setLastButtonSyncTime(millis());
}

void Button::setLastButtonSyncTime(long time)
{
    lastTimeButtonWasInSync = time;
}

long Button::retrieveLastButtonSyncTime()
{
    return lastTimeButtonWasInSync;
}