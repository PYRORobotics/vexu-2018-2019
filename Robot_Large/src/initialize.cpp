#include "../include/main.h"


/*
 * FILE DESCRIPTION
 * init.cpp defines the functions and tasks related
 * to the robot's boot sequence and code to run pre-match.
 */

/**
 * Below are tasks to be run immediately at boot (in initialize() ).
 */

 void SerialReadTask(void* param)
 {
   while(1)
   {
     serialRead(NULL);
     delay(10);
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
	//Task ReadSerial(SerialReadTask, NULL);
	//Task UpdateTelemetry(UpdateTelemetryTask, NULL);
  Screen_Init_SetStlyes();
  lv_obj_t * scr = lv_obj_create(NULL, NULL);
  lv_scr_load(scr);                                   /*Load the screen*/
  Screen_Background_Init();
  Screen_Title_Title();

	M_Drivetrain_LF.set_brake_mode(MOTOR_BRAKE_HOLD);
	M_Drivetrain_LM.set_brake_mode(MOTOR_BRAKE_HOLD);
	M_Drivetrain_LR.set_brake_mode(MOTOR_BRAKE_HOLD);
	M_Drivetrain_RF.set_brake_mode(MOTOR_BRAKE_HOLD);
	M_Drivetrain_RM.set_brake_mode(MOTOR_BRAKE_HOLD);
	M_Drivetrain_RR.set_brake_mode(MOTOR_BRAKE_HOLD);

  M_Claw_Main.set_brake_mode(MOTOR_BRAKE_HOLD);
  M_Claw_Rotate.set_brake_mode(MOTOR_BRAKE_HOLD);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled()
{
	M_Drivetrain_LF = 0;
	M_Drivetrain_LM = 0;
	M_Drivetrain_LR = 0;
	M_Drivetrain_RF = 0;
	M_Drivetrain_RM = 0;
	M_Drivetrain_RR = 0;

	M_Intake_Main = 0;
	M_Intake_Preflywheel = 0;

	M_Flywheel_F = 0;
	M_Flywheel_R = 0;
	M_Flywheel_Hood = 0;
	M_Flywheel_Turret = 0;

	M_Claw_Rotate = 0;

	M_Lift_L = 0;
	M_Lift_R = 0;

	M_Donger_Main = 0;

	M_Ramalign_Main = 0;
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
  LargeRobot.initializePreMatch();
	// Light LEDs to Show Initialize Connected Properly
	// Auto Select
}
