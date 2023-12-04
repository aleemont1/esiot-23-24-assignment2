#ifndef __SERIALRECEIVER__
#define __SERIALRECEIVER__

#include "Arduino.h"

/**
 * @class SerialReceiver
 */
class SerialReceiver
{

public:
    /**
     * @brief Default constructor. Initializes the class. It could be be instanziated when the arduino goes in error state.
     * in this way it waits for message from GUI.
     */
    SerialReceiver()
    {
       
    }

    /**
     * @brief ReadData from serial 
     * @return true if the read message is equal to "mnt:done" coincident with the "Maitanance done" 
     * @return false otherwise
     */
    bool readData();

    /**
     * @brief Simulate the read data from serial in the case of error state
     * 
     */
    void simulateReadData();
private:
    int status=ACTIVE;
    enum statuses{ACTIVE, INACTIVE};
    bool simulateDataReceived = false;

};

#endif
