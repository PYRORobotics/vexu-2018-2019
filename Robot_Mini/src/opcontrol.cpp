#include "../include/main.h"

using namespace pros;

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
void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Motor l1(1,pros::E_MOTOR_GEARSET_06);
	pros::Motor l2(2,pros::E_MOTOR_GEARSET_06,1);
	pros::Motor l3(3,pros::E_MOTOR_GEARSET_06);
	pros::Motor r1(7,pros::E_MOTOR_GEARSET_06,1);
	pros::Motor r2(9,pros::E_MOTOR_GEARSET_06);
	pros::Motor r3(10,pros::E_MOTOR_GEARSET_06,1);
	pros::Motor intake(13,pros::E_MOTOR_GEARSET_06);
	pros::Motor arm(6, pros::E_MOTOR_GEARSET_36,1,MOTOR_ENCODER_DEGREES);
	pros::Motor flywheelf(4,pros::E_MOTOR_GEARSET_06);
	pros::Motor flywheelr(5,pros::E_MOTOR_GEARSET_06,1);
	pros::Motor preflywheel(14,pros::E_MOTOR_GEARSET_18,1);
	pros::Motor hood(11,pros::E_MOTOR_GEARSET_18,0,MOTOR_ENCODER_ROTATIONS);
	l1.set_brake_mode(MOTOR_BRAKE_COAST);
  l2.set_brake_mode(MOTOR_BRAKE_COAST);
  l3.set_brake_mode(MOTOR_BRAKE_COAST);
  r1.set_brake_mode(MOTOR_BRAKE_COAST);
  r2.set_brake_mode(MOTOR_BRAKE_COAST);
  r3.set_brake_mode(MOTOR_BRAKE_COAST);

	arm.set_brake_mode(MOTOR_BRAKE_HOLD);

	static int armMode = 0;
	static bool runIntake = false;
	//static bool reverseIntake = false;
	//static bool shootBall = false;
	static int shiftIntake = 0; //0 = neither (do whatever toggle position runIntake says to do), 1 = reverse intake, 2 = shoot balls
	static bool runFlywheel = false;
	static bool reverseFlywheel = false;
	const double armHighPresetAngle = 200;
	const double armGroundPresetAngle = 260;
	static int armPresetTolerance = 2;
	static double armPresetKP = 2.0;
