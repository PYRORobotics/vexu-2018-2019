#include "../include/main.h"
//#include "../../Shared/shared.hpp"


//using namespace pros::literals;
double kp = 0.9;
double kd = 0.9;
double p;
int motorsignal;
double pidDerivative;
double pidLastError = 90;

void motorTestPIDSerial()
{
	p = 90 - heading;

	pidDerivative = p - pidLastError;
  pidLastError  = p;


	motorsignal = p * kp + pidDerivative * kd;
	M_Drivetrain_LF = motorsignal;
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol()
{
	Screen Screen;
	//Controller0 = Controller0Base;
	//taskSerialRead().resume();
	while (1)
	{
		while(!pros::competition::is_connected())	// FIX ME!!!
		{
			//M_Drivetrain_LF.move_absolute(90, 60);
			motorTestPIDSerial();
			//Screen.write();
			printSerial();
			// Do teleop stuff
			//Controller0.tankDrive();
			//Robot_Mini.tankDrive();
			//Motor ml(1,false);
			//Motor mr(4,true);
			//ml = Controller0Base.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
			//mr = Controller0Base.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
			//pros::lcd::print(0, "Controller: %d", Controller0Base.get_analog(E_CONTROLLER_ANALOG_LEFT_Y));
			pros::delay(20);
		}
		pros::lcd::print(0, "NOT CONNECTED TO FIELD CONTROLLER!");
		pros::delay(20);
	}
	//taskSerialRead().suspend();
}
