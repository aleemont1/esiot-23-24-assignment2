#include "CheckInTask.h"

CheckInTask::CheckInTask() {}

void CheckInTask::init()
{
    L1 = new Led(L1_PIN);
    L2 = new Led(L2_PIN);
    gate = new Servo();
    message = new String();
}

void CheckInTask::tick()
{
    L1->switchOn();
    
}