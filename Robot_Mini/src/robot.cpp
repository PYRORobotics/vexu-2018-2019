#include "../include/api.h"
#include "../include/ports.hpp"
#include "../include/robot.hpp"


Drivetrain::Drivetrain()
{
  MotorLF = &M_Drivetrain_LF;
  MotorLM = &M_Drivetrain_LM;
  MotorLR = &M_Drivetrain_LR;
  MotorRF = &M_Drivetrain_RF;
  MotorRM = &M_Drivetrain_RM;
  MotorRR = &M_Drivetrain_RR;
}



Robot::Robot()
{

}

void Robot::arcadeDrive()
{
  int speed;
  int turn;
  int leftSignal;
  int rightSignal;

  turn = Controller0Base.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);
  speed = Controller0Base.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);

  leftSignal = turn;
  rightSignal = turn;

  /*
  int deadzone = 2;
  int x = Controller0Base.get_analog(E_CONTROLLER_ANALOG_LEFT_X);
  int y = Controller0Base.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
  double scale = sqrt(x^2+y^2);

  int leftSignal;
  int rightSignal;

  if(abs(x) <= deadzone)  // Y-axis
  {
    leftSignal = scale * y;
    rightSignal = scale * y;
  }
  else if(abs(y) <= deadzone) // X-axis
  {
    leftSignal = scale * x;
    rightSignal = -scale * x;
  }
  else if(atan(y/x) > deadzone)
  {
    if(y>0) // Q1
    {
      leftSignal = scale;
      rightSignal = -scale * cos(2 * atan(y/x));
    }
    else  // Q3
    {
      leftSignal = -scale;
      rightSignal = scale * cos(2 * atan(y/x));
    }
  }
  else if(atan(y/x) < -deadzone)
  {
    if(y>0) // Q2
    {
      leftSignal = -scale * cos(2 * atan(y/x));
      rightSignal = scale;
    }
    else  // Q4
    {
      leftSignal = scale * cos(2 * atan(y/x));
      rightSignal = -scale;
    }
  }

  DrivetrainObj.MotorLF -> move(leftSignal);
  DrivetrainObj.MotorLM -> move(leftSignal);
  DrivetrainObj.MotorLR -> move(leftSignal);
  DrivetrainObj.MotorRF -> move(rightSignal);
  DrivetrainObj.MotorRM -> move(rightSignal);
  DrivetrainObj.MotorRR -> move(rightSignal);
  */
}

void Robot::tankDrive()
{
  DrivetrainObj.MotorLF -> move(Controller0Base.get_analog(E_CONTROLLER_ANALOG_LEFT_Y));
  DrivetrainObj.MotorLM -> move(Controller0Base.get_analog(E_CONTROLLER_ANALOG_LEFT_Y));
  DrivetrainObj.MotorLR -> move(Controller0Base.get_analog(E_CONTROLLER_ANALOG_LEFT_Y));
  DrivetrainObj.MotorRF -> move(-Controller0Base.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y));
  DrivetrainObj.MotorRM -> move(Controller0Base.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y));
  DrivetrainObj.MotorRR -> move(Controller0Base.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y));
}


Robot Robot_Mini;
