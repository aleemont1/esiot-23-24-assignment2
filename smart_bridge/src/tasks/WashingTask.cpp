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

void WashingTask::tick()
{
    if (this->DependantTask::getDependency(0)->isCompleted())
    {
        switch (this->getState())
        {
        case START_WASHING:
            if (this->getPreviousState() == ERROR)
            {
                this->setState(ERROR_RECOVERY);
            }
            Serial.println("WashingTask:: The washing process is started");
            this->resetTime(); // Reset the time spent in the current state
            this->countDownTask->startCountDown();
            Serial.println("WashingTask::The countdown is started");
            this->blinkTask->setActive(true);
            Serial.println("WashingTask::L2 blinking started");
            this->setState(COUNTDOWN);
            break;

/*             // TODO: To this purpose, during the washing process the temperature is monitored
            // by means of the TEMP sensor, reporting  the ongoing value on the PC Console Dashboard.
            Serial.println("WashingTask::Temperature monitored");
            Serial.println("WashingTask::Temperature printed on PC Console Dashboard" + String(tempSensor->getTemp()));

            if ((tempSensor->getTemp() > MAXTEMP) && (this->elapsedTime() > (N4_FOR_TEMP * 1000)))
            {
                // TODO: Stop the washing process and the countdown
                Serial.println("WashingTask::Temperature is critical");
                // TODO: then the washing process  is suspended and a message Maintenance required is displayed on the PC Console Dashboard
                // TODO: lcd->print("Detected a Problem - Please Wait");
                Serial.println("WashingTask::Detected a Problem - Please Wait");
                savedCountDown = ((countDown * 1000) - elapsedTime()); // Save the countdown before the error
                this->setState(ERROR);
            }
            if (this->countDownTask->isCompleted())
            {
                this->setCompleted();
            }
            break; */

        case ERROR_RECOVERY:
            Serial.println("WashingTask::Error recovery started");
            this->countDownTask->setActive(false);
            countDown = savedCountDown; // Restore the countdown from the saved value
            Serial.println("WashingTask::The countdown is restored");
            this->setState(COUNTDOWN); // Change the state back to COUNTDOWN
            break;

        case ERROR:
            Serial.println("WashingTask::Error detected");
            Serial.println("WashingTask::The washing process is suspended");
            Serial.println("Simulates the time to receive and press the buttons on the UI");
            Serial.println("WashingTask::OK message received");
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