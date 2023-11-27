#include "../api/Pir.h"
#include "config/config.h"
#include "Arduino.h"

Pir::Pir(int pin) : pirDetectionStatus(OBJECT_NOT_DETECTED)
{
    this->pirPin = PIR_PIN;
    lastTimePirWasInSync = 0;
    pinMode(pin, INPUT);
    calibrate();
    updatePirState();
}

bool Pir::checkDetectedStatus()
{
    return pirDetectionStatus == OBJECT_DETECTED;
}

bool Pir::checkNotDetectedStatus()
{
    return pirDetectionStatus == OBJECT_NOT_DETECTED;
}

void Pir::calibrate() {

}

void Pir::updatePirState()
{
    // If the PIR sensor detects movement, the pin will be HIGH.
    pirDetectionStatus = digitalRead(pirPin) == HIGH ? OBJECT_DETECTED : OBJECT_NOT_DETECTED;
    // Update the last time the PIR sensor state was synchronized.
    setLastPirSyncTime(millis());
}

void Pir::setLastPirSyncTime(long time)
{
    lastTimePirWasInSync = time;
}

long Pir::retrieveLastPirSyncTime()
{
    return lastTimePirWasInSync;
}
