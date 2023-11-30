#include "CountDown.h"
#include "Arduino.h"

CountDown::CountDown(int countDown) : Task()
{
    this->countDown = DEFAULT_COUNTDOWN;
    this->init(1000);
}

void CountDown::tick()
{
    printCountDown();
    decreaseCountDown();
    endsCountDown();
}

int CountDown::getCountDown()
{
    return countDown;
}

void CountDown::resetCountDown(int newCountDown)
{
    this->countDown = DEFAULT_COUNTDOWN;
}

void CountDown::decreaseCountDown(int decrement = 1)
{
    if (this->countDown - decrement <= 0)
    {
        endsCountDown();
    }
    else
    {
        this->countDown -= decrement;
    }
}

void CountDown::increaseCountDown(int increment = 1)
{
    this->countDown += increment;
}

void CountDown::pauseCountDown()
{
    this->pausedCountDown = this->countDown;
    this->setActive(false);
}

void CountDown::startCountDown()
{
    this->setActive(true);
}

void CountDown::printCountDown()
{
    Serial.println("ContDown::Current countdown: " + String(countDown));
}

void CountDown::endsCountDown()
{
    if (countDown <= 0)
    {
        this->setCompleted();
        this->printsEndsCountdown();
        this->setActive(false);
        this->countDown = DEFAULT_COUNTDOWN;
    }
}

void CountDown::printsEndsCountdown()
{
    Serial.println("CountDown::Countdown ended!");
}

bool CountDown::isCountDownActive()
{
    return this->isActive();
}

void CountDown::stopCountDown()
{
    this->setActive(false);
    this->countDown = DEFAULT_COUNTDOWN;
}

void CountDown::resumeCountDown()
{
    if (this->pausedCountDown != -1)
    {
        this->countDown = this->pausedCountDown;
        this->pausedCountDown = -1;
        this->setActive(true);
    }
}