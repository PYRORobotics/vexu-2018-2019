#include "../include/api.h"
#include "../include/controller.hpp"

/*
 * FILE DESCRIPTION
 * robot.hpp lays out the definitions of the functions, classes, and objects
 * related to the robot's structure and function.
 */

using namespace pros;

#ifdef __cplusplus
extern "C" {
#endif
void disabled(void);
#ifdef __cplusplus
}
#endif

/*
 *  See robot.cpp for detailed definitions
 */

enum driveType
{
  forward,
  reverse,
  leftPoint,
  rightPoint
};

struct Telemetry
{
  double position[2], heading, encoder_position_average, velocityL, velocityR, velocity;
};

struct Waypoint
{
  double position[2], heading;
};

static double motorPowerDifferential = 1;//0.990;
const double wheelBase = 14.25;
//double inToRotations = 1/4/M_PI;

/*
* Robot Class Definitions
*/

/* Pneumatic Piston Class (Uses Procedural-based ADI Digital-output Sensor) */

class Piston
{
 public:
   Piston(char portNum, bool normallyExtended);
   void extend();
   void retract();
 private:
   char port;
   bool isNormallyExtended;
};

/* LED Class (Uses Procedural-based ADI Analog-output Sensor) */

class LED
{
 public:
   LED(char portNum, double brightnessPct);
   void on();
   void off();
   pros::ADIAnalogOut LEDADIObj;
 protected:
   char port;
   double brightnessPct;
};

/* RGB LED (Common Cathode) Class (Uses Procedural-based ADI Analog-output Sensor) */

class RGBLED : LED
{
 public:
   RGBLED(char portNum, int r, int g, int b, double brightnessPct);
   void on();
   void off();
 private:
   int r;
   int g;
   int b;
};

/* Drivetrain Class */

class Drivetrain
{
  public:
    Drivetrain();
    void drive(int speed);
    void drive(int speedL, int speedR);
    void drive(driveType type, double distance, int speed);
    void tankDrive(int speedL, int speedR);
    void arcadeDrive(int power, int turnPercentage);
    //void arcadeDriveDualJoy(int power, int turnPercentage); JUST USE arcadeDrive and change X peram to Right Joy X
};

/* Intake Class */

enum intakeType
{
  mainIntake,
  preflywheel,
  both
};

class Intake
{
  public:
    Intake();
    void run(int speed, intakeType type);
};

/* Flywheel Class */

class Flywheel
{
  public:
    Flywheel();
    double currentHoodAngle;
    void run(int velocity);
};

/* Turret Class (extends Flywheel Class) */

class Turret : Flywheel
{
  public:
    Turret();
    double currentHoodAngle;
    double currentTurntableAngle;
    void run(int velocity);
};

/* Claw Class */
enum ClawPosition
{
  closed,
  open,
  vertical
};

class Claw
{
  protected:

  public:
    ClawPosition currentClawPosition;
    bool clockwise;
    double degrees;//TODO private
    double errorRotate;
    double errorClamp;
    Claw();
    void initialize();
    void grab();
    void rotate();//float degrees = 180);
    void goToPosition(ClawPosition clawPosition);
};

/* Lift Class */
enum LiftPosition
{
  ground,
  flipPosition,
  midPost//,
  //highPost
};

class Lift
{
  public:
    LiftPosition currentLiftPosition;
    double errorPosition;
    Lift();
    void control(bool goingUp);
    void run(int speed, double inches);
    void goToPosition(LiftPosition liftPosition);
    void liftAndFlip();
    void scoreCap();
};

/* Robot Class */

class Robot
{
  protected:
    Drivetrain DrivetrainObj;
    Intake IntakeObj;


    Lift LiftObj;
    //static double position[2];

  public:
    Telemetry telemetry;
    Claw ClawObj;
    double lastPosition[2];
    double setpoint_theta;
    double setpoint_distance;
    bool robotTurnIsDone;
    bool turnClockwise;
    Turret TurretObj;

    Robot();
    //void teleop(Controller C0 = Controller0, Controller C1 = Controller1);
    void teleop();
    void teleoptesting();
    void drive(int speed);
    void drive(int speedL, int speedR);
    void drive(driveType type, double distance, int speed);
    void tankDrive(int speedL, int speedR);
    void runIntake(int speed, intakeType type);
    void runFlywheel(int velocity);

    void resetPosition();
    double getPosition();
    void eStop();
    void runAllMotors(int speed);

    void initializePreMatch();


    void goToWaypoint(Waypoint wp);
};

//////////////////// END Class Definitions ////////////////////
///////////////////////////////////////////////////////////////

/*
 * Drivetrain Motors (M_Drivetrain)
 */

extern bool driveIsReversed;

extern Motor M_Drivetrain_LF;
extern Motor M_Drivetrain_LM;
extern Motor M_Drivetrain_LR;
extern Motor M_Drivetrain_RF;
extern Motor M_Drivetrain_RM;
extern Motor M_Drivetrain_RR;

/*
 * (Ball) Intake Motors (M_Intake)
 */

extern bool intakeIsReversed;

extern Motor M_Intake_Main;
extern Motor M_Intake_Preflywheel;

/*
 * Flywheel (Shooter) Motors (M_Flywheel)
 */

extern bool flywheelIsReversed;

extern Motor M_Flywheel_Turret;
extern Motor M_Flywheel_F;
extern Motor M_Flywheel_R;
extern Motor M_Flywheel_Hood;

/*
 * Cap Intake (Claw) Motors and Pneumatics (Actuators) (M_Claw and P_Claw)
 */

extern bool clawIsReversed;
extern bool clawStartsExtended;

//extern Piston P_Claw_Main;
//extern ADIDigitalOut P_Claw_Main;
extern Motor M_Claw_Main;
extern Motor M_Claw_Rotate;

/*
 * (Cap) Lift Motors (M_Drivetrain)
 */

extern bool liftIsReversed;

extern Motor M_Lift_L;
extern Motor M_Lift_R;

/*
 * Donger (Cap Tilter for Ball Intake) Motor (M_Donger)
 */

extern bool dongerIsReversed;

extern Motor M_Donger_Main;

/*
 * Ram Align Motor (M_Ramalign)
 */

extern bool ramAlignIsReversed;

extern Motor M_Ramalign_Main;

//////////////////// END MOTORS ////////////////////
////////////////////////////////////////////////////

/*
 * Sensors/LEDs Definitions
 */

extern RGBLED L_Indicator_Battery;

/*
 * Cameras (VEX Vision Sensors) (S_Camera)
 */

//extern Vision S_Camera_Flywheel; // Using real camera instead

//////////////////// END Sensors ////////////////////
/////////////////////////////////////////////////////

/*
 * Object Definitions
 */

/*
 * Robot Object
 */
extern Robot LargeRobot;
