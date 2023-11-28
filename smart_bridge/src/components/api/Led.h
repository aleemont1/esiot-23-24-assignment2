#ifndef __LED__
#define __LED__

#include "Light.h"
#include "Arduino.h"

/**
 * @brief The interval at which the led blinks
 *
 */
const unsigned long BLINK_INTERVAL = 250;

/**
 * @brief When the led last blinked
 *
 */
unsigned long lastBlinkTime = 0;

/**
 * @brief The current state of the led
 *
 */
int blinkState = LOW;

class Led : public Light
{
public:
  Led(int pin);
  void switchOn();
  void switchOff();
  /**
   * @brief Makes the led blink with a period of 0.5 secs
   *
   */
  void blink();

protected:
  int pin;
};

#endif
