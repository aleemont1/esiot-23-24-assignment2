#ifndef __EXIT_TRANSIT_TASK__
#define __EXIT_TRANSIT_TASK__

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
class ExitTransitTask : public DependantTaskWithState
{
public:
    /**
     * @brief Constructs a new ExitTransitTask.
     *
     * Initializes the sonar, L3 LED, and gate, and sets the initial state to READING_DISTANCE.
     */
    ExitTransitTask();

    /**
     * @brief Called periodically to update the task's state.
     *
     * This function is overridden from DependantTaskWithState.
     */
    void tick() override;

    /**
     * @brief Handles the reading of the distance from the sonar sensor.
     *
     * This function is called when the task's state is READING_DISTANCE.
     */
    void handleReadingDistance();

    /**
     * @brief Handles the checking of the distance from the sonar sensor.
     *
     * This function is called when the task's state is CHECKING_DISTANCE.
     */
    void handleCheckingDistance();

    /**
     * @brief Handles the closing of the gate.
     *
     * This function is called when the task's state is CLOSES_GATE.
     */
    void handleClosesGate();

    /**
     * @brief Handles the switching off of the L3 LED.
     *
     * This function is called when the task's state is SWITCH_OFF_L3.
     */
    void handleSwitchOffL3();

private:
    /**
     * @brief Enum for the possible states of the task.
     *
     */
    enum state
    {
        READING_DISTANCE,  ///< The task is currently reading the distance from the sonar sensor.
        CHECKING_DISTANCE, ///< The task is checking if the distance is within a certain range.
        CLOSES_GATE,       ///< The task is currently closing the gate.
        SWITCH_OFF_L3      ///< The task is currently switching off the L3 LED.
    };

    Led *L3;                       ///< Pointer to the L3 LED object.
    Sonar *sonar;                  ///< Pointer to the sonar object.
    ServoImpl *gate;               ///< Pointer to the ServoImpl object that controls the gate.
    float distance;                ///< The current distance read from the sonar sensor.
    unsigned long timeInExit;      ///< The time in milliseconds when the car entered the exit area.
    const int GATE_OPEN_POSITION;  ///< The position of the gate when it is open.
    const int GATE_CLOSE_POSITION; ///< The position of the gate when it is closed.
};

#endif // __EXIT_TRANSIT_TASK__