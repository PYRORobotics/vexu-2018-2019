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
	pros::Controller partner(pros::E_CONTROLLER_PARTNER);
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
	intake.set_brake_mode(MOTOR_BRAKE_BRAKE);
	preflywheel.set_brake_mode(MOTOR_BRAKE_BRAKE);
	arm.set_brake_mode(MOTOR_BRAKE_HOLD);

	static int actionShootSequence = 0;	//0 = off
	static double preflyPosInit = 0;
	static double preflyPosSet = 0;
	static int intakeSignal = 0;
	static int preflywheelSignal = 0;
	static double hoodAngleHigh = 34;
	static double hoodAngleMid = 23;
	static double hoodAngleCurr = 34;

	static int armSignal = 0;
	static int armMode = 0;
	const double armHighPresetAngle = -200;
	const double armGroundPresetAngle = -245;
	static int armPresetTolerance = 2;
	static double armPresetKP = 2.0;
	static int armPresetIterationCurr = 0;
	static int armPresetIterationEnd = 100;
	//const double armStartAngle = 0;	//FIXME
	//const double armEndAngle = 120;	//FIXME
	//static bool runIntake = false;
	//static bool reverseIntake = false;
	//static bool shootBall = false;
	//static int shiftIntake = 0; //0 = neither (do whatever toggle position runIntake says to do), 1 = reverse intake, 2 = shoot balls
	static bool runFlywheel = false;
	static bool reverseFlywheel = false;
	//static double hoodAngleSetpoint = 0;
	//static double hoodAngleCurr = 0;



	while(1)
	{
		// Spline controller motor curve coefficients:
		double speedL = master.get_analog(ANALOG_LEFT_Y);
		double speedR = master.get_analog(ANALOG_RIGHT_Y);
	  double a = 0.50703533709;
	  double b = 0.00004992507;
	  double c = 7.44251597e-9;
	  double d = 1.5203616e-13;
	  int motorCurveL = a * speedL - b * speedL*speedL*speedL + c * speedL*speedL*speedL*speedL*speedL - d * speedL*speedL*speedL*speedL*speedL*speedL*speedL;
	  int motorCurveR = a * speedR - b * speedR*speedR*speedR + c * speedR*speedR*speedR*speedR*speedR - d * speedR*speedR*speedR*speedR*speedR*speedR*speedR;

		l1 = motorCurveL;
	  l2 = motorCurveL;
	  l3 = motorCurveL;
	  r1 = motorCurveR;
	  r2 = motorCurveR;
	  r3 = motorCurveR;

		/*
		//ARCADE DRIVE
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
	  r3 = R;*/

		//BALL INTAKE CONTROL
		if (master.get_digital(DIGITAL_R1))	// Collect balls (hold)
		{
			// Forward intake, Backwards preflywheel
			intakeSignal = 120;
			preflywheelSignal = -120;
			actionShootSequence = 0;
		}
		else if (master.get_digital(DIGITAL_L1))
		{
			// Backwards intake, Backwards preflywheel
			intakeSignal = -120;
			preflywheelSignal = -120;
			actionShootSequence = 0;
		}
		else if (actionShootSequence == 0)
		{
			intakeSignal = 0;
			preflywheelSignal = 0;
		}

		if (master.get_digital_new_press(DIGITAL_R2))	// Shoot ball auto sequence activation
		{
			if (actionShootSequence == 0)
			{
				actionShootSequence = 1;
			}
			else
			{
				actionShootSequence = 0;
			}
		}

		if (actionShootSequence != 0)			// Shoot ball auto sequence
		{
			if (actionShootSequence == 1)
			{
				//read current preflywheel encoder value. preflywheel ratio = 3:1. assign preflywheel forward signal
				preflyPosInit = preflywheel.get_position();
				preflyPosSet = preflyPosInit + 1;
				preflywheelSignal = 120;
				actionShootSequence = 2;
			}
			else if (actionShootSequence == 2)
			{
				//turn preflywheel a certain amount of rotations
				if (preflywheel.get_position() >= preflyPosSet)	// if preflywheel has finished turning a certain amount of rotations move on to the next task
				{
					if (hoodAngleCurr == hoodAngleMid)
					{
						hoodAngleCurr = hoodAngleHigh;
					}
					else if (hoodAngleCurr == hoodAngleHigh)
					{
						hoodAngleCurr = hoodAngleMid;
					}
					preflyPosInit = preflywheel.get_position();
					preflyPosSet = preflyPosInit - 1;
					actionShootSequence = 3;
				}
			}
			else if (actionShootSequence == 3)
			{
				//intake is collecting balls and won't stop until time is reached
				intakeSignal = 120;
				preflywheelSignal = -120;
				if (preflywheel.get_position() <= preflyPosSet)
				{
					intakeSignal = 0;
					preflywheelSignal = 0;
					actionShootSequence = 0;
				}
			}
		}

		intake = intakeSignal;
		preflywheel = preflywheelSignal;

		//HOOD CONTROL
		if (partner.get_digital(DIGITAL_UP))
		{
			hoodAngleCurr = hoodAngleHigh;
		}
		else if (partner.get_digital(DIGITAL_DOWN))
		{
			hoodAngleCurr = hoodAngleMid;
		}
		hood.move_absolute((-1)*(54-hoodAngleCurr)*201/14/360,120);

		//SHOOTER CONTROL
		if(partner.get_digital(DIGITAL_R1))	// PRESS A to turn flywheel ON
		{
			runFlywheel = 1;
		}
		else if(partner.get_digital(DIGITAL_R2))	// PRESS B to turn flywheel ON
		{
			runFlywheel = 0;
		}
		if(partner.get_digital(DIGITAL_X))	// PRESS X (hold) to reverse direction of flywheel
		{
			reverseFlywheel = true;	//Reverse only if it is safe to reverse the flywheel, and it will do so as long as the button is being held
		}
		else
		{
			reverseFlywheel = false;
		}

		if(runFlywheel)	//Shooter logic
		{
			flywheelf.move_velocity(600);
			flywheelr.move_velocity(600);
		}
		else
		{
			if(reverseFlywheel)
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

		//ARM (DONGER) CONTROL
		pros::lcd::print(0, "Arm Position = %f\n", arm.get_position());

		armSignal = partner.get_analog(ANALOG_LEFT_Y);
		if (arm.get_position() > armHighPresetAngle && armSignal > 0 && !partner.get_digital(DIGITAL_L1))
		{
			armSignal = 0;
		}
		if ((partner.get_analog(ANALOG_LEFT_Y)>0 && arm.get_position()>-10) || (partner.get_analog(ANALOG_LEFT_Y)<0 && arm.get_position()<armGroundPresetAngle))
		{
			armSignal = 0;	//Set limits
		}

		/*
		//Define armMode
		if (abs(partner.get_analog(ANALOG_LEFT_Y)) > 2)	//No preset in action
		{
			armMode = 0;
		}
		else if (partner.get_digital_new_press(DIGITAL_L2))	//Ground preset
		{
			armPresetIterationCurr = 0;
			armMode = 1;
		}
		else if (partner.get_digital_new_press(DIGITAL_L1))	//High preset
		{
			armPresetIterationCurr = 0;
			armMode = 2;
		}

		//Execute armMode
		if (armMode == 2)	//armMode = 2
		{
			if (abs(arm.get_position() - armHighPresetAngle) > armPresetTolerance && armPresetIterationCurr < armPresetIterationEnd)
			{
				armSignal = abs(armHighPresetAngle - arm.get_position())/(armHighPresetAngle - arm.get_position()) * 120;
				armPresetIterationCurr++;
			}
			else
			{
				armMode = 0;
			}
		}
		else if (armMode == 1) //armMode = 1
		{
			if (abs(arm.get_position() - armHighPresetAngle) > armPresetTolerance && armPresetIterationCurr < armPresetIterationEnd)
			{
				armSignal = (armGroundPresetAngle - arm.get_position()) * armPresetKP;
				armPresetIterationCurr++;
			}
			else
			{
				armMode = 0;
			}
		}
		else	//armMode = 0
		{
			if ((partner.get_analog(ANALOG_LEFT_Y)>0 && arm.get_position()>-10) || (partner.get_analog(ANALOG_LEFT_Y)<0 && arm.get_position()<-255))
			{
				armSignal = 0;	//Set limits
			}
			else
			{
				armSignal = partner.get_analog(ANALOG_LEFT_Y);
			}
		}*/

		arm = armSignal;

		/*
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

		hood = abs(hoodAngleSetpoint - hoodAngleCurr)/(hoodAngleSetpoint - hoodAngleCurr) * (-30);

		//SHOOTER CONTROL
		if(master.get_digital(DIGITAL_A))	// PRESS A (toggle) to spin up flywheel
		{
			runFlywheel = 1;
		}
		else if(master.get_digital(DIGITAL_B))
		{
			runFlywheel = 0;
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

		*/
		//-------------------------------------------------------------------------
		/*
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
		}*/
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
