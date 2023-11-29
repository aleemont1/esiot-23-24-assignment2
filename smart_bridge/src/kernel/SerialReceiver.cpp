#include "SerialReceiver.h"

bool SerialReceiver::readData() {

    if (Serial.available() > 0) { //if some data has been received
        String data = Serial.readString(); 
        data.trim();
        if (data=="mnt:done") {
            Serial.println("Arduino received message: " + data);
            return true;
        }
    }
    return false;
}