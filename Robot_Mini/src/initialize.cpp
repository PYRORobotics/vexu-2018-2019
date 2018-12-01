#include "../include/main.h"
//#include "../../Shared/shared.hpp"



/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
	pros::lcd::initialize();
	//Setup the serial comms
	serialInit();
	//taskSerialRead().resume();
	//while can't connect -> throw error (LEDs?/screen write) and block program from exiting init()
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled()
{
	//Send serial command to Pi to stop sending data packets

	//Stop serial read task
	//taskSerialRead().suspend();
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
	//Send serial command to Pi to start sending data packets (Task?)
	//taskSerialRead().resume();
	//Auto selector on the LCD (while loop?)
	autoSelection = 1;
}
