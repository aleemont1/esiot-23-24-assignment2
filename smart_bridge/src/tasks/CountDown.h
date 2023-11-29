#ifndef __COUNT_DOWN_TASK__
#define __COUNT_DOWN_TASK__

#include "kernel/Task.h"

class CountDown : public Task
{
public:
    CountDown(int countDown) : Task()
    {
        this->countDown = countDown;
        this->init(1000);       // Periodic task, executed every 1000ms
        this->setActive(false); /** NOTE: Might be removed, this stops the countdown by default.
                                 setActive(true) to start the countdown in your task. **/
    }

    void tick() override;

    int getCountDown()
    {
        return countDown;
    }

private:
    int countDown;
};

#endif // __COUNT_DOWN_TASK__