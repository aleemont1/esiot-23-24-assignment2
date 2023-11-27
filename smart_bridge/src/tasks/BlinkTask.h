#ifndef __BLINK_TASK__
#define __BLINK_TASK__

#include "kernel/TaskWithState.h"
#include "components/api/Led.h"

class BlinkTask : public TaskWithState
{
private:
  int pin;
  Light *led;
  enum
  {
    ON,
    OFF
  } state;

public:
  BlinkTask(int pin) : TaskWithState()
  {
    Serial.println("BlinkTask created");
    this->pin = pin;
  }

  void init(int period)
  {
    Task::init(period);
    this->led = new Led(pin);
    this->setState(OFF);
  }

  void tick() override;
};

#endif
