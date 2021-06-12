/*
 * Trajectory.cpp
 *
 * Created on : 8 avril 2018
 * Author : Maxime
 */

#include "navigator.h"

#include "params.h"
#include "odometry.h"
#include "motorControl.h"
#include "math.h"
#include "utils.h"



Navigator navigator = Navigator();

Navigator::Navigator(){
	turn_done = false;
	displacement_done = false;
	trajectory_done = false;
	x_target = 0;
	y_target = 0;
	theta_target = 0;
	move_type = TURN;
	move_state = STOPPED;
}

void Navigator::move_to(float x, float y){
	odometry_motor.set_pos(odometry_wheel.get_pos_x(), odometry_wheel.get_pos_y(), odometry_wheel.get_pos_theta());
	SerialCtrl.println("odometry motor reset to odometry wheel position !");
	x_target = x;
	y_target = y;
	move_type = DISPLACEMENT;
	move_state = INITIAL_TURN;
	trajectory_done = false;
	SerialDebug.print("moving_to : ");
	SerialDebug.print(x_target);
	SerialDebug.print("\t");
	SerialDebug.println(y_target);
}//aa

void Navigator::move(float v, float omega){
	v_target = clamp(-SPEED_MAX, SPEED_MAX, v);
	omega_target = clamp(-OMEGA_MAX, OMEGA_MAX, omega);
	move_type = DISPLACEMENT;
	move_state = VELOCITY;
	trajectory_done = true;
	SerialDebug.print("velocity movement: ");
	SerialDebug.print(v_target);
	SerialDebug.print("\t");
	SerialDebug.println(omega_target);
}

void Navigator::step_forward(float d){
	move_to(d*cos(odometry_motor.get_pos_theta()) + odometry_motor.get_pos_x(),d*sin(odometry_motor.get_pos_theta()) + odometry_motor.get_pos_y());
}

void Navigator::step_backward(float d){
	move_to(-d*cos(odometry_motor.get_pos_theta()) + odometry_motor.get_pos_x(),-d*sin(odometry_motor.get_pos_theta()) + odometry_motor.get_pos_y());
}


void Navigator::turn_to(float theta){ // En degrés
	theta_target = center_radian(PI*theta/180);

	/*SerialDebug.print("Angle: ");
	SerialDebug.println(odometry_motor.get_pos_theta());
	SerialDebug.print("moving_to : ");
	SerialDebug.print(theta_target);
	SerialDebug.print(" ( <  ");
	SerialDebug.println(theta);*/

	move_type = TURN;
	move_state = INITIAL_TURN;
	trajectory_done = false;
}

void Navigator::throw_to(float x, float y, float theta){
	x_target = x;
	y_target = y;
	theta_target = theta;
	move_type = THROW;
	move_state = CRUISE;
	trajectory_done = false;
	/*SerialDebug.print("throwing_to : ");
	SerialDebug.print(x_target);
	SerialDebug.print("\t");
	SerialDebug.println(y_target);*/
}

float Navigator::compute_cons_speed()
{
	float speed_cons, dist_fore, t_stop, dist_objective;
	int sgn,MAX_ACCEL;

	if(move_type == THROW){
		MAX_ACCEL = ACCEL_MAX_THROW;
	}
	else{
		MAX_ACCEL = ACCEL_MAX;
	}
	sgn = scalaire(cos(odometry_motor.get_pos_theta()),sin(odometry_motor.get_pos_theta()),x_target - odometry_motor.get_pos_x(),y_target - odometry_motor.get_pos_y());

	/*SerialDebug.print("Sens d'avancée:");
	SerialDebug.print("\t");
	SerialDebug.println(sgn);*/

	//Test de décélération (on suppose l'accélération minimale et on intègre deux fois)
	t_stop = odometry_motor.get_speed()/MAX_ACCEL;
	dist_fore = (odometry_motor.get_speed()*t_stop-1/2*MAX_ACCEL*pow(t_stop,2));
	/*dist_fore = odometry_motor.get_speed()*t_stop;*/

	dist_objective = sqrt(pow(x_target - odometry_motor.get_pos_x(),2) + pow(y_target - odometry_motor.get_pos_y(),2));

	//Si le point estimé est suffisamment proche du point voulu, on décélére, sinon on accélére jusqu'à la vitesse maximale.
	if(abs( dist_fore - dist_objective ) < ADMITTED_POSITION_ERROR){
		speed_cons = sgn*max(0,-MAX_ACCEL*NAVIGATOR_PERIOD + abs(odometry_motor.get_speed()));
	}
	else{
		if(dist_fore - dist_objective > 0){
			speed_cons = sgn*max(0,abs(odometry_motor.get_speed()) - MAX_ACCEL*NAVIGATOR_PERIOD);
		}
		else{
			speed_cons = sgn*min(SPEED_MAX,abs(odometry_motor.get_speed()) + MAX_ACCEL*NAVIGATOR_PERIOD);
		}
	} /*
	SerialDebug.print("Distances estimées");
	SerialDebug.print("\t");
	SerialDebug.print(dist_fore - dist_objective);
	SerialDebug.print("\t");
	SerialDebug.print(dist_objective);
	SerialDebug.print("speed cons : ");
	SerialDebug.print(speed_cons);
	SerialDebug.print("\tspeed= ");
	SerialDebug.println(odometry_motor.get_speed()); */
	return speed_cons;
}


