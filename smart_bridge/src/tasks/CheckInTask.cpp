#include "CheckInTask.h"

void CheckInTask::tick()
{
    switch (this->getState())
    {

    case STARTED:
        lcd->clear(); // Clear the LCD
        lcd->write("WELCOME TO THE", 0, 0);
        lcd->write("SMART WASHING", 0, 1);
        L1->switchOn(); // Turn on L1
#ifdef __LOG
        Serial.println(F("CheckInTask::Turned on L1"));
#endif
        this->resetTime(); // Reset the elapsed time
        this->setState(WAITING); // Set the state to WAITING
        break;
    case WAITING:
        if (this->elapsedTime() >= (N1 * 1000)) // After N1 seconds have elapsed
        {
            L1->switchOff(); // Turn off L1
#ifdef __LOG
            Serial.println(F("CheckInTask::Turned off L1"));
#endif
            gate->write(90); // Open the gate
#ifdef __LOG
            Serial.println(F("CheckInTask::Opened the gate"));
#endif
            this->setCompleted(); // Mark the task as completed
        }
    }
}