#ifndef __CHECK_IN_TASK__
#define __CHECK_IN_TASK__

#include "kernel/DependantTaskWithState.h"
#include "components/api/Led.h"
#include "config/config.h"
#include <Servo.h>

/**
 * @class CheckInTask
 * @brief This task opens the gate after the car has been detected.
*/
class CheckInTask : public DependantTaskWithState
{
public:
    CheckInTask() : DependantTaskWithState()
    {
        this->L1 = new Led(L1_PIN);
        this->L2 = new Led(L2_PIN);
        this->gate = new Servo();
        this->gate->attach(SERVO_PIN);
        this->init();
        this->setState(STARTED);
        Serial.println("CheckInTask created");
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
