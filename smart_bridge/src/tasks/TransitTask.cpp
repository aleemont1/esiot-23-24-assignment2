#include "TransitTask.h"

void TransitTask::tick()
{
    if (this->getDependency(0) != nullptr)
    {
        if (this->getDependency(0)->isCompleted())
        {
            switch (this->getState())
            {
            case READING_DISTANCE:
                this->lcd->write("Proceed to the", 0, 0);
                this->lcd->write("washing area!", 0, 1);
                this->L2->switchOn();
                this->distance = sonar->detectDistance();
#ifdef __LOG
                // Serial.println(F("TransitTask::Distance: "));
                // Serial.print(String(this->distance));
#endif
                if (this->distance < MINDIST)
                {
                    this->resetTime();
                    this->setState(CHECKING_DISTANCE);
#ifdef __LOG
                    // Serial.println(F("TransitTask::Checking distance"));
#endif
                }
                break;

            case CHECKING_DISTANCE:
                if (!this->blinkTask->isActive())
                {
                    this->blinkTask->setActive(true);
                }
                this->distance = sonar->detectDistance();
#ifdef __LOG
                // Serial.print(F("TransitTask::Distance: "));
                // Serial.println(String(this->distance));
#endif
                if (this->distance < MINDIST)
                {
#ifdef __DEBUG
                    // Serial.print(F("TransitTask::Elapsed: "));
                    // Serial.println(String(this->elapsedTime()));
#endif
                    if (this->elapsedTime() >= (N2 * 1000))
                    {
#ifdef __LOG
                        // Serial.println(F("TransitTask::Distance: "));
                        // Serial.println(String(this->distance));
                        // Serial.println(F("TransitTask::Car entered"));
                        // Serial.println(F("TransitTask::Closing gate"));
#endif
                        this->gate->write(0);
                        if (this->blinkTask->isActive())
                        {
                            this->blinkTask->setActive(false);
                        }
                        this->L2->switchOn();
                        this->setCompleted();
                    }
                }
                else
                {
#ifdef __LOG
                    // Serial.println(F("TransitTask::Reading distance"));
#endif
                    if (this->blinkTask->isActive())
                    {
                        this->L2->switchOff();
                        this->blinkTask->setActive(false);
                    }
                    this->setState(READING_DISTANCE);
                }
                break;
            default:
                // Serial.println(F("TransitTask::Invalid state"));
                break;
            }
        }
    }
}
