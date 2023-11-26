#ifndef __DEPENDANT_TASK__
#define __DEPENDANT_TASK__

#include "Task.h"

class DependantTask : virtual public Task
{
public:
    DependantTask() : Task(){};

    void setDependency(Task *dependency)
    {
        this->dependency = dependency;
    }

    Task *getDependency()
    {
        return this->dependency;
    }

    bool canRun()
    {
        return this->dependency->isCompleted();
    }

private:
    Task *dependency;
};

#endif