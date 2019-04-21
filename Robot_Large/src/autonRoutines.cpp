#include "../include/autonRoutines.hpp"
#include "../include/main.h"


int autonomousIDNum = 0;

void autonomousRed1()
{
  //CW = (+), CCW, = (-) for turning
  // shooter.FlywheelPID.flipDisable(true);
  // chassis.MasterController.setMaxVelocity(10000); //rpm
  // arm.ArmPID.tarePosition();
  // arm.ArmMain->tare_position();
  //
  // intake.runMainIntake(100);    //Power on ball collector
  // intake.runPreFlywheel(-100);   //Power on ball collector
  // chassis.MasterController.moveDistance(44_in); //Drive forward into ball under cap
  // chassis.MasterController.waitUntilSettled();
  //
  // chassis.MasterController.turnAngle(-90_deg);  //Turn to back face bottom cap
  // chassis.MasterController.waitUntilSettled();
  //
  // chassis.MasterController.moveDistance(20_in); //Drive forward into platforms to align
  // chassis.MasterController.waitUntilSettled();
  //
  // arm.claw.runIntake(100,true);                 //Forward cap intake
  // arm.goToPos(-20, true);                       //Keep arm down to lower limit
  //
  // chassis.MasterController.moveDistance(-48_in); //Drive backward into cap to grab cap
  // chassis.MasterController.waitUntilSettled();
  //
  // arm.goToPos(0, false);                       //Keep arm boyant
  //
  // chassis.MasterController.moveDistance(20_in); //Drive forward to prepare to grab cap again
  // chassis.MasterController.waitUntilSettled();
  //
  // arm.goToPos(-20, true);                       //Keep arm down to lower limit
  //
  // chassis.MasterController.moveDistance(-20_in); //Drive backward into cap to grab cap again
  // chassis.MasterController.waitUntilSettled();
  //
  // chassis.MasterController.moveDistance(20_in); //Drive forward to horizontally align with side post
  // chassis.MasterController.waitUntilSettled();
  //
  // //chassis.MasterController.moveDistance(-30_in);  //Drive backward to inner edge of starting tile
  // //chassis.MasterController.waitUntilSettled();
  //
  //
  //
  // pros::delay(99999999);


  //------------------------------------old code ---------------------------------------------------
  //CW = (+), CCW, = (-) for turning
  shooter.FlywheelPID.flipDisable(true);
  chassis.MasterController.setMaxVelocity(10000); //rpm, originally 60
  arm.ArmPID.tarePosition();
  arm.ArmMain->tare_position();

  intake.runMainIntake(100);    //Power on ball collector
  intake.runPreFlywheel(-100);   //Power on ball collector
  // chassis.MasterController.moveDistance(30_in); //Drive forward toward ball under cap
  // chassis.MasterController.waitUntilSettled();
  //
  // chassis.MasterController.moveDistance(14_in); //Drive forward into ball under cap
  chassis.MasterController.moveDistance(44_in); //Drive forward into ball under cap
  chassis.MasterController.waitUntilSettled();

  std::cout << "At 1, going to 2\n";
  arm.ArmMain->move_absolute(425, 600);  //Raise arm out of the way
  chassis.MasterController.moveDistance(-30_in);  //Drive backward to inner edge of starting tile
  chassis.MasterController.waitUntilSettled();
  std::cout << "At 2, turning to 3\n";
  intake.runMainIntake(50);
  intake.runPreFlywheel(-50);

  // chassis.MasterController.moveDistance(-10_in);  //Drive backward to ram align with side wall
  // chassis.MasterController.waitUntilSettled();
  //
  // chassis.MasterController.moveDistance(10_in);  //Drive forward to align with cap
  // chassis.MasterController.waitUntilSettled();

  arm.goToPos(0, false);                        //Lower arm to lower limit
  chassis.MasterController.turnAngle(-140_deg); //Turn to have cap intake face lower cap
  chassis.MasterController.waitUntilSettled();

  arm.claw.runIntake(100, true);                   //Forward cap intake
  arm.goToPos(-20, true);                         //Keep arm down to lower limit
  chassis.MasterController.moveDistance(-34_in);  //Drive backward into lower cap
  chassis.MasterController.waitUntilSettled();

  chassis.MasterController.moveDistance(18_in); //Drive forward to be horizontally aligned with side post
  chassis.MasterController.waitUntilSettled();

  chassis.MasterController.turnAngle(-35_deg); //Turn to front face side post
  chassis.MasterController.waitUntilSettled();

  chassis.MasterController.moveDistance(25_in); //Drive forward into side post (ram align)
  chassis.MasterController.waitUntilSettled();

  arm.ArmMain->move_absolute(425, 600);           //Place cap on side post
  pros::delay(5000);

  arm.claw.runIntake(100, false);                 //Reverse cap intake
  chassis.MasterController.moveDistance(-10_in);  //Drive backward to be clear of obstacles before turning
  chassis.MasterController.waitUntilSettled();

  arm.claw.runIntake(0, true);                   //Stop cap intake
  chassis.MasterController.turnAngle(-60_deg); //Turn to prepare to horizontally align with upper cap
  chassis.MasterController.waitUntilSettled();

  chassis.MasterController.moveDistance(-14_in);  //Drive backward to horizontally align with upper cap
  chassis.MasterController.waitUntilSettled();

  arm.goToPos(0, false);                         //Bring arm down to lower limit
  chassis.MasterController.turnAngle(60_deg); //Turn to back face upper cap
  chassis.MasterController.waitUntilSettled();

  //chassis.MasterController.moveDistance(30_in);  //Drive forward to ram align into side wall
  //pros::delay(3000);

  arm.claw.runIntake(100, true);                   //Forward cap intake
  arm.goToPos(-20, true);                         //Keep arm down to lower limit
  chassis.MasterController.moveDistance(-30_in);  //Drive backward into upper cap
  chassis.MasterController.waitUntilSettled();

  arm.ArmMain->move_absolute(425, 600);           //Raise cap above robot
  chassis.MasterController.moveDistance(40_in);  //Drive forward to align with bottom post
  chassis.MasterController.waitUntilSettled();

  chassis.MasterController.turnAngle(-108_deg); //Turn to front face lower post
  chassis.MasterController.waitUntilSettled();

  arm.goToPos(0, false);                         //Bring arm down to lower limit
  chassis.MasterController.moveDistance(24_in);  //Drive forward into bottom post (ram align)
  chassis.MasterController.waitUntilSettled();

  arm.ArmMain->move_absolute(425, 600);           //Place cap on side post
  pros::delay(5000);

  arm.claw.runIntake(100, false);                 //Reverse cap intake
  chassis.MasterController.moveDistance(-10_in);  //Drive backward to be clear of obstacles before turning
  chassis.MasterController.waitUntilSettled();

  arm.claw.runIntake(0, true);                    //Stop cap intake
  chassis.MasterController.turnAngle(-90_deg);    //Turn to front face cross-court shooting area
  chassis.MasterController.waitUntilSettled();

  arm.goToPos(0, true);                         //Bring arm down to lower limit
  chassis.MasterController.moveDistance(30_in);  //Drive forward into bottom post (ram align)
  chassis.MasterController.waitUntilSettled();



  arm.goToPos(0, false);                         //Bring arm down to lower limit and release hold
  intake.runMainIntake(0);    //Power on ball collector
  intake.runPreFlywheel(0);   //Power on ball collector

  pros::delay(99999999);


  shooter.FlywheelPID.setTarget(300);
  pros::delay(1800);
  //while(fabs(shooter.FlywheelPID.getError()) > 50)
  //{
    //pros::delay(10);
  //}
  chassis.MasterController.stop();
  chassis.MasterController.setMaxVelocity(6000); //rpm

  //chassis.turn(-4.5);

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
  //chassis.turn(45);

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
