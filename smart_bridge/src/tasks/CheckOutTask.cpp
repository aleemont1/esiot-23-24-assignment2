#include "CheckOutTask.h"

CheckOutTask::CheckOutTask() : DependantTaskWithState()
{
    Serial.println("CheckOutTask created");
    this->sonar = new Sonar(SONAR_TRIG_PIN, SONAR_ECHO_PIN, SONAR_MAX_TIME);
    this->L3 = new Led(L3_PIN);
    this->gate = new ServoImpl(SERVO_PIN);
    this->init();
    this->setState(TURN_ON_L3);
};

void CheckOutTask::tick()
{
    if (this->getDependency(0) != nullptr)
    {
        if (this->getDependency(0)->isCompleted())
        {
            switch (this->getState())
            {

            case TURN_ON_L3:
                handleTurnOnL3();
                break;

            case OPENS_GATE:
                handleOpensGate();
                break;
            }
        }
    }
}

void CheckOutTask::handleTurnOnL3()
{
    this->L3->switchOn();
    Serial.println("CheckOutTask::L3 turned on");
    this->setState(OPENS_GATE);
}

void CheckOutTask::handleOpensGate()
{
    this->gate->write(GATE_OPEN_POSITION);
    Serial.println("CheckOutTask::Gate opened");
    this->setCompleted();
}