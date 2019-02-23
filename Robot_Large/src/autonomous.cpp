#include "../include/main.h"

enum autoSelection
{
  Red1,
  Blue1,
  Red2,
  Blue2,
  Red3,
  Blue3,
  Red4,
  Blue4
};

static double setpointPosition = 0;
static driveType moveType = forward;
static bool routeFinished = true;

double currentRotations = 0;
static double errorDrivetrain = 0;
int minimumSpeed = 25;
int minimumIncrementSpeedUpTime = 75;



void PositionPIDTask(void* param)
{
  double i = 0;
  while(1)
  {
    if(routeFinished == true) i = 0;
    double kp;
    if(moveType == forward || moveType == reverse)
    {
      kp = 8;
      currentRotations = M_Drivetrain_LF.get_position() * 4 * M_PI;
      errorDrivetrain = setpointPosition - currentRotations;

      double setSpeed = kp * errorDrivetrain;

      //std::cout << "currentPos:" << currentRotations <<  " errorDrivetrain:" << errorDrivetrain << " | setSpeed: " << setSpeed << "\n";

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
      LargeRobot.drive(setSpeed);
      delay(10);
    }
    else
    {
      kp = 1.5;
      currentRotations = M_Drivetrain_LF.get_position() * 360 * 4 / wheelBase; //FIXME
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
      LargeRobot.drive(setSpeed, -setSpeed);
      delay(10);
    }
  }
}


//////// 2/15/19 //////////



bool newMove = false;
bool readyToTurn = false;
bool readyToDrive = false;
//double setpointHeading = 0;
double distance_setpoint = 0;
double theta_setpoint = 0;
int routeID = -1;
int routeIDHolder = routeID;


void PositionPIDTaskOLD(void* param)
{
  double i = 0;
  while(1)
  {
    if(routeFinished == true) i = 0;
    double kp;
    if(moveType == forward || moveType == reverse)
    {
      kp = 8;
      currentRotations = M_Drivetrain_LF.get_position() * 4 * M_PI;
      errorDrivetrain = setpointPosition - currentRotations;

      double setSpeed = kp * errorDrivetrain;

      //std::cout << "currentPos:" << currentRotations <<  " errorDrivetrain:" << errorDrivetrain << " | setSpeed: " << setSpeed << "\n";

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
      LargeRobot.drive(setSpeed);
      delay(10);
    }
  }
}

void TurnPIDTaskOld(void* param)
{
  double kp = 20;
  while(1)
  {
    double error = LargeRobot.setpoint_theta - LargeRobot.telemetry.heading;
    pros::lcd::print(5, "Error: %f", LargeRobot.setpoint_theta);
    pros::lcd::print(6, "Error: %f", LargeRobot.telemetry.heading);
    pros::lcd::print(7, "Error: %f", error);

    if(LargeRobot.robotTurnIsDone)
    {
      LargeRobot.robotTurnIsDone = false;
      if(fabs(kp * error) < 10)
      {
        if(error > 0)
          LargeRobot.drive(10, -10);
        else
          LargeRobot.drive(-10, 10);
      }
      else
      {
        LargeRobot.drive(kp * error, -kp * error);
      }
      if(error < 1)
      {
        LargeRobot.robotTurnIsDone = true;
      }
    }
    delay(10);
  }
}

void TurnPIDTask(void* param)
{
  double i = 0;
  while(1)
  {
    if(routeFinished == true) i = 0;
    double kp;
    if(moveType == leftPoint || moveType == rightPoint)
    {
      kp = 8;
      errorDrivetrain = LargeRobot.setpoint_theta - LargeRobot.telemetry.heading;
      if(errorDrivetrain < 0)
      {
        LargeRobot.turnClockwise = false;
      }
      else
      {
        LargeRobot.turnClockwise = true;
      }

      double setSpeed = kp * errorDrivetrain;

      //std::cout << "currentPos:" << currentRotations <<  " errorDrivetrain:" << errorDrivetrain << " | setSpeed: " << setSpeed << "\n";

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
      if(LargeRobot.turnClockwise)
      {
        LargeRobot.drive(setSpeed, -setSpeed);
      }
      else
      {
        LargeRobot.drive(-setSpeed, setSpeed);
      }

      delay(10);
    }
  }
}


