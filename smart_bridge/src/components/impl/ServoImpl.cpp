#include "../api/ServoImpl.h"
#include "Arduino.h"

ServoImpl::ServoImpl(int pin)
{
    servo.attach(pin);
}

void ServoImpl::write(int angle)
{
    servo.write(map(angle, 0, 180, 750, 2250));
}

void ServoImpl::detach()
{
    servo.detach();
}