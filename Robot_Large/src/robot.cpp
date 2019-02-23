#include "../include/api.h"
#include "../include/robot.hpp"
#include "../include/controller.hpp"
#include <math.h>

/*
 * FILE DESCRIPTION
 * robot.cpp defines the functions, classes, and objects
 * related to the robot's structure and function.
 */

using namespace pros;

/*
 *  Controller Button/Axis Mapping TODO
 *
 *  Controller0 (Primary) Map [Tank Drive]
 *
 *          [L2: ]                            [R2. ]
 *          [L1: ]                            [R1. ]
 *
 *        [L. X-Axis: NONE]                       [L. X-Axis: NONE]
 *        [L. Y-Axis: Drivetrain L]       [L. Y-Axis: Drivetrain R]
 *
 *            [U: Presision Lift U]                         [X: ]
 *        [L: ]  [R: ]                  [Y: ]  [A: Shoot if ready]
 *            [D: Presision Lift D]         [HOME]          [B: Turn On/Off Flywheel based on dist from flag]
 *
 */

/*
 * Robot Class Definitions (Base Structure Found in robot.hpp)
 */

/*
 * Piston Class
 */

Piston::Piston(char portNum, bool normallyExtended = false)
{
  port = portNum;
  isNormallyExtended = normallyExtended;
}

void Piston::extend()
{
  c::adi_digital_write(port, true);
}

void Piston::retract()
{
  c::adi_digital_write(port, false);
}

/*
 * LED Class
 */

 LED::LED(char portNum, double brightnessPct = 0.8) : LEDADIObj(portNum)
 {
   port = portNum;
   this -> brightnessPct = brightnessPct;
 }

void LED::on()
{
  LEDADIObj.set_value(brightnessPct * 4095 * 3.3/5);  // Use 3.3V logic instead of 5V
}

void LED::off()
{
  LEDADIObj.set_value(0);  // Use 3.3V logic instead of 5V
}

/*
 * RGB LED Class TODO: FIXME
 */

 RGBLED::RGBLED(char portNum, int r, int g, int b, double brightnessPct = 0.8) : LED(portNum, brightnessPct)
 {
   this -> r = r;
   this -> g = g;
   this -> b = b;
 }

void RGBLED::on()
{
  LEDADIObj.set_value(brightnessPct * 4095 * 3.3/5);  // Use 3.3V logic instead of 5V
}

void RGBLED::off()
{
  LEDADIObj.set_value(0);  // Use 3.3V logic instead of 5V
}

/*
 * Drivetrain Class
 */

Drivetrain::Drivetrain(){}

void Drivetrain::drive(int speed)
{
  M_Drivetrain_LF = speed;
  M_Drivetrain_LM = speed;
  M_Drivetrain_LR = speed;
  M_Drivetrain_RF = speed;
  M_Drivetrain_RM = speed;
  M_Drivetrain_RR = speed;
}

void Drivetrain::drive(int speedL, int speedR)
{
  M_Drivetrain_LF = speedL;
  M_Drivetrain_LM = speedL;
  M_Drivetrain_LR = speedL;
  M_Drivetrain_RF = speedR;
  M_Drivetrain_RM = speedR;
  M_Drivetrain_RR = speedR;
}

void Drivetrain::drive(driveType type, double distance, int speed = 40)
{
  switch(type)
  {
    case forward:
      distance = distance;
      speed = speed;
      M_Drivetrain_LF.move_relative(distance*1/4/M_PI*motorPowerDifferential, speed * motorPowerDifferential);
      M_Drivetrain_LM.move_relative(distance*1/4/M_PI*motorPowerDifferential, speed * motorPowerDifferential);
      M_Drivetrain_LR.move_relative(distance*1/4/M_PI*motorPowerDifferential, speed * motorPowerDifferential);
      M_Drivetrain_RF.move_relative(distance*1/4/M_PI, speed);
      M_Drivetrain_RM.move_relative(distance*1/4/M_PI, speed);
      M_Drivetrain_RR.move_relative(distance*1/4/M_PI, speed);
      break;
    case reverse:
      distance = -1 * distance;
      speed = -1 * speed;
      M_Drivetrain_LF.move_relative(distance*1/4/M_PI*motorPowerDifferential, speed * motorPowerDifferential);
      M_Drivetrain_LM.move_relative(distance*1/4/M_PI*motorPowerDifferential, speed * motorPowerDifferential);
      M_Drivetrain_LR.move_relative(distance*1/4/M_PI*motorPowerDifferential, speed * motorPowerDifferential);
      M_Drivetrain_RF.move_relative(distance*1/4/M_PI, speed);
      M_Drivetrain_RM.move_relative(distance*1/4/M_PI, speed);
      M_Drivetrain_RR.move_relative(distance*1/4/M_PI, speed);
      break;
    case leftPoint:
      distance = distance;
      speed = speed;
      M_Drivetrain_LF.move_relative(-distance*wheelBase/4*motorPowerDifferential / 360, -1 * speed * motorPowerDifferential);
      M_Drivetrain_LM.move_relative(-distance*wheelBase/4*motorPowerDifferential / 360, -1 * speed * motorPowerDifferential);
      M_Drivetrain_LR.move_relative(-distance*wheelBase/4*motorPowerDifferential / 360, -1 * speed * motorPowerDifferential);
      M_Drivetrain_RF.move_relative(distance*wheelBase/4*motorPowerDifferential / 360, speed);
      M_Drivetrain_RM.move_relative(distance*wheelBase/4*motorPowerDifferential / 360, speed);
      M_Drivetrain_RR.move_relative(distance*wheelBase/4*motorPowerDifferential / 360, speed);
      break;
    case rightPoint:
      distance = distance;
      speed = speed;
      M_Drivetrain_LF.move_relative(distance*wheelBase/4*motorPowerDifferential / 360, speed * motorPowerDifferential);
      M_Drivetrain_LM.move_relative(distance*wheelBase/4*motorPowerDifferential / 360, speed * motorPowerDifferential);
      M_Drivetrain_LR.move_relative(distance*wheelBase/4*motorPowerDifferential / 360, speed * motorPowerDifferential);
      M_Drivetrain_RF.move_relative(-distance*wheelBase/4*motorPowerDifferential / 360, -1*speed);
      M_Drivetrain_RM.move_relative(-distance*wheelBase/4*motorPowerDifferential / 360, -1*speed);
      M_Drivetrain_RR.move_relative(-distance*wheelBase/4*motorPowerDifferential / 360, -1*speed);
      break;
  }
}

