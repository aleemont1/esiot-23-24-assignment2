#ifndef __WASHING_TASK__
#define __WASHING_TASK__

#define SONAR_MAX_TIME 10

#include "kernel/DependantTaskWIthState.h"
#include "BlinkTask.h"
#include "components/api/Led.h"
#include <components/api/Temp.h>
#include "components/api/LCD.h"
#include "config/config.h"

/**
 * @class CarWashingTask
 * @brief Represents the car washing task.
 */
class WashingTask : public DependantTaskWithState
{
public:
    WashingTask(BlinkTask *blinkTask) : DependantTaskWithState()
    {
        Serial.println("WashingTask created");
        this->L2 = new Led(L2_PIN);
        this->L3 = new Led(L3_PIN);
        this->tempSensor = new Temp(TMP_PIN);
        // TODO: this->lcd = new LCD(1, 16, 2);
        this->blinkTask = blinkTask;
        this->blinkTask->init(500);
        this->blinkTask->setActive(false);
        this->init();
        this->setState(START_WASHING);
    };
    void tick() override;

private:
    enum state
    {
        START_WASHING,
        COUNTDOWN,
        CRITICAL_TEMP,
        ERROR
    };

    int savedCountDown;
    unsigned long savedTimeInState;
    int countDown;
    Led *L2;          // Red led
    Led *L3;          // Green led
    Temp *tempSensor; // Temperature sensor
    LCD *lcd;         // The LCD display
    Task *blinkTask;  // The blink task for the leds
};

#endif // __WASHING_TASK__
