#include "Arduino.h"
#include "kernel/Scheduler.h"
#include "tasks/BlinkTask.h"
#include "tasks/CheckInTask.h"
#include "config/config.h"
#include "tasks/TransitTask.h"
#include "tasks/WaitingTask.h"
#include "tasks/WashingTask.h"
#include "tasks/CheckOutTask.h"

Scheduler scheduler;

void setup()
{
    Serial.begin(9600);
    scheduler.init(50);
    BlinkTask *blinkTaskTransit = new BlinkTask(L2_PIN);
    BlinkTask *blinkTaskForWashing = new BlinkTask(L2_PIN);
    // TODO: BlinkTask *blinkTaskForCheckOutTransit = new BlinkTask(L2_PIN);
    // SleepingTask *sleepingTask = new SleepingTask();

    WaitingTask *waitingTask = new WaitingTask();
    CheckInTask *checkInTask = new CheckInTask();
    TransitTask *transitTask = new TransitTask(blinkTaskTransit);
    WashingTask *washingTask = new WashingTask(blinkTaskForWashing);
    // TODO: CheckOutTask *checkOutTask = new CheckOutTask(blinkTaskForCheckOutTransit);

    scheduler.addTask(waitingTask);
    // checkInTask->addDependecy(waitingTask)
    transitTask->addDependency(checkInTask);
    scheduler.addTask(checkInTask);
    scheduler.addTask(transitTask);
    scheduler.addTask(blinkTaskTransit);
    washingTask->addDependency(transitTask);
    scheduler.addTask(washingTask);
    scheduler.addTask(blinkTaskForWashing);
    // TODO: checkOutTask->addDependency(washingTask);
    // TODO: scheduler.addTask(checkOutTask);
    // TODO: scheduler.addTask(blinkTaskForCheckOutTransit);
}

void loop()
{
    scheduler.schedule();
}