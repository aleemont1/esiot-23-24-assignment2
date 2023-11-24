#include "../api/Led.h"
#include "Arduino.h"

Led::Led(int pin){
  this->pin = pin;
  pinMode(pin,OUTPUT);
}

void Led::on(){
  digitalWrite(pin,HIGH);
}

void Led::off(){
  digitalWrite(pin,LOW);
};
