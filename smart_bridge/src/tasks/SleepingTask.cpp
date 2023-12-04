#include "SleepingTask.h"

void SleepingTask::tick()
{
    

    switch (this->getState())
    {
        case SLEEP:


            if (pir->checkDetectedStatus()) { //se ho rilevato qualcosa
                Serial.println("OBJECT reveal");
                this->setState(OBJECT_DETECTED_STATUS);
            } else {
                Serial.println("OBJECT not revealed");
            }
            break;

        case OBJECT_DETECTED_STATUS:
            break;

        case OBJECT_NOT_DETECTED_STATUS:
            
            break;

    }
}