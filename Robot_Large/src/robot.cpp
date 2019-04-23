#include "../include/robot.hpp"
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

PYROChassis chassis1();*/
void PYROChassis::teleop(ControllerMode mode, pros::Controller Cont)
{
  //yaw = IMU_YAW;
  switch (mode)
  {
    case tank:
      MasterController.tank((double)Cont.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)/127, (double)Cont.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y)/127);
      break;
    case arcade:
      MasterController.arcade((double)Cont.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)/127, (double)Cont.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X)/127);
      break;
    case arcade2joysticks:
      MasterController.arcade((double)Cont.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)/127, (double)Cont.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)/127);
      break;
  }
}

PYROChassis::PYROChassis(int a) :  MasterController(ChassisControllerFactory::create(
   MG_Drivetrain_Left, MG_Drivetrain_Right,
   //IterativePosPIDController::Gains{0.001, 0.0008, 0.0005},   //straight
   //IterativePosPIDController::Gains{0.01, 0.08, 0.00009},    //correct drift
   //IterativePosPIDController::Gains{0.0045, 0.005, 0.00008},  //turn

   IterativePosPIDController::Gains{0.00001, 0.00001, 0.000006},   //straight
   IterativePosPIDController::Gains{0.000, 0.0, 0.0000},    //correct drift
   IterativePosPIDController::Gains{0.001, 0.00001, 0.00000},  //turn

   //IterativePosPIDController::Gains{0.05, 0.000, 0.000},   //straight
   //IterativePosPIDController::Gains{0.0, 0.0, 0.0000},    //correct drift
   //IterativePosPIDController::Gains{0.00, 0.00, 0.0000},  //turn
   ratio,
   {WHEEL_DIAMETER, CHASSIS_WIDTH}
 )), MotionController(AsyncControllerFactory::motionProfile(
   10.0,  // Maximum linear velocity of the Chassis in m/s
   0.5,  // Maximum linear acceleration of the Chassis in m/s/s
   10.0, // Maximum linear jerk of the Chassis in m/s/s/s
   PYROChassis::MasterController // Chassis Controller
 ))
{

}

double PYROChassis::turn(double degrees)
{
  MasterController.setBrakeMode(AbstractMotor::brakeMode::brake);
  while(1)
  {
    double error = degrees - HEADING_ADJUSTED;
    if(fabs(error) > 8)
    {
      MasterController.right(-(degrees - HEADING_ADJUSTED) / 180 * 0.6);
      MasterController.left((degrees - HEADING_ADJUSTED) / 180 * 0.6);
    }
    else if(error > 0)
    {
      MasterController.right(-0.015);
      MasterController.left(0.015);
    }
    else
    {
      MasterController.right(0.015);
      MasterController.left(-0.015);
    }

    if(fabs(error) < 0.1)
    {
      MasterController.stop();
      MasterController.waitUntilSettled();
      break;
    }
    pros::delay(20);
  }
    return 1;
}

//double PYROChassis::getYaw()
//{
//  return yaw;
//}

PYROChassis chassis(0);


/*
 * (Ball) Intake Motors (M_Intake)
 */

/*Reverses (Ball) Intake Motors if true (Normally false)*/
bool intakeIsReversed = true;

/* Main (Front) (Ball) Intake Motor */
pros::Motor M_Intake_Main(1,pros::E_MOTOR_GEARSET_06,intakeIsReversed,pros::E_MOTOR_ENCODER_ROTATIONS);

/* Pre-flywheel Intake Motor */
pros::Motor M_Intake_Preflywheel(2,pros::E_MOTOR_GEARSET_06,intakeIsReversed,pros::E_MOTOR_ENCODER_ROTATIONS);

PYROIntake::PYROIntake(int) : MainIntakePID(AsyncControllerFactory::posIntegrated(-1)), PreFlywheelIntakePID(AsyncControllerFactory::posIntegrated(-2))
{
  IntakeMain = &M_Intake_Main;
  Preflywheel = &M_Intake_Preflywheel;
  MainIntakePID.flipDisable(true);
  PreFlywheelIntakePID.flipDisable(true);
}

