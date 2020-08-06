#include "../include/main.h"

void init_objects()
{
	const okapi::MotorGroup MG_Drivetrain_Left = {15,14,13};
	const okapi::MotorGroup MG_Drivetrain_Right = {-20,-18,-19};
	const okapi::QLength WHEEL_DIAMETER = 3.95_in;
	const okapi::QLength CHASSIS_WIDTH = 16.5_in;//13.9_in;//14.19_in;//13.625_in;
	const okapi::AbstractMotor::GearsetRatioPair ratio = okapi::AbstractMotor::gearset::green;// * (1.0382);

	okapi::ChassisControllerPID MasterController1 = ChassisControllerFactory::create(
	    MG_Drivetrain_Left, MG_Drivetrain_Right,
	    //IterativePosPIDController::Gains{0.001, 0.0008, 0.0005},   //straight
	    //IterativePosPIDController::Gains{0.01, 0.08, 0.00009},    //correct drift
	    //IterativePosPIDController::Gains{0.0045, 0.005, 0.00008},  //turn

	    IterativePosPIDController::Gains{0.00001, 0.00001, 0.000006},   //straight
	    IterativePosPIDController::Gains{0.000, 0.0, 0.0000},    //correct drift
	    IterativePosPIDController::Gains{0.001, 0.00001, 0.00000},  //turn

	    //IterativePosPIDController::Gains{0.05, 0.000, 0.000},   //straight
	    //IterativePosPIDController::Gains{0.0, 0.0, 0.0000},    //correct drift
	    //IterativePosPIDController::Gains{0.00, 0.00, 0.0000},  //turn
	    ratio,
	    {WHEEL_DIAMETER, CHASSIS_WIDTH}
	  );

		okapi::AsyncMotionProfileController MotionController = AsyncControllerFactory::motionProfile(
		    10.0,  // Maximum linear velocity of the Chassis in m/s
		    0.5,  // Maximum linear acceleration of the Chassis in m/s/s
		    10.0, // Maximum linear jerk of the Chassis in m/s/s/s
		    MasterController // Chassis Controller
		  );
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{

	pros::lcd::initialize();
	//pros::lcd::set_text(1, "Hello PROS User!");
	serialInit();

	styleInit();
	screenInit();//


}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled()
{
	//chassis.MasterController.stop();
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
}
