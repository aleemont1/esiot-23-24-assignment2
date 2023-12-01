#ifndef __WASHING_TASK__
#define __WASHING_TASK__

#include "kernel/DependantTaskWithState.h"
#include "BlinkTask.h"
#include "components/api/Led.h"
#include "components/api/Temp.h"
#include "components/api/LCD.h"
#include "config/config.h"
#include "tasks/CountDown.h"

/**
 * @class CarWashingTask
 * @brief Represents the car washing task.
 */
class WashingTask : public DependantTaskWithState
{
public:
    WashingTask(BlinkTask *blinkTask, CountDown *countDownTask) : DependantTaskWithState()
    {
        Serial.println("WashingTask created");
        this->L2 = new Led(L2_PIN);
        this->L3 = new Led(L3_PIN);
        this->tempSensor = new Temp(TMP_PIN);
        this->lcd = new LCD(0x27, 16, 2);
        this->blinkTask = blinkTask;
        this->blinkTask->init(500); // Blink every 500 ms the red led
        this->blinkTask->setActive(false);
        this->countDownTask = countDownTask;
        this->init();
        this->setState(START_WASHING);
    };
    void tick() override;

private:
    enum state
    {
        START_WASHING,
        COUNTDOWN,
        ERROR_RECOVERY,
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
    CountDown *countDownTask;
};

#endif // __WASHING_TASK__
