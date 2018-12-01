#include "api.h"

using namespace pros;



class Drivetrain
{
  friend class Robot;
  private:
    Motor *MotorLF;
    Motor *MotorLM;
    Motor *MotorLR;
    Motor *MotorRF;
    Motor *MotorRM;
    Motor *MotorRR;
  public:
    Drivetrain();
    //double getVelocity;
};

class Robot
{
  private:
    Drivetrain DrivetrainObj;
  public:
    Robot();
    void arcadeDrive();
    void tankDrive();


};

extern Robot Robot_Mini;
