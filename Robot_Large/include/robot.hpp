#ifndef ROBOT_HPP
#define ROBOT_HPP

#include "api.h"
#include "okapi/api.hpp"
#include "controller.hpp"

using namespace okapi;
/*
 * FILE DESCRIPTION
 * robot.hpp lays out the definitions of the functions, classes, and objects
 * related to the robot's structure and function.
 */

/*
 * Drivetrain pros::Motors (M_Drivetrain)
 */


class PYROChassis
{
 private:
   const okapi::MotorGroup MG_Drivetrain_Left = {1,-2,3};
   const okapi::MotorGroup MG_Drivetrain_Right = {-6,7,-8};
   const okapi::QLength WHEEL_DIAMETER = 3.95_in;
   const okapi::QLength CHASSIS_WIDTH = 12.25_in;
   const okapi::AbstractMotor::GearsetRatioPair ratio = okapi::AbstractMotor::gearset::green;// * (1.0382);

 public:
   ChassisControllerPID MasterController;// = ChassisControllerFactory::create(
      //MG_Drivetrain_Left, MG_Drivetrain_Right,
      //IterativePosPIDController::Gains{0.0045, 0.005, 0.00008},
      //IterativePosPIDController::Gains{0.00003, 0.00003, 0.00001},
      //IterativePosPIDController::Gains{0.0006, 0.00008, 0.00008},
      //ratio,
      //{WHEEL_DIAMETER, CHASSIS_WIDTH}
    //);

    //FIXME: Make ChassisControllerIntegrated into ChassisControllerPID

    okapi::AsyncMotionProfileController MotionController;// = AsyncControllerFactory::motionProfile(
      //10.0,  // Maximum linear velocity of the Chassis in m/s
      //0.5,  // Maximum linear acceleration of the Chassis in m/s/s
      //10.0, // Maximum linear jerk of the Chassis in m/s/s/s
      //MasterController // Chassis Controller
    //);

    void teleop( ControllerMode mode = tank, pros::Controller Cont = Controller_0);
    PYROChassis(int);
} extern chassis;
/*
class PYROIntake
{
  private:
    pros::Motor intakeMotors[2];

  public:
    void runMainIntake(int signal);
    void runMainIntake(int signal);
    void runAllMotors(int signal);
    void teleop( ControllerMode mode = tank, pros::Controller Cont = Controller_0);
    PYROIntake(int);
} extern intake;
*/

/*
 * (Ball) Intake pros::Motors (M_Intake)
 */

extern bool intakeIsReversed;

extern pros::Motor M_Intake_Main;
extern pros::Motor M_Intake_Preflywheel;

/*
 * Flywheel (Shooter) pros::Motors (M_Flywheel)
 */

extern bool flywheelIsReversed;

extern pros::Motor M_Flywheel_Turret;
extern pros::Motor M_Flywheel_F;
extern pros::Motor M_Flywheel_R;
extern pros::Motor M_Flywheel_Hood;

/*
 * Cap Intake (Claw) pros::Motors and Pneumatics (Actuators) (M_Claw and P_Claw)
 */

extern bool clawIsReversed;
extern bool clawStartsExtended;

//extern Piston P_Claw_Main;
//extern ADIDigitalOut P_Claw_Main;
//extern pros::Motor M_Claw_Main;
extern pros::Motor M_Claw_Rotate;

/*
 * (Cap) Lift pros::Motors (M_Drivetrain)
 */

extern bool liftIsReversed;

extern pros::Motor M_Lift_L;
extern pros::Motor M_Lift_R;

/*
 * Donger (Cap Tilter for Ball Intake) pros::Motor (M_Donger)
 */

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
