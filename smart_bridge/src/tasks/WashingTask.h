#ifndef __WASHING_TASK__
#define __WASHING_TASK__

#define SONAR_MAX_TIME 10

#include "kernel/DependantTaskWIthState.h"
#include "components/api/Led.h"
#include <components/api/Temp.h>
// TODO: #include "components/api/Lcd.h" actually missing the LCD component
#include "config/config.h"

/**
 * @class CarWashingTask
 * @brief Represents the car washing task.
 */
class WashingTask : public DependantTaskWithState
{
public:
    WashingTask() : DependantTaskWithState()
    {
        this->L2 = new Led(L2_PIN);
        this->L3 = new Led(L3_PIN);
        this->tempSensor = new Temp(TMP_PIN);
        this->init();
        this->setState(START_WASHING);
        Serial.println("WashingTask created");
    };
    void tick() override;

private:
    enum states
    {
        START_WASHING,
        COUNTDOWN,
        CRITICAL_TEMP,
        ERROR
    };

    int savedCountDown;
    unsigned long savedTimeInState;
    int countDown;
    /*     int washingTime;  it is the N3*/
    Led *L2;          // Red led
    Led *L3;          // Green led
    Temp *tempSensor; // Temperature sensor
    /* TODO: LCD* lcd */
};

#endif // __WASHING_TASK__