void PYROIntake::runMainIntake(int signal)
{
  IntakeMain -> move(signal);
}

void PYROIntake::runPreFlywheel(int signal)
{
  Preflywheel -> move(signal);
}

void PYROIntake::shootBall(int numBalls)
{
  if(numBalls > 0)
  {
    for(int i = 0; i < numBalls - 1; i++)
    {
      IntakeMain->move_relative(3 * M_PI, 100); //FIXME
      Preflywheel->move_relative(3 * M_PI, 100); //FIXME
      while ((Preflywheel->get_position() < Preflywheel->get_target_position()-0.1) || (Preflywheel->get_position() > Preflywheel->get_target_position()+0.1))
      {
        pros::delay(1);
      }
    }

    IntakeMain->move_relative(3 * M_PI, 100); //FIXME
    Preflywheel->move_relative(-3 * M_PI, -100); //FIXME
    while ((Preflywheel->get_position() < Preflywheel->get_target_position()-0.1) || (Preflywheel->get_position() > Preflywheel->get_target_position()+0.1))
    {
      pros::delay(1);
    }
  }
}

void PYROIntake::teleop(pros::Controller Cont)
{
  if(intake.MainIntakePID.isDisabled() &&
  intake.PreFlywheelIntakePID.isDisabled())
    {
    /*if(Cont.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
    {
      runMainIntake(100);
      runPreFlywheel(100);
    }
    else*/ if(Cont.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
    {
      runMainIntake(100);
      runPreFlywheel(-100);
    }
    else if(Cont.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
    {
      runMainIntake(-100);
      runPreFlywheel(-100);
    }
    else
    {
      runMainIntake(0);
      runPreFlywheel(0);
    }
  }
}

PYROIntake intake(0);

/*
 * Flywheel (Shooter) Motors (M_Flywheel)
 */

/*Reverses Flywheel Shooter Motors if true (Normally false)*/
bool flywheelIsReversed = false;

/* Flywheel Lazy Susan (Turret) Rotation Motor */
pros::Motor M_Flywheel_Turret(120,pros::E_MOTOR_GEARSET_36,!flywheelIsReversed,pros::E_MOTOR_ENCODER_DEGREES);

/* Flywheel Main Forward Driven Motor */
pros::Motor M_Flywheel_F(10,pros::E_MOTOR_GEARSET_06,flywheelIsReversed,pros::E_MOTOR_ENCODER_ROTATIONS);

/* Flywheel Main Rear Driven Motor */
pros::Motor M_Flywheel_R(9,pros::E_MOTOR_GEARSET_06,!flywheelIsReversed,pros::E_MOTOR_ENCODER_ROTATIONS);

/* Flywheel Hood Motor */
pros::Motor M_Flywheel_Hood(3,pros::E_MOTOR_GEARSET_18,flywheelIsReversed,pros::E_MOTOR_ENCODER_DEGREES);

PYROShooter::PYROShooter(int) : FlywheelPID(AsyncControllerFactory::velPID(
  {-9, 10}, 0.001, 0.0001)
 )
{
  FrontMotor = &M_Flywheel_F;
  RearMotor = &M_Flywheel_R;
  HoodMotor = &M_Flywheel_Hood;
  HoodMotor->tare_position();
  isRunning = 0;
  FlywheelPID.flipDisable(false); //FIXME Test default false?
}

void PYROShooter::setHoodAngle(double angle)
{
  if(angle >= HOOD_MIN_ANGLE && angle <= HOOD_MAX_ANGLE)
    HoodMotor->move_absolute((HOOD_MAX_ANGLE - angle)*201/14, 50); //FIXME Test and Increase speed?
}

void PYROShooter::runFlywheel(int rpm)
{
  //FrontMotor->move_velocity(500);
  FlywheelPID.setTarget(rpm);
}

int flywheelMillisSince;

void PYROShooter::teleop(pros::Controller Cont)
{
  if(Cont.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) //single shot
  {
    Cont.rumble(".");
    intake.MainIntakePID.flipDisable(false);
    intake.PreFlywheelIntakePID.flipDisable(false);
    //intake.MainIntakePID.reset();
    //intake.PreFlywheelIntakePID.reset();
    FlywheelPID.flipDisable(false);
    FlywheelPID.controllerSet(1);
    intake.MainIntakePID.setTarget(5000 + M_Intake_Main.get_position());
    intake.PreFlywheelIntakePID.setTarget(-5000 + M_Intake_Preflywheel.get_position());
    runFlywheel(80);
    pros::delay(500);
    FlywheelPID.waitUntilSettled();
    intake.MainIntakePID.setTarget(200 + M_Intake_Main.get_position());
    intake.PreFlywheelIntakePID.setTarget(200 + M_Intake_Preflywheel.get_position());
    intake.PreFlywheelIntakePID.waitUntilSettled();
    runFlywheel(0);
    intake.MainIntakePID.flipDisable(true);
    intake.PreFlywheelIntakePID.flipDisable(true);
    FlywheelPID.flipDisable(true);

    pros::lcd::print(7, "Shooting");
  }
  else if(Cont.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1))  //double shot
  {
    Cont.rumble("- .");
    setHoodAngle(HIGH_FLAG_ANGLE);
    intake.MainIntakePID.flipDisable(false);
    intake.PreFlywheelIntakePID.flipDisable(false);
    //intake.MainIntakePID.reset();
    //intake.PreFlywheelIntakePID.reset();
    FlywheelPID.flipDisable(false);
    FlywheelPID.controllerSet(1);
    intake.MainIntakePID.setTarget(5000 + M_Intake_Main.get_position());
    intake.PreFlywheelIntakePID.setTarget(-5000 + M_Intake_Preflywheel.get_position());
    runFlywheel(82);
    pros::delay(500);
    FlywheelPID.waitUntilSettled();
    intake.MainIntakePID.setTarget(200 + M_Intake_Main.get_position());
    intake.PreFlywheelIntakePID.setTarget(200 + M_Intake_Preflywheel.get_position());
    intake.PreFlywheelIntakePID.waitUntilSettled();

    setHoodAngle(MID_FLAG_ANGLE);
    FlywheelPID.controllerSet(1);
    intake.MainIntakePID.setTarget(5000 + M_Intake_Main.get_position());
    intake.PreFlywheelIntakePID.setTarget(-5000 + M_Intake_Preflywheel.get_position());
    runFlywheel(82);
    pros::delay(500);
    FlywheelPID.waitUntilSettled();
    intake.MainIntakePID.setTarget(1000 + M_Intake_Main.get_position());
    intake.PreFlywheelIntakePID.setTarget(1000 + M_Intake_Preflywheel.get_position());
    intake.PreFlywheelIntakePID.waitUntilSettled();
    runFlywheel(0);
    intake.MainIntakePID.flipDisable(true);
    intake.PreFlywheelIntakePID.flipDisable(true);
    FlywheelPID.flipDisable(true);

    pros::lcd::print(7, "Shooting");
  }
  if(Controller_1.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1))
  {
    setHoodAngle(HIGH_FLAG_ANGLE);
    Cont.rumble(". . .");
    Controller_1.rumble(". . .");
  }
  else if(Controller_1.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2))
  {
    setHoodAngle(MID_FLAG_ANGLE);
    Cont.rumble("- - -");
    Controller_1.rumble("- - -");
  }
  if(Controller_1.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A))
  {
    FlywheelPID.flipDisable(false);
    FlywheelPID.setTarget(87);
  }
  else if(Controller_1.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B))
  {
    FlywheelPID.controllerSet(0);
    FlywheelPID.flipDisable(true);
  }
}

