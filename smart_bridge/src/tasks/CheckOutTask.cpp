#include "CheckOutTask.h"

CheckOutTask::CheckOutTask()
    : DependantTaskWithState(),
      GATE_OPEN_POSITION(180),
      GATE_CLOSE_POSITION(0)
{
    Serial.println("CheckOutTask created");
    this->sonar = new Sonar(SONAR_TRIG_PIN, SONAR_ECHO_PIN, SONAR_MAX_TIME);
    this->L3 = new Led(L3_PIN);
    this->gate = new ServoImpl(SERVO_PIN);
    this->lcd = new LCD(0x27, 16, 2);
    this->init();
    this->setState(TURN_ON_L3);
};

void CheckOutTask::tick()
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

void CheckOutTask::handleTurnOnL3()
{
    this->L3->switchOn();
    Serial.println("CheckOutTask::L3 turned on");
    this->lcd->write("Turn on L3", 0, 0);
    this->lcd->write("Proceed slowly!", 0, 1);
    this->setState(OPENS_GATE);
}

void CheckOutTask::handleOpensGate()
{
    this->gate->write(GATE_OPEN_POSITION);
    this->lcd->write("Open gate", 0, 2);
    Serial.println("CheckOutTask::Gate opened");
    this->setCompleted();
}