void Drivetrain::tankDrive(int speedL, int speedR)
{
  /*
  M_Drivetrain_LF = speedL * 0.9;
  M_Drivetrain_LM = speedL * 0.9;
  M_Drivetrain_LR = speedL * 0.9;
  M_Drivetrain_RF = speedR * 0.9;
  M_Drivetrain_RM = speedR * 0.9;
  M_Drivetrain_RR = speedR * 0.9;
  */

  // Spline controller motor curve coefficients:
  double a = 0.50703533709;
  double b = 0.00004992507;
  double c = 7.44251597e-9;
  double d = 1.5203616e-13;
  int motorCurveL = a * speedL - b * speedL*speedL*speedL + c * speedL*speedL*speedL*speedL*speedL - d * speedL*speedL*speedL*speedL*speedL*speedL*speedL;
  int motorCurveR = a * speedR - b * speedR*speedR*speedR + c * speedR*speedR*speedR*speedR*speedR - d * speedR*speedR*speedR*speedR*speedR*speedR*speedR;

  M_Drivetrain_LF = motorCurveL;
  M_Drivetrain_LM = motorCurveL;
  M_Drivetrain_LR = motorCurveL;
  M_Drivetrain_RF = motorCurveR;
  M_Drivetrain_RM = motorCurveR;
  M_Drivetrain_RR = motorCurveR;
}

void Drivetrain::arcadeDrive(int x, int y)
{
  double a = 0.50703533709;
  double b = 0.00004992507;
  double c = 7.44251597e-9;
  double d = 1.5203616e-13;

  double power = sqrt(x*x+y*y);

  int motorCurvePower = power * 2;
  //int motorCurvePower = a * power - b * power*power*power + c * power*power*power*power*power - d * power*power*power*power*power*power*power;
  int L = motorCurvePower * (x+127)/254;
  int R = motorCurvePower * (127-x)/254;

  if(y<0)
  {
    L*=-1;
    R*=-1;
  }

  //std::cout << x << " | " << y << " | " << motorCurvePower << " | " << L << " | " << R << "\n";

  L = y + x;
  R = y - x;

  M_Drivetrain_LF = L;
  M_Drivetrain_LM = L;
  M_Drivetrain_LR = L;
  M_Drivetrain_RF = R;
  M_Drivetrain_RM = R;
  M_Drivetrain_RR = R;
}

/*
 * Intake Class
 */

Intake::Intake(){}
void Intake::run(int speed, intakeType type)
{
  switch (type)
  {
    case mainIntake:
      M_Intake_Main = speed;
      break;
    case preflywheel:
      M_Intake_Preflywheel = speed;
      break;
    case both:
      M_Intake_Main = speed;
      M_Intake_Preflywheel = speed;
  }
}

/*
 * Flywheel Class
 */

Flywheel::Flywheel()
{

}

/*
 * Turret Class
 */

Turret::Turret()
{
  M_Flywheel_F.set_gearing(E_MOTOR_GEARSET_06);
  M_Flywheel_R.set_gearing(E_MOTOR_GEARSET_06);
}

void Turret::run(int rpm)
{
  /*
  M_Flywheel_Turret = Controller1.get_analog(E_CONTROLLER_ANALOG_LEFT_X);

  M_Flywheel_F = Controller1.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
  M_Flywheel_R = Controller1.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);

  M_Flywheel_Hood = 0;
  int speed = 35;
  if(Controller1.get_digital(E_CONTROLLER_DIGITAL_R1))
  {

  }
  else if(Controller1.get_digital(E_CONTROLLER_DIGITAL_R2))
  {
    M_Flywheel_Hood = -speed;
  }*/

  M_Flywheel_F.move_velocity(0.8*rpm);
  M_Flywheel_R.move_velocity(0.8*rpm);
}

/*
 * Claw Class
 */

Claw::Claw()
{
  clockwise = true;
  errorRotate = 0;
  errorClamp = 0;
  degrees = M_Claw_Rotate.get_position();
  currentClawPosition = closed;
}

void Claw::rotate()
{
  if(clockwise)
  {
    M_Claw_Rotate.move_relative(180, 120);
  }
  else
  {
    M_Claw_Rotate.move_relative(-180, 120);
  }

}

void Claw::initialize()
{
  M_Claw_Main.tare_position();
  currentClawPosition = closed;
}

