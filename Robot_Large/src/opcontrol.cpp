#include "../include/main.h"

bool doStuff = false;

void printSerial()
{
	serialRead(NULL);
	pros::lcd::print(0, "PRINT SERIAL IS ON");
	pros::lcd::print(1, "Heading (deg): %f", HEADING_RAW);
	pros::lcd::print(2, "ax (linear) (m/s): %f", ax);
	pros::lcd::print(3, "ay (linear) (m/s): %f", ay);
	pros::lcd::print(4, "az (linear) (m/s): %f", az);
	//std::cout << "Heading: " << heading << "\n";
}


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

void shooterTask(void*)
{
	while(1)
	{
		shooter.teleop();
		pros::delay(5);
	}
}
void armTask(void*)
{
	while(1)
	{
		arm.teleop();
		pros::delay(5);
	}
}

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
	pros::Task printSerialTask(printSerialTaskfn, 0);
	//pros::Task shooterTeleopTask(shooterTask, NULL);
	//pros::Task armTeleopTask(armTask, NULL);
	//chassis.MasterController.stop();
/*
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

	//Create an array for the points of the line
	static short x0 = 0;
	static short y0 = 0;
	static short x1 = 10;
	static short y1 = 0;

	static lv_point_t heading_line_points[] = { {1, y0}, {x1, y1} };

	//Create line with default style
	lv_obj_t * line1;
	line1 = lv_line_create(lv_scr_act(), NULL);
	lv_line_set_points(line1, heading_line_points, 2);     //Set the points
	lv_obj_align(line1, BaseObject_PositionIndicator, LV_ALIGN_CENTER, 0, 0);

	bool screenShowLogoOnly = false;
	lv_obj_t * Teleop_LicensePlate;


  lv_style_copy(&style_plate_red, &lv_style_plain);    //Copy a built-in style to initialize the new style
  style_plate_red.body.main_color = LV_COLOR_RED;
  style_plate_red.body.grad_color = LV_COLOR_RED;
  style_plate_red.body.border.color = LV_COLOR_RED;

  lv_style_copy(&style_plate_blue, &lv_style_plain);    //Copy a built-in style to initialize the new style
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
	*/
	//auto controllerasdf = AsyncControllerFactory::posPID(5, OkapiIMUGyro, 0.1, 0.0, 0.0001);
	//controllerasdf.flipDisable(false);



	while(1)
	{
		//int x = Controller_0.get_analog(ANALOG_LEFT_X);
		//int y = Controller_0.get_analog(ANALOG_LEFT_Y);
		/*
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
		lv_line_set_points(line1, heading_line_points, 2);     //Set the points
		lv_obj_align(line1, BaseObject_PositionIndicator, LV_ALIGN_CENTER, -headingX/2, -headingY/2);

		//std::cout << "Autonomous " << autonomousIDNum << "Running...";
		*/
		//chassis.teleop(tank);
		////if(Controller_0.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y))
			////doStuff = !doStuff;
		////if(doStuff)
			////chassis.MasterController.rotate(heading / 15 * 0.048);
		chassis.teleop(arcade);
		//intake.teleop();
		//shooter.teleop();

		//arm.teleop();
		//donger.teleop();
		//...

		//printSerial();

		//int speed = (0 - heading) * 3;
		//M_Lift_L = speed;

		//OkapiIMUGyro.value += 0.00001;
		//pros::lcd::print(7,"%f",OkapiIMUGyro.get());

		//if(HEADING_ADJUSTED > -180 && HEADING_ADJUSTED <= 180)
		//controllerasdf.setTarget(-HEADING_ADJUSTED);
		//controller1234.rotate(-HEADING_ADJUSTED);
		//M_Lift_L = -HEADING_ADJUSTED;


		pros::lcd::print(4, "ms since last update: %f", msSinceLastUpdate);
		pros::lcd::print(5, "last ID: %d", lastID);

		pros::delay(20);
	}
}
