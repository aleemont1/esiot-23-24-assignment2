#ifndef __SLEEPING_TASK__
#define __SLEEPING_TASK__

#define _MAX_TIME_BEFORE_SLEEP 10000 /*ms*/

#include "config/config.h"
#include "components/api/Pir.h"
#include "components/api/LCD.h"
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
        this->lcd=new LCD(0x27, 16,2);
        this->init();
        this->setActive(true);
        this->setState(STARTING);
    };
    void tick() override;
    void wakeUp();
    void goInSleep();

private:
    enum state
    {
        STARTING,
        ALIVE,
        OBJECT_DETECTED
    };
    Pir *pir;
    LCD *lcd;
};

#endif
