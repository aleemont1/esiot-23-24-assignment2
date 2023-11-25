#ifndef __CHECK_IN_TASK__
#define __CHECK_IN_TASK__

#include "kernel/TaskWithState.h"
#include "components/api/Led.h"
#include "config/config.h"
#include <Servo.h>

class CheckInTask : public TaskWithState
{
public:
    CheckInTask() : TaskWithState()
    {
        this->L1 = new Led(L1_PIN);
        this->L2 = new Led(L2_PIN);
        this->gate = new Servo();
        gate->attach(SERVO_PIN);
        Serial.println("CheckInTask created");
        this->setState(STARTED);
    };
    void tick() override;

private:
    enum states
    {
        STARTED,
        WAITING
    };
    Led *L1;
    Led *L2;
    Servo *gate;
};

#endif