#include "SleepingTask.h"

SleepingTask* sleepingTaskInstance = nullptr;

static void staticWakeUp() {
    if (sleepingTaskInstance != nullptr) {
        sleepingTaskInstance->wakeUp();
    }
}

void SleepingTask::tick()
{
    switch (this->getState())
    {
        case STARTING:
            this->goInSleep();
            break;

        case ALIVE:
            if (pir->checkDetectedStatus()) {
                Serial.println("OBJECT revealed");
                this->setState(OBJECT_DETECTED);
            }
            break;
            
        case OBJECT_DETECTED:
            this->setState(ALIVE);
            this->setActive(false);
            this->setCompleted();
            break;
    }
}

void SleepingTask::goInSleep()
{
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleepingTaskInstance = this;
    attachInterrupt(digitalPinToInterrupt(2), staticWakeUp, RISING);
    sei();
    sleep_enable();
    sleep_mode();
}

void SleepingTask::wakeUp() {
    detachInterrupt(digitalPinToInterrupt(2));
    sleep_disable();
    this->setState(ALIVE);
}
