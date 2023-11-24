#ifndef __TASK_WITH_STATE__
#define __TASK_WITH_STATE__

#include "Task.h"
#include <Arduino.h>

// TODO: Check if state managing is necessary
// TODO: Create a stateless timed task class

class TaskWithState : public Task
{
public:
    TaskWithState() : Task(){}; // Default constructor

    void setState(const int state)
    {
        this->state = state;
        this->stateTimestamp = millis();
    }

    int getState()
    {
        return this->state;
    }

    long timeInState()
    {
        return millis() - stateTimestamp;
    }

private:
    int state;
    long stateTimestamp;
};

#endif