void Claw::goToPosition(ClawPosition clawPosition)
{
  switch(clawPosition)
  {
    case open:  // Go to open
      if(currentClawPosition == closed)
      {
        M_Claw_Main.move_relative(0.75, 50);
      }
      else if(currentClawPosition == vertical)
      {
        M_Claw_Main.move_relative(-0.583, 50);
      }
      currentClawPosition = open;
      break;
    case closed:  // Go to closed
      if(currentClawPosition == open)
      {
        M_Claw_Main.move_relative(-0.75, 50);
      }
      else if(currentClawPosition == vertical)
      {
        M_Claw_Main.move_relative(-1.333, 50);
      }
      currentClawPosition = closed;
      break;
    case vertical:  // Go to vertial
      if(currentClawPosition == open)
      {
        M_Claw_Main.move_relative(0.583, 50);
      }
      else if(currentClawPosition == closed)
      {
        M_Claw_Main.move_relative(1.333, 50);
      }
      currentClawPosition = vertical;
      break;
  }
}

/*
 * Lift Class
 */

Lift::Lift()
{
  M_Lift_L.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  M_Lift_R.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  currentLiftPosition = ground;
  errorPosition = 0;
}

void Lift::control(bool goingUp)
{
  int speed = 50;

  if(goingUp)
  {
    M_Lift_L = speed;
    M_Lift_R = speed;
  }
  else
  {
    M_Lift_L = -speed;
    M_Lift_R = -speed;
  }
}

void Lift::run(int speed, double inches = -1)
{
  M_Lift_L = speed;
  M_Lift_R = speed;
}

void Lift::liftAndFlip()
{
  M_Lift_L.move_relative(1.5, 50); //FIXME
  M_Lift_R.move_relative(1.5, 50); //FIXME
  delay(2000); //FIXME
  LargeRobot.ClawObj.rotate();
  delay(2000); //FIXME
  M_Lift_L.move_relative(-1.5, 50); //FIXME
  M_Lift_R.move_relative(-1.5, 50); //FIXME
}
void Lift::scoreCap()
{
  M_Lift_L.move_relative(-2 / M_PI / 4, 50); //FIXME
  M_Lift_R.move_relative(-2 / M_PI / 4, 50); //FIXME
  delay(2000); //FIXME
  LargeRobot.ClawObj.goToPosition(open);
  LargeRobot.ClawObj.currentClawPosition = open;
  delay(2000); //FIXME
  M_Lift_L.move_relative(2 / M_PI / 4, 50); //FIXME
  M_Lift_R.move_relative(2 / M_PI / 4, 50); //FIXME
}

void Lift::goToPosition(LiftPosition liftPosition)
{
  double inches;
  switch(liftPosition)
  {
    case ground:  // Go to ground
      if(currentLiftPosition == flipPosition)
      {
        inches = -4.75;
        M_Lift_L.move_relative(inches / 2.75 / M_PI, 90);
        M_Lift_R.move_relative(inches / 2.75 / M_PI, 90);
      }
      else if(currentLiftPosition == midPost)
      {
        inches = -23.25;
        M_Lift_L.move_relative(inches / 2.75 / M_PI, 90);
        M_Lift_R.move_relative(inches / 2.75 / M_PI, 90);
      }
      currentLiftPosition = ground;
      break;
    case flipPosition:  // Go to flipPosition
      if(currentLiftPosition == ground)
      {
        inches = 4.75;
        M_Lift_L.move_relative(inches / 2.75 / M_PI, 90);
        M_Lift_R.move_relative(inches / 2.75 / M_PI, 90);
      }
      else if(currentLiftPosition == midPost)
      {
        inches = -18.5;
        M_Lift_L.move_relative(inches / 2.75 / M_PI, 90);
        M_Lift_R.move_relative(inches / 2.75 / M_PI, 90);
      }
      currentLiftPosition = midPost;
      break;
    case midPost:  // Go to midPost
      if(currentLiftPosition == ground)
      {
        inches = 23.25;
        M_Lift_L.move_relative(inches / 2.75 / M_PI, 90);
        M_Lift_R.move_relative(inches / 2.75 / M_PI, 90);
      }
      else if(currentLiftPosition == flipPosition)
      {
        inches = 18.5;
        M_Lift_L.move_relative(inches / 2.75 / M_PI, 90);
        M_Lift_R.move_relative(inches / 2.75 / M_PI, 90);
      }
      currentLiftPosition = midPost;
      break;
  }
}

/*
 * Robot Class
 */

Robot::Robot(){
  //position[0] = 0;
  //position[1] = 0;
  lastPosition[0] = 0;
  lastPosition[1] = 0;
  setpoint_theta = 0;
  setpoint_distance = 0;
  robotTurnIsDone = true;
}

void Robot::resetPosition()
{
  //position[0] = 0;
  //position[1] = 0;
}

//void Robot::getPosition()

//void Robot::teleop(Controller C0 = Controller0, Controller C1 = Controller1)

