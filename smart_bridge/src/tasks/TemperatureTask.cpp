#include "TemperatureTask.h"

TemperatureTask::TemperatureTask()
    : TaskWithTimer(),
      voltageConversionFactor(30),
      voltageOffset(0.5)
{
    Serial.println("TemperatureTask created");
    this->lcd = new LCD(0x27, 16, 2);
    this->setTemperature(this->getTemperature());
    this->init(1000);
    this->setActive(false);
}

float TemperatureTask::readVoltage()
{
    int reading = analogRead(TMP_PIN);
    float voltage = reading * ADC_VOLTAGE_RANGE / ADC_RESOLUTION;
    return voltage;
}

float TemperatureTask::convertVoltageToTemperature(float voltage)
{
    float temperatureC = (voltage - voltageOffset) * voltageConversionFactor; // Converting from 10 mV per degree with 500 mV offset
    return temperatureC;
}

int TemperatureTask::getTemperature()
{
    float voltage = readVoltage();
    int temperatureC = convertVoltageToTemperature(voltage);
    return temperatureC;
}

void TemperatureTask::setTemperature(int temperature)
{
    this->temperature = temperature;
}

void TemperatureTask::printTemperature()
{
    int temp = getTemperature();
    lcd->write(("Temperature: " + String(temp) + (char)223 + "C").c_str(), 0, 0);
}

bool TemperatureTask::checkForCriticalTemperature()
{
    if (temperature > MAXTEMP)
    {
        if (this->elapsedTime() >= N5 * 1000)
        {
            return true;
        }
    }
    else
    {
        this->resetTime();
    }
    return false;
}

void TemperatureTask::criticalTemperatureReachedMessage()
{
    Serial.println("Critical temperature reached!");
}

void TemperatureTask::temperatureMaintenanceMessage()
{
    // Serial.println("Detected a Problem - Please Wait");
    lcd->write("Detected a Problem - Please Wait: ", 0, 0);
}

void TemperatureTask::startMonitoringTemperature()
{
    this->setActive(true);
}

void TemperatureTask::tick()
{
    startMonitoringTemperature();
    printTemperature();
}