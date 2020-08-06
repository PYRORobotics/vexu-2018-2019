#include "../include/autonRoutines.hpp"
#include "../include/main.h"


int autonomousIDNum = -1;

void autonomousRed1()
{
  //chassis.MasterController.setMaxVoltage(6000);
  std::cout << "BLUE" << "\n";
  std::cout << "CAMON" << "\n";

  intake.MainIntakePID.flipDisable(false); //
  intake.PreFlywheelIntakePID.flipDisable(false); //
  shooter.FlywheelPID.flipDisable(true);

  intake.runMainIntake(100);
  intake.runPreFlywheel(-100);

  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{34_in,0_in,0_deg}}, "1R");
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{40_in,0_in,0_deg}}, "2");
  chassis.MotionController.setTarget("1R", false); //default false (straight)
  chassis.MotionController.waitUntilSettled();

  chassis.MotionController.setTarget("2", true); //default false (straight)
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{52_in,0_in,0_deg}}, "3");
  chassis.MotionController.waitUntilSettled();

  intake.runMainIntake(0);
  intake.runPreFlywheel(-50);

  chassis.MasterController.stop();
  intake.MainIntakePID.flipDisable(true); //
  intake.PreFlywheelIntakePID.flipDisable(true); //
  chassis.MasterController.turnAngle(-96_deg);
  chassis.MasterController.waitUntilSettled();
  chassis.MasterController.stop();

  chassis.MasterController.waitUntilSettled();
  chassis.MasterController.stop();

  intake.MainIntakePID.flipDisable(false); //
  intake.PreFlywheelIntakePID.flipDisable(false);

  intake.MainIntakePID.flipDisable(true); //
  intake.PreFlywheelIntakePID.flipDisable(true); //


  //chassis.turn(-5);
  chassis.MasterController.waitUntilSettled();

  intake.MainIntakePID.flipDisable(false); //
  intake.PreFlywheelIntakePID.flipDisable(false); //


  //////
  shooter.setHoodAngle(36);
  intake.MainIntakePID.flipDisable(false); //
  intake.PreFlywheelIntakePID.flipDisable(false); //
  intake.MainIntakePID.reset();
  intake.PreFlywheelIntakePID.reset();
  shooter.FlywheelPID.flipDisable(false);
  shooter.FlywheelPID.controllerSet(1);
  intake.MainIntakePID.setTarget(4000 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(-4000 + M_Intake_Preflywheel.get_position());
  shooter.runFlywheel(87);
  pros::delay(500);
  shooter.FlywheelPID.waitUntilSettled();
  intake.MainIntakePID.setTarget(360 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(360 + M_Intake_Preflywheel.get_position());
  intake.PreFlywheelIntakePID.waitUntilSettled();

  shooter.setHoodAngle(22);
  shooter.FlywheelPID.controllerSet(1);
  intake.MainIntakePID.setTarget(4000 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(-4000 + M_Intake_Preflywheel.get_position());
  shooter.runFlywheel(87);
  pros::delay(500);
  shooter.FlywheelPID.waitUntilSettled();
  intake.MainIntakePID.setTarget(500 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(500 + M_Intake_Preflywheel.get_position());
  intake.PreFlywheelIntakePID.waitUntilSettled();
  shooter.runFlywheel(0);
  shooter.FlywheelPID.flipDisable(true);
  //////
  chassis.MasterController.stop();

  intake.runMainIntake(0);
  intake.runPreFlywheel(-50);

  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{14_in,0_in,0_deg}}, "4");
  chassis.MasterController.turnAngle(4_deg);
  chassis.MasterController.waitUntilSettled();
  //std::cout << "Facing 3, going to 3\n";
  chassis.MotionController.setTarget("4", true); //default false (straight)
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{30.5_in,-13.5_in,-45_deg}}, "5");
  chassis.MotionController.waitUntilSettled();

  donger.DongerPID.flipDisable(false);
  donger.DongerPID.setTarget(120*6);

  chassis.MotionController.setTarget("5", false); //default false (straight)
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{18_in,0_in,45_deg}}, "6");
  chassis.MotionController.waitUntilSettled();

  intake.MainIntakePID.flipDisable(true); //
  intake.PreFlywheelIntakePID.flipDisable(true); //

  chassis.MasterController.waitUntilSettled();

  intake.MainIntakePID.flipDisable(false); //
  intake.PreFlywheelIntakePID.flipDisable(false); //



  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{8_in,0_in,0_deg}}, "7");
  chassis.MotionController.waitUntilSettled();

  donger.DongerPID.setTarget(190*6);
  donger.DongerPID.waitUntilSettled();

  chassis.MotionController.setTarget("7", true); //default false (straight)

  chassis.MotionController.waitUntilSettled();

  donger.DongerPID.setTarget(130*6);
  intake.runMainIntake(110);
  intake.runPreFlywheel(-110);

  chassis.MotionController.setTarget("7", false); //default false (straight)
  chassis.MotionController.waitUntilSettled();

  chassis.MotionController.setTarget("7", true); //default false (straight)
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{16_in,0_in,0_deg}}, "8");
  chassis.MotionController.waitUntilSettled();

  intake.runMainIntake(0);

  chassis.MasterController.turnAngle(170_deg);
  chassis.MotionController.waitUntilSettled();

  chassis.MotionController.setTarget("8", true); //default false (straight)
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{12_in,0_in,0_deg}}, "9");
  chassis.MotionController.waitUntilSettled();

  chassis.MotionController.setTarget("9", true); //default false (straight)
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{26_in,0_in,45_deg}}, "10");

  arm.ArmPID.flipDisable(false);
  arm.ArmPID.setTarget(75); //3:1 Ratio
  arm.ArmPID.waitUntilSettled();
  arm.ArmPID.setTarget(0);
  chassis.MotionController.waitUntilSettled();

  chassis.MotionController.setTarget("7", false); //default false (straight)
  chassis.MotionController.waitUntilSettled();

  chassis.MasterController.turnAngle(-170_deg);
  chassis.MotionController.waitUntilSettled();

  chassis.MotionController.setTarget("10", true); //default false (straight)
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{46_in,0_in,0_deg}}, "11");
  chassis.MotionController.waitUntilSettled();

  chassis.MasterController.driveVector(-0.17, 0);
  pros::delay(1200);

  chassis.MasterController.stop();
  pros::delay(100);

  chassis.MotionController.setTarget("11", false); //default false (straight)
  chassis.MotionController.waitUntilSettled();

  chassis.MasterController.turnAngle(-89_deg);
  chassis.MasterController.waitUntilSettled();
  chassis.MasterController.stop();

  //////
  shooter.setHoodAngle(38);
  intake.MainIntakePID.reset();
  intake.PreFlywheelIntakePID.reset();
  shooter.FlywheelPID.flipDisable(false);
  shooter.FlywheelPID.controllerSet(1);
  intake.MainIntakePID.setTarget(4000 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(-4000 + M_Intake_Preflywheel.get_position());
  shooter.runFlywheel(87);
  pros::delay(500);
  shooter.FlywheelPID.waitUntilSettled();
  intake.MainIntakePID.setTarget(360 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(360 + M_Intake_Preflywheel.get_position());
  intake.PreFlywheelIntakePID.waitUntilSettled();

  shooter.setHoodAngle(26);
  shooter.FlywheelPID.controllerSet(1);
  intake.MainIntakePID.setTarget(4000 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(-4000 + M_Intake_Preflywheel.get_position());
  shooter.runFlywheel(87);
  pros::delay(500);
  shooter.FlywheelPID.waitUntilSettled();
  intake.MainIntakePID.setTarget(1000 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(1000 + M_Intake_Preflywheel.get_position());
  intake.PreFlywheelIntakePID.waitUntilSettled();
  shooter.runFlywheel(0);
  intake.MainIntakePID.flipDisable(true);
  intake.PreFlywheelIntakePID.flipDisable(true);
  shooter.FlywheelPID.flipDisable(true);

  chassis.MasterController.stop();
}

void autonomousBlue1OLDWOrlds()
{
  //chassis.MasterController.setMaxVoltage(6000);
  std::cout << "BLUE" << "\n";
  std::cout << "CAMON" << "\n";

  intake.MainIntakePID.flipDisable(false); //
  intake.PreFlywheelIntakePID.flipDisable(false); //
  shooter.FlywheelPID.flipDisable(true);

  intake.runMainIntake(100);
  intake.runPreFlywheel(-100);

  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{40.5_in,0_in,0_deg}}, "2");
  chassis.MotionController.setTarget("1", false); //default false (straight)
  chassis.MotionController.waitUntilSettled();

  chassis.MotionController.setTarget("2", true); //default false (straight)
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{52_in,0_in,0_deg}}, "3");
  chassis.MotionController.waitUntilSettled();

  intake.runMainIntake(0);
  intake.runPreFlywheel(-50);

  chassis.MasterController.stop();
  intake.MainIntakePID.flipDisable(true); //
  intake.PreFlywheelIntakePID.flipDisable(true); //
  chassis.MasterController.turnAngle(96_deg);
  chassis.MasterController.waitUntilSettled();
  chassis.MasterController.stop();

  chassis.MasterController.waitUntilSettled();
  chassis.MasterController.stop();

  intake.MainIntakePID.flipDisable(false); //
  intake.PreFlywheelIntakePID.flipDisable(false);

  intake.MainIntakePID.flipDisable(true); //
  intake.PreFlywheelIntakePID.flipDisable(true); //


  //chassis.turn(-5);
  chassis.MasterController.waitUntilSettled();

  intake.MainIntakePID.flipDisable(false); //
  intake.PreFlywheelIntakePID.flipDisable(false); //


  //////
  shooter.setHoodAngle(37);
  intake.MainIntakePID.flipDisable(false); //
  intake.PreFlywheelIntakePID.flipDisable(false); //
  intake.MainIntakePID.reset();
  intake.PreFlywheelIntakePID.reset();
  shooter.FlywheelPID.flipDisable(false);
  shooter.FlywheelPID.controllerSet(1);
  intake.MainIntakePID.setTarget(4000 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(-4000 + M_Intake_Preflywheel.get_position());
  shooter.runFlywheel(87);
  pros::delay(500);
  shooter.FlywheelPID.waitUntilSettled();
  intake.MainIntakePID.setTarget(360 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(360 + M_Intake_Preflywheel.get_position());
  intake.PreFlywheelIntakePID.waitUntilSettled();

  shooter.setHoodAngle(22);
  shooter.FlywheelPID.controllerSet(1);
  intake.MainIntakePID.setTarget(4000 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(-4000 + M_Intake_Preflywheel.get_position());
  shooter.runFlywheel(87);
  pros::delay(500);
  shooter.FlywheelPID.waitUntilSettled();
  intake.MainIntakePID.setTarget(500 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(500 + M_Intake_Preflywheel.get_position());
  intake.PreFlywheelIntakePID.waitUntilSettled();
  shooter.runFlywheel(0);
  shooter.FlywheelPID.flipDisable(true);
  //////
  chassis.MasterController.stop();

  intake.runMainIntake(0);
  intake.runPreFlywheel(-50);

  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{14_in,0_in,0_deg}}, "4");
  chassis.MasterController.turnAngle(-4_deg);
  chassis.MasterController.waitUntilSettled();
  //std::cout << "Facing 3, going to 3\n";
  chassis.MotionController.setTarget("4", true); //default false (straight)
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{31_in,13_in,44_deg}}, "5"); //+,-,-
  chassis.MotionController.waitUntilSettled();

  donger.DongerPID.flipDisable(false);
  donger.DongerPID.setTarget(120*6);

  chassis.MotionController.setTarget("5", false); //default false (straight)
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{18_in,0_in,-45_deg}}, "6");
  chassis.MotionController.waitUntilSettled();

  intake.MainIntakePID.flipDisable(true); //
  intake.PreFlywheelIntakePID.flipDisable(true); //

  chassis.MasterController.waitUntilSettled();

  intake.MainIntakePID.flipDisable(false); //
  intake.PreFlywheelIntakePID.flipDisable(false); //


  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{8_in,0_in,0_deg}}, "7");
  chassis.MotionController.waitUntilSettled();

  donger.DongerPID.setTarget(190*6);
  donger.DongerPID.waitUntilSettled();

  chassis.MotionController.setTarget("7", true); //default false (straight)

  chassis.MotionController.waitUntilSettled();

  donger.DongerPID.setTarget(130*6);
  intake.runMainIntake(110);
  intake.runPreFlywheel(-110);


  chassis.MotionController.setTarget("7", false); //default false (straight)
  chassis.MotionController.waitUntilSettled();

  chassis.MotionController.setTarget("7", true); //default false (straight)
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{16_in,0_in,0_deg}}, "8");
  chassis.MotionController.waitUntilSettled();


  chassis.MasterController.turnAngle(-170_deg);
  chassis.MotionController.waitUntilSettled();

  chassis.MotionController.setTarget("8", true); //default false (straight)
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{12_in,0_in,0_deg}}, "9");
  chassis.MotionController.waitUntilSettled();

  chassis.MotionController.setTarget("9", true); //default false (straight)
  intake.runMainIntake(0);
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{26_in,0_in,-45_deg}}, "10");

  arm.ArmPID.flipDisable(false);
  arm.ArmPID.setTarget(80); //3:1 Ratio
  arm.ArmPID.waitUntilSettled();
  arm.ArmPID.setTarget(0);
  chassis.MotionController.waitUntilSettled();

  chassis.MotionController.setTarget("7", false); //default false (straight)
  chassis.MotionController.waitUntilSettled();

  chassis.MasterController.turnAngle(170_deg);
  chassis.MotionController.waitUntilSettled();

  chassis.MotionController.setTarget("10", true); //default false (straight)
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{46_in,0_in,0_deg}}, "11");
  chassis.MotionController.waitUntilSettled();

  chassis.MasterController.driveVector(-0.17, 0);
  pros::delay(1200);

  chassis.MasterController.stop();
  pros::delay(100);

  chassis.MotionController.setTarget("11", false); //default false (straight)
  chassis.MotionController.waitUntilSettled();

  chassis.MasterController.turnAngle(86_deg);
  chassis.MasterController.waitUntilSettled();
  chassis.MasterController.stop();

  pros::delay(4750);

  //////
  shooter.setHoodAngle(38);
  intake.MainIntakePID.reset();
  intake.PreFlywheelIntakePID.reset();
  shooter.FlywheelPID.flipDisable(false);
  shooter.FlywheelPID.controllerSet(1);
  intake.MainIntakePID.setTarget(4000 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(-4000 + M_Intake_Preflywheel.get_position());
  shooter.runFlywheel(87);
  pros::delay(500);
  shooter.FlywheelPID.waitUntilSettled();
  intake.MainIntakePID.setTarget(360 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(360 + M_Intake_Preflywheel.get_position());
  intake.PreFlywheelIntakePID.waitUntilSettled();

  shooter.setHoodAngle(26);
  shooter.FlywheelPID.controllerSet(1);
  intake.MainIntakePID.setTarget(4000 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(-4000 + M_Intake_Preflywheel.get_position());
  shooter.runFlywheel(87);
  pros::delay(500);
  shooter.FlywheelPID.waitUntilSettled();
  intake.MainIntakePID.setTarget(1000 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(1000 + M_Intake_Preflywheel.get_position());
  intake.PreFlywheelIntakePID.waitUntilSettled();
  shooter.runFlywheel(0);
  intake.MainIntakePID.flipDisable(true);
  intake.PreFlywheelIntakePID.flipDisable(true);
  shooter.FlywheelPID.flipDisable(true);

  chassis.MasterController.stop();
}

void autonomousBlue1()
{
  //chassis.MasterController.setMaxVoltage(6000);
  std::cout << "BLUE" << "\n";
  std::cout << "CAMON" << "\n";

  intake.MainIntakePID.flipDisable(false); //
  intake.PreFlywheelIntakePID.flipDisable(false); //
  shooter.FlywheelPID.flipDisable(true);

  intake.runMainIntake(100);
  intake.runPreFlywheel(-100);

  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{40.5_in,0_in,0_deg}}, "2");
  chassis.MotionController.setTarget("1", false); //default false (straight)
  chassis.MotionController.waitUntilSettled();

  chassis.MotionController.setTarget("2", true); //default false (straight)
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{52_in,0_in,0_deg}}, "3");
  chassis.MotionController.waitUntilSettled();

  intake.runMainIntake(0);
  intake.runPreFlywheel(-50);

  chassis.MasterController.stop();
  intake.MainIntakePID.flipDisable(true); //
  intake.PreFlywheelIntakePID.flipDisable(true); //
  chassis.MasterController.turnAngle(96_deg);
  chassis.MasterController.waitUntilSettled();
  chassis.MasterController.stop();

  chassis.MasterController.waitUntilSettled();
  chassis.MasterController.stop();

  intake.MainIntakePID.flipDisable(false); //
  intake.PreFlywheelIntakePID.flipDisable(false);

  intake.MainIntakePID.flipDisable(true); //
  intake.PreFlywheelIntakePID.flipDisable(true); //


  //chassis.turn(-5);
  chassis.MasterController.waitUntilSettled();

  intake.MainIntakePID.flipDisable(false); //
  intake.PreFlywheelIntakePID.flipDisable(false); //


  //////
  shooter.setHoodAngle(37);
  intake.MainIntakePID.flipDisable(false); //
  intake.PreFlywheelIntakePID.flipDisable(false); //
  intake.MainIntakePID.reset();
  intake.PreFlywheelIntakePID.reset();
  shooter.FlywheelPID.flipDisable(false);
  shooter.FlywheelPID.controllerSet(1);
  intake.MainIntakePID.setTarget(4000 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(-4000 + M_Intake_Preflywheel.get_position());
  shooter.runFlywheel(87);
  pros::delay(500);
  shooter.FlywheelPID.waitUntilSettled();
  intake.MainIntakePID.setTarget(360 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(360 + M_Intake_Preflywheel.get_position());
  intake.PreFlywheelIntakePID.waitUntilSettled();

  shooter.setHoodAngle(22);
  shooter.FlywheelPID.controllerSet(1);
  intake.MainIntakePID.setTarget(4000 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(-4000 + M_Intake_Preflywheel.get_position());
  shooter.runFlywheel(87);
  pros::delay(500);
  shooter.FlywheelPID.waitUntilSettled();
  intake.MainIntakePID.setTarget(500 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(500 + M_Intake_Preflywheel.get_position());
  intake.PreFlywheelIntakePID.waitUntilSettled();
  shooter.runFlywheel(0);
  shooter.FlywheelPID.flipDisable(true);
  //////
  chassis.MasterController.stop();

  intake.runMainIntake(0);
  intake.runPreFlywheel(-50);

  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{14_in,0_in,0_deg}}, "4");
  chassis.MasterController.turnAngle(-4_deg);
  chassis.MasterController.waitUntilSettled();
  //std::cout << "Facing 3, going to 3\n";
  chassis.MotionController.setTarget("4", true); //default false (straight)
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{31_in,13_in,44_deg}}, "5"); //+,-,-
  chassis.MotionController.waitUntilSettled();

  donger.DongerPID.flipDisable(false);
  donger.DongerPID.setTarget(120*6);

  chassis.MotionController.setTarget("5", false); //default false (straight)
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{18_in,0_in,-45_deg}}, "6");
  chassis.MotionController.waitUntilSettled();

  intake.MainIntakePID.flipDisable(true); //
  intake.PreFlywheelIntakePID.flipDisable(true); //

  chassis.MasterController.waitUntilSettled();

  intake.MainIntakePID.flipDisable(false); //
  intake.PreFlywheelIntakePID.flipDisable(false); //


  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{8_in,0_in,0_deg}}, "7");
  chassis.MotionController.waitUntilSettled();

  donger.DongerPID.setTarget(190*6);
  donger.DongerPID.waitUntilSettled();

  chassis.MotionController.setTarget("7", true); //default false (straight)

  chassis.MotionController.waitUntilSettled();

  donger.DongerPID.setTarget(130*6);
  intake.runMainIntake(110);
  intake.runPreFlywheel(-110);


  chassis.MotionController.setTarget("7", false); //default false (straight)
  chassis.MotionController.waitUntilSettled();

  chassis.MotionController.setTarget("7", true); //default false (straight)
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{16_in,0_in,0_deg}}, "8");
  chassis.MotionController.waitUntilSettled();


  chassis.MasterController.turnAngle(-170_deg);
  chassis.MotionController.waitUntilSettled();

  chassis.MotionController.setTarget("8", true); //default false (straight)
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{12_in,0_in,0_deg}}, "9");
  chassis.MotionController.waitUntilSettled();

  chassis.MotionController.setTarget("9", true); //default false (straight)
  intake.runMainIntake(0);
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{26_in,0_in,-45_deg}}, "10");

  arm.ArmPID.flipDisable(false);
  arm.ArmPID.setTarget(80); //3:1 Ratio
  arm.ArmPID.waitUntilSettled();
  arm.ArmPID.setTarget(0);
  chassis.MotionController.waitUntilSettled();

  chassis.MotionController.setTarget("7", false); //default false (straight)
  chassis.MotionController.waitUntilSettled();

  chassis.MasterController.turnAngle(170_deg);
  chassis.MotionController.waitUntilSettled();

  chassis.MotionController.setTarget("10", true); //default false (straight)
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{46_in,0_in,0_deg}}, "11");
  chassis.MotionController.waitUntilSettled();

  chassis.MasterController.driveVector(-0.17, 0);
  pros::delay(1200);

  chassis.MasterController.stop();
  pros::delay(100);

  chassis.MotionController.setTarget("11", false); //default false (straight)
  chassis.MotionController.waitUntilSettled();

  chassis.MasterController.turnAngle(86_deg);
  chassis.MasterController.waitUntilSettled();
  chassis.MasterController.stop();

  pros::delay(4750);

  chassis.MasterController.stop();
}


