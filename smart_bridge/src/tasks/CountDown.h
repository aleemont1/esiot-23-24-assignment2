#ifndef __COUNT_DOWN_TASK__
#define __COUNT_DOWN_TASK__

#include "kernel/Task.h"
#include "components/api/LCD.h"
#include "config/config.h"
#include "Arduino.h"

/**
 * @brief A countdown timer task class.
 *
 * This class provides a countdown timer that can be started, paused, resumed, and stopped.
 * The countdown value can be increased, decreased, and reset.
 * The current countdown value and whether the countdown is active can be queried.
 */
class CountDown : public Task
{
public:
    /**
     * @brief Construct a new CountDown object
     *
     * @param countDown The initial countdown value.
     */
    CountDown(int countDown);

    /**
     * @brief Tick function that is called periodically.
     */
    void tick() override;

    /**
     * @brief Get the current countdown value.
     *
     * @return int The current countdown value.
     */
    int getCountDown();

    /**
     * @brief Reset the countdown value.
     *
     * @param newCountDown The new countdown value.
     */
    void resetCountDown(int newCountDown);

    /**
     * @brief Decrease the countdown value.
     *
     * @param decrement The amount to decrease the countdown value by.
     */
    void decreaseCountDown(int decrement = 1);

    /**
     * @brief Increase the countdown value.
     *
     * @param increment The amount to increase the countdown value by.
     */
    void increaseCountDown(int increment = 1);

    /**
     * @brief Pause the countdown task by saving its value.
     *
     */
    void pauseCountDown();

    /**
     * @brief Start the countdown.
     */
    void startCountDown();

    /**
     * @brief This function print the updated value of the countdown on the LCD display.
     *
     * @param count The countdown to be displayed on the LCD display.
     */
    void printCountDown();

    /**
     * @brief Ends the countdown task.
     *
     */
    void endsCountDown();

    /**
     * @brief Prints a message to the serial monitor when the countdown ends.
     *
     */
    void printsEndsCountdown();

    /**
     * @brief Check if the countdown task is active.
     *
     * @return true If the countdown task is active, false otherwise.
     */
    bool isCountDownActive();

    /**
     * @brief Stop the countdown task and reset the countdown value.
     *
     */
    void stopCountDown();

    /**
     * @brief Resume the countdown task if it was paused.
     *
     */
    void resumeCountDown();

    /**
     * @brief Set the status of the countdown task.
     *
     * @param value The value to set the status to (true if active, false otherwise).
     */
    void setStatus(bool value);

    /**
     * @brief Get the status of the countdown task.
     *
     */
    bool getStatus();

private:
    int countDown;            ///< The current countdown value
    int pausedCountDown = -1; ///< The countdown value when the countdown was paused, or -1 if the countdown was not paused.
    LCD *lcd;                 ///< The LCD display
    bool status;              ///< The status of the countdown task
};

#endif // __COUNT_DOWN_TASK__