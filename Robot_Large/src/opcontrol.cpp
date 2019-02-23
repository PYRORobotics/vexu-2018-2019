#include "../include/main.h"

static int tasknum = 1;

int driveToPos(double x, double y, double heading)
{

  int i = 0;
  double startingPos;
  while (tasknum>0)
  {
    switch(tasknum)
    {
      case 1: // Turn to x,y
        if(i == 0)
        {
          startingPos = M_Drivetrain_LF.get_position();
          if(y==0)
          {
            tasknum = -1;
            break;
          }
          if(x>0)
            LargeRobot.drive(rightPoint, atan((x-0)/(y-0))*180/M_PI, 100);
          else if(x<0)
            LargeRobot.drive(leftPoint, atan((-x-0)/(y-0))*180/M_PI, 100);
          if(x==0)
          {
            tasknum = 2;
            break;
          }
          i++;
        }
        printf("%d\n",tasknum);
        if(M_Drivetrain_LF.get_position()+0.1>=M_Drivetrain_LF.get_target_position())
        {
          i=0;
          tasknum++;
        }
        break;
      case 2:
        if(i == 0)
        {
          startingPos = M_Drivetrain_LF.get_position();
          LargeRobot.drive(forward, sqrt(x*x+y*y), 100);
          i++;
        }
        printf("%d\n",tasknum);
        if(M_Drivetrain_LF.get_position()==M_Drivetrain_LF.get_target_position())
        {
          i=0;
          tasknum=0;
        }
        break;
      case 3: // Turn to x,y
        if(i == 0)
        {
          startingPos = M_Drivetrain_LF.get_position();
          if(y==0)
          {
            tasknum = -1;
            break;
          }
          if(x>0)
            LargeRobot.drive(rightPoint, heading - atan((x-x)/(y-y))*180/M_PI, 100);
          else if(x<0)
            LargeRobot.drive(leftPoint, heading - atan((-x-0)/(y-y))*180/M_PI, 100);
          if(x==0)
          {
            tasknum = 0;
            break;
          }
          i++;
        }
        printf("%d\n",tasknum);
        if(M_Drivetrain_LF.get_position()+0.1>=M_Drivetrain_LF.get_target_position())
        {
          i=0;
          tasknum=0;
        }
        break;
}
}
}

int getOverallCurrent()
{
	return 	M_Drivetrain_LF.get_current_draw() +
					M_Drivetrain_LM.get_current_draw() +
					M_Drivetrain_LR.get_current_draw() +
					M_Drivetrain_RF.get_current_draw() +
					M_Drivetrain_RM.get_current_draw() +
					M_Drivetrain_RR.get_current_draw() +
					M_Intake_Main.get_current_draw() +
					M_Intake_Preflywheel.get_current_draw() +
					M_Flywheel_F.get_current_draw() +
					M_Flywheel_R.get_current_draw() +
					M_Flywheel_Hood.get_current_draw() +
					M_Flywheel_Turret.get_current_draw() +
					M_Claw_Rotate.get_current_draw() +
					M_Lift_L.get_current_draw() +
					M_Lift_R.get_current_draw() +
					M_Donger_Main.get_current_draw() +
					M_Ramalign_Main.get_current_draw();
}

