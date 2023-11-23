/* DO NOT REMOVE THE COMMENT - JUST A SIMPLE VERSION MADE FOR BRAINSTORMING IDEAS */

/*
#include "CarWashingTask.h"
#include "Arduino.h"
#include "config/config.h"

class CarWashingSystem
{
public:
    void handleWashing();
    void handleCriticalTemp();
    void handleWashingEnd();
    void handleCheckout();
    void handleError();

private:
    int COUNT_DOWN;
    unsigned long TIME_IN_CRITICAL_TEMP;
    unsigned long SAVED_TIME_IN_STATE;
    int SAVED_COUNT_DOWN;
    static const int WASHING_LED_BLINK_PERIOD = 500;
    static const int SECONDS_TO_MILLIS = 1000;
    static const int N3_SECONDS = 10; // Adjust as needed
    static const int N4_SECONDS = 15; // Adjust as needed
};

void CarWashingSystem::handleWashing()
{
    if (PREVIOUS_STATE == ERROR)
    {
        COUNT_DOWN = SAVED_COUNT_DOWN;
        TIME_IN_STATE = SAVED_TIME_IN_STATE;
    }

    if (TIME_IN_STATE < N3 * 1000 && COUNT_DOWN != 0)
    {
        // Implement washing process logic
        redLED.blink(500); // T = 0.5s
        lcd.displayCountdown(COUNT_DOWN);
        // Continue with the countdown logic
        COUNT_DOWN--;
    }
    else
    {
        currentState = CRITICAL_TEMP;
        stateStartTime = millis();
    }
}

void CarWashingSystem::handleCriticalTemp()
{
    if (CURRENT_TEMP > MAX_TEMP && TIME_IN_CRITICAL_TEMP > N4 * 1000)
    {
        // Implement critical temperature logic
        COUNT_DOWN = 0; // Stop COUNT_DOWN
        SAVED_TIME_IN_STATE = TIME_IN_STATE;
        SAVED_COUNT_DOWN = COUNT_DOWN;
        currentState = ERROR;
        stateStartTime = millis();
    }
    else
    {
        currentState = WASHING_END;
        stateStartTime = millis();
    }
}

void CarWashingSystem::handleWashingEnd()
{
    // Implement washing end logic
    COUNT_DOWN = 0; // Reset COUNT_DOWN
    redLED.turnOff();
    greenLED.turnOn();
    lcd.displayMessage("Washing complete, you can leave the area");
    gate.openGate();
    currentState = CHECKOUT;
    stateStartTime = millis();
}

void CarWashingSystem::handleCheckout()
{
    float distance = sonar.getDistance();
    pir.disable(); // Disable PIR

    if (distance > MAXDIST && TIME_IN_STATE > N4 * 1000)
    {
        // Implement checkout logic
        gate.closeGate();
        currentState = WAITING;
        stateStartTime = millis();
    }
}

void CarWashingSystem::handleError()
{
    // Implement error handling logic
    lcd.displayErrorMessage("Maintenance required");
    if (CURRENT_TEMP < MAX_TEMP - DELTA)
    {
        // Notify GUI for resumption
        Serial.println("ERROR_RESUME");
        // Wait for GUI notification
        // ...
        // If received OK code from GUI
        currentState = WASHING;
        stateStartTime = millis();
    }
}

// ... (The rest of the code)
*/