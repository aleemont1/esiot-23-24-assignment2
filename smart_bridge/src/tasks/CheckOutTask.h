#ifndef __CHECK_OUT_TASK__
#define __CHECK_OUT_TASK__

#include "kernel/DependantTaskWithState.h"
#include "config/config.h"
#include "components/api/Sonar.h"
#include "components/api/Led.h"
#include "components/api/ServoImpl.h"

/**
 * @brief Manages the process of a car exiting the transit area.
 *
 * This task is responsible for managing the process of a car exiting the transit area.
 * It reads the distance from the sonar sensor, checks if the distance is within a certain range,
 * and controls the gate and the L3 LED accordingly.
 *
 * @extends DependantTaskWithState
 */
class CheckOutTask : public DependantTaskWithState
{
public:
    /**
     * @brief Construct a new Exit Transit Task object
     *
     */
    CheckOutTask();

    /**
     * @brief Called periodically to update the task's state.
     *
     * This function is overridden from DependantTaskWithState.
     */
    void tick() override;

private:
    /**
     * @brief Handles the turning on of the L3 LED.
     *
     * This function is called when the task's state is TURN_ON_L3.
     */
    void handleTurnOnL3();

    /**
     * @brief Handles the opening of the gate.
     *
     * This function is called when the task's state is OPENS_GATE.
     */
    void handleOpensGate();

    /**
     * @brief Enum for the possible states of the task.
     *
     */
    enum state
    {
        TURN_ON_L3, ///< The task is currently turning on the L3 LED.
        OPENS_GATE, ///< The task is currently opening the gate.
    };

    Led *L3;                           ///< Pointer to the L3 LED object
    Sonar *sonar;                      ///< Pointer to the sonar object
    ServoImpl *gate;                   ///< Pointer to the ServoImpl object that controls the gate.
    float distance;                    ///< The current distance read from the sonar sensor.
    unsigned long timeInExit = 0;      ///< The time in milliseconds when the car entered the exit area.
    const int GATE_OPEN_POSITION = 90; ///< The position of the gate when it is open.
    const int GATE_CLOSE_POSITION = 0; ///< The position of the gate when it is closed.
};

#endif // __CHECK_OUT_TASK__