void CurrentLimiterTask(void* param)
{
  while(1)
  {
		std::cout << "CurrentDraw: " << getOverallCurrent() << " TempMLF: " << M_Drivetrain_LF.get_temperature() << " Battery Voltage: " << (double)pros::battery::get_voltage()/1000 << " V" << "\n";
		if(getOverallCurrent() > 18000)
		{
			int limit = getOverallCurrent() - 18000;
			limit /= 12;

			M_Drivetrain_LF.set_current_limit(M_Drivetrain_LF.get_current_draw() - limit);
			M_Drivetrain_LM.set_current_limit(M_Drivetrain_LM.get_current_draw() - limit);
			M_Drivetrain_LR.set_current_limit(M_Drivetrain_LR.get_current_draw() - limit);
			M_Drivetrain_RF.set_current_limit(M_Drivetrain_RF.get_current_draw() - limit);
			M_Drivetrain_RM.set_current_limit(M_Drivetrain_RM.get_current_draw() - limit);
			M_Drivetrain_RR.set_current_limit(M_Drivetrain_RR.get_current_draw() - limit);

			M_Intake_Main.set_current_limit(M_Intake_Main.get_current_draw() - limit);
			M_Intake_Preflywheel.set_current_limit(M_Intake_Preflywheel.get_current_draw() - limit);

			M_Flywheel_Turret.set_current_limit(M_Flywheel_Turret.get_current_draw() - limit);
			M_Claw_Rotate.set_current_limit(M_Claw_Rotate.get_current_draw() - limit);

			M_Donger_Main.set_current_limit(M_Donger_Main.get_current_draw() - limit);
			M_Ramalign_Main.set_current_limit(M_Ramalign_Main.get_current_draw() - limit);
		}
		else
		{
			int limit = 2500;
			M_Drivetrain_LF.set_current_limit(limit);
			M_Drivetrain_LM.set_current_limit(limit);
			M_Drivetrain_LR.set_current_limit(limit);
			M_Drivetrain_RF.set_current_limit(limit);
			M_Drivetrain_RM.set_current_limit(limit);
			M_Drivetrain_RR.set_current_limit(limit);

			M_Intake_Main.set_current_limit(limit);
			M_Intake_Preflywheel.set_current_limit(limit);
		}
    delay(10);
  }
}

//////////////////////////////////// 2/14/19 /////////////////////////////////////////////////////////////////////

void resetPosAutoREDTOP()
{
  LargeRobot.telemetry.position[0] = -60.125;
  LargeRobot.telemetry.position[1] = 82.25;
  LargeRobot.telemetry.encoder_position_average = ((M_Drivetrain_LM.get_position() + M_Drivetrain_RM.get_position())/2) * 4 * M_PI;
  LargeRobot.lastPosition[0] = (M_Drivetrain_LM.get_position() + M_Drivetrain_RM.get_position())/2;
  LargeRobot.lastPosition[1] = (M_Drivetrain_LM.get_position() + M_Drivetrain_RM.get_position())/2;
}



void printSerial()
{
	serialRead(NULL);
	pros::lcd::print(0, "PRINT SERIAL IS ON");
	pros::lcd::print(1, "Heading (deg): %f", LargeRobot.telemetry.heading);
	pros::lcd::print(2, "ax (linear) (m/s): %f", ax);
	pros::lcd::print(3, "ay (linear) (m/s): %f", ay);
	pros::lcd::print(4, "az (linear) (m/s): %f", az);
	pros::lcd::print(5, "getposL: %f, R: %f", M_Drivetrain_LM.get_position(), M_Drivetrain_RM.get_position());
	pros::lcd::print(6, "X: %f", LargeRobot.telemetry.position[0]);
	pros::lcd::print(7, "Y: %f", LargeRobot.telemetry.position[1]);
}

void oldOpControl()
{
  printf("opcontrol started");
	//Screen Screen;
	//Controller0 = Controller0Base;
	//taskSerialRead().resume();
	int i = 0;
	while (1)
	{
		while(pros::competition::is_connected())	// FIX ME!!!
		{
			//M_Drivetrain_LF.move_absolute(90, 60);
			//motorTestPIDSerial();
			//Screen.write();
			printSerial();
      while(true)
      {
        //LargeRobot.setpoint_theta = 90;
        //pros::lcd::print(7, "Error: %f", LargeRobot.setpoint_theta);
        printSerial();
        LargeRobot.setpoint_theta = Controller0.get_analog(ANALOG_LEFT_X);
        LargeRobot.drive(-(LargeRobot.telemetry.heading - LargeRobot.setpoint_theta) * 127/180, (LargeRobot.telemetry.heading - LargeRobot.setpoint_theta) * 127/180);
      }
      LargeRobot.teleop();
      /*
			if(i >= 500)
			{
				pros::lcd::print(7, "RESET!");
				serialWrite(NULL);
				i = 0;
			}*/
			//pros::lcd::print(7, "");
			// Do teleop stuff
			//Controller0.tankDrive();
			//Robot_Mini.tankDrive();
			//Motor ml(1,false);
			//Motor mr(4,true);
			//ml = Controller0Base.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
			//mr = Controller0Base.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
			//pros::lcd::print(0, "Controller: %d", Controller0Base.get_analog(E_CONTROLLER_ANALOG_LEFT_Y));
			//pros::delay(20);
			//pros::lcd::print(0, "%d", i);
			i++;
		}
		pros::lcd::print(0, "NOT CONNECTED TO FIELD CONTROLLER!");
		pros::delay(20);

	}
	//taskSerialRead().suspend();
}

