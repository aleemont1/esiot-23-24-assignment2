#include "CheckInTask.h"

void CheckInTask::tick()
{
    Serial.begin(9600);
#ifdef __DEBUG
    Serial.println("CheckInTask::tick(): Turning on L1");
    Serial.println("CheckInTask::tick(): Time in state: " + String(timeInState()));
#endif
    L1->switchOn();
    if (timeInState() > N1 * 1000)
    {
#ifdef __DEBUG
        Serial.println("CheckInTask::tick(): Turning off L1");
        Serial.println("CheckInTask::tick(): Turning on L2");
#endif
        L1->switchOff();
        L2->switchOn();
#ifdef __DEBUG
        Serial.println("CheckInTask::tick(): Opening gate: ");
        Serial.println("CheckInTask::tick(): Time in state: " + String(timeInState()));
#endif
        gate->write(90);
    }
}