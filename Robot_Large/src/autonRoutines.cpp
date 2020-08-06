#include "../include/autonRoutines.hpp"
#include "../include/main.h"


int autonomousIDNum = 1;

void autonomousRed1()
{
  // chassis.MotionController.generatePath({Point{58.306_in,35.669_in,0.000_deg}, Point{23.561_in,46.978_in,-45.000_deg}}, "0");  // Deg rel to start; CW = negative deg not positive
  // chassis.MotionController.generatePath({Point{23.561_in,46.978_in,-45.000_deg}, Point{-31.596_in,43.498_in,35.000_deg}}, "1"); // CCW = positive deg
  //chassis.MotionController.generatePath({Point{-58.741_in,-82.865_in,0.000_deg}, Point{-0.326_in,-58.505_in,0.000_deg}}, "0"); 	// Reversed! heading rel to start;CW = positive deg not negative; needs to negate both y and both new heading to match CW positive

  // chassis.MotionController.generatePath({Point{59.609_in,-58.723_in,0.000_deg}, Point{11.401_in,-81.342_in,45.000_deg}}, "0"); 	// Reversed!
  // chassis.MotionController.generatePath({Point{11.401_in,-81.342_in,45.000_deg}, Point{-31.162_in,-43.281_in,35.000_deg}}, "1"); 	// Reversed!
  // chassis.MotionController.generatePath({Point{59.609_in,-58.723_in,0.000_deg}, Point{-0.109_in,-33.711_in,-35.000_deg}}, "0"); 	// Reversed!
  // chassis.MotionController.generatePath({Point{-0.109_in,-33.711_in,-35.000_deg}, Point{-47.014_in,-46.761_in,45.000_deg}}, "1"); 	// Reversed!

  // chassis.MotionController.generatePath({Point{58.524_in,34.581_in,0.000_deg}, Point{59.175_in,34.799_in,-90.000_deg}}, "0");
  chassis.MotionController.generatePath({Point{59.175_in,34.799_in,0.000_deg}, Point{-0.326_in,82.212_in,-90.000_deg}}, "1");
  chassis.MotionController.generatePath({Point{-0.326_in,-82.212_in,90.000_deg}, Point{-58.306_in,-35.016_in,180.000_deg}}, "2"); 	// Reversed!
  chassis.MotionController.generatePath({Point{-58.306_in,35.016_in,180.000_deg}, Point{-0.326_in,35.016_in,180.000_deg}}, "3");
  chassis.MotionController.generatePath({Point{-0.326_in,35.016_in,180.000_deg}, Point{35.722_in,58.723_in,90.000_deg}}, "4");
  chassis.MotionController.generatePath({Point{35.722_in,-58.723_in,90.000_deg}, Point{58.524_in,-35.234_in,0.000_deg}}, "5"); 	// Reversed!

  // chassis.MotionController.setTarget("0", 0);  //Drive forward into ball under cap
  // chassis.MotionController.waitUntilSettled();
  chassis.MotionController.setTarget("1", 0);  //Drive forward into ball under cap
  chassis.MotionController.waitUntilSettled();
  chassis.MotionController.setTarget("2", true);  //Drive forward into ball under cap
  chassis.MotionController.waitUntilSettled();
  chassis.MotionController.setTarget("3", 0);  //Drive forward into ball under cap
  chassis.MotionController.waitUntilSettled();
  chassis.MotionController.setTarget("4", 0);  //Drive forward into ball under cap
  chassis.MotionController.waitUntilSettled();
  chassis.MotionController.setTarget("5", true);  //Drive forward into ball under cap
  chassis.MotionController.waitUntilSettled();

}

