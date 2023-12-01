#ifndef __TEMPERATURE_TASK__
#define __TEMPERATURE_TASK__

#include "kernel/Task.h"
#include "Arduino.h"
#include "config/config.h"
#include "components/api/LCD.h"

/**
 * @brief A task that reads the temperature from a sensor.
 *
 */
class TemperatureTask : public Task
{
public:
    /**
     * @brief Construct a new Temperature Task object
     *
     * @param temperature The temperature read from the sensor in Celsius degrees.
     */
    TemperatureTask();

    /**
     * @brief Tick function that is called periodically.
     *
     */
    void tick() override;

    /**
     * @brief Read the voltage from the temperature sensor.
     *
     * @return float The voltage read from the temperature sensor.
     * @note assumes that is used the TMP36 temperature sensor.
     */
    float readVoltage();

    /**
     * @brief Convert the voltage value to a temperature value.
     *
     * @param voltage The voltage value read from the sensor.
     * @return int The temperature value converted from the voltage value.
     * @note assumes that is used the TMP36 temperature sensor.
     */
    float convertVoltageToTemperature(float voltage);

    /**
     * @brief Get the current temperature value.
     *
     * @return int The current temperature value.
     */
    int getTemperature();

    /**
     * @brief Set the value of the temperature.
     *
     * @param temperature The new setted temperature value.
     */
    void setTemperature(int temperature);

    /**
     * @brief Print the temperature value on the PC Console Dashboard.
     *
     * @param temperature The temperature value read from the sensor.
     */
    void printTemperature();

    /**
     * @brief Handle the case where the temperature is critical.
     *
     * @param temperature The temperature value read from the sensor that is considerable as critical.
     */
    bool checkForCriticalTemperature();

    /**
     * @brief Set the Critical Temperature value.
     *
     * @param criticalTemperature The temperature value that is considerable as critical (muste be over 30 Celsius degrees)
     */
    void setCriticalTemperature(int criticalTemperature);

    /**
     * @brief Print the message "Maintenance required" on the PC Console Dashboard.
     *
     */
    void temperatureMaintenanceMessage();

private:
    int temperature;
    int criticalTemperature;
    LCD *lcd;
};

#endif // __TEMPERATURE_TASK__