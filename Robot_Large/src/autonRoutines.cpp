#include "../include/autonRoutines.hpp"
#include "../include/main.h"


int autonomousIDNum = -1;

void autonomousRed1()
{
  chassis.MasterController.setMaxVelocity(60); //rpm
  intake.runMainIntake(100);
  intake.runPreFlywheel(-100);
  chassis.MasterController.moveDistance(30_in);
  chassis.MasterController.waitUntilSettled();
  //chassis.MasterController.setMaxVelocity(40); //rpm
  chassis.MasterController.moveDistance(15_in);
  chassis.MasterController.waitUntilSettled();
  //chassis.MasterController.setMaxVelocity(60); //rpm

  std::cout << "At 1, going to 2\n";
  chassis.MasterController.moveDistance(-46_in);
  chassis.MasterController.waitUntilSettled();
  std::cout << "At 2, turning to 3\n";
  intake.runMainIntake(50);
  intake.runPreFlywheel(-50);
  //chassis.MasterController.turnAngle(-94_deg);
  //chassis.MasterController.waitUntilSettled();
  chassis.turn(0);

  if(shooter.FlywheelPID.isDisabled())
    shooter.FlywheelPID.flipDisable();

  shooter.FlywheelPID.setTarget(300);
  pros::delay(1800);
  //while(fabs(shooter.FlywheelPID.getError()) > 50)
  //{
    //pros::delay(10);
  //}
  chassis.MasterController.stop();
  chassis.MasterController.setMaxVelocity(6000); //rpm

  chassis.turn(-4.5);

  intake.runMainIntake(100);
  intake.runPreFlywheel(100);

  pros::delay(3000);

  intake.runMainIntake(50);
  intake.runPreFlywheel(-50);
  shooter.FlywheelPID.flipDisable();

  chassis.MasterController.setMaxVelocity(60); //rpm



  std::cout << "Facing 3, going to 3\n";
  chassis.MasterController.moveDistance(49_in);
  chassis.MasterController.waitUntilSettled();
  std::cout << "Facing 3, going to 3\n";
  chassis.MasterController.moveDistance(-49_in);
  chassis.MasterController.waitUntilSettled();
  std::cout << "At 2, turning to 3\n";
  //chassis.MasterController.turnAngle(30_deg);
  chassis.turn(45);
  chassis.MasterController.waitUntilSettled();
  /*std::cout << "Facing 3, going to 3\n";
  chassis.MasterController.moveDistance(10_in);
  chassis.MasterController.waitUntilSettled();
  std::cout << "At 2, turning to 3\n";
  chassis.MasterController.turnAngle(29_deg);
  chassis.MasterController.waitUntilSettled();*/
  intake.runMainIntake(0);
  intake.runPreFlywheel(0);
  std::cout << "Facing 3, going to 3\n";
  chassis.MasterController.moveDistance(14_in);
  chassis.MasterController.waitUntilSettled();
}

void autonomousRed1OLD()
{
  /*
  chassis.MotionController.generatePath({Point{0_in, 0_in, 0_deg}, Point{10_in, 0_in, 0_deg}}, "R1:1");
  chassis.MotionController.generatePath({Point{10_in, 0_in, 0_deg}, Point{0_in, 0_in, 0_deg}}, "R1:2");

  chassis.MotionController.setTarget("R1:1");
  chassis.MotionController.waitUntilSettled();
  std::cout << "At 1, going to 2\n";
  chassis.MotionController.setTarget("R1:2");
  chassis.MotionController.waitUntilSettled();
  std::cout << "At 2, going to 2\n";
  */

  //chassis.MasterController.setPosPIDFull(0,0.001, 0.0008, 0.0005,0.001,5,0.001,10);  //FIXME: Not doing anything - wrong controller
  //chassis.MasterController.setVelPIDFull(0,0, 0, 0,0,5,0.001,10);  //FIXME: Not doing anything - wrong controller

  chassis.MasterController.setMaxVelocity(60); //rpm
  intake.runMainIntake(100);
  intake.runPreFlywheel(-100);
  chassis.MasterController.moveDistance(30_in);
  chassis.MasterController.waitUntilSettled();
  chassis.MasterController.setMaxVelocity(40); //rpm
  chassis.MasterController.moveDistance(15_in);
  chassis.MasterController.waitUntilSettled();
  chassis.MasterController.setMaxVelocity(60); //rpm

  std::cout << "At 1, going to 2\n";
  chassis.MasterController.moveDistance(-46.5_in);
  chassis.MasterController.waitUntilSettled();
  std::cout << "At 2, turning to 3\n";
  intake.runMainIntake(50);
  intake.runPreFlywheel(-50);
  chassis.MasterController.turnAngle(-94_deg);
  chassis.MasterController.waitUntilSettled();

  if(shooter.FlywheelPID.isDisabled())
    shooter.FlywheelPID.flipDisable();

  shooter.FlywheelPID.setTarget(300);
  pros::delay(1800);
  //while(fabs(shooter.FlywheelPID.getError()) > 50)
  //{
    //pros::delay(10);
  //}
  intake.runMainIntake(100);
  intake.runPreFlywheel(100);

  pros::delay(3000);

  intake.runMainIntake(50);
  intake.runPreFlywheel(-50);
  shooter.FlywheelPID.flipDisable();


  std::cout << "Facing 3, going to 3\n";
  chassis.MasterController.moveDistance(49_in);
  chassis.MasterController.waitUntilSettled();
  std::cout << "Facing 3, going to 3\n";
  chassis.MasterController.moveDistance(-49_in);
  chassis.MasterController.waitUntilSettled();
  std::cout << "At 2, turning to 3\n";
  chassis.MasterController.turnAngle(30_deg);
  chassis.MasterController.waitUntilSettled();
  std::cout << "Facing 3, going to 3\n";
  chassis.MasterController.moveDistance(10_in);
  chassis.MasterController.waitUntilSettled();
  std::cout << "At 2, turning to 3\n";
  chassis.MasterController.turnAngle(29_deg);
  chassis.MasterController.waitUntilSettled();
  intake.runMainIntake(0);
  intake.runPreFlywheel(0);
  std::cout << "Facing 3, going to 3\n";
  chassis.MasterController.moveDistance(14_in);
  chassis.MasterController.waitUntilSettled();
}
