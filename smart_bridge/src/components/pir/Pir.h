#ifndef __PIR__
#define __PIR__

constexpr bool OBJECT_DETECTED = true;
constexpr bool OBJECT_NOT_DETECTED = false;

/**
 * @class Pir
 * @brief This class represents a Passive Infrared (PIR) sensor.
 *
 * This class provides functionalities to check the detection status
 * of the sensor, calibrate it, and update its state.
 */
class Pir
{

public:
    /**
     * @brief Construct a new Pir object.
     *
     * @param pin The pin number where the PIR sensor is connected.
     */
    Pir(int pin);

    /**
     * @brief Check if the PIR sensor has detected movement.
     *
     * @return true If the sensor has detected movement, false otherwise.
     */
    bool checkDetectedStatus();

    /**
     * @brief Check if the PIR sensor has not detected any movement.
     *
     * @return true If the sensor has not detected any movement, false otherwise.
     */
    bool checkNotDetectedStatus();

    /**
     * @brief Calibrate the PIR sensor.
     */
    void calibrate();

    /**
     * @brief Update the state of the PIR sensor.
     */
    void updatePirState();

    /**
     * @brief Retrieves the last time the PIR sensor state was synchronized.
     *
     * @return long The last synchronization time.
     */
    long retrieveLastPirSyncTime();

protected:
    /**
     * @brief Set the last synchronization time.
     *
     * @param time The new synchronization time.
     */
    void setLastPirSyncTime(long time);

private:
    /**
     * @brief The last time the PIR sensor state was synchronized.
     */
    long lastTimePirWasInSync;

    /**
     * @brief The pin number where the PIR sensor is connected.
     */
    int pirPin;

    /**
     * @brief The current detection status of the PIR sensor (true if movement is detected, false otherwise).
     */
    bool pirDetectionStatus;
};

#endif // __PIR__