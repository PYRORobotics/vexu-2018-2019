#include "../include/autonRoutines.hpp"
#include "../include/main.h"


int autonomousIDNum = 0;

void autonomousRed1()
{
  //CW = (+), CCW, = (-) for turning
  shooter.FlywheelPID.flipDisable(true);
  arm.resetPos();
  HoodMotor->tare_position();

  //intake.runMainIntake(100);    //Power on ball collector
  //intake.runPreFlywheel(-100);   //Power on ball collector
  HoodMotor->move_absolute((HOOD_MAX_ANGLE - 34)*201/14, 50);
  pros::delay(1000);
  HoodMotor->move_absolute((HOOD_MAX_ANGLE - 23)*201/14, 50);
  pros::delay(99999999);


  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{45_in,0_in,0_deg}}, "1f");

  shooter.FlywheelPID.flipDisable(true);
  arm.resetPos();

  intake.runMainIntake(100);    //Power on ball collector
  intake.runPreFlywheel(-100);   //Power on ball collector

  chassis.MotionController.setTarget("1f", false);  //Drive forward into ball under cap
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{15_in,-3_in,0_deg}}, "2b");
  chassis.MotionController.waitUntilSettled();

  chassis.MotionController.setTarget("2b", true); //Drive backward to prepare to turn to face bottom cap
  arm.goToPos(130);                               //Raise arm to release ram align
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{15_in,0_in,0_deg}}, "3b");
  chassis.MotionController.waitUntilSettled();
  pros::delay(500);

  chassis.MasterController.turnAngle(-133.5_deg); //Turn to have cap intake face lower cap
  arm.goToPos(-30, true);                        //Lower arm to lower limit
  chassis.MasterController.waitUntilSettled();
  pros::delay(500);

  chassis.MotionController.setTarget("3b", true); //Drive backward into lower cap
  arm.resetPos();
  arm.goToPos(-20, true);                         //Keep arm down to lower limit
  arm.claw.runIntake(100, true);                   //Forward cap intake
  chassis.MotionController.generatePath({Point{0_in,0_in,57_deg}, Point{2_in,35_in,90_deg}}, "4f");
  chassis.MotionController.waitUntilSettled();

  chassis.MotionController.setTarget("4f", false);  //Drive forward to bring bottom cap to side post
  arm.goToPos(140, true);
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{15_in,0_in,0_deg}}, "5b");
  chassis.MotionController.waitUntilSettled();

  chassis.MasterController.driveVector(0.3, 0);
  pros::delay(1000);
  chassis.MasterController.stop();

  //SCORE FIRST CAP
  arm.ArmMain->move_absolute(425, 600);           //Place cap on side post
  pros::delay(3000);

  chassis.MotionController.setTarget("5b", true); //Drive backward to cross-court area
  arm.claw.runIntake(60, false);                 //Reverse cap intake
  //arm.goToPos(450, true);
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{16_in,10_in,90_deg}}, "6b");
  chassis.MotionController.waitUntilSettled();

  chassis.MotionController.setTarget("6b", true); //Drive backward and turn and front face alliance platform
  arm.claw.runIntake(0, true);                    //Stop cap intake
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{20_in,0_in,0_deg}}, "7f");
  chassis.MotionController.waitUntilSettled();

  chassis.MotionController.setTarget("7f", false);  //Drive forward to prepare to ram align against alliance platform
  intake.runMainIntake(0);    //Power off temporarily ball collector
  intake.runPreFlywheel(0);   //Power off temporarily ball collector
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{10_in,6.5_in,33_deg}}, "8b");
  chassis.MotionController.waitUntilSettled();

  chassis.MasterController.driveVector(0.3, 0);
  arm.goToPos(0, true);                         //Keep arm down to lower limit
  pros::delay(1500);
  chassis.MasterController.stop();

  chassis.MotionController.setTarget("8b", true);
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{5_in,0_in,0_deg}}, "9f");
  chassis.MotionController.waitUntilSettled();

  chassis.MotionController.setTarget("9f", false);
  chassis.MotionController.waitUntilSettled();

  pros::delay(99999999);



  //old code to score 2 caps instead of just 1 due to not realizing lack of time remaining ---------------------------------
  //CW = (+), CCW, = (-) for turning
  shooter.FlywheelPID.flipDisable(true);
  arm.resetPos();

  intake.runPreFlywheel(-100);   //Power on ball collector
  chassis.MotionController.generatePath({Point{0_in,0_in,45_deg}, Point{10_in,40_in,90_deg}}, "4f_alt");
  chassis.MotionController.setTarget("4f_alt", false);  //Drive forward to be horizontally aligned with side post
  chassis.MotionController.waitUntilSettled();
  intake.runPreFlywheel(0);   //Power on ball collector
  pros::delay(99999999);

  intake.runMainIntake(100);    //Power on ball collector
  intake.runPreFlywheel(-100);   //Power on ball collector

  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{45_in,0_in,0_deg}}, "1f");
  chassis.MotionController.setTarget("1f", false);  //Drive forward into ball under cap
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{15_in,-3_in,0_deg}}, "2b");
  chassis.MotionController.waitUntilSettled();

  chassis.MotionController.setTarget("2b", true); //Drive backward to prepare to turn to face bottom cap
  arm.goToPos(130);
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{15_in,0_in,0_deg}}, "3b");
  chassis.MotionController.waitUntilSettled();
  pros::delay(500);

  chassis.MasterController.turnAngle(-134_deg); //Turn to have cap intake face lower cap
  arm.goToPos(-30, true);                        //Lower arm to lower limit
  chassis.MasterController.waitUntilSettled();
  pros::delay(500);

  chassis.MotionController.setTarget("3b", true); //Drive backward into lower cap
  arm.resetPos();
  arm.goToPos(-20, true);                         //Keep arm down to lower limit
  arm.claw.runIntake(100, true);                   //Forward cap intake
  //chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{10_in,0_in,0_deg}}, "4f");
  chassis.MotionController.generatePath({Point{0_in,0_in,45_deg}, Point{10_in,40_in,90_deg}}, "4f_alt");
  chassis.MotionController.waitUntilSettled();

  chassis.MotionController.setTarget("4f_alt", false);  //Drive forward to be horizontally aligned with side post
  arm.goToPos(140, true);
  //chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{32_in,0_in,0_deg}}, "5f");
  //chassis.MotionController.waitUntilSettled();

  //chassis.MasterController.turnAngle(-43_deg); //Turn to front face side post
  //chassis.MasterController.waitUntilSettled();

  //chassis.MotionController.setTarget("5f", false);  //Drive forward into side post (ram align)
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{10_in,0_in,0_deg}}, "6b");
  chassis.MotionController.waitUntilSettled();

  chassis.MasterController.driveVector(0.3, 0);
  pros::delay(1000);
  chassis.MasterController.stop();

  //SCORE FIRST CAP
  arm.ArmMain->move_absolute(425, 600);           //Place cap on side post
  pros::delay(3000);

  chassis.MotionController.setTarget("6b", true); //Drive backward to be clear of obstacles
  arm.claw.runIntake(60, false);                 //Reverse cap intake
  arm.goToPos(450, true);
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{35_in,-12_in,0_deg}}, "7b");
  chassis.MotionController.waitUntilSettled();

  chassis.MotionController.setTarget("7b", true); //Drive backward into upper cap
  arm.claw.runIntake(127, true);                   //Forward cap intake
  arm.goToPos(-20, true);                         //Keep arm down to lower limit
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{24_in,18_in,90_deg}}, "8f");
  chassis.MotionController.waitUntilSettled();

  chassis.MotionController.setTarget("8f", false); //Drive forward into bottom post
  arm.goToPos(140, true);
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{10_in,0_in,0_deg}}, "9b");//Point{24_in,-18_in,90_deg}}, "9b");
  chassis.MotionController.waitUntilSettled();

  chassis.MasterController.driveVector(0.3, 0);
  //arm.goToPos(-20, true);                         //Keep arm down to lower limit
  pros::delay(1000);
  chassis.MasterController.stop();

  //SCORE SECOND CAP
  arm.ArmMain->move_absolute(425, 600);           //Place cap on bottom post
  pros::delay(3000);

  chassis.MotionController.setTarget("9b", true); //Drive forward into bottom post
  arm.claw.runIntake(60, false);                 //Reverse cap intake
  arm.goToPos(450, true);
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{20_in,0_in,0_deg}}, "10b");
  chassis.MotionController.waitUntilSettled();

  chassis.MasterController.turnAngle(-90_deg); //Turn to back face side post
  arm.claw.runIntake(0, false);                 //Stop cap intake
  chassis.MasterController.waitUntilSettled();

  chassis.MotionController.setTarget("10b", true); //Drive backward into side post
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{44_in,0_in,0_deg}}, "11f");
  chassis.MotionController.waitUntilSettled();

  chassis.MasterController.driveVector(0.3, 0);   //Ram align into side wall
  pros::delay(1000);
  chassis.MasterController.stop();

  chassis.MotionController.setTarget("11f", false); //Drive forward to vertically align with alliance platform
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{20_in,0_in,0_deg}}, "12b");
  chassis.MotionController.waitUntilSettled();

  chassis.MasterController.turnAngle(-90_deg); //Turn to back face bottom wall
  chassis.MasterController.waitUntilSettled();

  chassis.MotionController.setTarget("12b", true); //Drive backward into bottom wall
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{20_in,0_in,-33_deg}}, "13f");
  chassis.MotionController.waitUntilSettled();

  chassis.MasterController.driveVector(0.3, 0);   //Ram align into bottom wall
  pros::delay(1000);
  chassis.MasterController.stop();

  chassis.MotionController.setTarget("13f", false); //Drive backward into bottom wall
  //chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{20_in,-10_in,33_deg}}, "13f");
  chassis.MotionController.waitUntilSettled();

  pros::delay(99999999);




  //old code before motion profile -------------------------------------------------------
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