float Navigator::compute_cons_omega()
{
	float omega_cons, angle_fore, alpha, t_rotation_stop;
	int sgn;

	if(move_type == DISPLACEMENT){
		alpha = odometry_motor.get_pos_theta() + center_axes(atan2((-y_target+odometry_motor.get_pos_y()),(-x_target+odometry_motor.get_pos_x())) - odometry_motor.get_pos_theta());
	}
	else{
		alpha = theta_target;
	}

	if (center_radian(alpha - odometry_motor.get_pos_theta()) > 0){
		sgn = 1;
	}
	else{
		sgn = -1;
	}
	t_rotation_stop = abs(odometry_motor.get_omega())/ACCEL_OMEGA_MAX;
	angle_fore = center_radian(odometry_motor.get_pos_theta() + sgn*(abs(odometry_motor.get_omega())*t_rotation_stop -1/2*ACCEL_OMEGA_MAX*pow(t_rotation_stop,2)));
	if(abs(center_radian(angle_fore - alpha)) < ADMITTED_ANGLE_ERROR){
		omega_cons = sgn*max(0,abs(odometry_motor.get_omega()) - NAVIGATOR_PERIOD*ACCEL_OMEGA_MAX);
	}
	else{
		if(sgn*(center_radian(alpha - angle_fore)) > 0){
			omega_cons = sgn*min(OMEGA_MAX, NAVIGATOR_PERIOD*ACCEL_OMEGA_MAX + abs(odometry_motor.get_omega()));
		}
		else{
			omega_cons = sgn*max(0,abs(odometry_motor.get_omega()) - NAVIGATOR_PERIOD*ACCEL_OMEGA_MAX);
		}
	} /*
	SerialDebug.print("Consigne angle:");
	SerialDebug.print(omega_cons);
	SerialDebug.print("\t");
	SerialDebug.print("Alpha:");
	SerialDebug.print(alpha);
	SerialDebug.print("\t");
	SerialDebug.print("angle_fore:");
	SerialDebug.println(angle_fore);
*/
	return omega_cons;
}

