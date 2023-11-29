#include "WaitForClickTask.h"

void WaitForClickTask::tick()
{
    if (this->getDependency(0) != nullptr)
    {
        Serial.println("WaitForClickTask::getDependency(0) != nullptr");
        if (this->getDependency(0)->isCompleted())
        {
            if (this->start->checkButtonReleaseStatus())
            {
                Serial.println("WaitForClickTask::START pressed");
                this->setCompleted();
            }
        }
    }
}