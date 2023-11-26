#ifndef __TASK_WITH_TIMER__
#define __TASK_WITH_TIMER__

#include "Task.h"
#include <Arduino.h>

class TaskWithTimer : virtual public Task
{
public:
    TaskWithTimer() : Task(){
        this->timerTimestamp = millis();
    };

    long elapsedTime()
    {
        return millis() - timerTimestamp;
    }
private:
    long timerTimestamp;
};
#endif