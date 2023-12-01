#include "TemperatureTask.h"

TemperatureTask::TemperatureTask() : Task()
{
    this->lcd = new LCD(0x27, 16, 2);
    this->setTemperature(this->getTemperature());
    this->init(1000);
}

float TemperatureTask::readVoltage()
{
    int reading = analogRead(TMP_PIN);
    float voltage = reading * 5.0 / 1024.0;
    return voltage;
}

float TemperatureTask::convertVoltageToTemperature(float voltage)
{
    float temperatureC = (voltage - 0.5) * 100; // Converting from 10 mV per degree with 500 mV offset
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
    Serial.println("Temperature: " + String(temp) + "°C");
    lcd->write(("Temperature: " + String(temp) + "°C").c_str(), 0, 0);
}

bool TemperatureTask::checkForCriticalTemperature()
{
    if (temperature > MAXTEMP)
    {
        Serial.println("Critical temperature reached!");
        this->temperatureMaintenanceMessage();
        return true;
    }
    return false;
}

void TemperatureTask::temperatureMaintenanceMessage()
{
    Serial.println("Detected a Problem - Please Wait");
}

void TemperatureTask::tick()
{
    printTemperature();
    checkForCriticalTemperature();
}