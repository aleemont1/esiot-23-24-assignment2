#ifndef __TASK_WITH_TIMER__
#define __TASK_WITH_TIMER__

#include "Task.h"
#include <Arduino.h>

/**
 * @class TaskWithTimer
 * @brief A task with a timer.
 * @note The timer is a long value that can be used to measure the time elapsed since the last reset. (First reset is done automatically at the initialization).
 *
 * @author Alessandro Monticelli
 */
class TaskWithTimer : virtual public Task
{
public:
    TaskWithTimer() : Task()
    {
        this->timerTimestamp = millis();
    };

    long elapsedTime()
    {
        return millis() - timerTimestamp;
    }

    void resetTime()
    {
        this->timerTimestamp = millis();
    }

private:
    long timerTimestamp;
};
#endif
