#ifndef __SLEEPING_TASK__
#define __SLEEPING_TASK__

#define _MAX_TIME_BEFORE_SLEEP 10000 /*ms*/

#include "config/config.h"
#include "components/api/Pir.h"
#include "kernel/DependantTaskWithState.h"
#include "avr/interrupt.h"
#include "avr/sleep.h"


/**
 * @class SleepingTask
 * @brief This task handle the sleeping state using the pir as sensor to 
 * detect movement and wake up arduino
 */

class SleepingTask : public TaskWithState
{
public:
    SleepingTask() : TaskWithState()
    {
        Serial.println("SleepingTask created");
        this->pir = new Pir(PIR_PIN);
        this->init();
        this->setState(WAITING_FOR_SOMEONE);
    };
    void tick() override;

private:
    enum state
    {
        WAITING_FOR_SOMEONE,
        GO_IN_SLEEP,
        WAKE_UP,
        OBJECT_DETECTED_STATUS,
        OBJECT_NOT_DETECTED_STATUS,
        SLEEP
    };
    Pir *pir;
};

#endif
