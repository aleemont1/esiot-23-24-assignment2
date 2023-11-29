#ifndef __BLINK_TASK__
#define __BLINK_TASK__

#include "kernel/TaskWithState.h"
#include "components/api/Led.h"

/**
 * @class BlinkTask
 * @brief A task that blinks a LED.
 */
class BlinkTask : public TaskWithState
{
public:
  /**
   * @brief Constructor
   * @param pin The pin where the LED is connected
   * @param period The period of the blinking
   */
  BlinkTask(int pin, int period) : TaskWithState()
  {
    Serial.println("BlinkTask created");
    this->pin = pin;
    this->init(period);
  }

  /**
   * @brief Constructor
   * @param pin The pin where the LED is connected
   */
  BlinkTask(int pin) : TaskWithState()
  {
    Serial.println("BlinkTask created");
    this->pin = pin;
  }

  /**
   * @brief Initializes the task
   * @param period The period of the blinking
   */
  void init(int period)
  {
    Task::init(period);
    this->led = new Led(pin);
    this->setState(OFF);
  }

  void tick() override;

private:
  int pin;
  Light *led;
  enum
  {
    ON,
    OFF
  } state;
};

#endif
