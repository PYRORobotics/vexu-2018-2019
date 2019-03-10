#include "../include/main.h"


using namespace okapi;


pros::Motor l1(1,pros::E_MOTOR_GEARSET_06,0,pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor l2(2,pros::E_MOTOR_GEARSET_06,1,pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor l3(3,pros::E_MOTOR_GEARSET_06,0,pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor r1(7,pros::E_MOTOR_GEARSET_06,1,pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor r2(9,pros::E_MOTOR_GEARSET_06,0,pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor r3(10,pros::E_MOTOR_GEARSET_06,1,pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor intake(13,pros::E_MOTOR_GEARSET_06,0,pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor arm(6, pros::E_MOTOR_GEARSET_36,0,pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor flywheelf(4,pros::E_MOTOR_GEARSET_06,0,pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor flywheelr(5,pros::E_MOTOR_GEARSET_06,1,pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor preflywheel(14,pros::E_MOTOR_GEARSET_18,1,pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor hood(11,pros::E_MOTOR_GEARSET_18,0,MOTOR_ENCODER_ROTATIONS);

const auto WHEEL_DIAMETER = 3.6_in;
const auto CHASSIS_WIDTH = 12_in;
static double preflyPosInit = 0;
static double preflyPosSet = 0;
static double hoodAngleHigh = 35;
static double hoodAngleMid = 23;

okapi::AbstractMotor::GearsetRatioPair ratio = okapi::AbstractMotor::gearset::blue * (3/1);

auto chassis = ChassisControllerFactory::create(
  {1,-2,3}, {-7,9,-10},
  IterativePosPIDController::Gains{0.0002, 0.00003, 0.00001},
  IterativePosPIDController::Gains{0.0001, 0, 0.00001},
  IterativePosPIDController::Gains{0.0003, 0.00008, 0.00001},
  ratio,
  {WHEEL_DIAMETER, CHASSIS_WIDTH}
);



void autonomousRED() //RED
{
  hood.tare_position();
  // Drive Forward
  intake = 127;
  preflywheel = -127;
  chassis.moveDistance(3.5_ft);
  // Drive Backward
  chassis.moveDistance(-3_ft);
  //intake = 0;
  //preflywheel = 0;
  // Turn to Flags
  chassis.turnAngle(-90_deg);
  // Flywheel Shot
  hood.move_absolute((-1)*(54-hoodAngleHigh)*201/14/360,120);
  pros::delay(1500);  //wait for hood to get to correct angle
  //+++++++++++++++++++++++++++++++++++++++++++++++++shoot first ball++++++++++++++++++++++++++++++++++++++

  while(flywheelf.get_actual_velocity() < 550)
  {
    flywheelf.move_velocity(600);
    flywheelr.move_velocity(600);
    //pros::lcd::print(0, "RPM: %f", flywheelf.get_actual_velocity());
    //pros::delay(10);
  }
  //preflyPosInit = preflywheel.get_position();
  //preflyPosSet = preflyPosInit + 1;
  intake = -1;
  preflywheel = 127;
  pros::delay(350);
  flywheelf.move_velocity(0);
  flywheelr.move_velocity(0);
  flywheelf = 0;
  flywheelr = 0;
  intake = 120;
  preflywheel = -120;
  pros::delay(1000);
  //while (preflywheel.get_position() >= preflyPosSet)
  hood.move_absolute((-1)*(54-hoodAngleMid)*201/14/360,120);
  pros::delay(1500);  //wait for hood to get to correct angle
  //preflyPosInit = preflywheel.get_position();
  //preflyPosSet = preflyPosInit - 1;

  /*while (preflywheel.get_position() <= preflyPosSet)
  {
    intake = 120;
    preflywheel = -120;
  }*/
  //+++++++++++++++++++++++++++++++++++++++++++++++++shoot second ball++++++++++++++++++++++++++++++++++++++

  while(flywheelf.get_actual_velocity() < 550)
  {
    flywheelf.move_velocity(600);
    flywheelr.move_velocity(600);
    //pros::lcd::print(0, "RPM: %f", flywheelf.get_actual_velocity());
    //pros::delay(10);
  }
  //preflyPosInit = preflywheel.get_position();
  //preflyPosSet = preflyPosInit + 3;
  preflywheel = 127;
  pros::delay(1000);
  //while (preflywheel.get_position() >= preflyPosSet)
  flywheelf.move_velocity(0);
  flywheelr.move_velocity(0);
  flywheelf = 0;
  flywheelr = 0;
  hood.move_absolute(0,120);
  intake = 0;
  preflywheel = 0;

  // Drive Forward
  intake = 120;
  preflywheel = -120;
  chassis.moveDistance(4_ft);
  // Drive Backward
  chassis.moveDistance(-5.9_ft);
  // Turn to Platform
  chassis.turnAngle(92_deg);
  // Drive Forward onto Platform
  //chassis.moveDistance(3.5_ft);
  l1 = 127;
  l2 = 127;
  l3 = 127;
  r1 = 127;
  r2 = 127;
  r3 = 127;
  pros::delay(1500);
  intake = 0;
  preflywheel = 0;
  l1 = 0;
  l2 = 0;
  l3 = 0;
  r1 = 0;
  r2 = 0;
  r3 = 0;
  pros::delay(500);
  l1.set_brake_mode(MOTOR_BRAKE_BRAKE);
  l2.set_brake_mode(MOTOR_BRAKE_BRAKE);
  l3.set_brake_mode(MOTOR_BRAKE_BRAKE);
  r1.set_brake_mode(MOTOR_BRAKE_BRAKE);
  r2.set_brake_mode(MOTOR_BRAKE_BRAKE);
  r3.set_brake_mode(MOTOR_BRAKE_BRAKE);
}

void autonomous() //Blue
{
  hood.tare_position();
  // Drive Forward
  intake = 127;
  preflywheel = -127;
  chassis.moveDistance(3.5_ft);
  // Drive Backward
  chassis.moveDistance(-3_ft);
  //intake = 0;
  //preflywheel = 0;
  // Turn to Flags
  chassis.turnAngle(88_deg);


  // Flywheel Shot
  hood.move_absolute((-1)*(54-hoodAngleHigh)*201/14/360,120);
  pros::delay(1500);  //wait for hood to get to correct angle
  //+++++++++++++++++++++++++++++++++++++++++++++++++shoot first ball++++++++++++++++++++++++++++++++++++++

  while(flywheelf.get_actual_velocity() < 550)
  {
    flywheelf.move_velocity(600);
    flywheelr.move_velocity(600);
    //pros::lcd::print(0, "RPM: %f", flywheelf.get_actual_velocity());
    //pros::delay(10);
  }
  //preflyPosInit = preflywheel.get_position();
  //preflyPosSet = preflyPosInit + 1;
  intake = -1;
  preflywheel = 127;
  pros::delay(350);
  flywheelf.move_velocity(0);
  flywheelr.move_velocity(0);
  flywheelf = 0;
  flywheelr = 0;
  intake = 120;
  preflywheel = -120;
  pros::delay(1000);
  //while (preflywheel.get_position() >= preflyPosSet)
  hood.move_absolute((-1)*(54-hoodAngleMid)*201/14/360,120);
  pros::delay(1500);  //wait for hood to get to correct angle
  //preflyPosInit = preflywheel.get_position();
  //preflyPosSet = preflyPosInit - 1;

  /*while (preflywheel.get_position() <= preflyPosSet)
  {
    intake = 120;
    preflywheel = -120;
  }*/
  //+++++++++++++++++++++++++++++++++++++++++++++++++shoot second ball++++++++++++++++++++++++++++++++++++++

  while(flywheelf.get_actual_velocity() < 550)
  {
    flywheelf.move_velocity(600);
    flywheelr.move_velocity(600);
    //pros::lcd::print(0, "RPM: %f", flywheelf.get_actual_velocity());
    //pros::delay(10);
  }
  //preflyPosInit = preflywheel.get_position();
  //preflyPosSet = preflyPosInit + 3;
  preflywheel = 127;
  pros::delay(1000);
  //while (preflywheel.get_position() >= preflyPosSet)
  flywheelf.move_velocity(0);
  flywheelr.move_velocity(0);
  flywheelf = 0;
  flywheelr = 0;
  hood.move_absolute(0,120);
  intake = 0;
  preflywheel = 0;


  // Drive Forward
  chassis.moveDistance(4_ft);
  // Drive Backward
  chassis.moveDistance(-5.9_ft);
  // Turn to Platform
  chassis.turnAngle(-92_deg);
  // Drive Forward onto Platform
  //chassis.moveDistance(3.5_ft);
  l1 = 127;
  l2 = 127;
  l3 = 127;
  r1 = 127;
  r2 = 127;
  r3 = 127;
  pros::delay(1500);
  intake = 0;
  preflywheel = 0;
  l1 = 0;
  l2 = 0;
  l3 = 0;
  r1 = 0;
  r2 = 0;
  r3 = 0;
  pros::delay(500);
}

///////////

void autonomousRMINES() //RED MINES
{
  double startTime = pros::millis();
  hood.tare_position();
  // Drive Forward
  intake = 127;
  preflywheel = -127;
  chassis.moveDistance(3.5_ft);
  // Drive Backward
  chassis.moveDistance(-3_ft);
  //intake = 0;
  //preflywheel = 0;
  // Turn to Flags
  chassis.turnAngle(-90_deg);

  // Drive Forward
  intake = 120;
  preflywheel = -120;
  chassis.moveDistance(4_ft);
  // Drive Backward
  chassis.moveDistance(-5.9_ft);
  chassis.turnAngle(2_deg);
  intake = 0;
  preflywheel = -0;
    hood.move_absolute((-1)*(54-hoodAngleHigh-3)*201/14/360,120);
  pros::delay(17500);
  intake = 120;
  preflywheel = -120;

  // Flywheel Shot


  //+++++++++++++++++++++++++++++++++++++++++++++++++shoot first ball++++++++++++++++++++++++++++++++++++++

  while(flywheelf.get_actual_velocity() < 550)
  {
    flywheelf.move_velocity(600);
    flywheelr.move_velocity(600);
    //pros::lcd::print(0, "RPM: %f", flywheelf.get_actual_velocity());
    //pros::delay(10);
  }
  //preflyPosInit = preflywheel.get_position();
  //preflyPosSet = preflyPosInit + 1;
  intake = -1;
  preflywheel = 127;
  pros::delay(350);
  flywheelf.move_velocity(0);
  flywheelr.move_velocity(0);
  flywheelf = 0;
  flywheelr = 0;
  intake = 120;
  preflywheel = -120;
  pros::delay(1000);
  //while (preflywheel.get_position() >= preflyPosSet)
  hood.move_absolute((-1)*(54-hoodAngleMid)*201/14/360,120);
  pros::delay(700);  //wait for hood to get to correct angle
  //preflyPosInit = preflywheel.get_position();
  //preflyPosSet = preflyPosInit - 1;

  /*while (preflywheel.get_position() <= preflyPosSet)
  {
    intake = 120;
    preflywheel = -120;
  }*/
  //+++++++++++++++++++++++++++++++++++++++++++++++++shoot second ball++++++++++++++++++++++++++++++++++++++

  while(flywheelf.get_actual_velocity() < 550)
  {
    flywheelf.move_velocity(600);
    flywheelr.move_velocity(600);
    //pros::lcd::print(0, "RPM: %f", flywheelf.get_actual_velocity());
    //pros::delay(10);
  }
  //preflyPosInit = preflywheel.get_position();
  //preflyPosSet = preflyPosInit + 3;
  preflywheel = 127;
  pros::delay(1000);
  //while (preflywheel.get_position() >= preflyPosSet)
  flywheelf.move_velocity(0);
  flywheelr.move_velocity(0);
  flywheelf = 0;
  flywheelr = 0;
  hood.move_absolute(0,120);
  intake = 0;
  preflywheel = 0;


}

///////////

void autonomousSKILLS() //RED SKILLS
{
  hood.tare_position();
  // Drive Forward
  intake = 127;
  preflywheel = -127;
  chassis.moveDistance(5.5_ft);
  // Drive Backward
  chassis.moveDistance(-5_ft);
  //intake = 0;
  //preflywheel = 0;
  // Turn to Flags
  chassis.turnAngle(-90_deg);
  // Flywheel Shot
  hood.move_absolute((-1)*(54-hoodAngleHigh)*201/14/360,120);
  pros::delay(1500);  //wait for hood to get to correct angle
  //+++++++++++++++++++++++++++++++++++++++++++++++++shoot first ball++++++++++++++++++++++++++++++++++++++

  while(flywheelf.get_actual_velocity() < 550)
  {
    flywheelf.move_velocity(600);
    flywheelr.move_velocity(600);
    //pros::lcd::print(0, "RPM: %f", flywheelf.get_actual_velocity());
    //pros::delay(10);
  }
  //preflyPosInit = preflywheel.get_position();
  //preflyPosSet = preflyPosInit + 1;
  intake = -1;
  preflywheel = 127;
  pros::delay(350);
  flywheelf.move_velocity(0);
  flywheelr.move_velocity(0);
  flywheelf = 0;
  flywheelr = 0;
  intake = 120;
  preflywheel = -120;
  pros::delay(1000);
  //while (preflywheel.get_position() >= preflyPosSet)
  hood.move_absolute((-1)*(54-hoodAngleMid)*201/14/360,120);
  pros::delay(1500);  //wait for hood to get to correct angle
  //preflyPosInit = preflywheel.get_position();
  //preflyPosSet = preflyPosInit - 1;

  /*while (preflywheel.get_position() <= preflyPosSet)
  {
    intake = 120;
    preflywheel = -120;
  }*/
  //+++++++++++++++++++++++++++++++++++++++++++++++++shoot second ball++++++++++++++++++++++++++++++++++++++

  while(flywheelf.get_actual_velocity() < 550)
  {
    flywheelf.move_velocity(600);
    flywheelr.move_velocity(600);
    //pros::lcd::print(0, "RPM: %f", flywheelf.get_actual_velocity());
    //pros::delay(10);
  }
  //preflyPosInit = preflywheel.get_position();
  //preflyPosSet = preflyPosInit + 3;
  preflywheel = 127;
  pros::delay(1000);
  //while (preflywheel.get_position() >= preflyPosSet)
  flywheelf.move_velocity(0);
  flywheelr.move_velocity(0);
  flywheelf = 0;
  flywheelr = 0;
  hood.move_absolute(0,120);
  intake = 0;
  preflywheel = 0;

  // Drive Forward
  intake = 120;
  preflywheel = -120;
  chassis.moveDistance(4_ft);
  // Drive Backward
  chassis.moveDistance(-5.9_ft);
  // Turn to Platform
  chassis.turnAngle(92_deg);
  // Drive Forward onto Platform
  //chassis.moveDistance(3.5_ft);
  l1 = 127;
  l2 = 127;
  l3 = 127;
  r1 = 127;
  r2 = 127;
  r3 = 127;
  pros::delay(1500);
  intake = 0;
  preflywheel = 0;
  l1 = 0;
  l2 = 0;
  l3 = 0;
  r1 = 0;
  r2 = 0;
  r3 = 0;
  pros::delay(500);
  l1.set_brake_mode(MOTOR_BRAKE_BRAKE);
  l2.set_brake_mode(MOTOR_BRAKE_BRAKE);
  l3.set_brake_mode(MOTOR_BRAKE_BRAKE);
  r1.set_brake_mode(MOTOR_BRAKE_BRAKE);
  r2.set_brake_mode(MOTOR_BRAKE_BRAKE);
  r3.set_brake_mode(MOTOR_BRAKE_BRAKE);
  l1 = 127;
  l2 = 127;
  l3 = 127;
  r1 = 127;
  r2 = 127;
  r3 = 127;
  pros::delay(1400);
  l1 = 0;
  l2 = 0;
  l3 = 0;
  r1 = 0;
  r2 = 0;
  r3 = 0;
}
