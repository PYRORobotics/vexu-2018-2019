#include "api.h"
#include "okapi/api.hpp"

using namespace okapi;
/*
 * FILE DESCRIPTION
 * robot.hpp lays out the definitions of the functions, classes, and objects
 * related to the robot's structure and function.
 */

/*
 * Drivetrain pros::Motors (M_Drivetrain)
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
