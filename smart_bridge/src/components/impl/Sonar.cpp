#include "../api/Sonar.h"
#include "config/config.h"
#include "Arduino.h"

// The temperature value is adjustable as preferred by the user
Sonar::Sonar(int echoP, int trigP, long maxTime) : echoPin(echoP), trigPin(trigP), timeOut(maxTime), temperature(20)
{
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void Sonar::adjustTemperature(float temperature)
{
    this->temperature = temperature;
}
float Sonar::getSoundSpeed()
{
    return SOUND_SPEED_CALCULUS;
}

// TODO: delayMicroseconds() need to be accurate enough for the sonar sensor (assumes predefined MHz clock speed)
float Sonar::detectDistance()
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(TRIG_LOW_DURATION);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(TRIG_HIGH_DURATION);
    digitalWrite(trigPin, LOW);

    float tUS = pulseIn(echoPin, HIGH, timeOut);
    if (tUS == 0)
    {
        return NO_OBJECT_DETECTED;
    }
    else
    {
        float t = tUS / MICROSECONDS_IN_SECOND / 2;
        float d = t * getSoundSpeed()*100;
        return d;
    }
}
