#include "Arduino.h"
#include "config/config.h"
#include "kernel/Scheduler.h"
#include "kernel/SerialReceiver.h"
#include "tasks/BlinkTask.h"
#include "tasks/CheckInTask.h"
#include "tasks/TransitTask.h"
#include "tasks/WaitingTask.h"
#include "tasks/WashingTask.h"
#include "tasks/CheckOutTask.h"
#include "tasks/CountDown.h"
#include "tasks/WaitForClickTask.h"
// #include "tasks/ServoTestTask.h"

Scheduler scheduler;

SerialReceiver *serialReceiver;

void setup()
{
    Serial.begin(9600);
    scheduler.init(100); // NOTE: Might be set higher to use less power, needs testing.
    /**CREATE TASKS**/
    // ServoTestTask *servoTask = new ServoTestTask();
    BlinkTask *blinkTask = new BlinkTask(L2_PIN);
    // TODO: BlinkTask *blinkTaskForCheckOutTransit = new BlinkTask(L2_PIN);
    // SleepingTask *sleepingTask = new SleepingTask();
    // WaitingTask *waitingTask = new WaitingTask();
    CheckInTask *checkInTask = new CheckInTask();
    TransitTask *transitTask = new TransitTask(blinkTask);
    WaitForClickTask *waitForClickTask = new WaitForClickTask();
    // WashingTask *washingTask = new WashingTask(blinkTask, new CountDown(N3));
    // TODO: CheckOutTask *checkOutTask = new CheckOutTask(blinkTaskForCheckOutTransit);
    // CountDown *countDown = new CountDown(N3); // NOTE: This is just a test.
    // countDown->setActive(true);               // NOTE: This is just a test.

    /// serialReceiver = new SerialReceiver(); //test test test test receiver



    /**DEPENDENCIES**/
    // checkInTask->addDependency(waitingTask);
    transitTask->addDependency(checkInTask);
    waitForClickTask->addDependency(transitTask);
    // washingTask->addDependency(transitTask);
    // checkOutTask->addDependency(washingTask);

    /**ADD TASKS TO THE SCHEDULER**/
    // scheduler.addTask(servoTask);
    // scheduler.addTask(countDown); // NOTE: This is just a test.
    // scheduler.addTask(waitingTask);
    scheduler.addTask(checkInTask);
    //Serial.println("err:errore");
    scheduler.addTask(transitTask);
    scheduler.addTask(blinkTask);
    scheduler.addTask(waitForClickTask);

    // scheduler.addTask(washingTask);

    // TODO: scheduler.addTask(checkOutTask);
    // TODO: scheduler.addTask(blinkTaskForCheckOutTransit);
}

void loop()
{
    // serialReceiver->readData(); //@EMANUELE this is a test to try the serialReceiver, it must go instantiate when the arduino is in error state
                                //read the class briefs
    scheduler.schedule();
}