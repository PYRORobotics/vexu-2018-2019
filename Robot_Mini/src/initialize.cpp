#include "../include/main.h"


void printSerialTaskfn(void*)
{
	while(1)
	{
		serialRead(NULL);
		pros::lcd::print(0, "PRINT SERIAL IS ON");
		pros::lcd::print(1, "Heading (deg): %f", HEADING_RAW);
		pros::lcd::print(2, "ax (linear) (m/s): %f", ax);
		pros::lcd::print(3, "ay (linear) (m/s): %f", ay);
		pros::lcd::print(4, "az (linear) (m/s): %f", az);
		pros::delay(20);
	}
}

void telemetryTaskfn(void*)
{
	while(1)
	{
		pros::Motor LF(1, pros::E_MOTOR_GEARSET_18, 1, pros::E_MOTOR_ENCODER_DEGREES);
		pros::Motor LM(2, pros::E_MOTOR_GEARSET_18, 0, pros::E_MOTOR_ENCODER_DEGREES);
		pros::Motor LR(3, pros::E_MOTOR_GEARSET_18, 1, pros::E_MOTOR_ENCODER_DEGREES);
		pros::Motor RF(8, pros::E_MOTOR_GEARSET_18, 0, pros::E_MOTOR_ENCODER_DEGREES);
		pros::Motor RM(9, pros::E_MOTOR_GEARSET_18, 1, pros::E_MOTOR_ENCODER_DEGREES);
		pros::Motor RR(10, pros::E_MOTOR_GEARSET_18, 0, pros::E_MOTOR_ENCODER_DEGREES);



		double ECLF = LF.get_position();
		double ECLM = LM.get_position();
		double ECLR = LR.get_position();
		double ECRF = RF.get_position();
		double ECRM = RM.get_position();
		double ECRR = RR.get_position();

		double wheelbase = (12.007 + 11.4173)/2;

		double headingViaEncoders = (-ECLM + ECRM)/wheelbase;// / (2 * PI);
		PYROChassis::heading = headingViaEncoders;
		PYROChassis::ECL = ECLM;
		PYROChassis::ECR = ECRM;

		double dist = (-ECLM - ECRM)/2;
		double x = dist * sinf(PYROChassis::heading * PI/180);
		double y = dist * cosf(PYROChassis::heading * PI/180);

		PYROChassis::x += x;
		PYROChassis::y += y;

		//pros::lcd::print(1, "Heading: %f", PYROChassis::heading);
		//pros::lcd::print(2, "x: %f", PYROChassis::x);
		//pros::lcd::print(3, "y: %f", PYROChassis::y);


		LF.~Motor();
		LM.~Motor();
		LR.~Motor();
		RF.~Motor();
		RM.~Motor();
		RR.~Motor();

		pros::delay(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{

	//pros::lcd::initialize();
	//pros::lcd::set_text(1, "Hello PROS User!");
	serialInit();

	styleInit();
	screenInit();//

	//arm.resetPos();
	chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{34.5_in,0_in,0_deg}}, "1");

	pros::Task printSerialTask(printSerialTaskfn, 0);
	//pros::Task telemetryTask(telemetryTaskfn, 0);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled()
{
	chassis.MasterController.stop();
	intake.MainIntakePID.flipDisable(true);
	intake.PreFlywheelIntakePID.flipDisable(true);
	shooter.FlywheelPID.flipDisable(true);
	arm.ArmPID.flipDisable(true);
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize()
{
	//screenCompetitionInit();
	while(1)
	{
		std::cout << "BLUE" << "\n";
		pros::delay(20);
	}
}
