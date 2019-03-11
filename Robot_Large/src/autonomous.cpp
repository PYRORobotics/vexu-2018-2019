#include "../include/main.h"

using namespace okapi;

const auto WHEEL_DIAMETER = 3.6_in;
const auto CHASSIS_WIDTH = 14.5_in;

auto chassis = ChassisControllerFactory::create(
  {16,15,18}, {-6,-7,-8},
  IterativePosPIDController::Gains{0.0008, 0.00005, 0.00005},
  IterativePosPIDController::Gains{0.00003, 0.00003, 0.00001},
  IterativePosPIDController::Gains{0.0006, 0.00008, 0.00008},
  AbstractMotor::gearset::green,
  {WHEEL_DIAMETER, CHASSIS_WIDTH}
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
  pros::ADIMotor m('A');

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
  }
}