/*void PYROShooter::teleopTask(void*)
{
  teleop();
}*/

PYROShooter shooter(0);
/*
 * Cap Intake (Claw) Motors and Pneumatics (Actuators) (M_Claw and P_Claw)
 */

PYROArm::PYROArm(int) : ArmPID(AsyncControllerFactory::posIntegrated(-6,7)), claw(0)
{
  ArmLeft = &M_Arm_Left;
  ArmRight = &M_Arm_Right;
  isFirstTime = true;
  isCurrentlyDown = false;
  //ArmLeft->set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  //ArmRight->set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  speed = 0;
  ArmPID.reset();
}

void PYROArm::resetPos()
{
  ArmLeft -> tare_position();
  ArmRight -> tare_position();
}

void PYROArm::goToPos(double degrees, bool hold)
{
  if(hold)
  {
    ArmLeft -> set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    ArmRight -> set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  }
  else
  {
    ArmLeft -> set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    ArmRight -> set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  }
  ArmLeft -> move_absolute(degrees, 120);
  ArmRight -> move_absolute(degrees, 120);
}


//int armMillisSince;

void PYROArm::teleop()
{
  // if(isFirstTime) //initialize arm and also trying hood
  // {
  //   goToPos(-30);
  //   //HoodMotor->move_absolute((HOOD_MAX_ANGLE - HOOD_MIN_ANGLE)*201/14, 50);
  //   pros::delay(500);
  //   resetPos();
  //   //HoodMotor->tare_position();
  //   goToPos(105, false);
  //   //setHoodAngle(HIGH_FLAG_ANGLE);
  //   isFirstTime = false;
  //   isCurrentlyDown = false;
  // }
  claw.teleop(Controller_1);

  if(Controller_1.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1))
  {
    ArmPID.flipDisable(false);
    double target = ArmPID.getTarget();
    goToPos(450, true);
    isCurrentlyDown = true;
  }
  else if(Controller_1.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2))
  {
    ArmPID.flipDisable(false);
    double target = ArmPID.getTarget();
    goToPos(4, true);
    isCurrentlyDown = true;
  }
  else if(Controller_0.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X))
  {
    ArmPID.flipDisable(false);
    if (isCurrentlyDown)
    {
      goToPos(105, true);
      isCurrentlyDown = !isCurrentlyDown;
    }
    else
    {
      goToPos(4, true);
      isCurrentlyDown = !isCurrentlyDown;
    }
  }
}