void autonomousSkills1()
{
  //chassis.MasterController.setMaxVoltage(6000);
  std::cout << "BLUE" << "\n";
  std::cout << "CAMON" << "\n";

  intake.MainIntakePID.flipDisable(false); //
  intake.PreFlywheelIntakePID.flipDisable(false); //
  shooter.FlywheelPID.flipDisable(true);

  intake.runMainIntake(100);
  intake.runPreFlywheel(-100);

  // DRIVE FORWARD
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{38_in,0_in,0_deg}}, "1SKILLS");
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{46_in,0_in,0_deg}}, "2");
  chassis.MotionController.setTarget("1SKILLS", false); //default false (straight)
  chassis.MotionController.waitUntilSettled();
  // DRIVE BACKWARD
  chassis.MotionController.setTarget("2", true); //default false (straight)
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{54_in,0_in,0_deg}}, "3");
  chassis.MotionController.waitUntilSettled();

  intake.runMainIntake(50);
  intake.runPreFlywheel(-50);

  // TURN TO CAP 1
  chassis.MasterController.stop();
  intake.MainIntakePID.flipDisable(true); //
  intake.PreFlywheelIntakePID.flipDisable(true); //
  chassis.MasterController.turnAngle(-94_deg);
  chassis.MasterController.waitUntilSettled();
  chassis.MasterController.stop();

  chassis.MasterController.waitUntilSettled();
  chassis.MasterController.stop();

  intake.MainIntakePID.flipDisable(false); //
  intake.PreFlywheelIntakePID.flipDisable(false);

  intake.MainIntakePID.flipDisable(true); //
  intake.PreFlywheelIntakePID.flipDisable(true); //


  //chassis.turn(-5);
  chassis.MasterController.waitUntilSettled();

  intake.MainIntakePID.flipDisable(false); //
  intake.PreFlywheelIntakePID.flipDisable(false); //


  //////// SHOOT FLAG
  shooter.setHoodAngle(37);
  intake.MainIntakePID.flipDisable(false); //
  intake.PreFlywheelIntakePID.flipDisable(false); //
  intake.MainIntakePID.reset();
  intake.PreFlywheelIntakePID.reset();
  shooter.FlywheelPID.flipDisable(false);
  shooter.FlywheelPID.controllerSet(1);
  intake.MainIntakePID.setTarget(4000 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(-4000 + M_Intake_Preflywheel.get_position());
  shooter.runFlywheel(87);
  pros::delay(500);
  shooter.FlywheelPID.waitUntilSettled();
  intake.MainIntakePID.setTarget(360 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(360 + M_Intake_Preflywheel.get_position());
  intake.PreFlywheelIntakePID.waitUntilSettled();

  shooter.setHoodAngle(22);
  shooter.FlywheelPID.controllerSet(1);
  intake.MainIntakePID.setTarget(4000 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(-4000 + M_Intake_Preflywheel.get_position());
  shooter.runFlywheel(87);
  pros::delay(500);
  shooter.FlywheelPID.waitUntilSettled();
  intake.MainIntakePID.setTarget(500 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(500 + M_Intake_Preflywheel.get_position());
  intake.PreFlywheelIntakePID.waitUntilSettled();
  shooter.runFlywheel(0);
  shooter.FlywheelPID.flipDisable(true);
  //////
  chassis.MasterController.stop();

  intake.runMainIntake(50);
  intake.runPreFlywheel(-50);

  // DRIVE BACKWARD TO SET DONGER ARM
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{14_in,0_in,0_deg}}, "4");
  chassis.MasterController.turnAngle(6_deg);
  chassis.MasterController.waitUntilSettled();
  //std::cout << "Facing 3, going to 3\n";
  chassis.MotionController.setTarget("4", true); //default false (straight)
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{30_in,-13.5_in,-45_deg}}, "5");
  chassis.MotionController.waitUntilSettled();

  donger.DongerPID.flipDisable(false);
  donger.DongerPID.setTarget(120*6);

  // DRIVE SPLINE FR TO CAP 2
  chassis.MotionController.setTarget("5", false); //default false (straight)
  chassis.MotionController.waitUntilSettled();

  intake.MainIntakePID.flipDisable(true); //
  intake.PreFlywheelIntakePID.flipDisable(true); //

  chassis.MasterController.waitUntilSettled();

  intake.MainIntakePID.flipDisable(false); //
  intake.PreFlywheelIntakePID.flipDisable(false); //

  intake.runMainIntake(110);
  intake.runPreFlywheel(-110);

  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{8_in,0_in,0_deg}}, "7");
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{10_in,0_in,0_deg}}, "7B");

  chassis.MotionController.waitUntilSettled();

  // DONG CAP 2
  donger.DongerPID.setTarget(190*6);
  donger.DongerPID.waitUntilSettled();

  chassis.MotionController.setTarget("7", true); //default false (straight)

  chassis.MotionController.waitUntilSettled();

  donger.DongerPID.setTarget(130*6);

  chassis.MotionController.setTarget("7B", false); //default false (straight)
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{16_in,0_in,0_deg}}, "8");
  chassis.MotionController.waitUntilSettled();

  // DRIVE BACKWARD TO RED TILE EDGE
  chassis.MotionController.setTarget("8", true); //default false (straight)
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{26_in,0_in,0_deg}}, "9A");
  chassis.MotionController.waitUntilSettled();

  chassis.MasterController.turnAngle(3_deg);
  chassis.MasterController.waitUntilSettled();


  //////// SHOOT CENTER FLAGS
  shooter.setHoodAngle(35);
  intake.MainIntakePID.reset();
  intake.PreFlywheelIntakePID.reset();
  shooter.FlywheelPID.flipDisable(false);
  shooter.FlywheelPID.controllerSet(1);
  intake.MainIntakePID.setTarget(4000 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(-4000 + M_Intake_Preflywheel.get_position());
  shooter.runFlywheel(87);
  pros::delay(500);
  shooter.FlywheelPID.waitUntilSettled();
  intake.MainIntakePID.setTarget(360 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(360 + M_Intake_Preflywheel.get_position());
  intake.PreFlywheelIntakePID.waitUntilSettled();

  shooter.setHoodAngle(21);
  shooter.FlywheelPID.controllerSet(1);
  intake.MainIntakePID.setTarget(4000 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(-4000 + M_Intake_Preflywheel.get_position());
  shooter.runFlywheel(87);
  pros::delay(500);
  shooter.FlywheelPID.waitUntilSettled();
  intake.MainIntakePID.setTarget(1000 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(1000 + M_Intake_Preflywheel.get_position());
  intake.PreFlywheelIntakePID.waitUntilSettled();
  shooter.runFlywheel(0);
  intake.MainIntakePID.flipDisable(true);
  intake.PreFlywheelIntakePID.flipDisable(true);
  shooter.FlywheelPID.flipDisable(true);
  //////

  // TURN TO ABS90DEG
  //chassis.MotionController.setTarget("8", false); //default false (straight)
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{25_in,14_in,45_deg}}, "9B");
  //chassis.MasterController.turnAngle(55_deg);
  chassis.MotionController.waitUntilSettled();

  chassis.MasterController.turnAngle(135_deg);
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{30_in,0_in,0_deg}}, "10");
  chassis.MasterController.waitUntilSettled();

  chassis.MotionController.setTarget("10", false); //default false (straight)
  chassis.MotionController.waitUntilSettled();

  chassis.MasterController.turnAngle(-90_deg);
  chassis.MasterController.waitUntilSettled();



  // DRIVE UP TO CENTER PARK
  chassis.MasterController.driveVector(0.8, 0);
  pros::delay(3100);
  chassis.MasterController.stop();

}


