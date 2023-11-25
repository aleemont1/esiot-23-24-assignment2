#include "WashingTask.h"

/*
    What I do have to realize:
    - The washing task
    - The critical temperature handling
    - Thw washing end handling
    - The Checkout task
*/

WashingTask::WashingTask(int washingTime, int redLedPin, int greenLedPin /* , LCD* lcd */)
    : state(START_WASHING), savedCountDown(0), savedTimeInState(0), countDown(0) {}

void WashingTask::init(int period)
{
    Task::init(period);
}

void WashingTask::tick()
{
    switch (this->getState())
    {
    case START_WASHING:
        if (this->getPreviousState() == CRITICAL_TEMP)
        {
            Serial.println("WashingTask::Previous state is CRITICAL_TEMP");
            countDown = savedCountDown; // Restore the countdown
            Serial.println("WashingTask::Countdown restored" + countDown);
            savedTimeInState = millis() - this->elapsedTime(); // Save the time spent in the current state
            Serial.println("WashingTask::Time in state saved" + savedTimeInState);
        }
        if (digitalRead(BUTTON_PIN) == HIGH)
        {
            Serial.println("WashingTask:: Button pressed");
            Serial.println("WashingTask:: The washing process is started");
            L2->switchOn(/* 500 */); // Blink red LED L2 with a period of 0.5s
            Serial.println("WashingTask::L2 turned on");
            this->setState(COUNTDOWN);
            countDown = N3;
            this->setState(COUNTDOWN);
        }
        break;

    case COUNTDOWN:
        if (countDown == 0)
        {
            Serial.println("WashingTask::Countdown expired");
            // TODO: resetTimer();
            Serial.println("WashingTask::Timer reset");
            /* lcd->updateCountdown(countDown); // Update countdown on LCD */
            Serial.println("WashingTask::LCD-Countdown expired and updated");
            this->setState(END_WASHING);
        }
        else
        {
            Serial.println("WashingTask::Countdown started");
            countDown--;
            this->setState(WASHING_IN_PROGRESS);
        }
        break;

    case WASHING_IN_PROGRESS:
        if (this->elapsedTime() < N3 * 1000)
        {
            Serial.println("WashingTask::Washing in progress");
            /* lcd->displayMessage("Washing complete, you can leave the area"); */
            Serial.println("WashingTask::LCD-Washing complete, you can leave the area");
            this->setState(END_WASHING);
            // Additional actions for washing completion
        }
        break;

    case END_WASHING:
        // TODO: Implement the car distance detector actually it is not implemented
        if (elapsedTime() > N4 * 1000 && !this->getPreviousState() == WASHING_IN_PROGRESS)
        {
            Serial.println("WashingTask::Washing completed");
            L2->switchOff();
            Serial.println("WashingTask::L2 turned off");
            L3->switchOn(); // Turn on L3 - static green LED
            Serial.println("WashingTask::L3 turned on");
            // TODO: lcd.displayMessage("Washing complete, you can leave the area");
            // TODO: gate->open(); // Open the gate to let the car out
            Serial.println("WashingTask::Gate opened to let the car out");
            this->setState(CHECK_OUT);
        }
        break;

    case CRITICAL_TEMP:
        // TODO: Implement logic for critical temperature handling
        // Possibilities: can transition to the next state or handle other actions
        break;
    case CHECK_OUT:
        if (/* carDistanceDetector->getDistance()*/ 50 > MAXDIST && this->elapsedTime() > N4)
        {
            Serial.println("WashingTask::Car left the area");
            // TODO: gate->close(); // Close the gate
            Serial.println("WashingTask::Gate closed");
            L3->switchOff(); // Turn off L3
            Serial.println("WashingTask::L3 turned off");
            // TODO: this->setState(WAITING_FOR_CAR);
        }

        break;
    }
}