void Robot::teleop()
{
//  DrivetrainObj.tankDrive(Controller0.get_analog(E_CONTROLLER_ANALOG_LEFT_Y),
//                          Controller0.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y));

  DrivetrainObj.arcadeDrive(Controller0.get_analog(E_CONTROLLER_ANALOG_LEFT_X),
                          Controller0.get_analog(E_CONTROLLER_ANALOG_LEFT_Y));


  IntakeObj.run((Controller0.get_digital(E_CONTROLLER_DIGITAL_L1))?100:(Controller0.get_digital(E_CONTROLLER_DIGITAL_L2))?-100:0, both);
  //TurretObj.run(0);

  M_Flywheel_Hood = Controller0.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);

  //pros::lcd::print(7, "Hood Angle: %f Deg", LargeRobot.TurretObj.currentHoodAngle);

  ClawObj.degrees = M_Claw_Rotate.get_position();
  ClawObj.errorRotate = M_Claw_Rotate.get_position() - M_Claw_Rotate.get_target_position();
  ClawObj.errorClamp = M_Claw_Main.get_position() - M_Claw_Main.get_target_position();
  LiftObj.errorPosition = M_Lift_L.get_position() - M_Lift_L.get_target_position();

  // Controller0
  switch(controller_digital_e_t var = E_CONTROLLER_DIGITAL_A)
  {
    case E_CONTROLLER_DIGITAL_A:
      if(Controller0.get_digital_new_press(E_CONTROLLER_DIGITAL_A))
      {
        contValues[0] = "A";
        TurretObj.run(600);
      }
    case E_CONTROLLER_DIGITAL_B:
      if(Controller0.get_digital(E_CONTROLLER_DIGITAL_B))
      {
        contValues[1] = "B";
        TurretObj.run(0);
      }
    case E_CONTROLLER_DIGITAL_X:
      if(Controller0.get_digital(E_CONTROLLER_DIGITAL_X))
      {
        contValues[2] = "X";
      }
    case E_CONTROLLER_DIGITAL_Y:
      if(Controller0.get_digital(E_CONTROLLER_DIGITAL_Y))
      {
        contValues[3] = "Y";
      }
    case E_CONTROLLER_DIGITAL_L1:
      if(Controller0.get_digital(E_CONTROLLER_DIGITAL_L1))
      {
        contValues[4] = "L1";
        //intakeSpeed = -50;
      }
    case E_CONTROLLER_DIGITAL_L2:
      if(Controller0.get_digital(E_CONTROLLER_DIGITAL_L2))
      {
        contValues[5] = "L2";
      }
    case E_CONTROLLER_DIGITAL_R1:
    if(Controller0.get_digital_new_press(E_CONTROLLER_DIGITAL_R1))
    {
      contValues[6] = "R1";
      if(fabs(ClawObj.errorClamp <= 0.2) && M_Claw_Main.get_actual_velocity() < 2)
      {
        if(ClawObj.currentClawPosition == open)
        {
          ClawObj.goToPosition(closed);
          ClawObj.currentClawPosition = closed;
        }
        else if(ClawObj.currentClawPosition == closed)
        {
          ClawObj.goToPosition(open);
          ClawObj.currentClawPosition = open;
        }
      }
    }
    case E_CONTROLLER_DIGITAL_R2:
      if(Controller0.get_digital_new_press(E_CONTROLLER_DIGITAL_R2))
      {
        contValues[7] = "R2";
        if(fabs(ClawObj.errorRotate <= 2) && M_Claw_Rotate.get_actual_velocity() < 2)
        {
          ClawObj.rotate();
          ClawObj.clockwise = !ClawObj.clockwise;
        }
      }
    case E_CONTROLLER_DIGITAL_UP:
      if(Controller0.get_digital(E_CONTROLLER_DIGITAL_UP))
      {
        contValues[8] = "U";
      }
    case E_CONTROLLER_DIGITAL_DOWN:
      if(Controller0.get_digital(E_CONTROLLER_DIGITAL_DOWN))
      {
        contValues[9] = "D";
      }
    case E_CONTROLLER_DIGITAL_LEFT:
      if(Controller0.get_digital(E_CONTROLLER_DIGITAL_LEFT))
      {
        contValues[10] = "L";
      }
    case E_CONTROLLER_DIGITAL_RIGHT:
      if(Controller0.get_digital(E_CONTROLLER_DIGITAL_RIGHT))
      {
        contValues[11] = "R";
      }
    break;
  }

  // Controller1
  //if((!Controller1.get_digital(E_CONTROLLER_DIGITAL_L1) || !Controller1.get_digital(E_CONTROLLER_DIGITAL_L2)) && fabs(LiftObj.errorPosition) > 0.1)
    //
  switch(controller_digital_e_t var = E_CONTROLLER_DIGITAL_A)
  {
    case E_CONTROLLER_DIGITAL_A:
    if(Controller1.get_digital_new_press(E_CONTROLLER_DIGITAL_A))
    {
      //if(fabs(LiftObj.errorPosition) > 0.1)
      //LiftObj.run(Controller1.get_analog(E_CONTROLLER_ANALOG_LEFT_Y) * 0.5, 0);

    }
    case E_CONTROLLER_DIGITAL_B:
    if(Controller1.get_digital_new_press(E_CONTROLLER_DIGITAL_B))
    {
      LargeRobot.LiftObj.liftAndFlip();
    }
    case E_CONTROLLER_DIGITAL_X:
    if(Controller1.get_digital(E_CONTROLLER_DIGITAL_X))
    {

    }
    case E_CONTROLLER_DIGITAL_Y:
    if(Controller1.get_digital_new_press(E_CONTROLLER_DIGITAL_Y))
    {
      LargeRobot.LiftObj.scoreCap();
    }
    case E_CONTROLLER_DIGITAL_L1:
    if(Controller1.get_digital_new_press(E_CONTROLLER_DIGITAL_L1))
    {
      if(fabs(LiftObj.errorPosition <= 0.2) && M_Lift_L.get_actual_velocity() < 2)
      {
        if(LiftObj.currentLiftPosition == ground)
        {
          LiftObj.goToPosition(flipPosition);
          LiftObj.currentLiftPosition = flipPosition;
        }
        else if(LiftObj.currentLiftPosition == flipPosition)
        {
          LiftObj.goToPosition(midPost);
          LiftObj.currentLiftPosition = midPost;
        }
        else if(LiftObj.currentLiftPosition == midPost)
        {
          //LiftObj.goToPosition(open);
          LiftObj.currentLiftPosition = midPost; //FIXME
        }
      }
    }
    case E_CONTROLLER_DIGITAL_L2:
    if(Controller1.get_digital_new_press(E_CONTROLLER_DIGITAL_L2))
    {
      if(fabs(LiftObj.errorPosition <= 0.2) && M_Lift_L.get_actual_velocity() < 2)
      {
        if(LiftObj.currentLiftPosition == ground)
        {
          LiftObj.currentLiftPosition = ground;
        }
        else if(LiftObj.currentLiftPosition == flipPosition)
        {
          LiftObj.goToPosition(ground);
          LiftObj.currentLiftPosition = ground;
        }
        else if(LiftObj.currentLiftPosition == midPost)
        {
          LiftObj.goToPosition(flipPosition);
          LiftObj.currentLiftPosition = flipPosition;
        }
      }
    }
    case E_CONTROLLER_DIGITAL_R1:
/*    if(Controller1.get_digital(E_CONTROLLER_DIGITAL_R1))
    {
      M_Flywheel_Hood = 50;
    }
    case E_CONTROLLER_DIGITAL_R2:
    if(Controller1.get_digital(E_CONTROLLER_DIGITAL_R2))
    {
      M_Flywheel_Hood = 50;
    }*/
    if(Controller1.get_digital_new_press(E_CONTROLLER_DIGITAL_R1))
    {
      if(fabs(ClawObj.errorClamp <= 0.2) && M_Claw_Main.get_actual_velocity() < 2)
      {
        if(ClawObj.currentClawPosition == open)
        {
          ClawObj.goToPosition(closed);
          ClawObj.currentClawPosition = closed;
        }
        else if(ClawObj.currentClawPosition == closed)
        {
          ClawObj.goToPosition(open);
          ClawObj.currentClawPosition = open;
        }
      }
    }
    case E_CONTROLLER_DIGITAL_R2:
      if(Controller1.get_digital_new_press(E_CONTROLLER_DIGITAL_R2))
      {
        if(fabs(ClawObj.errorRotate <= 2) && M_Claw_Rotate.get_actual_velocity() < 2)
        {
          ClawObj.rotate();
          ClawObj.clockwise = !ClawObj.clockwise;
        }
      }
    case E_CONTROLLER_DIGITAL_UP:
    if(Controller1.get_digital(E_CONTROLLER_DIGITAL_UP))
    {

    }
    case E_CONTROLLER_DIGITAL_DOWN:
    if(Controller1.get_digital(E_CONTROLLER_DIGITAL_DOWN))
    {

    }
    case E_CONTROLLER_DIGITAL_LEFT:
    if(Controller1.get_digital(E_CONTROLLER_DIGITAL_LEFT))
    {

    }
    case E_CONTROLLER_DIGITAL_RIGHT:
    if(Controller1.get_digital(E_CONTROLLER_DIGITAL_RIGHT))
    {

    }
    break;
  }

  //IntakeObj.run(intakeSpeed, mainIntake);
  //M_Intake_Main = intakeSpeed;

  contValues[12] = std::to_string(Controller0.get_analog(E_CONTROLLER_ANALOG_RIGHT_X));
  contValues[13] = std::to_string(Controller0.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y));
  contValues[14] = std::to_string(Controller0.get_analog(E_CONTROLLER_ANALOG_LEFT_Y));
  contValues[15] = std::to_string(Controller0.get_analog(E_CONTROLLER_ANALOG_LEFT_X));

}

