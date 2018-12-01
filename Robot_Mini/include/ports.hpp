#include "api.h"

extern pros::Controller Controller0Base;
extern pros::Controller Controller1Base;


// V5 Smart Ports
extern pros::Motor M_Drivetrain_LF;
extern pros::Motor M_Drivetrain_LM;
extern pros::Motor M_Drivetrain_LR;
extern pros::Motor M_Drivetrain_RF;
extern pros::Motor M_Drivetrain_RM;
extern pros::Motor M_Drivetrain_RR;

extern pros::Motor FlywheelMotor1;
extern pros::Motor FlywheelMotor2;
extern pros::Motor FlywheelMotorHood;

extern pros::Motor PreFlywheelMotor1;
extern pros::Motor PreFlywheelMotor2;

extern FILE * serialPort;

extern void serialRead(void* a);
//extern pros::Task taskSerialRead();

class PYROController
{
  private:
    pros::Controller *Controller;
  public:
    PYROController(pros::Controller &cont)
    {
      Controller = &cont;
    }
    void tankDrive(bool enabled = 1)
    {
      M_Drivetrain_LF = Controller->get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
      M_Drivetrain_LM = Controller->get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
      M_Drivetrain_LR = Controller->get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
      M_Drivetrain_RF = Controller->get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
      M_Drivetrain_RM = Controller->get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
      M_Drivetrain_RR = Controller->get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

    }
    int32_t get_digital(pros::controller_digital_e_t button)
    {
      Controller -> get_digital(button);
    }
    int32_t get_analog(pros::controller_analog_e_t channel)
    {
      Controller -> get_analog(channel);
    }
};

extern PYROController Controller0;
extern PYROController Controller1;
