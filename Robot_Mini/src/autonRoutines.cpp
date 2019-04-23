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

  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{41_in,0_in,0_deg}}, "2");
  chassis.MotionController.setTarget("1", false); //default false (straight)
  chassis.MotionController.waitUntilSettled();

  chassis.MotionController.setTarget("2", true); //default false (straight)
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{52_in,0_in,0_deg}}, "3");
  chassis.MotionController.waitUntilSettled();

  intake.runMainIntake(50);
  intake.runPreFlywheel(-50);

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

  intake.runMainIntake(50);
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

  intake.runMainIntake(110);
  intake.runPreFlywheel(-110);

  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{8_in,0_in,0_deg}}, "7");
  chassis.MotionController.waitUntilSettled();

  donger.DongerPID.setTarget(190*6);
  donger.DongerPID.waitUntilSettled();

  chassis.MotionController.setTarget("7", true); //default false (straight)

  chassis.MotionController.waitUntilSettled();

  donger.DongerPID.setTarget(130*6);

  chassis.MotionController.setTarget("7", false); //default false (straight)
  chassis.MotionController.waitUntilSettled();

  chassis.MotionController.setTarget("7", true); //default false (straight)
  chassis.MotionController.generatePath({Point{0_in,0_in,0_deg}, Point{16_in,0_in,0_deg}}, "8");
  chassis.MotionController.waitUntilSettled();

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

  chassis.MasterController.turnAngle(-90_deg);
  chassis.MasterController.waitUntilSettled();
  chassis.MasterController.stop();

  //////
  shooter.setHoodAngle(43);
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
