#ifndef __BUTTON__
#define __BUTTON__

#include "AbstractButton.h"

class Button: public AbstractButton {
 
public: 
  Button(int pin);
  bool isPressed();
  void sync();

private:
  int pin;
  bool pressed;
};

#endif