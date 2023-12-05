#include "ExitTransitTask.h"

ExitTransitTask::ExitTransitTask()
    : DependantTaskWithState(),
      GATE_OPEN_POSITION(180),
      GATE_CLOSE_POSITION(0)
{
    Serial.println("ExitTransitTask created");
    this->sonar = new Sonar(SONAR_TRIG_PIN, SONAR_ECHO_PIN, SONAR_MAX_TIME);
    this->L3 = new Led(L3_PIN);
    this->gate = new ServoImpl(SERVO_PIN);
    this->lcd = new LCD(0x27, 16, 2);
    this->init();
    this->setState(READING_DISTANCE);
};

void ExitTransitTask::tick()
{

    switch (this->getState())
    {
    case READING_DISTANCE:
        handleReadingDistance();
        break;

    case CHECKING_DISTANCE:
        handleCheckingDistance();
        break;

    case CLOSES_GATE:
        handleClosesGate();
        break;

    case SWITCH_OFF_L3:
        handleSwitchOffL3();
        break;
    }
}

void ExitTransitTask::handleReadingDistance()
{
    this->lcd->write("Exit area", 0, 0);
    this->lcd->write("Proceed slowly!", 0, 1);
    this->L3->switchOn();
    this->setState(CHECKING_DISTANCE);
}

void ExitTransitTask::handleCheckingDistance()
{
    this->distance = sonar->detectDistance();
    Serial.println("ExitTransitTask::Distance: " + String(this->distance));
    if (this->distance > MAXDIST)
    {
        this->distance = sonar->detectDistance();
        Serial.println("ExitTransitTask::Distance: " + String(this->distance));
        if (this->elapsedTime() >= (N4_FOR_DIST * 1000))
        {
            Serial.println("ExitTransitTask::Car left");
            this->setState(CLOSES_GATE);
        }
    }
    else
        this->resetTime();
}

void ExitTransitTask::handleClosesGate()
{
    this->gate->write(GATE_CLOSE_POSITION);
    Serial.println("ExitTransitTask::Gate closed");
    this->setState(SWITCH_OFF_L3);
}

void ExitTransitTask::handleSwitchOffL3()
{
    this->L3->switchOff();
    Serial.println("ExitTransitTask::L3 switched off");
    this->setCompleted();
}