#include "TransitTask.h"

void TransitTask::tick()
{
    if (this->getDependency(0)->isCompleted())
    {
        switch (this->getState())
        {
        case READING_DISTANCE:
            this->distance = sonar->detectDistance();
#ifdef __LOG
            Serial.println("TransitTask::Distance: " + String(this->distance));
#endif
            if (this->distance < MINDIST)
            {
                this->resetTime();
                this->setState(CHECKING_DISTANCE);
#ifdef __LOG
                Serial.println("TransitTask::Checking distance");
#endif
            }
            break;

        case CHECKING_DISTANCE:
            if (!this->blinkTask->isActive())
            {
                this->blinkTask->resetBlink();
                this->blinkTask->setActive(true);
            }
            this->distance = sonar->detectDistance();
#ifdef __LOG
            Serial.println("TransitTask::Distance: " + String(this->distance));
#endif
            if (this->distance < MINDIST)
            {
#ifdef __DEBUG
                Serial.println("TransitTask::Elapsed: " + String(this->elapsedTime()));
#endif
                if (this->elapsedTime() >= (N2 * 1000))
                {
#ifdef __LOG
                    Serial.println("TransitTask::Distance: " + String(this->distance));
                    Serial.println("TransitTask::Car entered");
                    Serial.println("TransitTask::Closing gate");
#endif
                    gate->write(0);
                    if (this->blinkTask->isActive())
                    {
                        this->blinkTask->resetBlink();
                        this->blinkTask->setActive(false);
                    }
                    this->L2->switchOn();
                    this->setCompleted();
                }
            }
            else
            {
#ifdef __LOG
                Serial.println("TransitTask::Reading distance");
#endif
                if (this->blinkTask->isActive())
                {
                    this->blinkTask->resetBlink();
                    this->blinkTask->setActive(false);
                }
                this->setState(READING_DISTANCE);
            }
            break;
        default:
            Serial.println("TransitTask::Invalid state");
            break;
        }
    }
}