void autonomousSkills1OLD()
{
  //chassis.MasterController.setMaxVoltage(6000);
  std::cout << "BLUE" << "\n";
  std::cout << "CAMON" << "\n";

  intake.MainIntakePID.flipDisable(false); //
  intake.PreFlywheelIntakePID.flipDisable(false); //
  shooter.FlywheelPID.flipDisable(true);

  intake.runMainIntake(100);
  intake.runPreFlywheel(-100);

  // DRIVE FORWARD
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{38_in,0_in,0_deg}}, "1SKILLS");
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{46_in,0_in,0_deg}}, "2");
  chassis.MotionController.setTarget("1SKILLS", false); //default false (straight)
  chassis.MotionController.waitUntilSettled();
  // DRIVE BACKWARD
  chassis.MotionController.setTarget("2", true); //default false (straight)
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{54_in,0_in,0_deg}}, "3");
  chassis.MotionController.waitUntilSettled();

  intake.runMainIntake(50);
  intake.runPreFlywheel(-50);

  // TURN TO CAP 1
  chassis.MasterController.stop();
  intake.MainIntakePID.flipDisable(true); //
  intake.PreFlywheelIntakePID.flipDisable(true); //
  chassis.MasterController.turnAngle(-96_deg);
  chassis.MasterController.waitUntilSettled();
  chassis.MasterController.stop();

  chassis.MasterController.waitUntilSettled();
  chassis.MasterController.stop();

  intake.MainIntakePID.flipDisable(false); //
  intake.PreFlywheelIntakePID.flipDisable(false);

  intake.MainIntakePID.flipDisable(true); //
  intake.PreFlywheelIntakePID.flipDisable(true); //


  //chassis.turn(-5);
  chassis.MasterController.waitUntilSettled();

  intake.MainIntakePID.flipDisable(false); //
  intake.PreFlywheelIntakePID.flipDisable(false); //


  //////// SHOOT FLAG
  shooter.setHoodAngle(37);
  intake.MainIntakePID.flipDisable(false); //
  intake.PreFlywheelIntakePID.flipDisable(false); //
  intake.MainIntakePID.reset();
  intake.PreFlywheelIntakePID.reset();
  shooter.FlywheelPID.flipDisable(false);
  shooter.FlywheelPID.controllerSet(1);
  intake.MainIntakePID.setTarget(4000 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(-4000 + M_Intake_Preflywheel.get_position());
  shooter.runFlywheel(87);
  pros::delay(500);
  shooter.FlywheelPID.waitUntilSettled();
  intake.MainIntakePID.setTarget(360 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(360 + M_Intake_Preflywheel.get_position());
  intake.PreFlywheelIntakePID.waitUntilSettled();

  shooter.setHoodAngle(22);
  shooter.FlywheelPID.controllerSet(1);
  intake.MainIntakePID.setTarget(4000 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(-4000 + M_Intake_Preflywheel.get_position());
  shooter.runFlywheel(87);
  pros::delay(500);
  shooter.FlywheelPID.waitUntilSettled();
  intake.MainIntakePID.setTarget(500 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(500 + M_Intake_Preflywheel.get_position());
  intake.PreFlywheelIntakePID.waitUntilSettled();
  shooter.runFlywheel(0);
  shooter.FlywheelPID.flipDisable(true);
  //////
  chassis.MasterController.stop();

  intake.runMainIntake(50);
  intake.runPreFlywheel(-50);

  // DRIVE BACKWARD TO SET DONGER ARM
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{14_in,0_in,0_deg}}, "4");
  chassis.MasterController.turnAngle(4_deg);
  chassis.MasterController.waitUntilSettled();
  //std::cout << "Facing 3, going to 3\n";
  chassis.MotionController.setTarget("4", true); //default false (straight)
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{30.5_in,-13.5_in,-45_deg}}, "5");
  chassis.MotionController.waitUntilSettled();

  donger.DongerPID.flipDisable(false);
  donger.DongerPID.setTarget(120*6);

  // DRIVE SPLINE FR TO CAP 2
  chassis.MotionController.setTarget("5", false); //default false (straight)
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{18_in,0_in,45_deg}}, "6");
  chassis.MotionController.waitUntilSettled();

  intake.MainIntakePID.flipDisable(true); //
  intake.PreFlywheelIntakePID.flipDisable(true); //

  chassis.MasterController.waitUntilSettled();

  intake.MainIntakePID.flipDisable(false); //
  intake.PreFlywheelIntakePID.flipDisable(false); //

  intake.runMainIntake(110);
  intake.runPreFlywheel(-110);

  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{8_in,0_in,0_deg}}, "7");
  chassis.MotionController.waitUntilSettled();

  // DONG CAP 2
  donger.DongerPID.setTarget(190*6);
  donger.DongerPID.waitUntilSettled();

  chassis.MotionController.setTarget("7", true); //default false (straight)

  chassis.MotionController.waitUntilSettled();

  donger.DongerPID.setTarget(130*6);

  chassis.MotionController.setTarget("7", false); //default false (straight)
  chassis.MotionController.waitUntilSettled();

  // DRIVE BACKWARD TO RED TILE EDGE
  chassis.MotionController.setTarget("7", true); //default false (straight)
  //chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{8_in,0_in,0_deg}}, "8");
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{26_in,0_in,0_deg}}, "9A");
  chassis.MotionController.waitUntilSettled();

  chassis.MasterController.turnAngle(10_deg);
  chassis.MotionController.waitUntilSettled();


  //////// SHOOT CENTER FLAGS
  shooter.setHoodAngle(35);
  intake.MainIntakePID.reset();
  intake.PreFlywheelIntakePID.reset();
  shooter.FlywheelPID.flipDisable(false);
  shooter.FlywheelPID.controllerSet(1);
  intake.MainIntakePID.setTarget(4000 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(-4000 + M_Intake_Preflywheel.get_position());
  shooter.runFlywheel(87);
  pros::delay(500);
  shooter.FlywheelPID.waitUntilSettled();
  intake.MainIntakePID.setTarget(360 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(360 + M_Intake_Preflywheel.get_position());
  intake.PreFlywheelIntakePID.waitUntilSettled();

  shooter.setHoodAngle(24);
  shooter.FlywheelPID.controllerSet(1);
  intake.MainIntakePID.setTarget(4000 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(-4000 + M_Intake_Preflywheel.get_position());
  shooter.runFlywheel(87);
  pros::delay(500);
  shooter.FlywheelPID.waitUntilSettled();
  intake.MainIntakePID.setTarget(1000 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(1000 + M_Intake_Preflywheel.get_position());
  intake.PreFlywheelIntakePID.waitUntilSettled();
  shooter.runFlywheel(0);
  intake.MainIntakePID.flipDisable(true);
  intake.PreFlywheelIntakePID.flipDisable(true);
  shooter.FlywheelPID.flipDisable(true);
  //////

  // TURN TO ABS90DEG
  //chassis.MotionController.setTarget("8", false); //default false (straight)
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{25_in,14_in,45_deg}}, "9B");
  chassis.MasterController.turnAngle(55_deg);
  chassis.MotionController.waitUntilSettled();

  // DRIVE FORWARD TO AVOID CAP 2 IN SPLINE
  chassis.MotionController.setTarget("9A", false); //default false (straight)
  chassis.MotionController.waitUntilSettled();

  // DRIVE SPLINE FL TO AVOID CAP 1 AND 2
  chassis.MotionController.setTarget("9B", false); //default false (straight)
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{26.35_in,-21.74_in,-90_deg}}, "10");
  chassis.MotionController.waitUntilSettled();

