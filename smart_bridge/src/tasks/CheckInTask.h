#ifndef __CHECK_IN_TASK__
#define __CHECK_IN_TASK__

#include "config/config.h"

#include "kernel/DependantTaskWithState.h"
#include "components/api/Led.h"
#include "components/api/LCD.h"
#include "components/api/ServoImpl.h"

/**
 * @class CheckInTask
 * @brief This task opens the gate after the car has been detected.
 * 
 * @author Alessandro Monticelli
*/
class CheckInTask : public DependantTaskWithState
{
public:
    CheckInTask() : DependantTaskWithState()
    {
        this->L1 = new Led(L1_PIN);
        this->L2 = new Led(L2_PIN);
        this->lcd = new LCD(0x27, 16, 2);
        this->gate = new ServoImpl(SERVO_PIN);
        this->init();
        this->setState(STARTED);
        // Serial.println(F("CheckInTask created"));
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
    LCD *lcd;
    ServoImpl *gate;
};

#endif
