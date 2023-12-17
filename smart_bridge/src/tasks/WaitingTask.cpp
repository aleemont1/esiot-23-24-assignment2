#include "WaitingTask.h"


void WaitingTask::tick()
{
   if (this->getDependency(0) != nullptr)
    {
        if (this->getDependency(0)->isCompleted())
        {
            switch (this->getState())
            {
                case STARTED:
                    break;
                    // Serial.println(F("sono qui in waiting"));
            }
            
        }
    }
}