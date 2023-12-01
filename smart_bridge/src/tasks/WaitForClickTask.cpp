#include "WaitForClickTask.h"

void WaitForClickTask::tick()
{
    if (this->getDependency(0) != nullptr)
    {
        //Serial.println("WaitForClickTask::getDependency(0) != nullptr");
        if (this->getDependency(0)->isCompleted())
        {
            if (this->start->isPressed())
            {
                Serial.println("WaitForClickTask::START pressed");
                this->setCompleted();
            }
        }
    }
}