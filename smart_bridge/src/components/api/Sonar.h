#ifndef __SONAR__
#define __SONAR__

/**
 * @class Sonar
 * @brief This class represents a sonar sensor.
 *
 * It provides functionalities to get the distance of an object from the sensor, and set the temperature for sound speed calculation.
 */
class Sonar
{

public:
    /**
     * @brief Construct a new Sonar object.
     *
     * @param echoPin The pin number where the echo pin of the sonar sensor is connected.
     * @param trigPin The pin number where the trigger pin of the sonar sensor is connected.
     * @param maxTime The maximum time to wait for the echo pin to go high in microseconds.
     */
    Sonar(int echoPin, int trigPin, long maxTime);

    /**
     * @brief Detect the distance of an object from the sonar sensor.
     *
     * @return float The distance of the object from the sensor in meters. Returns NO_OBJECT_DETECTED if no object is detected.
     */
    float detectDistance();

    /**
     * @brief Get the current temperature setting of the Sonar object.
     *
     * This temperature is used in the calculation of the speed of sound for distance measurements.
     *
     * @return float The current temperature setting in degrees Celsius.
     */
    float getTemperature() const { return temperature; }

    /**
     * @brief Adjust the temperature for sound speed calculation.
     *
     * @param temp The temperature in degrees Celsius.
     */
    void adjustTemperature(float temp);

private:
    /**
     * @brief The duration of the LOW state of the trigger pin in microseconds
     *
     */
    static constexpr int TRIG_LOW_DURATION = 3;

    /**
     * @brief The duration of the HIGH state of the trigger pin in microseconds
     *
     */
    static constexpr int TRIG_HIGH_DURATION = 5;

    /**
     * @brief The number of microseconds converted in a second
     *
     */
    const long MICROSECONDS_IN_SECOND = 1000000L;

    /**
     * @brief The default temperature setting in degrees Celsius.
     *
     */
    static constexpr float DEFAULT_TEMPERATURE = 20.0f;

    /**
     * @brief The speed of sound in air in meters per second at 20 degrees Celsius.
     *
     * The calculation `331.5 + 0.6 * 20` is used to
     * calculate the speed of sound in air
     * in meters per second at 20 degrees Celsius.
     *
     * The formula for sound velocity `v`
     * in air as a function of temperature `T`
     * in degrees Celsius is `v = 331.5 + 0.6 * T`.
     */
    static constexpr float SOUND_SPEED_CALCULUS = 331.5 + 0.6 * DEFAULT_TEMPERATURE;

    /**
     * @brief Determine the speed of sound based on the current temperature.
     *
     * @return float The speed of sound in meters per second.
     */
    float getSoundSpeed();

    /**
     * @brief The current temperature in degrees Celsius.
     */
    float temperature;

    /**
     * @brief The pin number where the echo pin of the sonar sensor is connected.
     */
    const int echoPin;

    /**
     * @brief The pin number where the trigger pin of the sonar sensor is connected.
     */
    const int trigPin;

    /**
     * @brief The maximum time to wait for the echo pin to go high in microseconds.
     */
    const long timeOut;

    /**
     * @brief Constant representing no object detected by the sonar sensor.
     */
    static constexpr float NO_OBJECT_DETECTED = -1.0f;
};

#endif // __SONAR__