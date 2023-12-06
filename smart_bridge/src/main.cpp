// #include "Arduino.h"

#include "config/config.h"

#include "kernel/Scheduler.h"

#include "components/api/LCD.h"

#include "tasks/BlinkTask.h"
#include "tasks/CountDown.h"
#include "tasks/TemperatureTask.h"
#include "tasks/SleepingTask.h"
#include "tasks/CheckInTask.h"
#include "tasks/TransitTask.h"
#include "tasks/WaitForClickTask.h"
#include "tasks/WashingTask.h"
#include "tasks/CheckOutTask.h"
#include "tasks/ExitTransitTask.h"

Scheduler scheduler;

SerialReceiver *serialReceiver;

void setup()
{
    Serial.begin(9600);
    scheduler.init(50); // NOTE: Might be set higher to use less power, needs testing.

    /**CREATE TASKS**/
<<<<<<< HEAD
    BlinkTask blinkTask = BlinkTask(L2_PIN);
    CountDown countDownTask = CountDown(N3);
    TemperatureTask temperatureTask = TemperatureTask();
    SleepingTask sleepingTask = SleepingTask();
    CheckInTask checkInTask = CheckInTask();
    TransitTask transitTask = TransitTask(&blinkTask);
    WaitForClickTask waitForClickTask = WaitForClickTask();
    WashingTask washingTask = WashingTask(&blinkTask, nullptr, &temperatureTask);
    CheckOutTask checkOutTask = CheckOutTask();
    ExitTransitTask exitTransitTask = ExitTransitTask();
    /**DEPENDENCIES**/
    checkInTask.addDependency(&sleepingTask);
    transitTask.addDependency(&checkInTask);
    waitForClickTask.addDependency(&transitTask);
    washingTask.addDependency(&waitForClickTask);
    checkOutTask.addDependency(&washingTask);
    exitTransitTask.addDependency(&checkOutTask);

    /**ADD TASKS TO THE SCHEDULER**/
    scheduler.addTask(&sleepingTask);
    scheduler.addTask(&checkInTask);
    scheduler.addTask(&transitTask);
    scheduler.addTask(&blinkTask);
    scheduler.addTask(&countDownTask);
    scheduler.addTask(&temperatureTask);
    scheduler.addTask(&waitForClickTask);
    scheduler.addTask(&washingTask);
    scheduler.addTask(&checkOutTask);
    scheduler.addTask(&exitTransitTask);
=======
    CheckInTask *checkInTask = new CheckInTask();
    BlinkTask *blinkTask = new BlinkTask(L2_PIN);
    TransitTask *transitTask = new TransitTask(blinkTask);
    WaitForClickTask *waitForClickTask = new WaitForClickTask();
    CountDown *countDownTask = new CountDown(N3);
    TemperatureTask *temperatureTask = new TemperatureTask();
    WashingTask *washingTask = new WashingTask(blinkTask, countDownTask, temperatureTask);
    CheckOutTask *checkOutTask = new CheckOutTask();
    ExitTransitTask *exitTransitTask = new ExitTransitTask();

    /**DEPENDENCIES**/
    transitTask->addDependency(checkInTask);
    waitForClickTask->addDependency(transitTask);
    washingTask->addDependency(waitForClickTask);
    checkOutTask->addDependency(washingTask);
    exitTransitTask->addDependency(checkOutTask);

    /**ADD TASKS TO THE SCHEDULER**/
    scheduler.addTask(checkInTask);
    scheduler.addTask(transitTask);
    scheduler.addTask(blinkTask);
    scheduler.addTask(waitForClickTask);
    scheduler.addTask(washingTask);
    scheduler.addTask(countDownTask);
    scheduler.addTask(temperatureTask);
    scheduler.addTask(checkOutTask);
    scheduler.addTask(exitTransitTask);
>>>>>>> ae7961de6fe356cd0044a8ce636b972a24eee768
}

void loop()
{
    scheduler.schedule();
}