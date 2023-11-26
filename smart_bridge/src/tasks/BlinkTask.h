#ifndef __BLINK_TASK__
#define __BLINK_TASK__

#include "kernel/TaskWithState.h"
#include "components/api/Led.h"

class BlinkTask: public TaskWithState {

  int pin;
  Light* led;
  enum {ON, OFF} state;

public:

  BlinkTask(int pin);  
  void init(int period);  
  void tick();
};

#endif
