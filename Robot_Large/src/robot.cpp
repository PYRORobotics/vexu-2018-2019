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
 class PYROChassis
 {
   private:
     const okapi::MotorGroup MG_Drivetrain_Left = {6};
     const okapi::MotorGroup MG_Drivetrain_Right = {6};
     const okapi::QLength WHEEL_DIAMETER = 4_in;
     const okapi::QLength CHASSIS_WIDTH = 12_in;
     const okapi::AbstractMotor::GearsetRatioPair ratio = okapi::AbstractMotor::gearset::green;// * (1.0382);

 public:
   ChassisControllerIntegrated MasterController;// = ChassisControllerFactory::create(
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

 public:
    void teleop(pros::Controller);
    PYROChassis();
 };



PYROChassis::PYROChassis() : MasterController(ChassisControllerFactory::create(
   MG_Drivetrain_Left, MG_Drivetrain_Right,
   //IterativePosPIDController::Gains{0.0045, 0.005, 0.00008},
   //IterativePosPIDController::Gains{0.00003, 0.00003, 0.00001},
   //IterativePosPIDController::Gains{0.0006, 0.00008, 0.00008},
   ratio,
   {WHEEL_DIAMETER, CHASSIS_WIDTH}
 )), MotionController(AsyncControllerFactory::motionProfile(
   10.0,  // Maximum linear velocity of the Chassis in m/s
   0.5,  // Maximum linear acceleration of the Chassis in m/s/s
   10.0, // Maximum linear jerk of the Chassis in m/s/s/s
   MasterController // Chassis Controller
 ))
{}

 void PYROChassis::teleop(pros::Controller Cont)
{
  //MasterController.tank(Cont.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), Cont.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));
}

PYROChassis chassis1();*/

void PYROChassis::teleop(ControllerMode mode, pros::Controller Cont)
{
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
   //IterativePosPIDController::Gains{0.0045, 0.005, 0.00008},
   //IterativePosPIDController::Gains{0.00003, 0.00003, 0.00001},
   //IterativePosPIDController::Gains{0.0006, 0.00008, 0.00008},
   ratio,
   {WHEEL_DIAMETER, CHASSIS_WIDTH}
 )), MotionController(AsyncControllerFactory::motionProfile(
   10.0,  // Maximum linear velocity of the Chassis in m/s
   0.5,  // Maximum linear acceleration of the Chassis in m/s/s
   10.0, // Maximum linear jerk of the Chassis in m/s/s/s
   MasterController // Chassis Controller
 ))
{

}

PYROChassis chassis(0);


/*
 * (Ball) Intake Motors (M_Intake)
 */

/*Reverses (Ball) Intake Motors if true (Normally false)*/
bool intakeIsReversed = true;

/* Main (Front) (Ball) Intake Motor */
pros::Motor M_Intake_Main(11,pros::E_MOTOR_GEARSET_06,intakeIsReversed,pros::E_MOTOR_ENCODER_ROTATIONS);

/* Pre-flywheel Intake Motor */
pros::Motor M_Intake_Preflywheel(13,pros::E_MOTOR_GEARSET_06,intakeIsReversed,pros::E_MOTOR_ENCODER_ROTATIONS);

/*
 * Flywheel (Shooter) Motors (M_Flywheel)
 */

/*Reverses Flywheel Shooter Motors if true (Normally false)*/
bool flywheelIsReversed = false;

/* Flywheel Lazy Susan (Turret) Rotation Motor */
pros::Motor M_Flywheel_Turret(12,pros::E_MOTOR_GEARSET_36,!flywheelIsReversed,pros::E_MOTOR_ENCODER_DEGREES);

/* Flywheel Main Forward Driven Motor */
pros::Motor M_Flywheel_F(20,pros::E_MOTOR_GEARSET_06,flywheelIsReversed,pros::E_MOTOR_ENCODER_ROTATIONS);

/* Flywheel Main Rear Driven Motor */
pros::Motor M_Flywheel_R(4,pros::E_MOTOR_GEARSET_06,!flywheelIsReversed,pros::E_MOTOR_ENCODER_ROTATIONS);

/* Flywheel Hood Motor */
pros::Motor M_Flywheel_Hood(5,pros::E_MOTOR_GEARSET_18,flywheelIsReversed,pros::E_MOTOR_ENCODER_ROTATIONS);

/*
 * Cap Intake (Claw) Motors and Pneumatics (Actuators) (M_Claw and P_Claw)
 */

/*Reverses Claw Acutators if true (Normally false)*/
bool clawIsReversed = false;
bool clawStartsExtended = false;

/* Claw Cap Grabbing Pneumatic Actuator */
//Piston P_Claw_Main('A', clawStartsExtended);
//ADIDigitalOut P_Claw_Main('A', clawIsReversed);
//pros::Motor M_Claw_Main(20,pros::E_MOTOR_GEARSET_36,clawIsReversed,pros::E_MOTOR_ENCODER_ROTATIONS);

/* Claw Rotation (Cap flip) Motor */
pros::Motor M_Claw_Rotate(10,pros::E_MOTOR_GEARSET_36,clawIsReversed,pros::E_MOTOR_ENCODER_DEGREES);

/*
 * (Cap) Lift Motors (M_Drivetrain)
 */

/*Reverses Lift Motors if true (Normally false)*/
bool liftIsReversed = true;

/* Left-front Drivetrain Motor */
pros::Motor M_Lift_L(19,pros::E_MOTOR_GEARSET_18,liftIsReversed,pros::E_MOTOR_ENCODER_ROTATIONS);

/* Left-middle Drivetrain Motor */
pros::Motor M_Lift_R(9,pros::E_MOTOR_GEARSET_18,!liftIsReversed,pros::E_MOTOR_ENCODER_ROTATIONS);

/*
 * Donger (Cap Tilter for Ball Intake) Motor (M_Donger)
 */

/*Reverses Donger Motor if true (Normally false)*/
bool dongerIsReversed = false;

/* Left-front Drivetrain Motor */
//pros::Motor M_Donger_Main(2,pros::E_MOTOR_GEARSET_18,dongerIsReversed,pros::E_MOTOR_ENCODER_DEGREES);

/*
 * Ram Align Motor (M_Ramalign)
 */

/*Reverses Ram Align Motor if true (Normally false)*/
bool ramAlignIsReversed = false;

/* Left-front Drivetrain Motor */
//pros::Motor M_Ramalign_Main(20,pros::E_MOTOR_GEARSET_18,ramAlignIsReversed,pros::E_MOTOR_ENCODER_ROTATIONS);

//////////////////// END MOTORS ////////////////////
