#ifndef __CHECKINTASK__
#define __CHECKINTASK__

#include <Arduino.h>
#include "kernel/Task.h"
#include "components/api/Led.h"
#include "config/config.h"
#include <Servo.h>

/**
 * @class CheckInTask
 * @brief Represents the check-in task.
 */

class CheckInTask : public Task
{
    Led *L1;
    Led *L2;
    Servo *gate;
    String *message;

public:
    CheckInTask();
    void init();
    void tick() override;
};

#endif