//	const double armStartAngle = 0;	//FIXME
//	const double armEndAngle = 120;	//FIXME
	static double hoodAngleSetpoint = 0;
	static double hoodAngleCurr = 0;



	while(1)
	{
		int x = master.get_analog(ANALOG_LEFT_X);
		int y = master.get_analog(ANALOG_LEFT_Y);

	  double a = 0.50703533709;
	  double b = 0.00004992507;
	  double c = 7.44251597e-9;
	  double d = 1.5203616e-13;

	  double power = sqrt(x*x+y*y);

	  int motorCurvePower = power * 2;
	  int L = motorCurvePower * (x+127)/254;
	  int R = motorCurvePower * (127-x)/254;

	  if(y<0)
	  {
	    L*=-1;
	    R*=-1;
	  }

	  L = y + x;
	  R = y - x;

	  l1 = L;
	  l2 = L;
	  l3 = L;
	  r1 = R;
	  r2 = R;
	  r3 = R;

		// Just below horizontal position = 200
		// Ground hardstop = 245

		pros::lcd::print(1, "%f\n", arm.get_position());
		//std::cout<<master.get_analog(ANALOG_RIGHT_Y)<<" degrees\n";

		//Define armMode
		if (abs(master.get_analog(ANALOG_RIGHT_Y)) > 2)	//No preset in action
		{
			armMode = 0;
		}
		else if (master.get_digital(DIGITAL_L2))	//Ground preset
		{
			armMode = 1;
		}
		else if (master.get_digital(DIGITAL_L1))	//High preset
		{
			armMode = 2;
		}

		//Execute armMode
		if (armMode == 2)	//armMode = 2
		{
			if (abs(arm.get_position() - armHighPresetAngle) > armPresetTolerance)
			{
				arm = abs(armHighPresetAngle - arm.get_position())/(armHighPresetAngle - arm.get_position()) * 127;
			}
			else
			{
				armMode = 0;
			}
		}
		else if (armMode == 1) //armMode = 1
		{
			arm = (armGroundPresetAngle - arm.get_position()) * armPresetKP;
			/*if (abs(arm.get_position() - armGroundPresetAngle) > armPresetTolerance)
			{
				arm = (armGroundPresetAngle - arm.get_position()) * armPresetKP;
			}
			else
			{
				armMode = 0;
			}*/
		}
		else	//armMode = 0
		{
			if ((master.get_analog(ANALOG_RIGHT_Y)>0 && arm.get_position()<10) || (master.get_analog(ANALOG_RIGHT_Y)<0 && arm.get_position()>255))
			{
				arm = 0;	//Set limits
			}
			else
			{
				arm = -master.get_analog(ANALOG_RIGHT_Y);
			}
		}

		//Define hood angle
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_UP))
		{
			hoodAngleSetpoint = 54-36;	//shallow shot
		}
		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
		{
			hoodAngleSetpoint = 54-26;	//steep shot
		}

		//Execute movement to adjust hood angle
		pros::lcd::print(3, "Hood setpoint = %d\n", hoodAngleSetpoint);
		pros::lcd::print(4, "Hood angle = %f\n", -hood.get_position()* 14/201*360);
		pros::lcd::print(5, "Hood error = %f\n", hoodAngleSetpoint - hoodAngleCurr);
		pros::lcd::print(6, "Hood motor signal = %f\n", hood);

		hoodAngleCurr = (-1)*hood.get_position()* 14/201*360;
		/*if ((hoodAngleSetpoint - hoodAngleCurr) < 0)
		{
			hood = 40;
		}
		if ((hoodAngleSetpoint - hoodAngleCurr) > 0)
		{
			hood = -40;
		}
		else
		{
			hood = 0;
		}*/
		hood = abs(hoodAngleSetpoint - hoodAngleCurr)/(hoodAngleSetpoint - hoodAngleCurr) * (-30);
		/*if (1)//(abs(hood.get_position() - ) > 1)
		{
			if (abs(hood.get_position() - hoodAngleSetpoint) > 1)
			{
				hood = abs(hoodAngleSetpoint - hood.get_position())/(hoodAngleSetpoint - hood.get_position()) * 127;
			}
			else
			{
				hood = 0;
			}
		}
		else
		{
			hood = 0;
		}*/

		//SHOOTER USER INPUT
		if(master.get_digital_new_press(DIGITAL_A))	// PRESS A (toggle) to spin up flywheel
		{
			runFlywheel = !runFlywheel;
		}
		if(master.get_digital(DIGITAL_B))	// PRESS B (toggle) to reverse direction of flywheel
		{
			reverseFlywheel = true;	//It's safe to reverse the flywheel, and it will do so as long as the button is being held
		}
		else
		{
			reverseFlywheel = false;
		}
		//INTAKE USER INPUT
		/*if(master.get_digital(DIGITAL_B))	// HOLD B to shoot ball
		{
			pros::delay(10);
			if(master.get_digital(DIGITAL_B))	// Check if still holding
			shootBall = true;
		}
		else
		{
			shootBall = false;
		}*/

		if(master.get_digital_new_press(DIGITAL_X))	// PRESS X (toggle) to continuously collect balls
		{
			runIntake = !runIntake;
		}

		if(master.get_digital(DIGITAL_R1))	// HOLD R1 to shoot ball
		{
			shiftIntake = 2;
		}
		else if(master.get_digital(DIGITAL_R2))	// HOLD Y to reverse intake
		{
			shiftIntake = 1;
		}
		else	// Defaults to whatever toggle position collect balls (X) is in
		{
			shiftIntake = 0;
		}
		/*if(master.get_digital(DIGITAL_R2))	// HOLD R2 to reverse intake
		{
			if(!runIntake) runIntake = true;
			reverseIntake = true;
		}
		else
		{
			runIntake = false;
			reverseIntake = false;
		}*/

		//-------------------------------------------------------------------------
		// FLYWHEEL LOGIC
		if(runFlywheel)	// (3)
		{
			flywheelf.move_velocity(600);
			flywheelr.move_velocity(600);
		}
		else
		{
			if(reverseFlywheel)	// (5)
			{
				flywheelf.move_velocity(0);
				flywheelr.move_velocity(0);
				flywheelf = -80;
				flywheelr = -80;
			}
			else
			{
				flywheelf.move_velocity(0);
				flywheelr.move_velocity(0);
				flywheelf = 0;
				flywheelr = 0;
			}
		}
		//INTAKE LOGIC
		if(shiftIntake == 2)
		{
			intake = 127;
			preflywheel = 127;
		}
		else if(shiftIntake == 1)
		{
			intake = -127;
			preflywheel = -127;
		}
		else
		{
			if(runIntake)		// collect balls
			{
				intake = 127;
				preflywheel = -127;
			}
			else  //don't do anything
			{
				intake = 0;
				preflywheel = 0;
			}
		}
		/*if(shootBall)	// (4)
		{
			intake = 127;
			preflywheel = 127;
		}
		else if(runIntake)
		{
			if(!reverseIntake)	// (1)
			{
				intake = 127;
				preflywheel = -127;
			}
			else	// (2)
			{
				intake = -127;
				preflywheel = -127;
			}
		}
		else
		{
			intake = 0;
			preflywheel = 0;
		}*/

		pros::delay(10);
	}

	while (0)	// REVERT TO TRUE AND SET ABOVE WHILE LOOP TO FALSE TO USE THE FOLLOWING OLD (PRE-CALI) TELEOP CODE
	{

		int left = master.get_analog(ANALOG_LEFT_Y);
		int right = master.get_analog(ANALOG_RIGHT_Y);

		l1 = left;
		l2 = left;
		l3 = left;
		r1 = right;
		r2 = right;
		r3 = right;


		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
		{
			intake = 127;
		}
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
		{
			intake = -127;
			preflywheel = -127;
		}
		else intake = 0;
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
		arm = 80;
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
		arm = -80;
		else arm = 0;

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_A))
		{
			flywheelf.move_velocity(600);
			flywheelr.move_velocity(600);
			preflywheel = 127;
		}
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_B))
		{
			flywheelf.move_velocity(0);
			flywheelr.move_velocity(0);
			preflywheel = 0;
		}

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_UP))
		{
			hood = -50;
		}
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
		{
			hood = 50;
		}
		else hood = 0;
		pros::lcd::print(2, "%f degree hood angle", 54 + hood.get_position() * 14/201*360); //26.5 deg from behind platf to high flag
		pros::delay(10);
	}
}
