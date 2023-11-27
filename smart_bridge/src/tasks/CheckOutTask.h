#ifndef __CHECK_OUT_TASK__
#define __CHECK_OUT_TASK__

#include "kernel/TaskWithState.h"
#include "components/api/Led.h"
#include "config/config.h"
#include <Servo.h>

class CheckOutTask : public TaskWithState
{
public:
    CheckOutTask() : TaskWithState()
    {
        this->L3 = new Led(L3_PIN);
        this->gate = new Servo();
        gate->attach(SERVO_PIN);
        this->init();
        this->setState(OPENING);
        Serial.println("CheckOutTask created");
    }
    void tick() override;

private:
    enum states
    {
        OPENING,
        MEASURE,
        CLOSURE
    };

    Led *L3;
    Servo *gate;
};

#endif __CHECK_OUT_TASK__