void Navigator::update(){
	float omega_cons,speed_cons,alpha,distance;

	if(move_type == BRAKE){
		int sgn = scalaire(cos(odometry_motor.get_pos_theta()),sin(odometry_motor.get_pos_theta()),x_target - odometry_motor.get_pos_x(),y_target - odometry_motor.get_pos_y());
		speed_cons = sgn*max(0,abs(odometry_motor.get_speed()) - EMERGENCY_BRAKE*NAVIGATOR_PERIOD);
		if(abs(odometry_motor.get_speed()) < ADMITTED_SPEED_ERROR){
			move_state = STOPPED;
			speed_cons = 0;
		}
		MotorControl::set_cons(speed_cons,0);
	}
	else{
		switch(move_state){
		case INITIAL_TURN:

			if(move_type==DISPLACEMENT){
				alpha = odometry_motor.get_pos_theta() + center_axes(atan2((-y_target+odometry_motor.get_pos_y()),(-x_target+odometry_motor.get_pos_x())) - odometry_motor.get_pos_theta());
			}
			else{
				alpha = theta_target;
			}
			turn_done = ((abs(center_radian(odometry_motor.get_pos_theta() - alpha)) < ADMITTED_ANGLE_ERROR)&&(odometry_motor.get_omega() < ADMITTED_OMEGA_ERROR));

			if(turn_done){

				MotorControl::set_cons(0,0);
				switch(move_type){
				case TURN:
					move_state = STOPPED;
					trajectory_done = true;
					break;
				case DISPLACEMENT:
					move_state = CRUISE;
					break;
				case THROW:
					//Do nothing
					break;
				case BRAKE:
					//Do nothing
					break;
				}
				break;
			}

			omega_cons = compute_cons_omega();
			MotorControl::set_cons(0,omega_cons);

			break;
		case CRUISE:
			distance = sqrt(pow(x_target - odometry_motor.get_pos_x(),2) + pow(y_target - odometry_motor.get_pos_y(),2));
			displacement_done = ((distance<ADMITTED_POSITION_ERROR)&&(odometry_motor.get_speed() < ADMITTED_SPEED_ERROR));
			if(displacement_done){
				MotorControl::set_cons(0,0);
				move_state=STOPPED;
				trajectory_done = true;
				break;
			}

			speed_cons=compute_cons_speed();
			omega_cons = compute_cons_omega();
			Serial.println("cruise mode : ");
			Serial.print("\t speed_cons :  ");
			Serial.print(speed_cons);
			Serial.print("\t omega_cons :  ");
			Serial.print(omega_cons);
			Serial.print("\t distance :  ");
			Serial.print(distance);
			Serial.println("***");
			MotorControl::set_cons(speed_cons,omega_cons);
			break;
		case STOPPED:
			//do nothing
			break;
		case VELOCITY:
			MotorControl::set_cons(v_target,omega_target);
			break;
		}
	}
}
//void recalibrate_x_with_wall(float x, float real_x)
//{
	// on donne un x target assez loin en avant
	//Si on patine -> on reset, sinon on continue
	/*
		float error_speed = MotorControl::get_cons_speed() - odometry_motor.get_speed();
		while(abs(prev_pos_x-odometry_motor.get_pos_x()) >= 0.00001f)
		{
			set_cons(0.05f, 0f); //verifier ce que fait le omega
		}
		set cons(0f, 0f);
		if(abs(error_speed) >= 0.00001f)
		{
			return; //false, still slowing down
		}
		odometry_motor.set_pos(real_x, odometry_motor.get_pos_y(), odometry_motor.get_pos_theta());
*/
//}

void Navigator::forceStop(){
	move_type = BRAKE;
}

bool Navigator::moveForward(){
	int dir = scalaire(cos(odometry_motor.get_pos_theta()),sin(odometry_motor.get_pos_theta()),x_target - odometry_motor.get_pos_x(),y_target - odometry_motor.get_pos_y());
	if(dir>0){
		return true;
	}
	else{
		return false;
	}
}


float Navigator::center_axes(float angle)
{
	/*SerialDebug.print("center radian:");
		SerialDebug.print("\t");
		SerialDebug.print(angle);
		SerialDebug.print("\t");*/
	if (abs(angle) > PI){
		if(angle<0){
			while(abs(angle)>PI){
				angle+=PI*2;
			}
		}
		else{
			while(abs(angle)>PI){
				angle-=2*PI;
			}
		}
	}
	if(abs(angle+PI) + ADMITTED_ANGLE_ERROR < abs(angle)){
		angle+=PI;
	}
	if(abs(angle-PI) + ADMITTED_ANGLE_ERROR< abs(angle)){
		angle-=PI;
	}
	/*SerialDebug.println(angle);*/
	return angle;
}

float Navigator::center_radian(float angle)
{
	if (abs(angle) > PI){
		if(angle<0){
			while(abs(angle)>PI){
				angle+=PI*2;
			}
		}
		else{
			while(abs(angle)>PI){
				angle-=2*PI;
			}
		}
	}
	return angle;
}


int Navigator::scalaire(float x,float y,float x2,float y2){
	if(x*x2 + y*y2>0){
		return 1;
	}
	else{
		return -1;
	}
}

bool Navigator::isTrajectoryFinished(){
	return trajectory_done;
}
