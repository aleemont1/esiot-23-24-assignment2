#include "Scheduler.h"
#include <TimerOne.h>

volatile bool timerFlag = false;

void timeHandler(void)
{
    timerFlag = true;
}

void Scheduler::init(int period)
{
    this->period = period;
    timerFlag = false;
    long u_period = 1000L * period;
    Timer1.initialize(u_period);
    Timer1.attachInterrupt(timeHandler);
    this->numTasks = 0;
}

bool Scheduler::addTask(Task *task)
{
    if (this->numTasks < MAX_TASKS - 1)
    {
        this->tasks[this->numTasks++] = task;
        return true;
    }
    return false;
}

void Scheduler::schedule()
{
    while (!timerFlag);
    timerFlag = false;

    for (int i = 0; i < this->numTasks; i++)
    {
        if (this->tasks[i]->isActive())
        {
            if (this->tasks[i]->isPeriodic())
            {
                if (this->tasks[i]->updateAndCheckTime(this->period))
                {
                    this->tasks[i]->tick();
                }
            }
            else
            {
                this->tasks[i]->tick();
            }
            if (this->tasks[i]->isCompleted())
            {
                this->tasks[i]->setActive(false);
            }
        }
    }
}
