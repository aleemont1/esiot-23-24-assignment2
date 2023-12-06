#ifndef __WASHING_TASK__
#define __WASHING_TASK__

#include "kernel/DependantTaskWithState.h"
#include "BlinkTask.h"
#include "components/api/Led.h"
#include "components/api/Temp.h"
#include "components/api/LCD.h"
#include "config/config.h"
#include "tasks/CountDown.h"
#include "tasks/TemperatureTask.h"
#include "kernel/SerialReceiver.h"
#include "components/api/ServoImpl.h"

/**
 * @brief Manages the car washing process.
 *
 * This class is responsible for managing the car washing process. It controls the blinking of LEDs,
 * the countdown, temperature monitoring, and communicates with the serial receiver.
 *
 * @extends DependantTaskWithState
 */
class WashingTask : public DependantTaskWithState
{
public:
    /**
     * @brief Construct a new WashingTask object.
     *
     * @param blinkTask Pointer to the BlinkTask object.
     * @param countDownTask Pointer to the CountDown object.
     * @param temperatureTask Pointer to the TemperatureTask object.
     */
    WashingTask(BlinkTask *blinkTask, CountDown *countDownTask, TemperatureTask *temperatureTask);

    /**
     * @brief Called periodically to update the task's state.
     *
     * This function is overridden from DependantTaskWithState.
     */
    void tick() override;

private:
    /**
     * @brief Handles the start of the washing process.
     *
     * This function is called when the task's state is START_WASHING.
     */
    void handleStartWashing();

    /**
     * @brief Handles the end of the countdown.
     *
     * This function is called when the task's state is ENDS_COUNTDOWN.
     */
    void handleStartsCountdown();

    /**
     * @brief Handles the end of the countdown.
     *
     * This function is called when the task's state is ENDS_COUNTDOWN.
     */
    void handleEndsCountdown();

    /**
     * @brief Handles any errors that occur during the washing process.
     *
     * This function is called when the task's state is ERROR.
     */
    void handleError();

    /**
     * @brief Prints the message "Washing complete, you can leave the area" on the LCD display.
     *
     */
    void printWashingCompletedMessage();

    /**
     * @brief Enum for the possible states of the task.
     *
     */
    enum state
    {
        START_WASHING,    ///< The task is currently starting the washing process.
        STARTS_COUNTDOWN, ///< The task is currently starting the countdown.
        ENDS_COUNTDOWN,   ///< The task is currently ending the countdown.
        ERROR,            ///< The task is currently handling an error.
    };

    int savedCountDown;               ///< The saved value of the countdown.
    unsigned long savedTimeInState;   ///< The time that the task has been in the current state.
    int checkInterval = 5000;         ///< 5 seconds
    int countDown;                    ///< The current value of the countdown.
    Led *L2;                          ///< Pointer to the L2 LED object.
    Led *L3;                          ///< Pointer to the L3 LED object.
    Temp *tempSensor;                 ///< Pointer to the temperature sensor object.
    LCD *lcd;                         ///< Pointer to the LCD object.
    Task *blinkTask;                  ///< Pointer to the blink task.
    CountDown *countDownTask;         ///< Pointer to the countdown task.
    TemperatureTask *temperatureTask; ///< Pointer to the temperature task.
    SerialReceiver *serialReceiver;   ///< Pointer to the serial receiver object.
    ServoImpl *gate;                  ///< Pointer to the ServoImpl object that controls the gate.
};

#endif // __WASHING_TASK__
