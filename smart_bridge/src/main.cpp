#include "Arduino.h"
#include "kernel/Scheduler.h"
#include "tasks/BlinkTask.h"
#include "tasks/CheckInTask.h"
#include "config/config.h"
#include "tasks/TransitTask.h"

Scheduler scheduler;

void setup()
{
    Serial.begin(9600);
    scheduler.init(50);
    BlinkTask *blinkTaskTransit = new BlinkTask(L2_PIN);
    CheckInTask *checkInTask = new CheckInTask();
    TransitTask *transitTask = new TransitTask(blinkTaskTransit);
    BlinkTask *blink = new BlinkTask(L3_PIN);
    transitTask->addDependency(checkInTask);

    scheduler.addTask(checkInTask);
    scheduler.addTask(transitTask);
    scheduler.addTask(blinkTaskTransit);

}

void loop()
{
    scheduler.schedule();
}