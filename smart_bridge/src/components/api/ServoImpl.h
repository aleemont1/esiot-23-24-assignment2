#ifndef __SERVO_IMPL__
#define __SERVO_IMPL__
#include "Arduino.h"
#include "ServoTimer2.h"

class ServoImpl
{
public:
    ServoImpl(int pin);

    void write(int angle);

    void detach();

private:
    ServoTimer2 servo;
    int pin;
};

#endif