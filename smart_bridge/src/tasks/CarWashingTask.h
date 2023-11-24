#ifndef __CAR_WASHING_TASK__
#define __CAR_WASHING_TASK__

#include "kernel/Task.h"

/**
 * @class CarWashingTask
 * @brief Represents the car washing task.
 */
class CarWashingTask : public Task
{
public:
    /**
     * @brief Default constructor for the CarWashingTask class.
     */
    CarWashingTask();

    /**
     * @brief Initializes the car washing task with specific parameters.
     * @param initialState The initial state of the task.
     * @param sampleInterval The interval at which the task should sample.
     */
    void initialize(int initialState, long sampleInterval);

    /**
     * @brief This function is called at each tick of the task.
     */
    void tick() override;

private:
    /**
     * @brief Sets the state of the task.
     * @param state The new state of the task.
     */
    void setState(int state);

    /**
     * @brief The elapsed time in the current state.
     * @return The elapsed time in the current state.
     */
    long elapsedTimeInState() const;

    /**
     * @brief Checks if it's time to sample.
     * @return True if it's time to sample, false otherwise.
     */
    bool isTimeToSample() const;

    /**
     * @brief Returns the timestamp of the current state.
     * @return The timestamp of the current state.
     */
    long stateTimeStamp() const;

    // TODO: continue from here
};

#endif // __CAR_WASHING_TASK__