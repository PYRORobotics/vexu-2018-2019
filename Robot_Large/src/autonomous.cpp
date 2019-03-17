#include "../include/main.h"

//using namespace okapi;

okapi::QLength WHEEL_DIAMETER = 4_in;//3.6_in;
okapi::QLength CHASSIS_WIDTH = 12_in;
okapi::MotorGroup MG_Drivetrain_Left = {6};
okapi::MotorGroup MG_Drivetrain_Right = {6};


okapi::AbstractMotor::GearsetRatioPair ratio = okapi::AbstractMotor::gearset::green;// * (1.0382);


auto chassis = ChassisControllerFactory::create(
   //{16,15,18}, {-6,-7,-8},
   MG_Drivetrain_Left, MG_Drivetrain_Right,
   //IterativePosPIDController::Gains{0.0045, 0.005, 0.00008},
   //IterativePosPIDController::Gains{0.00003, 0.00003, 0.00001},
   //IterativePosPIDController::Gains{0.0006, 0.00008, 0.00008},
   ratio,
   {WHEEL_DIAMETER, CHASSIS_WIDTH}
 );

 auto profileController = AsyncControllerFactory::motionProfile(
   10.0,  // Maximum linear velocity of the Chassis in m/s
   0.5,  // Maximum linear acceleration of the Chassis in m/s/s
   10.0, // Maximum linear jerk of the Chassis in m/s/s/s
   chassis // Chassis Controller
 );




/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous()
{//int i = 0;
  //pros::ADIMotor m('A');


  bool screenShowLogoOnly = true;
	lv_obj_t * Teleop_LicensePlate;

  lv_style_copy(&style_plate_red, &lv_style_plain);    /*Copy a built-in style to initialize the new style*/
  style_plate_red.body.main_color = LV_COLOR_RED;
  style_plate_red.body.grad_color = LV_COLOR_RED;
  style_plate_red.body.border.color = LV_COLOR_RED;

  lv_style_copy(&style_plate_blue, &lv_style_plain);    /*Copy a built-in style to initialize the new style*/
  style_plate_blue.body.main_color = LV_COLOR_BLUE;
  style_plate_blue.body.grad_color = LV_COLOR_BLUE;
  style_plate_blue.body.border.color = LV_COLOR_BLUE;

	if(screenShowLogoOnly)
	{
		Teleop_LicensePlate = lv_obj_create(lv_scr_act(), NULL);
		lv_obj_set_size(Teleop_LicensePlate, 480, 240);
		if (autonomousIDNum % 2 && autonomousIDNum > 0)
			lv_obj_set_style(Teleop_LicensePlate, &style_plate_blue);
		else
			lv_obj_set_style(Teleop_LicensePlate, &style_plate_red);

		lv_obj_align(Teleop_LicensePlate, NULL, LV_ALIGN_CENTER, 0, 0);

		LV_IMG_DECLARE(Image_PYRO_License_Plate);

		PYRO_License_Plate = lv_img_create(lv_scr_act(), NULL);
		lv_img_set_src(PYRO_License_Plate, &Image_PYRO_License_Plate);
		lv_obj_align(PYRO_License_Plate, NULL, LV_ALIGN_CENTER, 0, -18);

	}

  chassis.setBrakeMode(AbstractMotor::brakeMode::brake);

  //chassis.moveDistance(10*M_PI*4_in);
  //profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{2*1.008*M_PI*4_in, 0_ft, 0_deg}}, "A");//
  //profileController.setTarget("A");

  chassis.stop();
/*
  while(1)
  {
  //printf();
  if(autonomousIDNum == 0)
  {
    std::cout << "Autonomous " << autonomousIDNum << " Running...\n";
    m.set_value(100);
  }
  else if(autonomousIDNum == 1)
  {
    std::cout << "Autonomous " << autonomousIDNum << " Running...\n";
    m.set_value(-100);
  }
  //std::cout << i++ << "\n";
  pros::delay(10);
}*/


}
