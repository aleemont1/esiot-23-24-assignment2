#ifndef __TASK_WITH_TIMER__
#define __TASK_WITH_TIMER__

#include "Task.h"
#include <Arduino.h>

class TaskWithTimer : public Task
{
public:
    TaskWithTimer() : Task(){
        this->timerTimestamp = millis();
    }; // Default constructor

    long elapsedTime()
    {
        return millis() - timerTimestamp;
    }
private:
    long timerTimestamp;
};
#endif