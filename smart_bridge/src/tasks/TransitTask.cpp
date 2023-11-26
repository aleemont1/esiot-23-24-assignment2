#include "TransitTask.h"

void TransitTask::tick()
{

    if (this->DependantTask::getDependency()->isCompleted())
    {
        switch (this->getState())
        {
        case READING_DISTANCE:
            Serial.println("TransitTask::Reading distance");
            this->L2->switchOn();
            this->distance = sonar->detectDistance();
            Serial.println("TransitTask::Distance: " + String(this->distance));
            if (this->distance < MINDIST)
            {
                this->setState(CHECKING_DISTANCE);
                this->resetTime();
            }
            break;

        case CHECKING_DISTANCE:
            Serial.println("TransitTask::Checking distance");
            this->distance = sonar->detectDistance();
            Serial.println("TransitTask::Distance: " + String(this->distance));
            if (this->distance < MINDIST)
            {
                if (this->elapsedTime() >= (N2 * 1000))
                {
                    Serial.println("TransitTask::Distance: " + String(this->distance));
                    this->L2->switchOff();
                    this->DependantTask::setCompleted();
                }
            }
            else
            {
                this->setState(READING_DISTANCE);
            }
            break;
        default:
            Serial.println("TransitTask::Invalid state");
            break;
        }
    }
}
