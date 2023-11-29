#include "CountDown.h"
#include "Arduino.h"
#

void CountDown::tick()
{
    Serial.println("Countdown: " + String(countDown));
    countDown--;
    if (countDown <= 0)
    {
        this->setCompleted();
    }
}