#include "Arduino.h"
#include "kernel/Scheduler.h"
#include "tasks/BlinkTask.h"
#include "tasks/CheckInTask.h"
#include "config/config.h"
#include "tasks/TransitTask.h"
#include "tasks/WaitingTask.h"
#include "tasks/WashingTask.h"
#include "tasks/CheckOutTask.h"
#include "tasks/CountDown.h"

Scheduler scheduler;

void setup()
{
    Serial.begin(9600);
    scheduler.init(50);
    BlinkTask *blinkTask = new BlinkTask(L2_PIN);
    // TODO: BlinkTask *blinkTaskForCheckOutTransit = new BlinkTask(L2_PIN);
    // SleepingTask *sleepingTask = new SleepingTask();

    // WaitingTask *waitingTask = new WaitingTask();
    CheckInTask *checkInTask = new CheckInTask();
    TransitTask *transitTask = new TransitTask(blinkTask);
    WashingTask *washingTask = new WashingTask(blinkTask, new CountDown(N3));
    CountDown *countDown = new CountDown(N3);
    
    // TODO: CheckOutTask *checkOutTask = new CheckOutTask(blinkTaskForCheckOutTransit);

    countDown->init(1000);
    scheduler.addTask(countDown);
    // scheduler.addTask(waitingTask);
    // checkInTask->addDependency(waitingTask);
    transitTask->addDependency(checkInTask);
    scheduler.addTask(checkInTask);
    scheduler.addTask(transitTask);
    scheduler.addTask(blinkTask);
    washingTask->addDependency(transitTask);
    scheduler.addTask(washingTask);
    // TODO: checkOutTask->addDependency(washingTask);
    // TODO: scheduler.addTask(checkOutTask);
    // TODO: scheduler.addTask(blinkTaskForCheckOutTransit);
}

void loop()
{
    scheduler.schedule();
}