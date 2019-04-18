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

	//styleInit();
	//screenInit();//

	arm.resetPos();

	pros::Task printSerialTask(printSerialTaskfn, 0);
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