void Robot::teleoptesting()
{
//  DrivetrainObj.tankDrive(Controller0.get_analog(E_CONTROLLER_ANALOG_LEFT_Y),
//                          Controller0.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y));

  //DrivetrainObj.arcadeDrive(Controller0.get_analog(E_CONTROLLER_ANALOG_LEFT_X),
  //                        Controller0.get_analog(E_CONTROLLER_ANALOG_LEFT_Y));


  IntakeObj.run((Controller0.get_digital(E_CONTROLLER_DIGITAL_L1))?100:(Controller0.get_digital(E_CONTROLLER_DIGITAL_L2))?-100:0, both);
  //TurretObj.run(0);

  M_Flywheel_Hood = Controller0.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
  M_Flywheel_Turret = Controller0.get_analog(E_CONTROLLER_ANALOG_LEFT_X);

  //pros::lcd::print(7, "Hood Angle: %f Deg", LargeRobot.TurretObj.currentHoodAngle);

  ClawObj.degrees = M_Claw_Rotate.get_position();
  ClawObj.errorRotate = M_Claw_Rotate.get_position() - M_Claw_Rotate.get_target_position();
  ClawObj.errorClamp = M_Claw_Main.get_position() - M_Claw_Main.get_target_position();
  LiftObj.errorPosition = M_Lift_L.get_position() - M_Lift_L.get_target_position();

  // Controller0
  switch(controller_digital_e_t var = E_CONTROLLER_DIGITAL_A)
  {
    case E_CONTROLLER_DIGITAL_A:
      if(Controller0.get_digital_new_press(E_CONTROLLER_DIGITAL_A))
      {
        contValues[0] = "A";
        //TurretObj.run(600);|
        M_Flywheel_R = 127;
        M_Flywheel_F = 127;
      }
    case E_CONTROLLER_DIGITAL_B:
      if(Controller0.get_digital(E_CONTROLLER_DIGITAL_B))
      {
        contValues[1] = "B";
        TurretObj.run(0);
      }
    case E_CONTROLLER_DIGITAL_X:
      if(Controller0.get_digital(E_CONTROLLER_DIGITAL_X))
      {
        contValues[2] = "X";
      }
    case E_CONTROLLER_DIGITAL_Y:
      if(Controller0.get_digital(E_CONTROLLER_DIGITAL_Y))
      {
        contValues[3] = "Y";
      }
    case E_CONTROLLER_DIGITAL_L1:
      if(Controller0.get_digital(E_CONTROLLER_DIGITAL_L1))
      {
        contValues[4] = "L1";

      }
    case E_CONTROLLER_DIGITAL_L2:
      if(Controller0.get_digital(E_CONTROLLER_DIGITAL_L2))
      {
        contValues[5] = "L2";
      }
    case E_CONTROLLER_DIGITAL_R1:
    if(Controller0.get_digital_new_press(E_CONTROLLER_DIGITAL_R1))
    {
      contValues[6] = "R1";
    }
    case E_CONTROLLER_DIGITAL_R2:
      if(Controller0.get_digital_new_press(E_CONTROLLER_DIGITAL_R2))
      {

      }
    case E_CONTROLLER_DIGITAL_UP:
      if(Controller0.get_digital(E_CONTROLLER_DIGITAL_UP))
      {
        contValues[8] = "U";
      }
    case E_CONTROLLER_DIGITAL_DOWN:
      if(Controller0.get_digital(E_CONTROLLER_DIGITAL_DOWN))
      {
        contValues[9] = "D";
      }
    case E_CONTROLLER_DIGITAL_LEFT:
      if(Controller0.get_digital(E_CONTROLLER_DIGITAL_LEFT))
      {
        contValues[10] = "L";
      }
    case E_CONTROLLER_DIGITAL_RIGHT:
      if(Controller0.get_digital(E_CONTROLLER_DIGITAL_RIGHT))
      {
        contValues[11] = "R";
      }
    break;
  }

  // Controller1
  //if((!Controller1.get_digital(E_CONTROLLER_DIGITAL_L1) || !Controller1.get_digital(E_CONTROLLER_DIGITAL_L2)) && fabs(LiftObj.errorPosition) > 0.1)
    //
  switch(controller_digital_e_t var = E_CONTROLLER_DIGITAL_A)
  {
    case E_CONTROLLER_DIGITAL_A:
    if(Controller1.get_digital(E_CONTROLLER_DIGITAL_A))
    {

    }
    case E_CONTROLLER_DIGITAL_B:
    if(Controller1.get_digital(E_CONTROLLER_DIGITAL_B))
    {

    }
    case E_CONTROLLER_DIGITAL_X:
    if(Controller1.get_digital(E_CONTROLLER_DIGITAL_X))
    {

    }
    case E_CONTROLLER_DIGITAL_Y:
    if(Controller1.get_digital(E_CONTROLLER_DIGITAL_Y))
    {

    }
    case E_CONTROLLER_DIGITAL_L1:
    if(Controller1.get_digital_new_press(E_CONTROLLER_DIGITAL_L1))
    {

    }
    case E_CONTROLLER_DIGITAL_L2:
    if(Controller1.get_digital_new_press(E_CONTROLLER_DIGITAL_L2))
    {

    }
    case E_CONTROLLER_DIGITAL_R1:
    if(Controller1.get_digital(E_CONTROLLER_DIGITAL_R1))
    {

    }
    case E_CONTROLLER_DIGITAL_R2:
    if(Controller1.get_digital(E_CONTROLLER_DIGITAL_R2))
    {

    }
    if(Controller1.get_digital_new_press(E_CONTROLLER_DIGITAL_R1))
    {

    }
    case E_CONTROLLER_DIGITAL_UP:
    if(Controller1.get_digital(E_CONTROLLER_DIGITAL_UP))
    {

    }
    case E_CONTROLLER_DIGITAL_DOWN:
    if(Controller1.get_digital(E_CONTROLLER_DIGITAL_DOWN))
    {

    }
    case E_CONTROLLER_DIGITAL_LEFT:
    if(Controller1.get_digital(E_CONTROLLER_DIGITAL_LEFT))
    {

    }
    case E_CONTROLLER_DIGITAL_RIGHT:
    if(Controller1.get_digital(E_CONTROLLER_DIGITAL_RIGHT))
    {

    }
    break;
  }

  //IntakeObj.run(intakeSpeed, mainIntake);
  //M_Intake_Main = intakeSpeed;

  contValues[12] = std::to_string(Controller0.get_analog(E_CONTROLLER_ANALOG_RIGHT_X));
  contValues[13] = std::to_string(Controller0.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y));
  contValues[14] = std::to_string(Controller0.get_analog(E_CONTROLLER_ANALOG_LEFT_Y));
  contValues[15] = std::to_string(Controller0.get_analog(E_CONTROLLER_ANALOG_LEFT_X));

}

