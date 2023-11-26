#include "Scheduler.h"
#include <TimerOne.h>

Scheduler::Scheduler() : numTasks(0), lastRunTime(0) {}

void Scheduler::init(int schedulerPeriod)
{
  // Set up the interval for the scheduler
  // You may want to use a timer or other mechanisms for more accurate timing
  // For simplicity, using millis() in this example
  this->schedulerPeriod = schedulerPeriod;
  lastRunTime = millis() - schedulerPeriod;
}

void Scheduler::addTask(Task *task)
{
  if (numTasks < sizeof(tasks) / sizeof(tasks[0]))
  {
    tasks[numTasks++] = task;
  }
}

void Scheduler::schedule()
{
  unsigned long now = millis();
  if ((now - lastRunTime) >= schedulerPeriod) // It's time for scheduler to tick
  {
    for (register unsigned int i = 0; i < numTasks; ++i) // For each task in the scheduler
    {
      if (tasks[i] != nullptr && tasks[i]->isActive()) // If task is active
      {
        if (tasks[i]->isPeriodic()) // If the task is periodic
        {
          if (tasks[i]->updateAndCheckTime(schedulerPeriod)) // Check if it's time to execute
          {
            tasks[i]->tick(); // Execute task
          }
        }
        else // Task is aperiodic
        {
          tasks[i]->tick(); // Execute task without checking time
        }
      }
    }
    lastRunTime = now; // Update lastRunTime
  }
}
