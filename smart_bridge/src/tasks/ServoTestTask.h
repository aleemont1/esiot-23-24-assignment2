// #ifndef __SERVO_TEST_TASK__
// #define __SERVO_TEST_TASK__

// #include "kernel/TaskWithState.h"
// #include "config/config.h"
// #include <Servo.h>

// class ServoTestTask : public TaskWithState
// {
// public:
//     ServoTestTask() : TaskWithState()
//     {
//         // this->servo = new Servo();
//         this->servo.detach();
//         Serial.println("Servo::attach" + String(this->servo.attach(SERVO_PIN)));
//         this->init(1000); // Periodic task, executed every 1000ms
//         this->setActive(true);
//         this->setState(OPEN);
//     }

//     void tick() override;

// private:
//     Servo servo;
//     enum state
//     {
//         OPEN,
//         CLOSE
//     };
// };
// #endif