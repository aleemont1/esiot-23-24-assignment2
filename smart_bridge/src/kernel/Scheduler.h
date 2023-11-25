#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "Task.h"

#define MAX_TASKS 50

class Scheduler
{
private:
  unsigned int numTasks;
  Task *tasks[MAX_TASKS]; // Adjust the size based on the number of tasks
  unsigned long lastRunTime;
  unsigned int schedulerPeriod;

public:
  Scheduler();
  void init(int schedulerPeriod);
  void addTask(Task *task);
  void schedule();
};

#endif