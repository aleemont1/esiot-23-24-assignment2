#include "ExitTransitTask.h"

ExitTransitTask::ExitTransitTask()
    : DependantTaskWithState(),
      GATE_OPEN_POSITION(90),
      GATE_CLOSE_POSITION(0)
{
    Serial.println("ExitTransitTask created");
    this->sonar = new Sonar(SONAR_TRIG_PIN, SONAR_ECHO_PIN, SONAR_MAX_TIME);
    this->L3 = new Led(L3_PIN);
    this->gate = new ServoImpl(SERVO_PIN);
    this->init(1000);
    this->setState(READING_DISTANCE);
};

void ExitTransitTask::tick()
{
    if (this->getDependency(0) != nullptr)
    {
        if (this->getDependency(0)->isCompleted())
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
    }
    else
        Serial.println("ExitTransitTask::tick()::getDependency(0) is nullptr");
}

void ExitTransitTask::handleReadingDistance()
{
    this->distance = sonar->detectDistance();
    Serial.println("ExitTransitTask::Distance: " + String(this->distance));
    this->setState(CHECKING_DISTANCE);
}

void ExitTransitTask::handleCheckingDistance()
{
    if (this->distance > MAXDIST)
    {
        if (timeInExit == 0)
        {
            timeInExit = millis();
        }
        else if (millis() - timeInExit >= N4_FOR_DIST * 1000)
        {
            this->setState(CLOSES_GATE);
        }
    }
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