#ifndef __TASK_WITH_STATE__
#define __TASK_WITH_STATE__

#include "TaskWithTimer.h"
#include <Arduino.h>

/**
 * @class TaskWithState
 * @brief A task with a state.
 * @note The state is an integer value that can be used to represent the state of the task.
 * 
 * @author Alessandro Monticelli
*/
class TaskWithState : public TaskWithTimer
{
public:
    TaskWithState() : TaskWithTimer(){}; // Default constructor

    void setState(const int state)
    {
        this->state = state;
        this->stateTimestamp = millis();
    }

    int getState()
    {
        return this->state;
    }

private:
    int state;
    long stateTimestamp;
};

#endif
