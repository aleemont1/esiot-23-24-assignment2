#include "WashingTask.h"

/*
—
1)
Sezione del testo: Washing != CriticalTemp
- the simulated washing process begins and lasts for N3 secs.
- During this time, the light L2 blinks with a period equal to 0.5 secs.
- On the USER LCD a countdown is displayed–either using numbers.
—

Washing:
- If PREVIOUS_STATE == ERROR:
    - COUNT_DOWN = SAVED_COUNT_DOWN
    - TIME_IN_STATE = SAVED_TIME_IN_STATE
- If TIME_IN_STATE < N3 sec: [COUNT_DOWN != 0]
    - LED ROSSO L2 blink (T = 0.5s)
    - Avvia countdown su LCD
    - Passa a Critical-Temp.
*/

void WashingTask::printWashingCompletedMessage()
{
    // Serial.println("Washing complete, you can leave the area");
    lcd->write("Washing complete, you can leave the area", 0, 0);
}

void WashingTask::tick()
{
    if (this->DependantTask::getDependency(0)->isCompleted())
    {
        switch (this->getState())
        {
        case START_WASHING:
            // TODO: this->countDownTask->startCountDown(); check if this is necessary
            // TODO: this->countDownTask->printCountDown(); check if this is necessary
            this->blinkTask->setActive(true);
            this->setState(STARTS_COUNTDOWN);
            break;

        case STARTS_COUNTDOWN:
            this->countDownTask->tick();
            this->temperatureTask->tick();
            if (this->temperatureTask->checkForCriticalTemperature() == true && this->countDownTask->getStatus() == false)
            {
                this->setState(ERROR);
            }
            if (this->countDownTask->getStatus() == true)
            {
                this->setState(ENDS_COUNTDOWN);
            }
            break;

        case ENDS_COUNTDOWN:
            this->countDownTask->endsCountDown();
            this->blinkTask->setActive(false);
            this->L3->switchOn();
            this->printWashingCompletedMessage();
            this->setCompleted();
            // TODO: this->setState(OPENS_GATE);
            break;

            // TODO: Check if this is necessary
            // case OPENS_GATE:

            //     // TODO: opens the gate
            //     // TODO: checks for the car leaving the area completely (> then MAXDISTANCE for N4 secs)
            //     // TODO: closes the gate
            //     // TODO: this->L3->switchOff();
            //     this->setCompleted();
            //     break;

        case ERROR:
            this->countDownTask->pauseCountDown();
            this->temperatureTask->criticalTemperatureReachedMessage();
            this->temperatureTask->temperatureMaintenanceMessage();
            this->serialReceiver->simulateReadData(); // TODO: remove, but now simulate receiving "mnt:done"
            if (serialReceiver->readData() == true)
            {
                this->countDownTask->resumeCountDown();
                this->setState(STARTS_COUNTDOWN);
            }
            break;
        }
    }
}