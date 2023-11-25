#ifndef __LED_BLINK_TASK__
#define __LED_BLINK_TASK__

#include "kernel/Task.h"
#include "components/api/Light.h"

/**
 * @brief Represents a task for blinking an LED.
 *
 * This class extends the Task class and provides functionalities to initialize and perform the task.
 */
class LedBlinkTask : public Task
{
public:
    /**
     * @brief Construct a new LedBlinkTask object.
     *
     * @param ledPin The pin number where the LED is connected.
     */
    LedBlinkTask(int ledPin);

    /**
     * @brief Initialize the LedBlinkTask.
     *
     * @param period The period of the task in milliseconds.
     */
    void init(int period);

    /**
     * @brief Perform the LedBlinkTask.
     *
     * This method is called periodically based on the period of the task.
     */
    void tick();

private:
    /**
     * @brief The pin number where the LED is connected.
     */
    int ledPin;

    /**
     * @brief Pointer to the Light object representing the LED.
     */
    Light *led;

    /**
     * @brief The current state of the LED (SWITCH_ON if the LED is on, SWITCH_OFF if the LED is off).
     */
    enum State
    {
        SWITCH_ON,
        SWITCH_OFF
    } state;
};

#endif // __LED_BLINK_TASK__