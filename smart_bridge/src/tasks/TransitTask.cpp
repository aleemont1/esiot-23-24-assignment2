#include "TransitTask.h"

void TransitTask::tick()
{
    if (this->getDependency(0)->isCompleted())
    {
        switch (this->getState())
        {
        case READING_DISTANCE:
#ifdef __LOG
            Serial.println("TransitTask::Reading distance");
#endif
            this->blinkTask->setActive(true);
            this->distance = sonar->detectDistance();
            // Serial.println("TransitTask::Distance: " + String(this->distance));
            if (this->distance < MINDIST)
            {
                this->setState(CHECKING_DISTANCE);
#ifdef __LOG
                Serial.println("TransitTask::Checking distance");
#endif
                this->resetTime();
            }
            break;

        case CHECKING_DISTANCE:
            this->distance = sonar->detectDistance();
            // Serial.println("TransitTask::Distance: " + String(this->distance));
            if (this->distance < MINDIST)
            {
                if (this->elapsedTime() >= (N2 * 1000))
                {
                    // Serial.println("TransitTask::Distance: " + String(this->distance));
                    gate->write(0);
                    this->blinkTask->setActive(false);
                    this->setCompleted();
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
