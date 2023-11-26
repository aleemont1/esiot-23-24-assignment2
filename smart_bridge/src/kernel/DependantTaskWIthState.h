#ifndef __DEPENDANT_TASK_WITH_STATE__
#define __DEPENDANT_TASK_WITH_STATE__

// Create a task that depends on another (its dependency) and has a state
#include "DependantTask.h"
#include "TaskWithState.h"

class DependantTaskWithState : public TaskWithState, public DependantTask
{
public:
    DependantTaskWithState() : TaskWithState(), DependantTask(){};
};

#endif