PYROArm arm(0);


PYROClaw::PYROClaw(int)
{
  ClawMain = &M_Claw_Main;
  ClawRotate = &M_Claw_Rotate;
  ClawRotate->tare_position();
}

void PYROClaw::runIntake(int signal, bool inward)
{
  if(inward)
  {
    ClawMain->move(signal);
  }
  else
  {
    ClawMain->move(-signal);
  }
}

void PYROClaw::rotate(double deg)
{
  ClawRotate->move_absolute(deg, 50);
}


double lastTorques[100] = {0};
int torquei = 0;
double averageTorque = 0;
void PYROClaw::teleop(pros::Controller Cont)
{
  ClawRotate->set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  lastTorques[torquei] = ClawMain->get_torque();
  averageTorque = 0;
  for(int i = 0; i < 100; i++)
  {
    averageTorque += lastTorques[i];
  }
  averageTorque /= 100;

  runIntake(0);
    if(Cont.get_digital(pros::E_CONTROLLER_DIGITAL_UP))
    {
      pros::lcd::print(4, "Torque (Nm): %f", ClawMain->get_torque());
      pros::lcd::print(5, "AVG Torque (Nm): %f", averageTorque);
      ClawMain->set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

      if(averageTorque<0.2)
        runIntake(120);
    }
    else if(Cont.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
    {
      ClawMain->set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
      runIntake(-60);
    }

    if(Cont.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT))
    {
      if(ClawRotate->get_position() > -10)
        rotate(-181);
      else
        rotate(0);
    }



    /* //UNCOMMENT AND CHANGE NEW PRESS -> get_digital FOR HOLD INSTEAD OF TOGGLE
    else
    {
      runIntake(0);
    }*/

    if(torquei == 99)
      torquei = 0;
    else
      torquei++;
}

