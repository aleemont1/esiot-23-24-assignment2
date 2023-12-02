#include "CheckOutTask.h"

/*
—
4)
Sezione del testo: Check-out
    - and the gate GATE is opened to allow the vehicle to move away from the Washing Area.
    - In this stage, the leaving process can be considered completed when the CAR DISTANCE DETECTOR measures a distance greater than MAXDIST for N4 secs. At that point, the gate GATE is closed, L3 is turned off.
—
Checkout:
- SONAR misura dist
- Disabilita PIR
- If dist > MAXDIST and TIME_IN_STATE > N4 sec:
    - GATE si chiude
    - Passa a waiting state
*/

void CheckOutTask::tick()
{
    if (this->getDependency(0)->isCompleted())
    {
        Serial.println("CheckOutTask::started");
        switch (this->getState())
        {
        case OPENING_GATE:
            Serial.println("CheckOutTask::Opening the gate");
            gate->write(90);
            Serial.println("CheckOutTask::Opened the gate");
            this->setState(CHECKING_DISTANCE);
            break;

        case CHECKING_DISTANCE:
            Serial.println("CheckOutTask::Measuring car distance");
            this->detectedDistance = sonar->detectDistance();
            Serial.println("CheckOutTask::The distance detected is: " + String(this->detectedDistance));
            if (this->detectedDistance > MAXDIST && this->elapsedTime() >= (N4_FOR_DIST * 1000))
            {
                Serial.println("CheckOutTask::The car is far enough");
                this->resetTime();
                this->setState(CLOSING_GATE);
            }
            break;

        case CLOSING_GATE:
            Serial.println("CheckOutTask::Closing the gate");
            gate->write(0);
            delay(2000); // Simulates the time needed to close the gate
            Serial.println("CheckOutTask::Closed the gate");
            this->setState(TURN_OFF_L3);
            break;

        case TURN_OFF_L3:
            Serial.println("CheckOutTask::Turning off L3");
            L3->switchOff();
            this->setCompleted();
            break;

        default:
            Serial.println("CheckOutTask::Invalid state");
            break;
        }
    }
}
