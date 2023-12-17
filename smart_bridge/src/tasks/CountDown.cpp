#include "CountDown.h"

CountDown::CountDown(int countDown) : Task()
{
    // Serial.println(F("CountDownTask created"));
    this->setStatus(false);
    this->lcd = new LCD(0x27, 16, 2);
    this->resetCountDown(N3);
    this->init(1000);
    this->setActive(false);
}

int CountDown::getCountDown()
{
    return this->countDown;
}

void CountDown::resetCountDown(int newCountDown)
{
    this->countDown = newCountDown;
}

void CountDown::decreaseCountDown(int decrement)
{
    if (getCountDown() - decrement < 0)
    {
        endsCountDown();
    }
    else
    {
        this->countDown -= decrement;
    }
}

void CountDown::increaseCountDown(int increment)
{
    this->countDown += increment;
}

void CountDown::pauseCountDown()
{
    this->pausedCountDown = getCountDown();
    this->setActive(false);
}

void CountDown::startCountDown()
{
    this->setActive(true);
}

void CountDown::printCountDown()
{
    int count = getCountDown();
    char buffer[3];
    sprintf(buffer, "%02d", count);
    lcd->write(("Countdown: " + String(buffer)).c_str(), 0, 0);
}

void CountDown::endsCountDown()
{
    if (getCountDown() <= 0)
    {
        this->setStatus(true);
        this->isCompleted();
        this->printsEndsCountdown();
        this->resetCountDown(N3);
        // Serial.println(F("CountDown::Countdown resetted"));
        this->setCompleted();
    }
}

void CountDown::printsEndsCountdown()
{
    // Serial.println(F("CountDown::Countdown ended!"));
}

bool CountDown::isCountDownActive()
{
    return this->isActive();
}

void CountDown::stopCountDown()
{
    this->setActive(false);
    this->resetCountDown(N3);
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

void CountDown::setStatus(bool value)
{
    this->status = value;
}

bool CountDown::getStatus()
{
    return this->status;
}

void CountDown::tick()
{
    startCountDown();
    printCountDown();
    decreaseCountDown();
}