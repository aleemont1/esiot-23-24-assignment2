#include "Arduino.h"
#include "kernel/Scheduler.h"
#include "tasks/BlinkTask.h"
#include "tasks/CheckInTask.h"
#include "config/config.h"
#include "tasks/TransitTask.h"
#include "tasks/WaitingTask.h"
#include "tasks/WashingTask.h"
#include "tasks/SleepingTask.h"
#include "tasks/CheckOutTask.h"
#include "tasks/CountDown.h"
#include "kernel/SerialReceiver.h"
// #include "tasks/ServoTestTask.h"

Scheduler scheduler;

SerialReceiver *serialReceiver;
LCD *lcd;

void setup()
{
    Serial.begin(9600);
    scheduler.init(50); // NOTE: Might be set higher to use less power, needs testing.
    /**CREATE TASKS**/
    // ServoTestTask *servoTask = new ServoTestTask();
    BlinkTask *blinkTask = new BlinkTask(L2_PIN);
    // TODO: BlinkTask *blinkTaskForCheckOutTransit = new BlinkTask(L2_PIN);
    SleepingTask *sleepingTask = new SleepingTask();
    WaitingTask *waitingTask = new WaitingTask(sleepingTask);
    lcd = new LCD(0x27, 16, 2);
    lcd->write("ciao",0,1);


    CheckInTask *checkInTask = new CheckInTask();
    TransitTask *transitTask = new TransitTask(blinkTask);
    // WashingTask *washingTask = new WashingTask(blinkTask, new CountDown(N3));
    // TODO: CheckOutTask *checkOutTask = new CheckOutTask(blinkTaskForCheckOutTransit);
    CountDown *countDown = new CountDown(N3); // NOTE: This is just a test.
    countDown->tick();                        // NOTE: This is just a test.

    serialReceiver = new SerialReceiver(); //test test test test receiver


    /**DEPENDENCIES**/
    //waitingTask->addDependency(sleepingTask);
    // checkInTask->addDependency(waitingTask);
    
    checkInTask->addDependency(sleepingTask);
    // washingTask->addDependency(transitTask);
    // checkOutTask->addDependency(washingTask);

    /**ADD TASKS TO THE SCHEDULER**/
    // scheduler.addTask(servoTask);
    // scheduler.addTask(countDown); // NOTE: This is just a test.
    // scheduler.addTask(waitingTask);

    scheduler.addTask(sleepingTask);
    //scheduler.addTask(waitingTask);


    scheduler.addTask(checkInTask);
    Serial.println("err:errore");
    scheduler.addTask(transitTask);
    scheduler.addTask(blinkTask);

    // scheduler.addTask(washingTask);

    // TODO: scheduler.addTask(checkOutTask);
    // TODO: scheduler.addTask(blinkTaskForCheckOutTransit);
}

void loop()
{
    serialReceiver->readData(); //@EMANUELE this is a test to try the serialReceiver, it must go instantiate when the arduino is in error state
                                //read the class briefs
    scheduler.schedule();
}