void autonomousBlue1()
{
  //CW = (+), CCW, = (-) for turning
  // shooter.FlywheelPID.flipDisable(false);
  // arm.resetPos();
  //
  // chassis.MotionController.generatePath({Point{0_in,0_in,-57_deg}, Point{2_in,-35_in,-90_deg}}, "4f_Place_Cap"); //CHECK RIGHT HERE!
  // chassis.MotionController.setTarget("4f_Place_Cap", false);  //Drive forward to bring bottom cap to side post
  // chassis.MotionController.waitUntilSettled();
  //
  // pros::delay(99999999);


  shooter.FlywheelPID.flipDisable(true);
  arm.resetPos();

  intake.runMainIntake(100);    //Power on ball collector
  intake.runPreFlywheel(-100);   //Power on ball collector
  arm.claw.ClawMain->move(100);                   //Forward cap intake

  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{45_in,0_in,0_deg}}, "1f_Collect_Ball");
  chassis.MotionController.setTarget("1f_Collect_Ball", false);  //Drive forward into ball under cap
  arm.goToPos(-25, true);                           //Keep arm at lower limit
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{15.5_in,3_in,0_deg}}, "2b_Grab_Cap");
  chassis.MotionController.waitUntilSettled();

  chassis.MotionController.setTarget("2b_Grab_Cap", true); //Drive backward to prepare to turn to face bottom cap
  arm.resetPos();
  //arm.goToPos(130, true);                               //Raise arm to release ram align
  arm.goToPos(4, true);                        //Lower arm to lower limit
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{15_in,0_in,0_deg}}, "3b_Grab_Cap");
  chassis.MotionController.waitUntilSettled();
  pros::delay(500);

  chassis.MasterController.turnAngle(128_deg); //Turn to have cap intake face lower cap
  arm.goToPos(4, true);                        //Lower arm to lower limit
  chassis.MasterController.waitUntilSettled();
  pros::delay(250);

  chassis.MotionController.setTarget("3b_Grab_Cap", true); //Drive backward into lower cap
  arm.resetPos();
  arm.goToPos(3, true);                         //Keep arm down to lower limit while picking up cap
  arm.claw.ClawMain->move(100);                   //Forward cap intake
  chassis.MotionController.generatePath({Point{0_in,0_in,-57_deg}, Point{2_in,-35_in,-90_deg}}, "4f_Place_Cap");
  chassis.MotionController.waitUntilSettled();

  chassis.MotionController.setTarget("4f_Place_Cap", false);  //Drive forward to bring bottom cap to side post
  arm.claw.ClawMain->move(50);                   //Forward cap intake
  arm.goToPos(300, true);
  arm.claw.rotate(-45);
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{15_in,0_in,0_deg}}, "5b_Cross_Court");
  chassis.MotionController.waitUntilSettled();

  chassis.MasterController.driveVector(0.25, 0);
  arm.claw.rotate(0);
  pros::delay(500);
  chassis.MasterController.stop();

  //SCORE ONLY ONE CAP
  arm.ArmLeft->move_absolute(450, 600);           //Place cap on side post
  arm.ArmRight->move_absolute(450, 600);           //Place cap on side post
  pros::delay(2000);

  chassis.MotionController.setTarget("5b_Cross_Court", true); //Drive backward to cross-court area
  arm.claw.runIntake(60, false);                 //Reverse cap intake
  //arm.goToPos(450, true);
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{16_in,-10_in,-90_deg}}, "6b_Cross_Court");
  chassis.MotionController.waitUntilSettled();

  chassis.MotionController.setTarget("6b_Cross_Court", true); //Drive backward and turn and front face alliance platform
  arm.goToPos(4, true);                           //Keep arm down to lower limit
  arm.claw.runIntake(0, true);                    //Stop cap intake
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{20_in,0_in,0_deg}}, "7f_Cross_Court");
  chassis.MotionController.waitUntilSettled();

  chassis.MotionController.setTarget("7f_Cross_Court", false);  //Drive forward to prepare to ram align against alliance platform
  intake.runMainIntake(0);    //Power off temporarily ball collector
  intake.runPreFlywheel(0);   //Power off temporarily ball collector
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{10_in,-6.5_in,-32_deg}}, "8b_Cross_Court");
  chassis.MotionController.waitUntilSettled();

  chassis.MasterController.driveVector(0.075, 0);
  pros::delay(1500);
  chassis.MasterController.stop();

  chassis.MotionController.setTarget("8b_Cross_Court", true);   //Drive backwards and turn to proper angle to shoot cross-court
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{5_in,0_in,0_deg}}, "9f_Cross_Court");
  chassis.MotionController.waitUntilSettled();

  chassis.MotionController.setTarget("9f_Cross_Court", false);  //Drive forward to proper distance for shooting cross-court
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{28_in,28_in,45_deg}}, "10f_Alliance_Park");  //12_in,0_in,0_deg
  chassis.MotionController.waitUntilSettled();

  //SHOOTING SEQUENCE
  shooter.setHoodAngle(31);//31); //28
  shooter.FlywheelPID.flipDisable(false);
  intake.MainIntakePID.flipDisable(false);
  intake.PreFlywheelIntakePID.flipDisable(false);
  //intake.MainIntakePID.reset();
  //intake.PreFlywheelIntakePID.reset();
  shooter.FlywheelPID.flipDisable(false);
  shooter.FlywheelPID.controllerSet(1);
  intake.MainIntakePID.setTarget(10000 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(-10000 + M_Intake_Preflywheel.get_position());
  shooter.runFlywheel(82);
  pros::delay(500);
  shooter.FlywheelPID.waitUntilSettled();
  pros::delay(500);
  intake.MainIntakePID.setTarget(200 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(200 + M_Intake_Preflywheel.get_position());
  intake.PreFlywheelIntakePID.waitUntilSettled();

  shooter.setHoodAngle(24);//24); //20
  shooter.FlywheelPID.controllerSet(1);
  intake.MainIntakePID.setTarget(15000 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(-15000 + M_Intake_Preflywheel.get_position());
  shooter.runFlywheel(82);
  pros::delay(500);
  shooter.FlywheelPID.waitUntilSettled();
  pros::delay(500);
  intake.MainIntakePID.setTarget(1000 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(1000 + M_Intake_Preflywheel.get_position());
  intake.PreFlywheelIntakePID.waitUntilSettled();
  shooter.runFlywheel(0);
  intake.MainIntakePID.flipDisable(true);
  intake.PreFlywheelIntakePID.flipDisable(true);
  shooter.FlywheelPID.flipDisable(true);

  //CLIMBING ON THE ALLIANCE PLATFORM
  chassis.MasterController.turnAngle(120_deg); //Turn to have cap intake face lower cap
  chassis.MasterController.waitUntilSettled();
  pros::delay(250);

  chassis.MotionController.setTarget("10f_Alliance_Park", false);  //Drive forward to side of alliance platform
  intake.runMainIntake(100);    //Power on ball collector
  intake.runPreFlywheel(-100);   //Power on ball collector
  shooter.setHoodAngle(14);
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{42_in,0_in,0_deg}}, "11f_Alliance_Park");  //24_in,-26_in,0_deg + false
  chassis.MotionController.waitUntilSettled();

  chassis.MasterController.turnAngle(50_deg); //Turn to rear face alliance platform
  chassis.MasterController.waitUntilSettled();
  pros::delay(250);

  chassis.MotionController.setTarget("11f_Alliance_Park", true);  //Drive backward onto alliance platform
  arm.goToPos(145, false);   //Raise arm out of the way while alliance parking
  chassis.MotionController.waitUntilSettled();

  intake.runMainIntake(0);    //Power off ball collector
  intake.runPreFlywheel(0);   //Power off ball collector

  pros::delay(99999999);  //End of Blue1 autonomous
}
