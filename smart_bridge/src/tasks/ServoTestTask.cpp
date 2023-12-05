// #include "ServoTestTask.h"

// void ServoTestTask::tick()
// {
//     Serial.println(F("ServoTestTask::tick()"));
//     switch (this->getState())
//     {
//     case OPEN:
//         Serial.println(F("ServoTestTask::OPEN"));
//         this->servo.writeMicroseconds(1500);
//         this->setState(CLOSE);
//         break;
//     case CLOSE:
//         // if (this->elapsedTime() >= 1000)
//         {
//             Serial.println(F("ServoTestTask::CLOSE"));
//             this->servo.writeMicroseconds(0);
//             this->setState(OPEN);
//         }
//         break;
//     }
// }