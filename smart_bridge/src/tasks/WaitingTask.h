#ifndef __WAITING_TASK__
#define __WAITING_TASK__

#include "kernel/DependantTaskWithState.h"
#include "components/api/Pir.h"
#include "SleepingTask.h"
#include "config/config.h"

class WaitingTask : public DependantTaskWithState
{
public:
/**
 * 
 * 
*/
    WaitingTask(SleepingTask *SleepingTask) : DependantTaskWithState()
    {
        this->pir=new Pir(PIR_PIN); //attached to the INTERRUPT_PIN 2
        this->init();
        this->setState(STARTED);
        Serial.println("WaitingTask created");
    };
    void tick() override;

private:
    enum states
    {
        STARTED, //is just left ... so
        IN_SUSPENSION, //is going to go in sleep mode
        FINISHED //is going to go in checkin state
    };
    Pir *pir;
};

#endif