/*Reverses Claw Acutators if true (Normally false)*/
bool clawIsReversed = false;
bool clawStartsExtended = false;

/* Claw Cap Grabbing Pneumatic Actuator */
//Piston P_Claw_Main('A', clawStartsExtended);
//ADIDigitalOut P_Claw_Main('A', clawIsReversed);
pros::Motor M_Claw_Main(16,pros::E_MOTOR_GEARSET_36,clawIsReversed,pros::E_MOTOR_ENCODER_ROTATIONS);
//pros::Motor M_Claw_Main(121,pros::E_MOTOR_GEARSET_36,clawIsReversed,pros::E_MOTOR_ENCODER_ROTATIONS);

/* Claw Rotation (Cap flip) Motor */
pros::Motor M_Claw_Rotate(17,pros::E_MOTOR_GEARSET_36,!clawIsReversed,pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor M_Arm_Left(6, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor M_Arm_Right(7, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_DEGREES);

/*
 * (Cap) Lift Motors (M_Drivetrain)
 */

/*Reverses Lift Motors if true (Normally false)*/
bool liftIsReversed = true;

/* Left-front Drivetrain Motor */
//pros::Motor M_Lift_L(191,pros::E_MOTOR_GEARSET_18,liftIsReversed,pros::E_MOTOR_ENCODER_ROTATIONS);

/* Left-middle Drivetrain Motor */
//pros::Motor M_Lift_R(129,pros::E_MOTOR_GEARSET_18,!liftIsReversed,pros::E_MOTOR_ENCODER_ROTATIONS);

/*
 * Donger (Cap Tilter for Ball Intake) Motor (M_Donger)
 */
/*
 PYRODonger::PYRODonger(int) : DongerPID(AsyncControllerFactory::posIntegrated(104))
 {
   DongerMain = &M_Donger_Main;
 }

 void PYRODonger::resetPos()
 {
   DongerMain -> tare_position();
 }

 void PYRODonger::goToPos(double degrees, bool hold)
 {
   if(hold)
     DongerMain -> set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
   else
     DongerMain -> set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
   DongerMain -> move_absolute(degrees * 6, 100);
 }

 bool dongerCurrentlyDown = false;
 void PYRODonger::teleop(pros::Controller Cont)
 {

   if(Cont.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) //Dong balls
   {
     if(dongerCurrentlyDown)
     {
       //goToPos(190);
       DongerPID.setTarget(190*6);

       dongerCurrentlyDown = !dongerCurrentlyDown;
     }
     else
     {
       //goToPos(150); //faster up

       DongerPID.setTarget(150*6);

       dongerCurrentlyDown = !dongerCurrentlyDown;
     }
   }
     /*
     else if(Cont.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) //Flip
     {
       goToPos(0);
       while ((DongerMain->get_position() < DongerMain->get_target_position()-0.1) || (DongerMain->get_position() > DongerMain->get_target_position()+0.1))
       {
         pros::delay(1);
       }
       goToPos(0); //faster up
     }*/
 //}

// PYRODonger donger(0);

/*Reverses Donger Motor if true (Normally false)*/
bool dongerIsReversed = false;

/* Left-front Drivetrain Motor */
//pros::Motor M_Donger_Main(14,pros::E_MOTOR_GEARSET_18,dongerIsReversed,pros::E_MOTOR_ENCODER_DEGREES);

/*
 * Ram Align Motor (M_Ramalign)
 */

/*Reverses Ram Align Motor if true (Normally false)*/
bool ramAlignIsReversed = false;

/* Left-front Drivetrain Motor */
//pros::Motor M_Ramalign_Main(20,pros::E_MOTOR_GEARSET_18,ramAlignIsReversed,pros::E_MOTOR_ENCODER_ROTATIONS);

//////////////////// END MOTORS ////////////////////
