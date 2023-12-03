#ifndef __EXIT_TRANSIT_TASK__
#define __EXIT_TRANSIT_TASK__

#include "kernel/DependantTaskWithState.h"
#include "config/config.h"
#include "components/api/Sonar.h"
#include "components/api/Led.h"
#include "components/api/ServoImpl.h"

/**
 * @brief Task for managing the exit transit process.
 *
 * This task is responsible for managing the process of a car exiting the transit area.
 * It reads the distance from the sonar sensor, checks if the distance is within a certain range,
 * and controls the gate and the L3 LED accordingly.
 *
 * @extends DependantTaskWithState
 */
class ExitTransitTask : public DependantTaskWithState
{
public:
    ExitTransitTask() : DependantTaskWithState()
    {
        Serial.println("ExitTransitTask created");
        this->sonar = new Sonar(SONAR_TRIG_PIN, SONAR_ECHO_PIN, SONAR_MAX_TIME);
        this->L3 = new Led(L3_PIN);
        this->gate = new ServoImpl(SERVO_PIN);
        this->init();
        this->setState(READING_DISTANCE);
    };

    /**
     * @brief Tick function that is called periodically.
     */
    void tick() override;

private:
    enum state
    {
        /**
         * @brief The task is currently turning on the L3 LED.
         *
         */
        TURN_ON_L3,
        /**
         * @brief The task is currently opening the gate.
         *
         */
        OPENS_GATE,
        /**
         * @brief The task is currently reading the distance from the sonar sensor.
         *
         */
        READING_DISTANCE,
        /**
         * @brief The task is checking if the distance is within a certain range.
         *
         */
        CHECKING_DISTANCE,
        /**
         * @brief The task is currently closing the gate.
         *
         */
        CLOSES_GATE,

        /**
         * @brief The task is currently switching off the L3 LED.
         *
         */
        SWITCH_OFF_L3

    };

    Led *L3;                           // Pointer to the L3 LED object
    Sonar *sonar;                      // Pointer to the sonar object
    ServoImpl *gate;                   // Pointer to the ServoImpl object that controls the gate.
    float distance;                    // The current distance read from the sonar sensor.
    unsigned long timeInExit = 0;      // The time in milliseconds when the car entered the exit area.
    const int GATE_OPEN_POSITION = 90; // The position of the gate when it is open.
    const int GATE_CLOSE_POSITION = 0; // The position of the gate when it is closed.
};

#endif __EXIT_TRANSIT_TASK__