#include "CheckInTask.h"

// Implement the CheckInTask class that executes the checkin process.
// The checkin process is as follows:
// 1. Turn on the L1 led.
// 2. Wait for N1 seconds.
// 3. Turn on the L2 led.
// 4. Open the gate.

void CheckInTask::tick()
{
    switch (this->getState())
    {

    case STARTED:
        L1->switchOn(); // Turn on L1
#ifdef __LOG
        Serial.println("CheckInTask::Turned on L1");
#endif
        this->setState(WAITING); // Set the state to STATE1
        break;
    case WAITING:
        if (this->elapsedTime() >= (N1 * 1000)) // After N1 seconds have elapsed
        {
            L1->switchOff(); // Turn off L1
#ifdef __LOG
            Serial.println("CheckInTask::Turned off L1");
#endif
            gate->write(90); // Open the gate
#ifdef __LOG
            Serial.println("CheckInTask::Opened the gate");
#endif
            this->setCompleted(); // Mark the task as completed
        }
    }
}