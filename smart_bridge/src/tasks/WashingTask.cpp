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

// TODO: WashingTask *washingTask = new WashingTask();
// TODO: washingTask->setDependency();
// TODO: scheduler->addTask(washingTask);

void WashingTask::tick()
{
    if (this->DependantTask::getDependency()->isCompleted())
    {
        switch (this->getState())
        {
        case START_WASHING:
            if (this->getPreviousState() == ERROR)
            {
                Serial.println("WashingTask::Previous state is ERROR");
                delay(500);
                countDown = savedCountDown; // Restore the countdown
                Serial.println("WashingTask::Countdown restored" + countDown);
                delay(500);
                savedTimeInState = millis() - this->elapsedTime(); // Save the time spent in the current state
                Serial.println("WashingTask::Time in state saved" + savedTimeInState);
                delay(500);
            }
            resetTime(); // Reset the time spent in the current state
            Serial.println("WashingTask:: Button has been pressed");
            delay(500);
            Serial.println("WashingTask:: The washing process is started");
            delay(500);
            L2->blink();
            Serial.println("WashingTask::L2 blinking started");
            delay(500);
            countDown = N3;
            this->setState(COUNTDOWN);
            break;

        case COUNTDOWN:
            Serial.println("WashingTask::Countdown started");
            delay(500);
            // TODO: lcd->print(countDown);
            Serial.println("WashingTask::Countdown printed on LCD");
            delay(500);
            // TODO: To this purpose, during the washing process the temperature is monitored
            // by means of the TEMP sensor, reporting  the ongoing value on the PC Console Dashboard.
            Serial.println("WashingTask::Temperature monitored");
            delay(500);
            Serial.println("WashingTask::Temperature printed on PC Console Dashboard" + tempSensor->getTemp());
            delay(500);

            if ((tempSensor->getTemp() > MAXTEMP) && (this->elapsedTime() > (N4_FOR_TEMP * 1000)))
            {
                // TODO: Stop the washing process and the countdown
                Serial.println("WashingTask::Temperature is critical");
                delay(500);
                // TODO: then the washing process  is suspended and a message Maintenance required is displayed on the PC Console Dashboard
                // TODO: lcd->print("Detected a Problem - Please Wait");
                Serial.println("WashingTask::Detected a Problem - Please Wait");
                delay(500);
                savedCountDown = countDown; // Save the countdown before the error
                this->setState(ERROR);
            }
            if (this->elapsedTime() >= (countDown * 1000))
            {
                Serial.println("WashingTask::Countdown finished");
                delay(500);
                this->setCompleted();
            }
            break;

        case ERROR:
            Serial.println("WashingTask::Error detected");
            delay(500);
            Serial.println("WashingTask::The washing process is suspended");
            delay(500);
            Serial.println("Simulates the time to receive and press the buttons on the UI");
            Serial.println(5000);
            Serial.println("WashingTask::OK message received");
            delay(500);
            this->setState(START_WASHING);
            // TODO: Missing the ok message from the serial
            // if (Serial.read() == "Messaggio di OK da seriale")
            // {
            //     Serial.println("WashingTask::OK message received");
            //     delay(500);
            //     this->setState(START_WASHING);
            // }
        }
    }
}