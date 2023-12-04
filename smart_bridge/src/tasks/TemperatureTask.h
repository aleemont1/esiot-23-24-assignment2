#ifndef __TEMPERATURE_TASK__
#define __TEMPERATURE_TASK__

#include "kernel/TaskWithTimer.h"
#include "Arduino.h"
#include "config/config.h"
#include "components/api/LCD.h"

/**
 * @brief Manages the temperature reading and monitoring.
 *
 * This class is responsible for reading the temperature from a sensor, converting the voltage to temperature,
 * checking for critical temperature, and printing the temperature and related messages.
 *
 * @extends Task
 */
class TemperatureTask : public TaskWithTimer
{
public:
    /**
     * @brief Construct a new Temperature Task object
     *
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
     * @return float The temperature value converted from the voltage value.
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
     */
    void printTemperature();

    /**
     * @brief Handle the case where the temperature is critical.
     *
     * @return bool True if the temperature is critical, false otherwise.
     */
    bool checkForCriticalTemperature();

    /**
     * @brief Set the Critical Temperature value.
     *
     * @param criticalTemperature The temperature value that is considerable as critical (must be over MAXTEMP Celsius degrees)
     */
    void setCriticalTemperature(int criticalTemperature);

    /**
     * @brief Print the message "Maintenance required" on the LCD display.
     *
     */
    void temperatureMaintenanceMessage();

    /**
     * @brief Print the message "Critical temperature reached!" on the serial monitor.
     *
     */
    void criticalTemperatureReachedMessage();

    /**
     * @brief Start monitoring the temperature and print it on the LCD display.
     *
     */
    void startMonitoringTemperature();

private:
    int temperature;                                ///< The current temperature.
    int criticalTemperature;                        ///< The temperature value that is considered as critical.
    LCD *lcd;                                       ///< Pointer to the LCD object.
    unsigned long timeExceededMaxTemp = 0;          ///<  Used to keep track of the time when the temperature first exceeds MAXTEMP and then check if N5 seconds have passed since that time.
    static constexpr float ADC_VOLTAGE_RANGE = 5.0; ///< The voltage range of the ADC.
    static constexpr float ADC_RESOLUTION = 1024.0; ///< The resolution of the ADC.
    float voltageConversionFactor;                  ///< The factor to convert voltage to temperature.
    float voltageOffset;                            ///< The offset to convert voltage to temperature.
};

#endif // __TEMPERATURE_TASK__