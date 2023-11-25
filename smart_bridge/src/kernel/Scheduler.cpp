#include "Scheduler.h"
#include <TimerOne.h>

Scheduler::Scheduler() : numTasks(0), lastMillis(0) {}

void Scheduler::init(int intervalMillis) {
  // Set up the interval for the scheduler
  // You may want to use a timer or other mechanisms for more accurate timing
  // For simplicity, using millis() in this example
  this->intervalMillis = intervalMillis;
  lastMillis = millis() - intervalMillis;
}

void Scheduler::addTask(Task *task) {
    if (numTasks < sizeof(tasks) / sizeof(tasks[0])) {
        tasks[numTasks++] = task;
    }
}

void Scheduler::schedule() {
  unsigned long currentMillis = millis();
  if (currentMillis - lastMillis >= intervalMillis) { // Adjust the interval as needed
    for (int i = 0; i < numTasks; ++i) {
      if (tasks[i] != nullptr && tasks[i]->isActive()) {
        tasks[i]->tick();
      }
    }
    lastMillis = currentMillis;
  }
}