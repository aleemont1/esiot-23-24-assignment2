#include "Arduino.h"
#include "kernel/Scheduler.h"
#include "tasks/CheckInTask.h"

Scheduler *scheduler = new Scheduler();

void setup()
{
    Serial.begin(9600);
    scheduler->init(1900);
    CheckInTask *checkInTask = new CheckInTask();
    checkInTask->init();
    checkInTask->setActive(true);

    if (scheduler->addTask(checkInTask))
    {
        Serial.println("Task added");
    }
    else
    {
        Serial.println("Task not added");
    }
}

void loop()
{
    scheduler->schedule();
}