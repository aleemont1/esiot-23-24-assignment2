#ifndef __TASK__
#define __TASK__

/**
 * @class Task
 * @brief This class represents a task that can be either periodic or aperiodic.
 */
class Task
{

public:
    /**
     * @brief Default constructor. Initializes the task as inactive.
     */
    Task()
    {
        active = false;
    }

    /**
     * @brief Initializes a periodic task.
     * @param period The period of the task.
     */
    virtual void init(int period)
    {
        myPeriod = period;
        periodic = true;
        active = true;
        timeElapsed = 0;
    }

    /**
     * @brief Initializes an aperiodic task.
     */
    virtual void init()
    {
        timeElapsed = 0;
        periodic = false;
        active = true;
        completed = false;
    }

    virtual void tick() = 0;

    /**
     * @brief Updates the elapsed time and checks if it's time to execute the task.
     * @param schedulerPeriod The base period to add to the elapsed time.
     * @return True if it's time to execute the task, false otherwise.
     */
    virtual bool updateAndCheckTime(unsigned long schedulerPeriod)
    {
        timeElapsed += schedulerPeriod;
        if (timeElapsed >= myPeriod)
        {
            timeElapsed = 0;
            return true;
        }
        return false;
    }

    /**
     * @brief Marks the task as completed and deactivates it.
     */
    void setCompleted()
    {
        completed = true;
        active = false;
    }

    /**
     * @brief Checks if the task is completed.
     * @return True if the task is completed, false otherwise.
     */
    bool isCompleted()
    {
        return completed;
    }

    /**
     * @brief Checks if the task is periodic.
     * @return True if the task is periodic, false otherwise.
     */
    bool isPeriodic()
    {
        return periodic;
    }

    /**
     * @brief Checks if the task is active.
     * @return True if the task is active, false otherwise.
     */
    bool isActive()
    {
        return active;
    }

    /**
     * @brief Sets the task as active or inactive.
     * @param active The new state of the task.
     */
    virtual void setActive(bool active)
    {
        timeElapsed = 0;
        this->active = active;
    }

private:
    int myPeriod;    // The period of the task.
    int timeElapsed; // The elapsed time since the last execution of the task.
    bool active;     // The state of the task (active or inactive).
    bool periodic;   // The type of the task (periodic or aperiodic).
    bool completed;  // The completion status of the task.
};

#endif // __TASK__
