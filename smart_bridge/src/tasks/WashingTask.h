#ifndef __WASHING_TASK__
#define __WASHING_TASK__

#include "kernel/DependantTaskWithState.h"
#include "BlinkTask.h"
#include "components/api/Led.h"
#include "components/api/Temp.h"
#include "components/api/LCD.h"
#include "config/config.h"
#include "tasks/CountDown.h"
#include "tasks/TemperatureTask.h"
#include "kernel/SerialReceiver.h"
#include "components/api/ServoImpl.h"

/**
 * @class CarWashingTask
 * @brief Represents the car washing task.
 */
class WashingTask : public DependantTaskWithState
{
public:
    WashingTask(BlinkTask *blinkTask, CountDown *countDownTask, TemperatureTask *temperatureTask) : DependantTaskWithState()
    {
        Serial.println("WashingTask created");
        this->L2 = new Led(L2_PIN);
        this->L3 = new Led(L3_PIN);
        this->tempSensor = new Temp(TMP_PIN);
        this->lcd = new LCD(0x27, 16, 2);
        this->gate = new ServoImpl(SERVO_PIN);
        this->blinkTask = blinkTask;
        this->blinkTask->init(500);        // Blink every 500 ms the red led
        this->blinkTask->setActive(false); // TODO: Check if this is necessary
        this->countDownTask = countDownTask;
        this->temperatureTask = temperatureTask;
        this->init(1000);
        this->setState(START_WASHING);
    };

    /**
     * @brief Tick function that is called periodically.
     *
     */
    void tick() override;

    /**
     * @brief Prints the message "Washing complete, you can leave the area" on the LCD display.
     *
     */
    void printWashingCompletedMessage();

private:
    enum state
    {
        START_WASHING,
        STARTS_COUNTDOWN,
        ENDS_COUNTDOWN,
        ERROR,
        OPENS_GATE,
        CLOSES_GATE
    };

    int savedCountDown;
    unsigned long savedTimeInState;
    int countDown;
    Led *L2;                          // Red led
    Led *L3;                          // Green led
    Temp *tempSensor;                 // Temperature sensor
    LCD *lcd;                         // The LCD display
    Task *blinkTask;                  // The blink task for the leds
    CountDown *countDownTask;         // The countdown task
    TemperatureTask *temperatureTask; // The temperature task
    SerialReceiver *serialReceiver;   // The serial receiver
    ServoImpl *gate;                  // The servo used to open and close the gate
};

#endif // __WASHING_TASK__
