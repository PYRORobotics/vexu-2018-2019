#ifndef ROBOT_HPP
#define ROBOT_HPP

#include "api.h"
#include "okapi/api.hpp"
#include "controller.hpp"
#include "serial.hpp"

using namespace okapi;
/*
 * FILE DESCRIPTION
 * robot.hpp lays out the definitions of the functions, classes, and objects
 * related to the robot's structure and function.
 */

class PYROChassis
{
 private:

   const okapi::QLength WHEEL_DIAMETER = 3.95_in;
   const okapi::QLength CHASSIS_WIDTH = 12.25_in;
   const okapi::AbstractMotor::GearsetRatioPair ratio = okapi::AbstractMotor::gearset::green;// * (1.0382);
   //double yaw;
 public:
   const okapi::MotorGroup MG_Drivetrain_Left = {3,-4,5};
   const okapi::MotorGroup MG_Drivetrain_Right = {-8,9,-10};
   static double heading;
   static double x;
   static double y;
   static double ECL;
   static double ECR;
   ChassisControllerPID MasterController;// = ChassisControllerFactory::create(
      //MG_Drivetrain_Left, MG_Drivetrain_Right,
      //IterativePosPIDController::Gains{0.0045, 0.005, 0.00008},
      //IterativePosPIDController::Gains{0.00003, 0.00003, 0.00001},
      //IterativePosPIDController::Gains{0.0006, 0.00008, 0.00008},
      //ratio,
      //{WHEEL_DIAMETER, CHASSIS_WIDTH}
    //);

    okapi::AsyncMotionProfileController MotionController;// = AsyncControllerFactory::motionProfile(
      //10.0,  // Maximum linear velocity of the Chassis in m/s
      //0.5,  // Maximum linear acceleration of the Chassis in m/s/s
      //10.0, // Maximum linear jerk of the Chassis in m/s/s/s
      //MasterController // Chassis Controller
    //);

    double turn(double degrees);
    //double getYaw();
    void teleop( ControllerMode mode = tank, pros::Controller Cont = Controller_0);
    PYROChassis(int);
} extern chassis;




/*
 * (Ball) Intake pros::Motors (M_Intake)
 */

extern bool intakeIsReversed;

extern pros::Motor M_Intake_Main;
extern pros::Motor M_Intake_Preflywheel;

class PYROIntake
{
  private:


  public:
    pros::Motor* IntakeMain;
    pros::Motor* Preflywheel;
    okapi::AsyncPosIntegratedController MainIntakePID;
    okapi::AsyncPosIntegratedController PreFlywheelIntakePID;
    void runMainIntake(int signal);
    void runPreFlywheel(int signal);
    //void runAllMotors(int signal);
    void shootBall(int numBalls = 1);
    void teleop(pros::Controller Cont = Controller_0);
    PYROIntake(int);
} extern intake;

/*
 * Flywheel (Shooter) pros::Motors (M_Flywheel)
 */

extern bool flywheelIsReversed;

extern pros::Motor M_Flywheel_F;
extern pros::Motor M_Flywheel_R;
extern pros::Motor M_Flywheel_Hood;

class PYROShooter
{
  private:
    pros::Motor* FrontMotor;
    pros::Motor* RearMotor;
    pros::Motor* HoodMotor;
    bool isRunning;

  public:
    bool isCurrentlyMid;
    const double HOOD_MIN_ANGLE = 18;
    const double HOOD_MAX_ANGLE = 54;

    okapi::AsyncVelPIDController FlywheelPID;
    void runFlywheel(int signal);
    //void runAllMotors(int signal);
    void teleop(pros::Controller Cont = Controller_0);
    void setHoodAngle(double angle);
    PYROShooter(int);
} extern shooter;

/*
 * Cap Intake (Claw) pros::Motors and Pneumatics (Actuators) (M_Claw and P_Claw)
 */

 class PYROClaw
 {
  private:
    pros::Motor* ClawMain;

  public:
    void runIntake(int signal, bool inward = true);

    void teleop(pros::Controller Cont = Controller_0);
    PYROClaw(int);
 };

class PYROArm
{
 private:
   pros::Motor* ArmMain;
   int speed;

 public:
   //PYROClaw claw;
   okapi::AsyncPosIntegratedController ArmPID;
   void resetPos();
   void goToPos(double degrees, bool hold = true); //1:3

   void teleop();
   PYROArm(int);
} extern arm;


extern bool clawIsReversed;
extern bool clawStartsExtended;

//extern Piston P_Claw_Main;
//extern ADIDigitalOut P_Claw_Main;
extern pros::Motor M_Claw_Main;
//extern pros::Motor M_Claw_Rotate;
extern pros::Motor M_Arm_Main;

/*
 * (Cap) Lift pros::Motors (M_Drivetrain)
 */

extern bool liftIsReversed;

extern pros::Motor M_Lift_L;
extern pros::Motor M_Lift_R;

/*
 * Donger (Cap Tilter for Ball Intake) pros::Motor (M_Donger)
 */

 class PYRODonger
 {
  private:
    pros::Motor* DongerMain;

  public:
    okapi::AsyncPosIntegratedController DongerPID;
    void resetPos();
    void goToPos(double degrees, bool hold = false); //1:3

    void teleop(pros::Controller Cont = Controller_1);
    PYRODonger(int);
 } extern donger;

extern bool dongerIsReversed;

extern pros::Motor M_Donger_Main;

/*
 * Ram Align pros::Motor (M_Ramalign)
 */

extern bool ramAlignIsReversed;

extern pros::Motor M_Ramalign_Main;

//////////////////// END MOTORS ////////////////////
////////////////////////////////////////////////////

#endif
