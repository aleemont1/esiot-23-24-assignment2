#ifndef __DEPENDANT_TASK__
#define __DEPENDANT_TASK__

#include "Task.h"
#include <Arduino.h>
#define MAX_DEPENDENCIES 2

/**
 * @class DependantTask
 * @brief A task that depends on another (its dependency).
 *
 * @example "Task *myTask" needs to wait for "Task *dependency" to finish before it can perform some action in its tick() method.
 *
 * @note A maximum of MAX_DEPENDENCIES (default 2) dependencies can be added to a task.
 *
 * @author Alessandro Monticelli
 */
class DependantTask : virtual public Task
{
public:
    DependantTask() : Task(){
        this->dependencies = new Task *[MAX_DEPENDENCIES];
        this->nDependencies = 0;
    };

    /**
     * @brief Add a dependency.
     */
    void addDependency(Task *dependency)
    {
        if (nDependencies <= MAX_DEPENDENCIES)
        {
            Serial.println("DependantTask::addDependency()");
            this->dependencies[nDependencies++] = dependency;
        }
    }

    /**
     * @brief Get the all the dependencies.
     * @returns An array of Task pointers.
     */
    Task **getDependencies()
    {
        return this->dependencies;
    }

    /**
     * @brief Get a dependency.
     * @param index The index of the dependency to get.
     * @returns A Task pointer.
     */
    Task *getDependency(unsigned short index)
    {
        if (index < nDependencies && index >= 0 && this->dependencies[index] != nullptr)
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
