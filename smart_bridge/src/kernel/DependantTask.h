#ifndef __DEPENDANT_TASK__
#define __DEPENDANT_TASK__

#include "Task.h"

#define MAX_DEPENDENCIES 2

class DependantTask : virtual public Task
{
public:
    DependantTask() : Task(){};

    void addDependency(Task *dependency)
    {
        if (nDependencies < sizeof(dependencies) / sizeof(dependencies[0]) && nDependencies <= MAX_DEPENDENCIES)
        {
            this->dependencies[nDependencies++] = dependency;
        }
    }

    Task **getDependencies()
    {
        return this->dependencies;
    }

    Task *getDependency(unsigned short index)
    {
        if (index < sizeof(dependencies) / sizeof(dependencies[0]))
        {
            return this->dependencies[index];
        }
        return nullptr;
    }

private:
    Task **dependencies;
    unsigned short nDependencies;
};

#endif
