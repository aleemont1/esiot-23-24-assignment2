#include "Arduino.h"
#include "kernel/Scheduler.h"
#include "tasks/BlinkTask.h"
#include "tasks/CheckInTask.h"
#include "config/config.h"

Scheduler scheduler;

void setup()
{
    Serial.begin(9600);
    scheduler.init(100);
    //NOTE: THIS IS JUST A TEST TASK
    BlinkTask *blinkTask = new BlinkTask(L3_PIN);
    blinkTask->init(1000);
    blinkTask->setActive(true);
    //NOTE: THIS IS THE REAL TASK
    CheckInTask *checkInTask = new CheckInTask();
    checkInTask->init();
    checkInTask->setActive(true);
    scheduler.addTask(checkInTask);
    scheduler.addTask(blinkTask);
}

void loop()
{
    scheduler.schedule();
}