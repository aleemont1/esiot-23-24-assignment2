#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "Task.h"

#define MAX_TASKS 30
class Scheduler {
    //A simple cooperative scheduler to execute tasks
    Task *tasks[MAX_TASKS];
    int numTasks;
    int period;

    public:
        void init(int period);
        virtual bool addTask(Task *task);
        virtual void schedule();
};

#endif