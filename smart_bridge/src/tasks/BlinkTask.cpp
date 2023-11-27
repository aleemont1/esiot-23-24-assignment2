#include "BlinkTask.h"

void BlinkTask::tick()
{
    switch (this->getState())
    {
    case OFF:
        this->led->switchOn();
        this->setState(ON);
        break;
    case ON:
        this->led->switchOff();
        this->setState(OFF);
        break;
    }
}
