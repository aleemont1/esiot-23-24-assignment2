#ifndef __TRANSIT_TASK__
#define __TRANSIT_TASK__

#define SONAR_MAX_TIME 10

#include "kernel/DependantTaskWIthState.h"
#include "config/config.h"
#include "components/api/Sonar.h"
#include "components/api/Led.h"

#include <Servo.h>
/**
 * @class TransitTask
 * @brief This task reads the distance of the car while entering the washing area.
 *        If the distance is less than a threshold, the task is completed.
 */

class TransitTask : public DependantTaskWithState
{
public:
    TransitTask() : DependantTaskWithState()
    {
        this->L2 = new Led(L2_PIN);
        this->sonar = new Sonar(SONAR_TRIG_PIN, SONAR_ECHO_PIN, SONAR_MAX_TIME);
        this->gate = new Servo();
        this->gate->detach();
        this->gate->attach(SERVO_PIN);
        this->init();
        this->setState(READING_DISTANCE);
        Serial.println("TransitTask created");
    };
    void tick() override;

private:
    enum state
    {
        READING_DISTANCE,
        CHECKING_DISTANCE
    };
    Led *L2;
    Sonar *sonar;
    Servo *gate;
    float distance;
};

#endif