void Robot::drive(int speed)
{
  DrivetrainObj.drive(speed);
}

void Robot::drive(int speedL, int speedR)
{
  DrivetrainObj.drive(speedL, speedR);
}

void Robot::drive(driveType type, double distance, int speed)
{
  switch(type)
  {
    case forward:
      DrivetrainObj.drive(forward, distance, speed);
      break;
    case reverse:
      DrivetrainObj.drive(reverse, distance, speed);
      break;
    case leftPoint:
      DrivetrainObj.drive(leftPoint, distance, speed);
      break;
    case rightPoint:
      DrivetrainObj.drive(rightPoint, distance, speed);
      break;
  }
}

void Robot::tankDrive(int speedL, int speedR)
{
  DrivetrainObj.tankDrive(speedL, speedR);
}

void Robot::eStop()
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
  disabled();
}


void Robot::runIntake(int speed, intakeType type)
{
  switch (type)
  {
    case mainIntake:
      M_Intake_Main = speed;
      break;
    case preflywheel:
      M_Intake_Preflywheel = speed;
      break;
    case both:
      M_Intake_Main = speed;
      M_Intake_Preflywheel = speed;
  }
}

void Robot::runAllMotors(int speed)
{
  M_Drivetrain_LF = speed;
  M_Drivetrain_LM = speed;
  M_Drivetrain_LR = speed;
  M_Drivetrain_RF = speed;
  M_Drivetrain_RM = speed;
  M_Drivetrain_RR = speed;

  M_Intake_Main = speed;
  M_Intake_Preflywheel = speed;

  M_Flywheel_F = speed;
  M_Flywheel_R = speed;
  M_Flywheel_Hood = speed;
  M_Flywheel_Turret = speed;

  M_Claw_Rotate = speed;

  M_Lift_L = speed;
  M_Lift_R = speed;

  M_Donger_Main = speed;

  M_Ramalign_Main = speed;
}

