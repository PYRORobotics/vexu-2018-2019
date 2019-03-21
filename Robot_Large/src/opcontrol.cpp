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
void opcontrol()
{
	chassis.MasterController.stop();

	// SET UP SCREEN //
	lv_obj_t * Teleop_MainBackground = lv_obj_create(lv_scr_act(), NULL);
	lv_obj_set_size(Teleop_MainBackground, 480, 240);
	lv_obj_set_style(Teleop_MainBackground, &lv_style_plain);
	lv_obj_align(Teleop_MainBackground, NULL, LV_ALIGN_CENTER, 0, 0);


	static lv_style_t robot;
	lv_style_copy(&robot, &lv_style_scr);
  robot.body.main_color = LV_COLOR_BLACK;
  robot.body.grad_color = LV_COLOR_BLACK;
	robot.body.radius = 7;


	LV_IMG_DECLARE(Image_VEX_Field);

	lv_obj_t * FieldImage = lv_img_create(lv_scr_act(), NULL);
	lv_img_set_src(FieldImage, &Image_VEX_Field);
	lv_obj_align(FieldImage, NULL, LV_ALIGN_CENTER, 0, 0);

	BaseObject_PositionIndicator = lv_obj_create(lv_scr_act(), NULL);
	lv_obj_set_size(BaseObject_PositionIndicator, 20, 20);
	lv_obj_set_style(BaseObject_PositionIndicator, &robot);
	lv_obj_align(BaseObject_PositionIndicator, NULL, LV_ALIGN_CENTER, 0, 0);

	/*Create an array for the points of the line*/
	static short x0 = 0;
	static short y0 = 0;
	static short x1 = 10;
	static short y1 = 0;

	static lv_point_t heading_line_points[] = { {1, y0}, {x1, y1} };

	/*Create line with default style*/
	lv_obj_t * line1;
	line1 = lv_line_create(lv_scr_act(), NULL);
	lv_line_set_points(line1, heading_line_points, 2);     /*Set the points*/
	lv_obj_align(line1, BaseObject_PositionIndicator, LV_ALIGN_CENTER, 0, 0);

	bool screenShowLogoOnly = false;
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
	// END SCREEN SETUP //


	while(1)
	{
		int x = Controller_0.get_analog(ANALOG_LEFT_X);
		int y = Controller_0.get_analog(ANALOG_LEFT_Y);

		int heading;
		int headingX = -Controller_0.get_analog(ANALOG_RIGHT_X) * 10/127;
		int headingY = Controller_0.get_analog(ANALOG_RIGHT_Y) * 10/127;

		x0 = 0;
		y0 = 0;
		if(headingX<0)
		{
			x0 = -headingX;
			x1 = 0;
		}
		else
		x1 = headingX;
		if(headingY<0)
		{
			y0 = -headingY;
			y1 = 0;
		}
		else
		y1 = headingY;

		//x1 = 10 * cos(y/x);
		//y1 = 10 * sin(y/x);

		lv_point_t heading_line_point[] = { {x0, y0}, {x1, y1} };
		heading_line_points[0] = heading_line_point[0];
		heading_line_points[1] = heading_line_point[1];


		lv_obj_align(BaseObject_PositionIndicator, NULL, LV_ALIGN_CENTER, x, -y);
		lv_line_set_points(line1, heading_line_points, 2);     /*Set the points*/
		lv_obj_align(line1, BaseObject_PositionIndicator, LV_ALIGN_CENTER, -headingX/2, -headingY/2);

		//std::cout << "Autonomous " << autonomousIDNum << "Running...";

		chassis.teleop(arcade);
		//intake.teleop();
		//flywheel.teleop();
		//...

		pros::delay(20);
	}
}
