#ifndef __CHECK_OUT_TASK__
#define __CHECK_OUT_TASK__

#include "kernel/DependantTaskWithState.h"
#include "BlinkTask.h"
#include "components/api/Led.h"
#include "components/api/Sonar.h"
#include "config/config.h"
#include "components/api/ServoImpl.h"

class CheckOutTask : public DependantTaskWithState
{
public:
    CheckOutTask(BlinkTask *blinkTask) : DependantTaskWithState()
    {
        Serial.println("CheckOutTask created");
        this->L2 = new Led(L2_PIN);
        this->L3 = new Led(L3_PIN);
        this->sonar = new Sonar(SONAR_TRIG_PIN, SONAR_ECHO_PIN, SONAR_MAX_TIME);
        this->gate = new ServoImpl(SERVO_PIN);
        this->blinkTask = blinkTask;
        this->blinkTask->isCompleted();
        this->blinkTask->setActive(false);
        this->L3->switchOn();
        this->init();
        this->setState(OPENING_GATE);
    }
    void tick() override;

private:
    enum state
    {
        OPENING_GATE,
        CHECKING_DISTANCE,
        CLOSING_GATE,
        TURN_OFF_L3
    };

    Led *L2;
    Led *L3;
    ServoImpl *gate;
    Sonar *sonar;
    Task *blinkTask;
    float detectedDistance; // Distance of the car from the sensor
};

#endif // __CHECK_OUT_TASK__