// From Robot Mapping
void Robot::goToWaypoint(Waypoint wp)
{
  // (1)
  Waypoint start;
  start.position[0] = telemetry.position[0];
  start.position[1] = telemetry.position[1];
  Waypoint end = wp;

  // (2)
  int vector_up[2] = {0,1};
  double vector_1[2] = {end.position[0]-start.position[0], end.position[1]-start.position[1]};

  // (3)
  double theta_1 = acos((vector_1[1])/(sqrt(vector_1[0]*vector_1[0] + vector_1[1]*vector_1[1]) ));
  theta_1 *= 180 / M_PI;

  // (4)
  if(vector_1[0] < 0)
    theta_1 *= -1;

  // (5)
  start.heading = telemetry.heading; // IN -170.999999 to 180.0

  if(start.heading < 0)
  {
    start.heading += 360;   // IN 0 to 360
  }

  // (6)
  //bool runClockwise;
  if(start.heading < 180)
  {
    if(start.heading + 180 < theta_1)
      //CCW
      turnClockwise = false;
    else
      //CW
      turnClockwise = true;
  }
  else  // start.heading >= 180
  {
    if(start.heading - 180 < theta_1)
      //CCW
      turnClockwise = false;
    else
      //CW
      turnClockwise = true;
  }

  // (7)

  double unit_vector_0[2] = {sin(start.heading * M_PI / 180), cos(start.heading * M_PI / 180)};
  double unit_vector_1[2] = {sin(theta_1 * M_PI / 180), cos(theta_1 * M_PI / 180)};

  // (8)
  double theta_setpoint = acos( (unit_vector_0[0] * unit_vector_1[0] + unit_vector_0[1] * unit_vector_1[1])/
                                (sqrt(unit_vector_0[0]*unit_vector_0[0] + unit_vector_0[1]*unit_vector_0[1]) * sqrt(unit_vector_1[0]*unit_vector_1[0] + unit_vector_1[1]*unit_vector_1[1])));

  // (9) Run Turn PID

  if(!turnClockwise) theta_setpoint *= -1;

  LargeRobot.setpoint_theta = theta_setpoint;

  // (10) Get linear distance
  start.position[0] = telemetry.position[0];
  start.position[1] = telemetry.position[1];

  double distance_setpoint = sqrt((end.position[0] - start.position[0]) * (end.position[0] - start.position[0]) + (end.position[1] - start.position[1]) * (end.position[1] - start.position[1]));

  // (11) Run Drive PID
  LargeRobot.setpoint_distance = distance_setpoint;
}

void Robot::initializePreMatch()
{
  ClawObj.initialize();
}


//////////////////// END Class Definitions ////////////////////


/*
 *  Port Definitions
 *
 *  v5 Brain Map
 *
 *  (Left)                          (Right)
 *
 *  [11. M_Intake_Main ]            [1. M_Intake_Preflywheel ]
 *  [12. M_Flywheel_Turret ]        [2.  ]
 *  [13. M_Donger_Main ]            [3. M_Flywheel_F ]
 *  [14.  ]                         [4. M_Flywheel_R ]
 *  [15.  ]                         [5. M_Flywheel_Hood ]
 *
 *  [16. M_Drivetrain_LF ]          [6. M_Drivetrain_RF ]
 *  [17. M_Drivetrain_LM ]          [7. M_Drivetrain_RM ]
 *  [18. M_Drivetrain_LR ]          [8. M_Drivetrain_RR ]
 *  [19. M_Lift_L ]                 [9. M_Lift_R ]
 *  [20. M_Claw_Main ]          [10. M_Claw_Rotate ]
 *                        [21. VEXNet Radio ]
 *
 *  ADI PINS (3 Wire Ports)
 *  [A. P_Claw_Main]
 *
 */

/*
 * Motor Definitions
 *
 *  Motor m(int Port_1-21,
 *          E_MOTOR_GEARSET_36 (36:1, 100 RPM, Red)
 *                  /E_MOTOR_GEARSET_18 (18:1, 200 RPM, Green)
 *                  /E_MOTOR_GEARSET_06 (6:1, 600 RPM, Blue),
 *          bool is_reversed,
 *          E_MOTOR_ENCODER_DEGREES
 *                  /E_MOTOR_ENCODER_ROTATIONS
 *                  /E_MOTOR_ENCODER_COUNTS)
 */

