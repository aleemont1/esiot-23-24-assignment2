#include "WashingTask.h"

WashingTask::WashingTask(BlinkTask *blinkTask,
                         CountDown *countDownTask,
                         TemperatureTask *temperatureTask)
    : DependantTaskWithState()
{
    // Serial.println(F("WashingTask created"));
    this->L2 = new Led(L2_PIN);
    this->L3 = new Led(L3_PIN);
    this->tempSensor = new Temp(TMP_PIN);
    this->lcd = new LCD(0x27, 16, 2);
    this->gate = new ServoImpl(SERVO_PIN);
    this->blinkTask = blinkTask;
    this->blinkTask->init(500);        // Blink every 500 ms the red led
    this->blinkTask->setActive(false);
    this->countDownTask = countDownTask;
    this->temperatureTask = temperatureTask;
    this->init(1000);
    this->setState(START_WASHING);
}

void WashingTask::tick()
{
    if (this->DependantTask::getDependency(0)->isCompleted())
    {
        switch (this->getState())
        {
        case START_WASHING:
            handleStartWashing();
            break;

        case STARTS_COUNTDOWN:
            handleStartsCountdown();
            break;

        case ENDS_COUNTDOWN:
            handleEndsCountdown();
            break;

        case ERROR:
            handleError();
            break;
        }
    }
}

void WashingTask::printWashingCompletedMessage()
{
    lcd->write("Washing complete, you can leave the area", 0, 0);
}

void WashingTask::handleStartWashing()
{
    this->blinkTask->setActive(true);
    this->countDownTask->setActive(true);
    this->temperatureTask->setActive(true);
    this->setState(STARTS_COUNTDOWN);
}

void WashingTask::handleStartsCountdown()
{
    // this->countDownTask->tick();
    // this->temperatureTask->tick();
    if (this->elapsedTime() >= checkInterval)
    {
        this->resetTime();
        if (this->temperatureTask->checkForCriticalTemperature() == true && this->countDownTask->getStatus() == false)
        {
            this->setState(ERROR);
        }
        if (this->countDownTask->getStatus() == true)
        {
            this->setState(ENDS_COUNTDOWN);
        }
    }
}

void WashingTask::handleEndsCountdown()
{
    this->countDownTask->endsCountDown();
    this->temperatureTask->setCompleted();
    this->blinkTask->setActive(false);
    this->L3->switchOn();
    this->printWashingCompletedMessage();
    this->setCompleted();
}

void WashingTask::handleError()
{
    this->countDownTask->pauseCountDown();
    this->temperatureTask->criticalTemperatureReachedMessage();
    this->temperatureTask->temperatureMaintenanceMessage();
    this->serialReceiver->simulateReadData(); // TODO: remove, but now simulate receiving "mnt:done"
    if (serialReceiver->readData() == true)
    {
        this->countDownTask->resumeCountDown();
        this->setState(STARTS_COUNTDOWN);
    }
}