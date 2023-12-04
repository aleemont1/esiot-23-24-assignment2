#include "WaitForClickTask.h"

void WaitForClickTask::tick()
{
    if (this->getDependency(0) != nullptr)
    {
        if (this->getDependency(0)->isCompleted())
        {
            this->lcd->write("Press START to", 0, 0);
            this->lcd->write("begin washing", 0, 1);
#ifdef __LOG
            Serial.println("WaitForClickTask::Waiting for START click");
#endif
            this->start->sync();
            if (this->start->isPressed())
            {
#ifdef __LOG
                Serial.println("WaitForClickTask::START pressed");
#endif
                this->lcd->clear();
                this->lcd->write("Starting to wash", 0, 0);
                this->setCompleted();
            }
        }
    }
}