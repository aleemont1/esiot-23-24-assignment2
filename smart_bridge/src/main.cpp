#include "Arduino.h"
#include "kernel/Scheduler.h"
#include "tasks/BlinkTask.h"
#include "tasks/CheckInTask.h"
#include "config/config.h"
#include "tasks/TransitTask.h"
#include "tasks/WaitingTask.h"




Scheduler scheduler;

void setup()
{
    Serial.begin(9600);
    scheduler.init(50);
    BlinkTask *blinkTaskTransit = new BlinkTask(L2_PIN);
    //SleepingTask *sleepingTask = new SleepingTask();

    
    WaitingTask *waitingTask = new WaitingTask();
    CheckInTask *checkInTask = new CheckInTask();
    TransitTask *transitTask = new TransitTask(blinkTaskTransit);
    
    scheduler.addTask(waitingTask);
    //checkInTask->addDependecy(waitingTask)
    transitTask->addDependency(checkInTask);
    scheduler.addTask(checkInTask);
    scheduler.addTask(transitTask);
    scheduler.addTask(blinkTaskTransit);
}

void loop()
{
    scheduler.schedule();

}