#ifndef __SLEEPING_TASK__
#define __SLEEPING_TASK__

#define _MAX_TIME_BEFORE_SLEEP 10

#include "config/config.h"
#include "components/api/Pir.h"
#include "kernel/DependantTaskWithState.h"


/**
 * @class SleepingTask
 * @brief This task handle the sleeping state using the pir as sensor to detect movement and 
 * wake up arduino
 */

class SleepingTask : public DependantTaskWithState
{
public:
    SleepingTask(SleepingTask *sleepingTask) : DependantTaskWithState()
    {
        Serial.println("SleepingTask created");
        this->pir = new Pir(PIR_PIN);
        this->setState(WAITING_FOR_SOMEONE);
    };
    void tick() override;

private:
    enum state
    {
        WAITING_FOR_SOMEONE,
        GO_IN_SLEEP,
        WAKE_UP,
    };
    Pir *pir;
};

#endif
