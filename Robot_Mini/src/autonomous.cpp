#include "../include/main.h"

pros::Motor l1(1,pros::E_MOTOR_GEARSET_06,0,pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor l2(2,pros::E_MOTOR_GEARSET_18,1,pros::E_MOTOR_ENCODER_ROTATIONS);
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

static double currHoodPos = 54 + hood.get_position() * 14/201*360;
static double hoodNextPos;
static bool readyToMoveHood = false;

static bool routeFinished = true;
enum driveType
{
  forward,
  reverse,
  leftPoint,
  rightPoint
} static moveType;
static double currentRotations;
static double setpointPosition;
static double errorDrivetrain;
int minimumSpeed = 20;
int minimumIncrementSpeedUpTime = 100;
double wheelBase = 11.5;

void drivetrainDriveAll(int speedL, int speedR)
{
  l1 = speedL;
  l2 = speedL;
  l3 = speedL;
  r1 = speedR;
  r2 = speedR;
  r3 = speedR;
}

double getHoodError()
{
  return hoodNextPos - (54 + hood.get_position() * 14/201*360);
}

void hoodDriveToAngleTask(void* param)
{
  while(1)
  {
    while(readyToMoveHood)
    {
      if(getHoodError() > 1)
      {
        hood = -30;
      }
      else if(getHoodError() < -1)
      {
        hood = 30;
      }
      else
      {
        hood = 0;
      }
    }
  }
}

void PositionPIDTask(void* param)
{
  double i = 0;
  while(1)
  {
    if(routeFinished == true) i = 0;
    double kp;
    if(moveType == forward || moveType == reverse)
    {
      kp = 6;
      currentRotations = l2.get_position() * 4 * M_PI;
      errorDrivetrain = setpointPosition - currentRotations;

      double setSpeed = kp * errorDrivetrain;

      std::cout << "currentPos:" << currentRotations <<  " errorDrivetrain:" << errorDrivetrain << " | setSpeed: " << setSpeed << "\n";

      if(setSpeed < minimumSpeed && setSpeed > 0) setSpeed = minimumSpeed;
      if(setSpeed > -minimumSpeed && setSpeed < 0) setSpeed = -minimumSpeed;
      if(setSpeed >=50 && i < minimumIncrementSpeedUpTime) setSpeed = i;
      if(setSpeed <=-50 && i < minimumIncrementSpeedUpTime) setSpeed = -i;
      i+=0.5;

      if(fabs(errorDrivetrain) - 0.15 < 0)
      {
        setSpeed = 0;
        //M_Drivetrain_LF.tare_position();
        //delay(500);
        routeFinished = true;
      }
      drivetrainDriveAll(setSpeed, 0.98* setSpeed);
      //l2 = setSpeed;
      //l3 = setSpeed;
      pros::delay(10);
    }
    else
    {
      kp = 1.6;
      currentRotations = l2.get_position() * 360 * 4 / wheelBase; //FIXME
      if(moveType == rightPoint)
      {
        errorDrivetrain = setpointPosition - currentRotations;
      }
      else
      {
        errorDrivetrain = -setpointPosition - currentRotations;
        //errorDrivetrain *= -1;
      }
      double setSpeed = kp * errorDrivetrain;

      //std::cout << "currentPos:" << currentRotations <<  " errorDrivetrain:" << errorDrivetrain << " | setSpeed: " << setSpeed << "\n";

      if(setSpeed < minimumSpeed && setSpeed >= 0) setSpeed = minimumSpeed;
      if(setSpeed > -minimumSpeed && setSpeed <= 0) setSpeed = -minimumSpeed;
      if(setSpeed >=50 && i < minimumIncrementSpeedUpTime) setSpeed = i;
      if(setSpeed <=-50 && i < minimumIncrementSpeedUpTime) setSpeed = -i;
      i+=0.5;


      if(fabs(errorDrivetrain) - 0.3 < 0)
      {
        setSpeed = 0;
        //M_Drivetrain_LF.tare_position();
        //delay(500);
        routeFinished = true;
      }
      drivetrainDriveAll(setSpeed, -setSpeed);
      //l2 = setSpeed;
      //l3 = setSpeed;
      pros::delay(10);
    }
  }
}


/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
 void autonomousRED()
   {
     l1.set_brake_mode(MOTOR_BRAKE_BRAKE);
     l2.set_brake_mode(MOTOR_BRAKE_BRAKE);
     l3.set_brake_mode(MOTOR_BRAKE_BRAKE);
     r1.set_brake_mode(MOTOR_BRAKE_BRAKE);
     r2.set_brake_mode(MOTOR_BRAKE_BRAKE);
     r3.set_brake_mode(MOTOR_BRAKE_BRAKE);
   l2.tare_position();
   int startTime = pros::millis();
   pros::Task PositionPID(PositionPIDTask, NULL);
   pros::Task HoodControl(hoodDriveToAngleTask, NULL);

   //PositionPID:Task
   //PositionPID.resume();
   //Task LiftPID(LiftPIDTask, NULL);

   int routeID = -1;
   routeFinished = true;

   while(pros::millis() - startTime < 44000)
   {
     pros::lcd::print(0, "SP %f", setpointPosition);
     pros::lcd::print(1, "CurPos %f", currentRotations);
     pros::lcd::print(2, "Error %f", errorDrivetrain);

     std::cout << "SP " << setpointPosition << "\nCurPos " << currentRotations << "\nError " << errorDrivetrain <<"\n";

     if(routeFinished == true)
     {
       if(routeID>=0) pros::delay(1000);
       routeID++;
       l2.tare_position();



       switch (routeID)
       {
         case 0:
           //std::cout << "START R0 - DF:C1, BI:1\n";
           moveType = forward;
           setpointPosition = 46;
           intake = 127;
           preflywheel = -127;
           break;
         case 1:
           //std::cout << "START R1 - DR:24, BI:0\n";
           moveType = reverse;
           setpointPosition = -36;
           intake = 0;
           preflywheel = 0;
           break;
         case 2:
           //std::cout << "START R2\n";
           moveType = leftPoint;
           setpointPosition = 108;
           break;
         case 3:
         //setpointPosition = 0;
         //currentRotations = 0;
         //errorDrivetrain = 0;
         intake = -127;
         preflywheel = -127;
         pros::delay(100);

         intake = 0;
         preflywheel = 0;

           //setHoodAngle
           hood.move_relative(-0.72, 80);
           pros::delay(4000);
           flywheelf.move_velocity(600);
           flywheelr.move_velocity(600);
           //while(flywheelf.get_actual_velocity()<500)
           //{
             pros::delay(5000);
           //}
           intake = 127;
           preflywheel = 127;
           pros::delay(200); //FIXME SHOOTING 1st Ball NOW
           intake = 0;
           preflywheel = 0;
           //setHoodAngle
           hood.move_relative(-0.54, 80);
           pros::delay(4000);
           //while(flywheelf.get_actual_velocity()<500)
           //{
             pros::delay(5000);
           //}
           intake = 127;
           preflywheel = 127;
           pros::delay(1000); //FIXME SHOOTING 2nd Ball NOW
           intake = 0;
           preflywheel = 0;
           flywheelr = 0;
           flywheelf = 0;
           moveType = leftPoint;
           setpointPosition = 5;
           break;
         case 4:
           moveType = forward;
           setpointPosition = 52;
           break;
         case 5:
           moveType = reverse;
           setpointPosition = -66;

           break;
         default:
           drivetrainDriveAll(0, 0);
           setpointPosition = 0;
           currentRotations = 0;
           errorDrivetrain = 0;
           //PositionPID.suspend();
           break;
       }
       routeFinished = false;
       pros::delay(10);
     }
   }
   std::cout << "AUTONOMOUS OVER!\n";
   //LargeRobot.eStop();

   drivetrainDriveAll(0, 0);
   disabled();
 }

 void autonomousBLUEFINAL()
 {
   l1.set_brake_mode(MOTOR_BRAKE_BRAKE);
   l2.set_brake_mode(MOTOR_BRAKE_BRAKE);
   l3.set_brake_mode(MOTOR_BRAKE_BRAKE);
   r1.set_brake_mode(MOTOR_BRAKE_BRAKE);
   r2.set_brake_mode(MOTOR_BRAKE_BRAKE);
   r3.set_brake_mode(MOTOR_BRAKE_BRAKE);
 l2.tare_position();
 int startTime = pros::millis();
 pros::Task PositionPID(PositionPIDTask, NULL);
 pros::Task HoodControl(hoodDriveToAngleTask, NULL);

 //PositionPID:Task
 //PositionPID.resume();
 //Task LiftPID(LiftPIDTask, NULL);

 int routeID = -1;
 routeFinished = true;

 while(pros::millis() - startTime < 44000)
 {
   pros::lcd::print(0, "SP %f", setpointPosition);
   pros::lcd::print(1, "CurPos %f", currentRotations);
   pros::lcd::print(2, "Error %f", errorDrivetrain);

   std::cout << "SP " << setpointPosition << "\nCurPos " << currentRotations << "\nError " << errorDrivetrain <<"\n";

   if(routeFinished == true)
   {
     if(routeID>=0) pros::delay(1000);
     routeID++;
     l2.tare_position();



     switch (routeID)
     {
       case 0:
         //std::cout << "START R0 - DF:C1, BI:1\n";
         moveType = forward;
         setpointPosition = 48;
         intake = 127;
         preflywheel = -127;
         break;
       case 1:
         //std::cout << "START R1 - DR:24, BI:0\n";
         PositionPID.suspend();

         drivetrainDriveAll(30, 30);
         pros::delay(900);

         PositionPID.resume();
         moveType = reverse;
         setpointPosition = -42;

         break;
       case 2:
         //std::cout << "START R2\n";
         intake = 0;
         preflywheel = 0;
         moveType = rightPoint;
         setpointPosition = 96;
         //setHoodAngle

         break;
       case 3:
       //setpointPosition = 0;
       //currentRotations = 0;
       //errorDrivetrain = 0;

       //pros::delay(100);

       hood.move_relative(-0.72, 80);
       intake = -127;
       preflywheel = -127;
       pros::delay(20);
       intake = 0;
       preflywheel = 0;

       flywheelf.move_velocity(600);
       flywheelr.move_velocity(600);


         //while(flywheelf.get_actual_velocity()<500)
         //{
           pros::delay(5000);
         //}
         intake = 127;
         preflywheel = 127;
         pros::delay(200); //FIXME SHOOTING 1st Ball NOW
         intake = 0;
         preflywheel = 0;
         //setHoodAngle
         hood.move_relative(-0.54, 80);
         //pros::delay(4000);
         //while(flywheelf.get_actual_velocity()<500)
         //{
           pros::delay(2000);
         //}
         intake = 127;
         preflywheel = 127;
         pros::delay(500); //FIXME SHOOTING 2nd Ball NOW
         intake = 80;
         preflywheel = -80;
         flywheelr = 0;
         flywheelf = 0;
         moveType = rightPoint;
         setpointPosition = 10;
         break;
       case 4:
         moveType = forward;
         setpointPosition = 52;
         break;
       case 5:
         moveType = reverse;
         setpointPosition = -77;

         break;
       case 6:
         moveType = leftPoint;
         setpointPosition = 110;
         break;

       case 7:
         //moveType = forward;
         //setpointPosition = 14;
         PositionPID.suspend();

         drivetrainDriveAll(40, 40);
         pros::delay(1500);
         drivetrainDriveAll(0, 0);
         routeID++;
         case 8:
           //moveType = forward;
           //setpointPosition = -14;
           drivetrainDriveAll(-40, -40);
           pros::delay(1000);
           routeID++;
           routeFinished = true;
       case 9:
        PositionPID.resume();
         moveType = forward;
         setpointPosition = 43;
         break;
       default:
         drivetrainDriveAll(0, 0);
         setpointPosition = 0;
         currentRotations = 0;
         errorDrivetrain = 0;
         intake = 0;
         preflywheel = 0;
         //PositionPID.suspend();
         break;
     }
     routeFinished = false;
     pros::delay(10);
   }
 }
 std::cout << "AUTONOMOUS OVER!\n";
 //LargeRobot.eStop();

 drivetrainDriveAll(0, 0);
 disabled();
}

void autonomous()//REDFINAL
{
  l1.set_brake_mode(MOTOR_BRAKE_BRAKE);
  l2.set_brake_mode(MOTOR_BRAKE_BRAKE);
  l3.set_brake_mode(MOTOR_BRAKE_BRAKE);
  r1.set_brake_mode(MOTOR_BRAKE_BRAKE);
  r2.set_brake_mode(MOTOR_BRAKE_BRAKE);
  r3.set_brake_mode(MOTOR_BRAKE_BRAKE);
l2.tare_position();
int startTime = pros::millis();
pros::Task PositionPID(PositionPIDTask, NULL);
pros::Task HoodControl(hoodDriveToAngleTask, NULL);

//PositionPID:Task
//PositionPID.resume();
//Task LiftPID(LiftPIDTask, NULL);

int routeID = -1;
routeFinished = true;

while(pros::millis() - startTime < 44000)
{
  pros::lcd::print(0, "SP %f", setpointPosition);
  pros::lcd::print(1, "CurPos %f", currentRotations);
  pros::lcd::print(2, "Error %f", errorDrivetrain);

  std::cout << "SP " << setpointPosition << "\nCurPos " << currentRotations << "\nError " << errorDrivetrain <<"\n";

  if(routeFinished == true)
  {
    if(routeID>=0) pros::delay(1000);
    routeID++;
    l2.tare_position();



    switch (routeID)
    {
      case 0:
        //std::cout << "START R0 - DF:C1, BI:1\n";
        moveType = forward;
        setpointPosition = 48;
        intake = 127;
        preflywheel = -127;
        break;
      case 1:
        //std::cout << "START R1 - DR:24, BI:0\n";
        PositionPID.suspend();

        drivetrainDriveAll(30, 30);
        pros::delay(900);

        PositionPID.resume();
        moveType = reverse;
        setpointPosition = -42;

        break;
      case 2:
        //std::cout << "START R2\n";
        intake = 0;
        preflywheel = 0;
        moveType = leftPoint;
        setpointPosition = 96;
        //setHoodAngle

        break;
      case 3:
      //setpointPosition = 0;
      //currentRotations = 0;
      //errorDrivetrain = 0;

      //pros::delay(100);

      hood.move_relative(-0.72, 80);
      intake = -127;
      preflywheel = -127;
      pros::delay(20);
      intake = 0;
      preflywheel = 0;

      flywheelf.move_velocity(600);
      flywheelr.move_velocity(600);


        //while(flywheelf.get_actual_velocity()<500)
        //{
          pros::delay(5000);
        //}
        intake = 127;
        preflywheel = 127;
        pros::delay(200); //FIXME SHOOTING 1st Ball NOW
        intake = 0;
        preflywheel = 0;
        //setHoodAngle
        hood.move_relative(-0.54, 80);
        //pros::delay(4000);
        //while(flywheelf.get_actual_velocity()<500)
        //{
          pros::delay(2000);
        //}
        intake = 127;
        preflywheel = 127;
        pros::delay(500); //FIXME SHOOTING 2nd Ball NOW
        intake = 80;
        preflywheel = -80;
        flywheelr = 0;
        flywheelf = 0;
        moveType = leftPoint;
        setpointPosition = 10;
        break;
      case 4:
        moveType = forward;
        setpointPosition = 52;
        break;
      case 5:
        moveType = reverse;
        setpointPosition = -77;

        break;
      case 6:
        moveType = rightPoint;
        setpointPosition = 110;
        break;

      case 7:
        //moveType = forward;
        //setpointPosition = 14;
        PositionPID.suspend();

        drivetrainDriveAll(40, 40);
        pros::delay(1500);
        drivetrainDriveAll(0, 0);
        routeID++;
        case 8:
          //moveType = forward;
          //setpointPosition = -14;
          drivetrainDriveAll(-40, -40);
          pros::delay(1000);
          routeID++;
          routeFinished = true;
      case 9:
       PositionPID.resume();
        moveType = forward;
        setpointPosition = 43;
        break;
      default:
        drivetrainDriveAll(0, 0);
        setpointPosition = 0;
        currentRotations = 0;
        errorDrivetrain = 0;
        intake = 0;
        preflywheel = 0;
        //PositionPID.suspend();
        break;
    }
    routeFinished = false;
    pros::delay(10);
  }
}
std::cout << "AUTONOMOUS OVER!\n";
//LargeRobot.eStop();

drivetrainDriveAll(0, 0);
disabled();
}
