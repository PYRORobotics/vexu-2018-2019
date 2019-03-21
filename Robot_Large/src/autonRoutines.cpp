#include "../include/autonRoutines.hpp"
#include "../include/main.h"


int autonomousIDNum = -1;

void autonomousRed1()
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

  chassis.MasterController.setPosPIDFull(0.001,0.0045, 0.005, 0.00008,0.001,0.001,0.001,10);  //FIXME: Not doing anything - wrong controller
  chassis.MasterController.setVelPIDFull(0.001,0.0045, 0.005, 0.00008,0.001,0.001,0.001,10);  //FIXME: Not doing anything - wrong controller

  chassis.MasterController.setMaxVelocity(90); //rpm

  chassis.MasterController.moveDistance(42_in);
  chassis.MasterController.waitUntilSettled();
  std::cout << "At 1, going to 2\n";
  chassis.MasterController.moveDistance(-35_in);
  chassis.MasterController.waitUntilSettled();
  std::cout << "At 2, turning to 3\n";
  chassis.MasterController.turnAngle(-90_deg);
  chassis.MasterController.waitUntilSettled();
  std::cout << "Facing 3, going to 3\n";
  chassis.MasterController.moveDistance(42_in);
  chassis.MasterController.waitUntilSettled();



}
