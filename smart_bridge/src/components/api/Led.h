#ifndef __LED__
#define __LED__

#include "Light.h"

class Led: public Light { 
public:
  Led(int pin);
  void on();
  void off();    
protected:
  int pin;  
};

#endif