//  chassis.MotionController.setTarget("10", false); //default false (straight)
   chassis.MotionController.generatePath({Point{0_in,0_in,-45_deg}, Point{51_in,21_in,45_deg}}, "11");
   chassis.MotionController.setTarget("11", false); //default false (straight)

//  chassis.MotionController.waitUntilSettled();

  // DO DONG SEQUENCE
  chassis.MotionController.setTarget("7", false); //default false (straight)
  chassis.MotionController.waitUntilSettled();

  donger.DongerPID.setTarget(190*6);
  donger.DongerPID.waitUntilSettled();

  chassis.MotionController.setTarget("7", true); //default false (straight)
  chassis.MotionController.waitUntilSettled();

  donger.DongerPID.setTarget(130*6);

  chassis.MotionController.setTarget("7", false); //default false (straight)
  chassis.MotionController.waitUntilSettled();

  // DRIVE BACKWARD FOR 180 TURN
  chassis.MotionController.setTarget("7", true); //default false (straight)
  chassis.MotionController.waitUntilSettled();

  chassis.MasterController.turnAngle(180_deg);
  chassis.MotionController.waitUntilSettled();

  // DRIVE BACKWARD TO RESET AT FRONT OF CAP 3
  chassis.MotionController.setTarget("7", true); //default false (straight)
  chassis.MotionController.waitUntilSettled();

  // DRIVE SPLINE BL TO LINE UP WITH FLAGS (BLUE TILE) AND FLIP CAP 3
  //chassis.MotionController.setTarget("11", false); //default false (straight)
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{40_in,0_in,0_deg}}, "12");
  arm.ArmPID.flipDisable(false);
  arm.ArmPID.setTarget(75); //3:1 Ratio
  arm.ArmPID.waitUntilSettled();
  arm.ArmPID.setTarget(0);
  chassis.MotionController.waitUntilSettled();

  //////// SHOOT RIGHT FLAGS
  shooter.setHoodAngle(37);
  intake.MainIntakePID.reset();
  intake.PreFlywheelIntakePID.reset();
  shooter.FlywheelPID.flipDisable(false);
  shooter.FlywheelPID.controllerSet(1);
  intake.MainIntakePID.setTarget(4000 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(-4000 + M_Intake_Preflywheel.get_position());
  shooter.runFlywheel(87);
  pros::delay(500);
  shooter.FlywheelPID.waitUntilSettled();
  intake.MainIntakePID.setTarget(360 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(360 + M_Intake_Preflywheel.get_position());
  intake.PreFlywheelIntakePID.waitUntilSettled();

  shooter.setHoodAngle(26);
  shooter.FlywheelPID.controllerSet(1);
  intake.MainIntakePID.setTarget(4000 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(-4000 + M_Intake_Preflywheel.get_position());
  shooter.runFlywheel(87);
  pros::delay(500);
  shooter.FlywheelPID.waitUntilSettled();
  intake.MainIntakePID.setTarget(1000 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(1000 + M_Intake_Preflywheel.get_position());
  intake.PreFlywheelIntakePID.waitUntilSettled();
  shooter.runFlywheel(0);
  intake.MainIntakePID.flipDisable(true);
  intake.PreFlywheelIntakePID.flipDisable(true);
  shooter.FlywheelPID.flipDisable(true);

  // TURN TO PLATFORM
  chassis.MasterController.turnAngle(-90_deg);
  chassis.MotionController.waitUntilSettled();

  // DRIVE FORWARD TO EDGE OF PLATFORM
  chassis.MotionController.setTarget("12", true); //default false (straight)
  chassis.MotionController.waitUntilSettled();

  // DRIVE UP TO CENTER PARK
  chassis.MasterController.driveVector(0.8, 0);
  pros::delay(2500);
  chassis.MasterController.stop();

}























void autonomousRed1BEAST()
{
  //chassis.MasterController.setMaxVelocity(150); //rpm
  //chassis.MasterController.
  //chassis.MG_Drivetrain_Left.setMaxCurrent(1000);
  chassis.MasterController.setMaxVoltage(2000);

  intake.MainIntakePID.flipDisable(true); //
  intake.PreFlywheelIntakePID.flipDisable(true); //

  shooter.FlywheelPID.flipDisable(true);
  intake.runMainIntake(100);
  intake.runPreFlywheel(-100);
  chassis.MasterController.moveDistance(35_in);
  chassis.MasterController.waitUntilSettled();
  //chassis.MasterController.setMaxVelocity(40); //rpm
  //chassis.MasterController.moveDistance(15_in);
  chassis.MasterController.waitUntilSettled();
  //chassis.MasterController.setMaxVelocity(60); //rpm

  //std::cout << "At 1, going to 2\n";
  chassis.MasterController.moveDistance(-41.5_in);
  chassis.MasterController.waitUntilSettled();
  //std::cout << "At 2, turning to 3\n";
  intake.runMainIntake(50);
  intake.runPreFlywheel(-50);
  //chassis.MasterController.turnAngle(-94_deg);
  //chassis.MasterController.waitUntilSettled();

  //chassis.MasterController.setMaxVelocity(600);
  chassis.MasterController.stop();
  chassis.MasterController.turnAngle(-91_deg);
  //chassis.turn(0);
  chassis.MasterController.stop();


    //std::cout << "Facing 3, going to 3\n";
    chassis.MasterController.moveDistance(52_in);
    chassis.MasterController.waitUntilSettled();
    //std::cout << "Facing 3, going to 3\n";
    chassis.MasterController.moveDistance(-59_in); //-49
    chassis.MasterController.waitUntilSettled();

    donger.DongerPID.flipDisable(false);
    donger.DongerPID.setTarget(120*6);
    //donger.DongerPID.waitUntilSettled();

    chassis.MasterController.moveDistance(16_in);
    chassis.MasterController.waitUntilSettled();

  //////
  shooter.setHoodAngle(33);
  intake.MainIntakePID.flipDisable(true); //
  intake.PreFlywheelIntakePID.flipDisable(true); //
  intake.MainIntakePID.reset();
  intake.PreFlywheelIntakePID.reset();
  shooter.FlywheelPID.flipDisable(false);
  shooter.FlywheelPID.controllerSet(1);
  intake.MainIntakePID.setTarget(5000 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(-5000 + M_Intake_Preflywheel.get_position());
  shooter.runFlywheel(87);
  pros::delay(500);
  shooter.FlywheelPID.waitUntilSettled();
  intake.MainIntakePID.setTarget(360 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(360 + M_Intake_Preflywheel.get_position());
  intake.PreFlywheelIntakePID.waitUntilSettled();

  shooter.setHoodAngle(22);
  shooter.FlywheelPID.controllerSet(1);
  intake.MainIntakePID.setTarget(5000 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(-5000 + M_Intake_Preflywheel.get_position());
  shooter.runFlywheel(87);
  pros::delay(500);
  shooter.FlywheelPID.waitUntilSettled();
  intake.MainIntakePID.setTarget(1000 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(1000 + M_Intake_Preflywheel.get_position());
  intake.PreFlywheelIntakePID.waitUntilSettled();
  shooter.runFlywheel(0);
  intake.MainIntakePID.flipDisable(true);
  intake.PreFlywheelIntakePID.flipDisable(true);
  shooter.FlywheelPID.flipDisable(true);
  //////
  chassis.MasterController.stop();
  //chassis.MasterController.setMaxVelocity(6000); //rpm

  //chassis.turn(-4.5);

  ////intake.runMain/Intake(100);
  ////intake.runPreFlywheel(100);

  //pros::delay(3000);

  //intake.runMain//intake(50);
  //intake.runPreFlywheel(-50);
  //shooter.FlywheelPID.flipDisable();

  //chassis.MasterController.setMaxVelocity(60); //rpm



  //std::cout << "At 2, turning to 3\n";
  //chassis.MasterController.turnAngle(30_deg);
  //chassis.turn(45);
  chassis.MasterController.waitUntilSettled();
  /*//std::cout << "Facing 3, going to 3\n";
  chassis.MasterController.moveDistance(10_in);
  chassis.MasterController.waitUntilSettled();
  //std::cout << "At 2, turning to 3\n";
  chassis.MasterController.turnAngle(29_deg);
  chassis.MasterController.waitUntilSettled();*/
  ////intake.runMain//intake(0);
  ////intake.runPreFlywheel(0);
  //std::cout << "Facing 3, going to 3\n";



  chassis.MasterController.turnAngle(53_deg);
  //chassis.turn(45);
  chassis.MasterController.waitUntilSettled();
  chassis.MasterController.moveDistance(18_in);
  chassis.MasterController.waitUntilSettled();

  donger.DongerPID.setTarget(190*6);
  donger.DongerPID.waitUntilSettled();

  chassis.MasterController.moveDistance(-8_in);
  chassis.MasterController.waitUntilSettled();
  donger.DongerPID.setTarget(130*6);
  chassis.MasterController.moveDistance(12_in);
  chassis.MasterController.waitUntilSettled();
  chassis.MasterController.moveDistance(-14_in);
  chassis.MasterController.waitUntilSettled();

  chassis.MasterController.turnAngle(-53_deg);
  //chassis.turn(0);
  chassis.MasterController.waitUntilSettled();
  chassis.MasterController.moveDistance(-34_in);
  chassis.MasterController.waitUntilSettled();

  chassis.MasterController.turnAngle(90_deg);
  //chassis.turn(90);
  chassis.MasterController.waitUntilSettled();
  //chassis.MasterController.setMaxVelocity(150);
  //chassis.MasterController.moveDistance(40_in);
  chassis.MasterController.driveVector(0.5, 0);
  pros::delay(2500);
  chassis.MasterController.stop();
  //chassis.MasterController.waitUntilSettled();
  //chassis.MasterController.setMaxVelocity(60);
  chassis.MasterController.moveDistance(2_in);
  chassis.MasterController.moveDistance(-5_in);
  chassis.MasterController.waitUntilSettled();

  chassis.MasterController.turnAngle(-85_deg);
  //chassis.turn(6);
  chassis.MasterController.waitUntilSettled();

  //////
  shooter.setHoodAngle(25);
  intake.MainIntakePID.flipDisable(true); //
  intake.PreFlywheelIntakePID.flipDisable(true); //
  intake.MainIntakePID.reset();
  intake.PreFlywheelIntakePID.reset();
  shooter.FlywheelPID.flipDisable(false);
  shooter.FlywheelPID.controllerSet(1);
  intake.MainIntakePID.setTarget(5000 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(-5000 + M_Intake_Preflywheel.get_position());
  shooter.runFlywheel(87);
  pros::delay(500);
  shooter.FlywheelPID.waitUntilSettled();
  intake.MainIntakePID.setTarget(360 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(360 + M_Intake_Preflywheel.get_position());
  intake.PreFlywheelIntakePID.waitUntilSettled();

  shooter.setHoodAngle(22);
  shooter.FlywheelPID.controllerSet(1);
  intake.MainIntakePID.setTarget(5000 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(-5000 + M_Intake_Preflywheel.get_position());
  shooter.runFlywheel(87);
  pros::delay(500);
  shooter.FlywheelPID.waitUntilSettled();
  intake.MainIntakePID.setTarget(1000 + M_Intake_Main.get_position());
  intake.PreFlywheelIntakePID.setTarget(1000 + M_Intake_Preflywheel.get_position());
  intake.PreFlywheelIntakePID.waitUntilSettled();
  shooter.runFlywheel(0);
  intake.MainIntakePID.flipDisable(true);
  intake.PreFlywheelIntakePID.flipDisable(true);
  shooter.FlywheelPID.flipDisable(true);


  //intake.runMain//intake(0);
  //intake.runPreFlywheel(0);

}

void autonomousRed1OLD()
{
  /*
  chassis.MotionController.generatePath({Point{0_in, 0_in, 0_deg}, Point{10_in, 0_in, 0_deg}}, "R1:1");
  chassis.MotionController.generatePath({Point{10_in, 0_in, 0_deg}, Point{0_in, 0_in, 0_deg}}, "R1:2");

  chassis.MotionController.setTarget("R1:1");
  chassis.MotionController.waitUntilSettled();
  //std::cout << "At 1, going to 2\n";
  chassis.MotionController.setTarget("R1:2");
  chassis.MotionController.waitUntilSettled();
  //std::cout << "At 2, going to 2\n";
  */

  //chassis.MasterController.setPosPIDFull(0,0.001, 0.0008, 0.0005,0.001,5,0.001,10);  //FIXME: Not doing anything - wrong controller
  //chassis.MasterController.setVelPIDFull(0,0, 0, 0,0,5,0.001,10);  //FIXME: Not doing anything - wrong controller

  chassis.MasterController.setMaxVelocity(60); //rpm
  //intake.runMain//intake(100);
  //intake.runPreFlywheel(-100);
  chassis.MasterController.moveDistance(30_in);
  chassis.MasterController.waitUntilSettled();
  chassis.MasterController.setMaxVelocity(40); //rpm
  chassis.MasterController.moveDistance(15_in);
  chassis.MasterController.waitUntilSettled();
  chassis.MasterController.setMaxVelocity(60); //rpm

  ////std::cout << "At 1, going to 2\n";
  chassis.MasterController.moveDistance(-46.5_in);
  chassis.MasterController.waitUntilSettled();
  ////std::cout << "At 2, turning to 3\n";
  //intake.runMain//intake(50);
  //intake.runPreFlywheel(-50);
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
  //intake.runMain//intake(100);
  //intake.runPreFlywheel(100);

  pros::delay(3000);

  //intake.runMain//intake(50);
  //intake.runPreFlywheel(-50);
  shooter.FlywheelPID.flipDisable();


  //std::cout << "Facing 3, going to 3\n";
  chassis.MasterController.moveDistance(49_in);
  chassis.MasterController.waitUntilSettled();
  //std::cout << "Facing 3, going to 3\n";
  chassis.MasterController.moveDistance(-49_in);
  chassis.MasterController.waitUntilSettled();
  //std::cout << "At 2, turning to 3\n";
  chassis.MasterController.turnAngle(30_deg);
  chassis.MasterController.waitUntilSettled();
  //std::cout << "Facing 3, going to 3\n";
  chassis.MasterController.moveDistance(10_in);
  chassis.MasterController.waitUntilSettled();
  //std::cout << "At 2, turning to 3\n";
  chassis.MasterController.turnAngle(29_deg);
  chassis.MasterController.waitUntilSettled();
  //intake.runMain//intake(0);
  //intake.runPreFlywheel(0);
  //std::cout << "Facing 3, going to 3\n";
  chassis.MasterController.moveDistance(14_in);
  chassis.MasterController.waitUntilSettled();
}