void WaypointPIDTask(void* param)
{
  double i = 0;
  bool readyToDrivePID = false;
  while(1)
  {
    if(routeFinished == true) i = 0;
    double kp;
    if(!readyToDrivePID)
    {
      kp = 0.8;
      errorDrivetrain = LargeRobot.setpoint_theta - LargeRobot.telemetry.heading;
      if(errorDrivetrain > 0)
      {
        LargeRobot.turnClockwise = false;
      }
      else
      {
        LargeRobot.turnClockwise = true;
      }

      double setSpeed = kp * errorDrivetrain;

      //std::cout << "currentPos:" << currentRotations <<  " errorDrivetrain:" << errorDrivetrain << " | setSpeed: " << setSpeed << "\n";

      if(setSpeed < minimumSpeed && setSpeed > 0) setSpeed = minimumSpeed;
      if(setSpeed > -minimumSpeed && setSpeed < 0) setSpeed = -minimumSpeed;
      //if(setSpeed >=50 && i < minimumIncrementSpeedUpTime) setSpeed = i;
      //if(setSpeed <=-50 && i < minimumIncrementSpeedUpTime) setSpeed = -i;
      i+=0.5;

      if(fabs(errorDrivetrain) - 2 < 0)
      {
        setSpeed = 0;
        //M_Drivetrain_LF.tare_position();
        //delay(500);
        readyToDrivePID = true;
        //routeFinished = true;
      }
      if(LargeRobot.turnClockwise)
      {
        LargeRobot.drive(setSpeed, -setSpeed);
      }
      else
      {
        LargeRobot.drive(-setSpeed, setSpeed);
      }
    }


    if(readyToDrivePID)
    {
      kp = 8;
      currentRotations = M_Drivetrain_LM.get_position() * 4 * M_PI;
      errorDrivetrain = LargeRobot.setpoint_distance - currentRotations;

      double setSpeed = kp * errorDrivetrain;

      //std::cout << "currentPos:" << currentRotations <<  " errorDrivetrain:" << errorDrivetrain << " | setSpeed: " << setSpeed << "\n";

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
        readyToDrivePID = false;
        routeFinished = true;
      }
      LargeRobot.drive(setSpeed);
    }
    delay(10);
  }
}


void setWaypoint(Waypoint wp)
{
  newMove = true;

  LargeRobot.goToWaypoint(wp);

  distance_setpoint = 0;
  theta_setpoint = 0;
  routeID = -1;
}

void resetPosAutoREDBOTTOM()
{
  LargeRobot.telemetry.position[0] = -60.125;
  LargeRobot.telemetry.position[1] = 35.5;
  LargeRobot.telemetry.encoder_position_average = ((M_Drivetrain_LM.get_position() + M_Drivetrain_RM.get_position())/2) * 4 * M_PI;
  LargeRobot.lastPosition[0] = (M_Drivetrain_LM.get_position() + M_Drivetrain_RM.get_position())/2;
  LargeRobot.lastPosition[1] = (M_Drivetrain_LM.get_position() + M_Drivetrain_RM.get_position())/2;
}

