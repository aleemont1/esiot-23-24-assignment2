#include "LedBlinkTask.h"

/**
 * @brief Construct a new LedBlinkTask object.
 * 
 * @param ledPin The pin number where the LED is connected.
 */
LedBlinkTask::LedBlinkTask(int ledPin)
{
    this->ledPin = ledPin;
}

/**
 * @brief Initialize the LedBlinkTask.
 * 
 * @param period The period of the task in milliseconds.
 */
void LedBlinkTask::init(int period)
{
    Task::init(period);
    state = SWITCH_OFF;
}

/**
 * @brief Perform the LedBlinkTask.
 * 
 * This method is called periodically based on the period of the task.
 * It switches the state of the LED from on to off, or from off to on.
 */
void LedBlinkTask::tick()
{
    switch (state)
    {
    case State::SWITCH_OFF:
        state = State::SWITCH_ON;
        break;
    case State::SWITCH_ON:
        state = State::SWITCH_OFF;
        break;
    }
}