#ifndef __WAITING_TASK__
#define __WAITING_TASK__

#include "kernel/TaskWithState.h"
#include "components/api/Pir.h"
#include "config/config.h"

class WaitingTask : public TaskWithState
{
public:
    WaitingTask() : TaskWithState()
    {
        this->pir=new Pir(PIR_PIN); //attached to the INTERRUPT_PIN
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
        FINSHED //is going to go in checkin state
    };
    Pir *pir;
};

#endif
