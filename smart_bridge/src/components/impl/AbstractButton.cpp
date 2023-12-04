#include "../api/AbstractButton.h"

AbstractButton::AbstractButton(){}

void AbstractButton::updateSyncTime(long time)
{
    lastTimeSync = time;
}

long AbstractButton::getLastSyncTime()
{
    return lastTimeSync;
}