#include "ExitTransitTask.h"

void ExitTransitTask::tick()
{
    if (this->getDependency(0) != nullptr)
    {
        if (this->getDependency(0)->isCompleted())
        {
            switch (this->getState())
            {

            case TURN_ON_L3:
                this->L3->switchOn();
                this->setState(OPENS_GATE);
                break;

            case OPENS_GATE:
                this->gate->write(GATE_OPEN_POSITION);
                this->setState(READING_DISTANCE);
                break;

            case READING_DISTANCE:
                this->distance = sonar->detectDistance();
                Serial.println("ExitTransitTask::Distance: " + String(this->distance));
                this->setState(CHECKING_DISTANCE);
                break;

            case CHECKING_DISTANCE:
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
                break;

            case CLOSES_GATE:
                this->gate->write(GATE_CLOSE_POSITION);
                this->setState(SWITCH_OFF_L3);
                break;

            case SWITCH_OFF_L3:
                this->L3->switchOff();
                this->setCompleted();
                break;
            }
        }
    }
}