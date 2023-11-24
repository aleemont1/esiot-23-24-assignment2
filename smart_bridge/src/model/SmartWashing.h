#ifndef __SMARTWASHING__
#define __SMARTWASHING__

#include <Arduino.h>

/**
 * @class SmartWashing
 * @brief This class encapsulates the functionality of the SmartWashing system.
 *
 * The SmartWashing system is a state machine with various states representing different stages of the washing process.
 * Each state represents a specific stage in the washing process or a specific condition of the system.
 *
 * @note This class is currently under development and only created for testing purposes.
 */

class SmartWashing
{

private:
    // The current state of the system
    enum
    {
        SLEEP,
        WAITING,
        CHECK_IN,
        TRANSIT,
        WAIT_FOR_CLICK,
        WASHING,
        CRITICAL_TEMP,
        WASHING_DONE,
        CHECK_OUT,
        ERROR
    } state;
};

#endif // __SMARTWASHING__