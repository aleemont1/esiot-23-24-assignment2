#ifndef __DEPENDANT_TASK__
#define __DEPENDANT_TASK__

#include "Task.h"

class DependantTask : public Task
{
public:
    DependantTask() : Task(){};
    void init() override
    {
        Task::init();
        this->setDependant(true);
    }

    void init(int period) override
    {
        Task::init(period);
        this->setDependant(true);
    }

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