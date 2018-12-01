#include "../include/api.h"
#include "../include/ports.hpp"
#include "../include/screen.hpp"
#include "../include/global.hpp"


int process;
double distTraveled = 0;
bool velIsLocked = 0;
int setVel = 0;
bool runAuto = 0;

void printSerial()
{
	serialRead(NULL);
	pros::lcd::print(0, "PRINT SERIAL IS ON");
	pros::lcd::print(1, "Heading (deg): %f", heading);
	pros::lcd::print(2, "ax (linear) (m/s): %f", ax);
	pros::lcd::print(3, "ay (linear) (m/s): %f", ay);
	pros::lcd::print(4, "az (linear) (m/s): %f", az);
	pros::lcd::print(5, "");
	pros::lcd::print(6, "");
	pros::lcd::print(7, "");
}

void mainCenter()
{
	//if(process == 0)
	process = 1;
	//else process = 0;
}
void toFlywheel()
{
	process = 1;
}
void selectedFlywheel()
{
	process = 2;
}
void toDrivetrain()
{
	process = 3;
}
void selectedDrivetrain()
{
	process = 4;
}
void toAuto()
{
	process = 5;
}
void selectedAuto()
{
	process = 6;
}

void Screen::write()
{

    switch(process)
    {
			case 0:
				//printSerial();
      case 10:
        pros::lcd::print(0, "");
        pros::lcd::print(1, "PYRO Robotics | VEX U");
        pros::lcd::print(2, "2018-2019 TURNING POINT");
        pros::lcd::print(3, "");
        pros::lcd::print(4, "Mini Robot | Pre-Cali Tournament");
        pros::lcd::print(5, "");
        pros::lcd::print(6, "");
        pros::lcd::print(7, "[   -    ]         [  Continue  ]        [    -   ]");
        //printCenteredButton(7, "-", "Continue", "-");
        pros::lcd::register_btn0_cb(NULL);
        pros::lcd::register_btn1_cb(mainCenter);
        pros::lcd::register_btn2_cb(NULL);
        if(Controller0.get_digital(pros::E_CONTROLLER_DIGITAL_B))
        {
          mainCenter();
          while(Controller0.get_digital(pros::E_CONTROLLER_DIGITAL_B))
          {
            pros::delay(10);
          }
        }

        break;
      case 1:
        pros::lcd::print(0, "");
        pros::lcd::print(1, "Flywheel");
        pros::lcd::print(2, "");
        pros::lcd::print(3, "Control the flywheel using the joysticks.");
        pros::lcd::print(4, "");
        pros::lcd::print(5, "");
        pros::lcd::print(6, "");
        pros::lcd::print(7, "[   <-   ]          [ Select  ]          [   ->   ]");
        pros::lcd::register_btn0_cb(toAuto);
        pros::lcd::register_btn1_cb(selectedFlywheel);
        pros::lcd::register_btn2_cb(toDrivetrain);
        if(Controller0.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT))
        {
          pros::delay(50);
          toAuto();
        }
        if(Controller0.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT))
        {
          pros::delay(50);
          toDrivetrain();
        }
        if(Controller0.get_digital(pros::E_CONTROLLER_DIGITAL_B))
        {
          selectedFlywheel();
          while(Controller0.get_digital(pros::E_CONTROLLER_DIGITAL_B))
          {
            pros::delay(10);
          }
        }
        break;
      case 2:
        pros::lcd::print(0, "");
        pros::lcd::print(1, "Flywheel SELECTED");
        pros::lcd::print(2, "");
        pros::lcd::print(3, "Control the flywheel using the joysticks.");
        pros::lcd::print(4, "");
        pros::lcd::print(5, "RPM: %f", FlywheelMotor1.get_actual_velocity() * 15);
        pros::lcd::print(6, "");
        pros::lcd::print(7, "[   -    ]          [   Back   ]         [    -   ]");
        pros::lcd::register_btn0_cb(NULL);
        pros::lcd::register_btn1_cb(toFlywheel);
        pros::lcd::register_btn2_cb(NULL);


        if(velIsLocked)
        {
          //FlywheelMotor1.move_velocity(3000/15);
          //FlywheelMotor2.move_velocity(3000/15);
          FlywheelMotor1.move_voltage(setVel);
          FlywheelMotor2.move_voltage(setVel);
          FlywheelMotorHood = Controller0.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y) * 30/127;
        }
        else
        {
          FlywheelMotor1 = Controller0.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
          FlywheelMotor2 = Controller0.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
          FlywheelMotorHood = Controller0.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y) * 30/127;
        }

        if(Controller0.get_digital(pros::E_CONTROLLER_DIGITAL_B))
        {
          toFlywheel();
          while(Controller0.get_digital(pros::E_CONTROLLER_DIGITAL_B))
          {
            pros::delay(10);
          }
        }
        if(Controller0.get_digital(pros::E_CONTROLLER_DIGITAL_A))
        {
          velIsLocked == 0? velIsLocked = 1 : velIsLocked = 0;
          setVel = FlywheelMotor1.get_voltage();
          while(Controller0.get_digital(pros::E_CONTROLLER_DIGITAL_A))
          {
            pros::delay(10);
          }
        }

        PreFlywheelMotor1 = 0;
        PreFlywheelMotor2 = 0;
        if(Controller0.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
        {
          PreFlywheelMotor1 = 115;
          PreFlywheelMotor2 = 115;
          while(Controller0.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
          {
            pros::delay(10);
          }
        }
        else if(Controller0.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
        {
          PreFlywheelMotor1 = -115;
          PreFlywheelMotor2 = -115;
          while(Controller0.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
          {
            pros::delay(10);
          }
        }
        break;
      case 3:
        pros::lcd::print(0, "");
        pros::lcd::print(1, "Drivetrain");
        pros::lcd::print(2, "");
        pros::lcd::print(3, "Control the drive using the joysticks.");
        pros::lcd::print(4, "");
        pros::lcd::print(5, "");
        pros::lcd::print(6, "");
        pros::lcd::print(7, "[   <-   ]          [ Select  ]          [   ->   ]");
        pros::lcd::register_btn0_cb(toFlywheel);
        pros::lcd::register_btn1_cb(selectedDrivetrain);
        pros::lcd::register_btn2_cb(toAuto);

        if(Controller0.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT))
        {
          pros::delay(50);
          toFlywheel();
        }
        if(Controller0.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT))
        {
          pros::delay(50);
          toAuto();
        }
        if(Controller0.get_digital(pros::E_CONTROLLER_DIGITAL_B))
        {
          selectedDrivetrain();
          distTraveled = 0;
          while(Controller0.get_digital(pros::E_CONTROLLER_DIGITAL_B))
          {
            pros::delay(10);
          }
        }
        break;
      case 4:
        distTraveled += M_Drivetrain_LF.get_actual_velocity() * 4.125 * M_PI * 20 / 60000;

        pros::lcd::print(0, "");
        pros::lcd::print(1, "Drivetrain SELECTED");
        pros::lcd::print(2, "");
        pros::lcd::print(3, "Control the drive using the joysticks.");
        pros::lcd::print(4, "Calc. Displacement (in): %f", distTraveled);
        pros::lcd::print(5, "Velocity: %f", M_Drivetrain_LF.get_actual_velocity() * 4.125 * M_PI);
        pros::lcd::print(6, "");
        pros::lcd::print(7, "[   -    ]          [   Back   ]         [    -   ]");
        pros::lcd::register_btn0_cb(NULL);
        pros::lcd::register_btn1_cb(toDrivetrain);
        pros::lcd::register_btn2_cb(NULL);

        M_Drivetrain_RF = Controller0.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        M_Drivetrain_RM = Controller0.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        M_Drivetrain_RR = Controller0.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        M_Drivetrain_LF = Controller0.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
        M_Drivetrain_LM = Controller0.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
        M_Drivetrain_LR = Controller0.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

        if(Controller0.get_digital(pros::E_CONTROLLER_DIGITAL_B))
        {
          toDrivetrain();
          while(Controller0.get_digital(pros::E_CONTROLLER_DIGITAL_B))
          {
            pros::delay(10);
          }
        }
        break;
        case 5:
          pros::lcd::print(0, "");
          pros::lcd::print(1, "Autonomous Test");
          pros::lcd::print(2, "");
          pros::lcd::print(3, "Test the autonomous function.");
          pros::lcd::print(4, "");
          pros::lcd::print(5, "");
          pros::lcd::print(6, "");
          pros::lcd::print(7, "[   <-   ]          [ Select  ]          [   ->   ]");
          pros::lcd::register_btn0_cb(toDrivetrain);
          pros::lcd::register_btn1_cb(selectedAuto);
          pros::lcd::register_btn2_cb(toFlywheel);

          if(Controller0.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT))
          {
            pros::delay(50);
            toDrivetrain();
          }
          if(Controller0.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT))
          {
            pros::delay(50);
            toFlywheel();
          }
          if(Controller0.get_digital(pros::E_CONTROLLER_DIGITAL_B))
          {
            selectedAuto();
            while(Controller0.get_digital(pros::E_CONTROLLER_DIGITAL_B))
            {
              pros::delay(10);
            }
          }
          break;
        case 6:
          pros::lcd::print(0, "");
          pros::lcd::print(1, "Autonomous SELECTED");
          pros::lcd::print(2, "");
          pros::lcd::print(3, "Test the autonomous function.");
          pros::lcd::print(4, "");
          pros::lcd::print(5, "Press A to start/abort test.");
          pros::lcd::print(6, "");
          pros::lcd::print(7, "[   -    ]          [   Back   ]         [    -   ]");
          pros::lcd::register_btn0_cb(NULL);
          pros::lcd::register_btn1_cb(toAuto);
          pros::lcd::register_btn2_cb(NULL);


          //pros::Task Auto(PYROAutonomous1, 0, 0, 0, "Autonomous");
          //Auto.suspend();
          while(Controller0.get_digital(pros::E_CONTROLLER_DIGITAL_A))
          {
            //PYROAutonomous1();
          }

          if(Controller0.get_digital(pros::E_CONTROLLER_DIGITAL_B))
          {
            toAuto();
            while(Controller0.get_digital(pros::E_CONTROLLER_DIGITAL_B))
            {
              pros::delay(10);
            }
          }
          break;
    }
}
