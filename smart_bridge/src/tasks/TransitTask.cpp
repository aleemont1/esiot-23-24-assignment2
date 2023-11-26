#include "TransitTask.h"

void TransitTask::tick()
{
    switch (this->getState())
    {
    case READING_DISTANCE:
        this->L2->switchOn();
        this->distance = sonar->detectDistance();
        if (this->distance < MINDIST)
        {
            this->setState(CHECKING_DISTANCE);
        }
        break;
    case CHECKING_DISTANCE:
        const long start = millis(); 
        if (millis() - start >= (N2 * 1000) && this->distance < MINDIST)
        {
            this->L2->switchOff();
            this->setCompleted();
        }
        else
        {
            this->setState(READING_DISTANCE);
        }
    }
}