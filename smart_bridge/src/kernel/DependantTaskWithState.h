#ifndef __DEPENDANT_TASK_WITH_STATE__
#define __DEPENDANT_TASK_WITH_STATE__

#include "DependantTask.h"
#include "TaskWithState.h"

/**
 * @class DependantTaskWithState
 * @brief A task that depends on other tasks and has a state
 * 
 * @author Alessandro Monticelli
 */
class DependantTaskWithState : virtual public TaskWithState, virtual public DependantTask
{
public:
    /**
     * @brief Default constructor (no dependencies)
     */
    DependantTaskWithState() : TaskWithState(), DependantTask(){};
    /**
     * @brief Constructor with two dependencies
     * @param dependency1 The first dependency
     * @param dependency2 The second dependency
     */
    DependantTaskWithState(Task *dependency1, Task *dependency2) : TaskWithState(), DependantTask(dependency1, dependency2){};
};

#endif
