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
    Serial.println("CheckOutTask::started");
    switch (this->getState())
    {
    case OPENING:
        gate->write(90);
        Serial.println("CheckOutTask::Opened the gate");
        this->setState(MEASURE);
        break;
    case MEASURE:

    default:
        break;
    }
}