void FlywheelUpdateTaskOLD(void* param)
{
  while(1)
  {
    double hoodAngle = 45;

    Waypoint flag;
    flag.position[0] = -54.5;
    flag.position[1] = 130.5;
    double flagHeight = 29;

    double flagHeightm = flagHeight * 0.0254;
    double distance = sqrt((flag.position[0] - LargeRobot.telemetry.position[0]) * (flag.position[0] - LargeRobot.telemetry.position[0]) + (flag.position[1] - LargeRobot.telemetry.position[1]) * (flag.position[1] - LargeRobot.telemetry.position[1])) - 4;

    double distancem = distance * 0.0254;

    double v_linearmps = 4.905 * distancem * distancem / (cos(hoodAngle * M_PI/180) * cos(hoodAngle * M_PI/180) * (tan(hoodAngle * M_PI/180) * distancem - flagHeightm));

    double v_linearinps = v_linearmps * 39.3701;

    double v_rpm_wheel = v_linearinps * 60 / 2.945 / M_PI;

    double v_rpm_motor = 0.12 * v_rpm_wheel;

    pros::lcd::print(0, "rpm: %f",  v_rpm_motor);
    pros::lcd::print(1, "distin: %f",  distance);
    pros::lcd::print(2, "distm: %f",  distancem);

    delay(10);
  }
}

void FlywheelUpdateTask(void* param)
{
  while(1)
  {
    double hoodAngle = LargeRobot.TurretObj.currentHoodAngle;

    Waypoint flag;
    flag.position[0] = -54.5;
    flag.position[1] = 130.5;
    double flagHeight = 29;

    double flagHeightm = flagHeight * 0.0254;
    double distance = sqrt((flag.position[0] - LargeRobot.telemetry.position[0]) * (flag.position[0] - LargeRobot.telemetry.position[0]) + (flag.position[1] - LargeRobot.telemetry.position[1]) * (flag.position[1] - LargeRobot.telemetry.position[1])) - 4;

    double distancem = distance * 0.0254;

    double v_linearmps = 4.905 * distancem * distancem / (cos(hoodAngle * M_PI/180) * cos(hoodAngle * M_PI/180) * (tan(hoodAngle * M_PI/180) * distancem - flagHeightm));

    double v_linearinps = v_linearmps * 39.3701;

    double v_rpm_wheel = v_linearinps * 60 / 2.945 / M_PI;

    double v_rpm_motor = 0.12 * v_rpm_wheel;

    pros::lcd::print(0, "rpm: %f",  v_rpm_motor);
    pros::lcd::print(1, "distin: %f",  distance);
    pros::lcd::print(2, "distm: %f",  distancem);

    delay(10);
  }
}

void UpdateTelemetryTask(void* param)
{
  while(1)
  {
    if(heading > 180)
    {
      heading = heading - 360;
    }
    LargeRobot.telemetry.heading = heading;

    LargeRobot.telemetry.encoder_position_average = ((M_Drivetrain_LM.get_position() + M_Drivetrain_RM.get_position())/2) * 4 * M_PI;

    LargeRobot.telemetry.position[0] = LargeRobot.telemetry.position[0] + ((M_Drivetrain_LM.get_position() + M_Drivetrain_RM.get_position())/2 - LargeRobot.lastPosition[0]) * 4 * M_PI *sin(LargeRobot.telemetry.heading * M_PI/180);
    LargeRobot.telemetry.position[1] = LargeRobot.telemetry.position[1] + ((M_Drivetrain_LM.get_position() + M_Drivetrain_RM.get_position())/2 - LargeRobot.lastPosition[1]) * 4 * M_PI *cos(LargeRobot.telemetry.heading* M_PI/180);

    LargeRobot.lastPosition[0] = (M_Drivetrain_LM.get_position() + M_Drivetrain_RM.get_position())/2;
    LargeRobot.lastPosition[1] = (M_Drivetrain_LM.get_position() + M_Drivetrain_RM.get_position())/2;

    LargeRobot.TurretObj.currentHoodAngle = 54 - M_Flywheel_Hood.get_position() * 14/201*360;
    if(M_Flywheel_Turret.get_position()>=0)
    LargeRobot.TurretObj.currentTurntableAngle = M_Flywheel_Turret.get_position() + 39.4/2 * 18/84;
    else
    LargeRobot.TurretObj.currentTurntableAngle = M_Flywheel_Turret.get_position();// * 18/84;

    delay(10);
  }
}

