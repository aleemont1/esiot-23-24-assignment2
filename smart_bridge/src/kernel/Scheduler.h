#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "Task.h"

class Scheduler {
private:
  Task *tasks[10]; // Adjust the size based on the number of tasks
  int numTasks;
  unsigned long lastMillis;
  int intervalMillis;

public:
  Scheduler();
  void init(int intervalMillis);
  void addTask(Task *task);
  void schedule();
};

#endif