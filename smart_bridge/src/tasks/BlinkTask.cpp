#include "BlinkTask.h"

BlinkTask::BlinkTask(int pin)
{
    this->pin = pin;
}

void BlinkTask::init(int period)
{
    Task::init(period);
    led = new Led(pin);
    this->setState(OFF);
}

void BlinkTask::tick()
{
    switch (this->getState())
    {
    case OFF:
        led->switchOn();
        this->setState(ON);
        break;
    case ON:
        led->switchOff();
        this->setState(OFF);
        break;
    }
}
