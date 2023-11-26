#ifndef __WASHING_TASK__
#define __WASHING_TASK__

#include "kernel/TaskWithState.h"
#include "components/api/Led.h"
#include "config/config.h"
// TODO: #include "components/api/Lcd.h" actually missing the LCD component
#include "config/config.h"

/**
 * @class CarWashingTask
 * @brief Represents the car washing task.
 */
class WashingTask : public TaskWithState
{
public:
    WashingTask(int washingTime, int redLedPin, int greenLedPin /* , LCD* lcd  */) : TaskWithState()
    {
        this->L2 = new Led(L2_PIN);
        this->L2 = new Led(L3_PIN);
        Serial.println("WashingTask created");
        this->setState(START_WASHING);
    };
    void init(int period);
    void tick() override;

private:
    enum
    {
        START_WASHING,
        COUNTDOWN,
        WASHING_IN_PROGRESS,
        CRITICAL_TEMP,
        END_WASHING,
        CHECK_OUT,
    } state;

    int savedCountDown;
    unsigned long savedTimeInState;
    int countDown;
/*     int washingTime;  it is the N3*/
    Led *L2; // Red led
    Led *L3; // Green led
    /* TODO: LCD* lcd */
};

#endif // __WASHING_TASK__
