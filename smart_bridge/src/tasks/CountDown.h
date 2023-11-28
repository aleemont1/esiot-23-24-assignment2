#ifndef __COUNT_DOWN_TASK__
#define __COUNT_DOWN_TASK__

#include "kernel/Task.h"

class CountDown : public Task
{
public:
    CountDown(int countDown) : Task()
    {
        this->countDown = countDown;
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