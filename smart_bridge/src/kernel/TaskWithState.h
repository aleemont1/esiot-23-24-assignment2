#ifndef __TASK_WITH_STATE__
#define __TASK_WITH_STATE__

#include "TaskWithTimer.h"
#include <Arduino.h>

/**
 * @class TaskWithState
 * @brief A task with a state.
 * @note The state is an integer value that can be used to represent the state of the task.
*/
class TaskWithState : public TaskWithTimer
{
public:
    TaskWithState() : TaskWithTimer(), previousState(0){}; // Default constructor

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

private:
    int previousState;
    int state;
    long stateTimestamp;
};

#endif