void UpdateTelemetryTaskAUTO(void* param)
{
  while(1)
  {
    if(heading > 180)
    {
      heading = heading - 360;
    }
    LargeRobot.telemetry.heading = heading;

    LargeRobot.telemetry.encoder_position_average = ((M_Drivetrain_LM.get_position() + M_Drivetrain_RM.get_position())/2) * 4 * M_PI;

    LargeRobot.telemetry.position[0] = LargeRobot.telemetry.position[0] + ((M_Drivetrain_LM.get_position() + M_Drivetrain_RM.get_position())/2 - LargeRobot.lastPosition[0]) * 4 * M_PI *sin(LargeRobot.telemetry.heading * M_PI/180);
    LargeRobot.telemetry.position[1] = LargeRobot.telemetry.position[1] + ((M_Drivetrain_LM.get_position() + M_Drivetrain_RM.get_position())/2 - LargeRobot.lastPosition[1]) * 4 * M_PI *cos(LargeRobot.telemetry.heading* M_PI/180);

    LargeRobot.lastPosition[0] = (M_Drivetrain_LM.get_position() + M_Drivetrain_RM.get_position())/2;
    LargeRobot.lastPosition[1] = (M_Drivetrain_LM.get_position() + M_Drivetrain_RM.get_position())/2;

    LargeRobot.TurretObj.currentHoodAngle = 54 - M_Flywheel_Hood.get_position() * 14/201*360;

    delay(10);
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
 void autonomous()
 {
   if(selectedAutoMode == red1 || selectedAutoMode == blue1)  //FIXME
   {
     M_Drivetrain_LF.tare_position();
     int startTime = millis();
     // PositionPID:Task
     Task PositionPID(PositionPIDTask, NULL);
     //Task LiftPID(LiftPIDTask, NULL);

     int routeID = -1;
     routeFinished = true;

     while(millis() - startTime < 44000)
     {
       if(routeFinished == true)
       {
         if(routeID>=0) delay(1000);
         routeID++;
         M_Drivetrain_LF.tare_position();



         switch (routeID)
         {
           case 0:
             std::cout << "START R0 - DF:C1, BI:1\n";
             moveType = forward;
             setpointPosition = 36;
             LargeRobot.runIntake(127, mainIntake);
             break;
           case 1:
             std::cout << "START R1 - DR:24, BI:0\n";
             moveType = reverse;
             setpointPosition = -12;
             break;
           case 2:
            LargeRobot.runIntake(0, mainIntake);
            LargeRobot.eStop();
            break;
           default:
             PositionPID.suspend();
             break;
         }
         routeFinished = false;
       }
     }
   }
   std::cout << "AUTONOMOUS OVER!\n";
   LargeRobot.eStop();
}



void autonomousWaypointsNotWorking()
{
  // 2/15/19
  M_Drivetrain_LF.tare_position();
  resetPosAutoREDBOTTOM();
  int startTime = millis();
  //PositionPID:Task
  //Task TurnPID(TurnPIDTask, NULL);
  //Task PositionPID(PositionPIDTask, NULL);
  Task UpdateTele(UpdateTelemetryTaskAUTO, NULL);
  Task WaypointPID(WaypointPIDTask, NULL);

  int routeID = -1;
  routeFinished = true;

  Waypoint nextWaypoint;

  while(millis() - startTime < 44000)
  {
    pros::lcd::print(1, "sp theta: %f", LargeRobot.setpoint_theta);
    pros::lcd::print(2, "heading: %f", LargeRobot.telemetry.heading);
    pros::lcd::print(6, "Error: %f", LargeRobot.setpoint_theta - LargeRobot.telemetry.heading);
    serialRead(NULL);
    if(routeFinished == true)
    {
      if(routeID>=0) delay(1000);
        routeID++;
      M_Drivetrain_LF.tare_position();

      switch (routeID)
      {
        case 0:
          pros::lcd::print(5, "Case 0");
          nextWaypoint.position[0] = -11;
          nextWaypoint.position[1] = 35.5;

          LargeRobot.goToWaypoint(nextWaypoint);

          break;
        //case 1:
          //std::cout << "START R1 - DR:24, BI:0\n";
          //moveType = reverse;
          //setpointPosition = -24;
          //LargeRobot.runIntake(0, mainIntake);
          //break;
          /*
        case 0:
          moveType = forward;
          setpointPosition = 36;
          LargeRobot.runIntake(120, mainIntake);
          break;
        case 1:
          std::cout << "START R1 - DR:24, BI:0\n";
          moveType = reverse;
          setpointPosition = -24;
          LargeRobot.runIntake(0, mainIntake);
          break;*/
        //case 2:
          //std::cout << "START R2\n";
          //LargeRobot.setpoint_theta = 180;
          //break;
        //case 3:
        default:
          WaypointPID.suspend();
          break;
      }
      routeFinished = false;
    }
    delay(10);
  }
  std::cout << "AUTONOMOUS OVER!\n";
  LargeRobot.eStop();
}


  /*  WORKING PRE-2/9/2019
  M_Drivetrain_LF.tare_position();
  int startTime = millis();
  // PositionPID:Task
  Task PositionPID(PositionPIDTask, NULL);
  Task LiftPID(LiftPIDTask, NULL);

  int routeID = -1;
  routeFinished = true;

  while(millis() - startTime < 44000)
  {
    if(routeFinished == true)
    {
      if(routeID>=0) delay(1000);
      routeID++;
      M_Drivetrain_LF.tare_position();



      switch (routeID)
      {
        case 0:
          std::cout << "START R0 - DF:C1, BI:1\n";
          moveType = forward;
          setpointPosition = 36;
          LargeRobot.runIntake(100, mainIntake);
          break;
        case 1:
          std::cout << "START R1 - DR:24, BI:0\n";
          moveType = reverse;
          setpointPosition = -24;
          LargeRobot.runIntake(0, mainIntake);
          break;
        case 2:
          std::cout << "START R2\n";
          moveType = leftPoint;
          setpointPosition = 180 * 2/3;
          break;
        case 3:
          std::cout << "START R3\n";
          moveType = reverse;
          setpointPosition = -24;
          break;
        case 4:
          std::cout << "START R4\n";
          moveType = forward;
          setpointPosition = 24;
          break;
        case 5:
          std::cout << "START R5\n";
          moveType = rightPoint;
          setpointPosition = 116.5;
          break;
        case 6:
          std::cout << "START R6\n";
          moveType = reverse;
          setpointPosition = -26;
          break;
        case 7:
          std::cout << "START R7\n";
          moveType = forward;
          setpointPosition = 4; // Centered y with red square
          break;
        case 8:
          std::cout << "START R8\n";
          moveType = leftPoint;
          setpointPosition = 90;
          break;
        case 9:
          std::cout << "START R9\n";
          moveType = forward;
          setpointPosition = 48 + 6; // push flag in 6 in
          break;

        default:
          PositionPID.suspend();
          break;
      }
      routeFinished = false;
    }
  }
  std::cout << "AUTONOMOUS OVER!\n";
  LargeRobot.eStop();
}

END COMMENT 2/9/2019

LargeRobot.eStop();

}*/
