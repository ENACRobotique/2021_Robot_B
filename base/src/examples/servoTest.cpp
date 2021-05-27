#include "servoTest.h"
#include "../params.h"

void servoTest::update() {
    ActuatorSupervisor::otherServos[0].moveServo(SERVO_PAV_ANGLE_RTRCTED);
    delay(1000);
    ActuatorSupervisor::otherServos[0].moveServo(SERVO_PAV_ANGLE_DPLOYED);
    delay(3000);

    /*
        if(TestTime.check())
    {
      MotorControl::set_cons(0.f,sp[i]);
      i = (i+1) % 4;
    }  */
    /*
		if (TestTime.check())
    {
		  mot2=(mot2+20)%255;
    }
    */
}
