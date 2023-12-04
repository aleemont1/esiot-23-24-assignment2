#include "Arduino.h"
#include "config/config.h"
#include "kernel/Scheduler.h"
#include "kernel/SerialReceiver.h"
#include "tasks/BlinkTask.h"
#include "tasks/CheckInTask.h"
#include "tasks/TransitTask.h"
#include "tasks/WaitingTask.h"
#include "tasks/WashingTask.h"
#include "tasks/SleepingTask.h"
#include "tasks/CheckOutTask.h"
#include "tasks/CountDown.h"
#include "tasks/WaitForClickTask.h"
#include "tasks/WashingTask.h"
#include "tasks/CheckOutTask.h"
#include "tasks/ExitTransitTask.h"
#include "tasks/TemperatureTask.h"

// #include "tasks/ServoTestTask.h"

Scheduler scheduler;

SerialReceiver *serialReceiver;
LCD *lcd;

void setup()
{
    Serial.begin(9600);
    scheduler.init(50); // NOTE: Might be set higher to use less power, needs testing.

    /**CREATE TASKS**/
    BlinkTask *blinkTaskTransit = new BlinkTask(L2_PIN);
    BlinkTask *blinkTaskWashing = new BlinkTask(L2_PIN);
    // CountDown *countDownTask = new CountDown(N3);
    TemperatureTask *temperatureTask = new TemperatureTask();
    // SleepingTask *sleepingTask = new SleepingTask();
    CheckInTask *checkInTask = new CheckInTask();
    TransitTask *transitTask = new TransitTask(blinkTaskTransit);
    WaitForClickTask *waitForClickTask = new WaitForClickTask();
    // WashingTask *washingTask = new WashingTask(blinkTaskTransit, nullptr, temperatureTask);
    // CheckOutTask *checkOutTask = new CheckOutTask();
    // ExitTransitTask *exitTransitTask = new ExitTransitTask();

    /**DEPENDENCIES**/
    // checkInTask->addDependency(sleepingTask);
    transitTask->addDependency(checkInTask);
    waitForClickTask->addDependency(transitTask);
    //washingTask->addDependency(waitForClickTask);
    // checkOutTask->addDependency(washingTask);
    // exitTransitTask->addDependency(checkOutTask);

    /**ADD TASKS TO THE SCHEDULER**/
    // scheduler.addTask(sleepingTask);
    scheduler.addTask(checkInTask);
    scheduler.addTask(transitTask);
    scheduler.addTask(blinkTaskTransit);
    scheduler.addTask(blinkTaskWashing);
    // scheduler.addTask(countDownTask);
    scheduler.addTask(temperatureTask);
    scheduler.addTask(waitForClickTask);
    // scheduler.addTask(washingTask);
    // scheduler.addTask(checkOutTask);
    // scheduler.addTask(exitTransitTask);
}

void loop()
{
    // serialReceiver->readData(); //@EMANUELE this is a test to try the serialReceiver, it must go instantiate when the arduino is in error state
    // read the class briefs
    scheduler.schedule();
}