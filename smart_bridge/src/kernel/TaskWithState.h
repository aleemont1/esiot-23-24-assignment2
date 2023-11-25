#ifndef __TASK_WITH_STATE__
#define __TASK_WITH_STATE__

#include "Task.h"
#include <Arduino.h>

// TODO: Check if state managing is necessary
// TODO: Create a stateless timed task class

class TaskWithState : public Task
{
public:
    TaskWithState() : Task(), previousState(0){}; // Default constructor

    void setState(const int state)
    {
        this->previousState = this->state;
        this->state = state;
        this->stateTimestamp = millis();
    }

    int getState()
    {
        return this->state;
    }

    int getPreviousState()
    {
        return this->previousState;
    }

    long elapsedTime()
    {
        return millis() - stateTimestamp;
    }

private:
    int previousState;
    int state;
    long stateTimestamp;
};

#endif