/*
 * Drivetrain Motors (M_Drivetrain)
 */

/*Reverses Drivetrain Motors if true (Normally false)*/
bool driveIsReversed = false;

/* Left-front Drivetrain Motor */
Motor M_Drivetrain_LF(16,E_MOTOR_GEARSET_18,driveIsReversed,E_MOTOR_ENCODER_ROTATIONS);

/* Left-middle Drivetrain Motor */
Motor M_Drivetrain_LM(17,E_MOTOR_GEARSET_18,driveIsReversed,E_MOTOR_ENCODER_ROTATIONS);

/* Left-rear Drivetrain Motor */
Motor M_Drivetrain_LR(18,E_MOTOR_GEARSET_18,driveIsReversed,E_MOTOR_ENCODER_ROTATIONS);

/* Right-front Drivetrain Motor */
Motor M_Drivetrain_RF(6,E_MOTOR_GEARSET_18,!driveIsReversed,E_MOTOR_ENCODER_ROTATIONS);

/* Right-middle Drivetrain Motor */
Motor M_Drivetrain_RM(7,E_MOTOR_GEARSET_18,!driveIsReversed,E_MOTOR_ENCODER_ROTATIONS);

/* Right-rear Drivetrain Motor */
Motor M_Drivetrain_RR(8,E_MOTOR_GEARSET_18,!driveIsReversed,E_MOTOR_ENCODER_ROTATIONS);

/*
 * (Ball) Intake Motors (M_Intake)
 */

/*Reverses (Ball) Intake Motors if true (Normally false)*/
bool intakeIsReversed = true;

/* Main (Front) (Ball) Intake Motor */
Motor M_Intake_Main(11,E_MOTOR_GEARSET_06,intakeIsReversed,E_MOTOR_ENCODER_ROTATIONS);

/* Pre-flywheel Intake Motor */
Motor M_Intake_Preflywheel(1,E_MOTOR_GEARSET_06,intakeIsReversed,E_MOTOR_ENCODER_ROTATIONS);

/*
 * Flywheel (Shooter) Motors (M_Flywheel)
 */

/*Reverses Flywheel Shooter Motors if true (Normally false)*/
bool flywheelIsReversed = false;

/* Flywheel Lazy Susan (Turret) Rotation Motor */
Motor M_Flywheel_Turret(12,E_MOTOR_GEARSET_36,!flywheelIsReversed,E_MOTOR_ENCODER_DEGREES);

/* Flywheel Main Forward Driven Motor */
Motor M_Flywheel_F(3,E_MOTOR_GEARSET_06,flywheelIsReversed,E_MOTOR_ENCODER_ROTATIONS);

/* Flywheel Main Rear Driven Motor */
Motor M_Flywheel_R(4,E_MOTOR_GEARSET_06,!flywheelIsReversed,E_MOTOR_ENCODER_ROTATIONS);

/* Flywheel Hood Motor */
Motor M_Flywheel_Hood(5,E_MOTOR_GEARSET_18,flywheelIsReversed,E_MOTOR_ENCODER_ROTATIONS);

/*
 * Cap Intake (Claw) Motors and Pneumatics (Actuators) (M_Claw and P_Claw)
 */

/*Reverses Claw Acutators if true (Normally false)*/
bool clawIsReversed = false;
bool clawStartsExtended = false;

/* Claw Cap Grabbing Pneumatic Actuator */
//Piston P_Claw_Main('A', clawStartsExtended);
//ADIDigitalOut P_Claw_Main('A', clawIsReversed);
Motor M_Claw_Main(20,E_MOTOR_GEARSET_36,clawIsReversed,E_MOTOR_ENCODER_ROTATIONS);

/* Claw Rotation (Cap flip) Motor */
Motor M_Claw_Rotate(10,E_MOTOR_GEARSET_36,clawIsReversed,E_MOTOR_ENCODER_DEGREES);

/*
 * (Cap) Lift Motors (M_Drivetrain)
 */

/*Reverses Lift Motors if true (Normally false)*/
bool liftIsReversed = true;

/* Left-front Drivetrain Motor */
Motor M_Lift_L(19,E_MOTOR_GEARSET_18,liftIsReversed,E_MOTOR_ENCODER_ROTATIONS);

/* Left-middle Drivetrain Motor */
Motor M_Lift_R(9,E_MOTOR_GEARSET_18,!liftIsReversed,E_MOTOR_ENCODER_ROTATIONS);

/*
 * Donger (Cap Tilter for Ball Intake) Motor (M_Donger)
 */

/*Reverses Donger Motor if true (Normally false)*/
bool dongerIsReversed = false;

/* Left-front Drivetrain Motor */
Motor M_Donger_Main(13,E_MOTOR_GEARSET_18,dongerIsReversed,E_MOTOR_ENCODER_DEGREES);

/*
 * Ram Align Motor (M_Ramalign)
 */

/*Reverses Ram Align Motor if true (Normally false)*/
bool ramAlignIsReversed = false;

/* Left-front Drivetrain Motor */
Motor M_Ramalign_Main(20,E_MOTOR_GEARSET_18,ramAlignIsReversed,E_MOTOR_ENCODER_ROTATIONS);

//////////////////// END MOTORS ////////////////////

/*
 * Sensors Definitions
 */

/*
 * Cameras (VEX Vision Sensors) (S_Camera)
 */

/* Flywheel Camera (VEX Vision Sensor) */
//Vision S_Camera_Flywheel (2);

//////////////////// END Sensors ////////////////////

/*
 * Robot Object Defintion
 */

Robot LargeRobot;
