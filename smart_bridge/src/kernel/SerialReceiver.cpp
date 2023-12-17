#include "SerialReceiver.h"

bool SerialReceiver::readData() {

    // if (this->simulateDataReceived) {
    //     this->simulateDataReceived = false;
    //     return true;
    // }

    if (Serial.available() > 0) { //if some data has been received
        String data = Serial.readString(); 
        data.trim();
        if (data=="mnt:done") {
            // Serial.println(F("Arduino received message: " + data);
            return true;
        }
    }
    return false;
}

void SerialReceiver::simulateReadData() {
    this->simulateDataReceived = true;
    // Serial.println(F("Arduino received message: simulates mnt:done"));
}