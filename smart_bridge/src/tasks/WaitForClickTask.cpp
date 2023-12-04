#include "WaitForClickTask.h"

void WaitForClickTask::tick()
{
    if (this->getDependency(0) != nullptr)
    {
        if (this->getDependency(0)->isCompleted())
        {
#ifdef __LOG
            Serial.println("WaitForClickTask::Waiting for START click");
#endif
            this->start->sync();
            if (this->start->isPressed())
            {
#ifdef __LOG
                Serial.println("WaitForClickTask::START pressed");
#endif
                this->setCompleted();
            }
        }
    }
}