#include "servoTest.h"
#include "../params.h"

void servoTest::update() {
    ActuatorSupervisor::otherServos[0].moveServo(SERVO_PAV_ANGLE_RTRCTED);
    delay(1000);
    ActuatorSupervisor::otherServos[0].moveServo(SERVO_PAV_ANGLE_DPLOYED);
    delay(3000);
}
