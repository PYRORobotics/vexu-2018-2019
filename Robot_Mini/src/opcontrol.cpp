#include "../include/main.h"



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
	pros::Motor arm(6, pros::E_MOTOR_GEARSET_36,0,MOTOR_ENCODER_DEGREES);
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

	static bool runIntake = false;
	static bool reverseIntake = false;
	static bool shootBall = false;
	static bool runFlywheel = false;
	static bool reverseFlywheel = false;
	const double armStartAngle = 0;	//FIXME
	const double armEndAngle = 120;	//FIXME


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

		if(arm.get_position() < armStartAngle + 20 || arm.get_position() > armEndAngle - 20) //FIXME // Sees if in expansion zone
		{
			if(master.get_digital(DIGITAL_Y))	// Controller override for inside exp. zone
			{
				if(master.get_digital(DIGITAL_L1))
					arm = 127;
				else if(master.get_digital(DIGITAL_L2))
					arm = -127;
				else
					arm = 0;
			}
		}
		else
		{
			if(master.get_digital(DIGITAL_L1))
				arm = 127;
			else if(master.get_digital(DIGITAL_L2))
				arm = -127;
			else
				arm = 0;
		}


		if(master.get_digital_new_press(DIGITAL_A))	// PRESS A (toggle) to run intake
		{
			runIntake = !runIntake;
		}
		if(master.get_digital(DIGITAL_Y))	// HOLD Y to reverse intake
		{
			if(!runIntake) runIntake = true;
			reverseIntake = true;
		}
		else
		{
			runIntake = false;
			reverseIntake = false;
		}
		if(master.get_digital_new_press(DIGITAL_B))	// PRESS B (toggle) to spin up flywheel
		{
			runFlywheel = !runFlywheel;
		}
		if(master.get_digital_new_press(DIGITAL_X))	// PRESS X (toggle) to reverse direction
		{
			reverseFlywheel = true;
		}
		if(master.get_digital(DIGITAL_B))	// HOLD B to shoot ball
		{
			pros::delay(10);
			if(master.get_digital(DIGITAL_B))	// Check if still holding
			shootBall = true;
		}
		else
		{
			shootBall = false;
		}
		if(master.get_digital(DIGITAL_R1))	// HOLD R1 to shoot ball
		{
			shootBall = true;
		}
		else
		{
			shootBall = false;
		}


		if(runFlywheel)
		{
			if(!reverseFlywheel)	// (5)
			{
				flywheelf.move_velocity(600);
				flywheelr.move_velocity(600);
			}
			else	// (3)
			{
				flywheelf.move_velocity(0);
				flywheelr.move_velocity(0);

				flywheelf = -80;
				flywheelr = -80;
			}
		}
		else
		{
			flywheelf.move_velocity(0);
			flywheelr.move_velocity(0);
		}

		if(shootBall)	// (4)
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
		}

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
