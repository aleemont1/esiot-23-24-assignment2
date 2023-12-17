#include "Scheduler.h"
#include "Arduino.h"

Scheduler::Scheduler() : numTasks(0), lastRunTime(0) {}

void Scheduler::init(int schedulerPeriod)
{
  this->schedulerPeriod = schedulerPeriod;
  lastRunTime = millis() - schedulerPeriod;
}

void Scheduler::addTask(Task *task)
{
  if (numTasks < sizeof(tasks) / sizeof(tasks[0]))
  {
    tasks[numTasks++] = task;
#ifdef __DEBUG
    // Serial.println(F("tasks[" + String(numTasks - 1) + "]: [" + String(reinterpret_cast<uintptr_t>(tasks[numTasks - 1])) + "]"));
#endif
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
#ifdef __DEBUG
            // Serial.println(F("Scheduler::tasks[" + String(i) + "]: " + String(reinterpret_cast<uintptr_t>(tasks[i])) + " tick"));
#endif
            tasks[i]->tick(); // Execute task
            // // Serial.println(F("Scheduler::numTasks: " + numTasks);
          }
        }
        else // Task is aperiodic
        {
#ifdef __DEBUG
          // Serial.println(F("Scheduler::tasks[" + String(i) + "]: " + String(reinterpret_cast<uintptr_t>(tasks[i])) + " tick"));
#endif
          tasks[i]->tick(); // Execute task without checking time
        }
      }
    }
    lastRunTime = now; // Update lastRunTime
  }
}