void SerialTask(void*)
{
  while(1)
  {
    serialRead(NULL);
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
  resetPosAutoREDTOP();
  //Task FlywheelUpdate(FlywheelUpdateTask, NULL);
  Task serial(SerialTask,NULL);
  Task UpdateTelemetry(UpdateTelemetryTask, NULL);
  M_Drivetrain_LF.set_brake_mode(MOTOR_BRAKE_HOLD);

  while(1)
  {
    LargeRobot.teleop();
    //M_Flywheel_F = Controller0.get_analog(ANALOG_LEFT_Y);
    //M_Flywheel_R = Controller0.get_analog(ANALOG_LEFT_Y);
    //serialRead(NULL);
    //pros::lcd::clear();
    pros::lcd::print(0, "%f RPM", M_Flywheel_F.get_actual_velocity());
    pros::lcd::print(1, "Hood Angle: %f Deg", LargeRobot.TurretObj.currentHoodAngle);
    pros::lcd::print(2, "Turntable Angle: %f Deg", LargeRobot.TurretObj.currentTurntableAngle);

    delay(10);
  }
}
void OLDopcontrol()
{

	//driveToPos(-48, 24, 0);
	//autonomous();
	//LargeRobot.getPosition();

  resetPosAutoREDTOP();


  //delay(1000);
  //oldOpControl();

	//Task CurrentLimiter(CurrentLimiterTask, NULL);

	while (true)
	{
		for(int i = 0; i<16; i++)
		{
			contValues[i]=" ";
		}
		LargeRobot.teleop();
    pros::delay(20);
    printSerial();
    pros::delay(20);

    controllerPrintValues(0);
		/*
		pros::lcd::print(0, "Motor Left  Front: %f in", M_Drivetrain_LF.get_position());
		pros::lcd::print(1, "Motor Left  Mid:   %f in", M_Drivetrain_LM.get_position());
		pros::lcd::print(2, "Motor Left  Rear:  %f in", M_Drivetrain_LR.get_position());
		pros::lcd::print(3, "Motor Right Front: %f in", M_Drivetrain_RF.get_position());
		pros::lcd::print(4, "Motor Right Mid:   %f in", M_Drivetrain_RM.get_position());
		pros::lcd::print(5, "Motor Right Rear:  %f in", M_Drivetrain_RR.get_position());
		pros::lcd::print(6, "Flywheel RPM:  %f rpm", M_Flywheel_F.get_actual_velocity()*5000/600);
		pros::lcd::print(7, "Hood Angle:  %f degrees", 58-M_Flywheel_Hood.get_position()*14/201);*/

		std::string temp = contValues[0];
		char * tab2 = new char [temp.length()+1];
		strcpy (tab2, temp.c_str());
		bool write = false;

		if (Controller0.get_digital_new_press(E_CONTROLLER_DIGITAL_A)) {
      write = true;
    }


		if(write)
		{
		Controller0.print(0, 3, "MAX. 12 CHAR");	//MUST BE: (0, 3 to center, LIMIT 12 CHARACTERS!!!),
	}

		pros::delay(20);
		if (Controller0.get_digital_new_press(E_CONTROLLER_DIGITAL_B)) {

		Controller0.print(0, 3, "");	//MUST BE: (0, 3 to center, LIMIT 12 CHARACTERS!!!),
	}
}
}
