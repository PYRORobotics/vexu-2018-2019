#include "../include/api.h"
#include "../include/ports.hpp"

// V5 Smart Ports
pros::Motor M_Drivetrain_LF(1,0);
pros::Motor M_Drivetrain_LM(2,false);
pros::Motor M_Drivetrain_LR(3,false);
pros::Motor M_Drivetrain_RF(4,1);
pros::Motor M_Drivetrain_RM(5,true);
pros::Motor M_Drivetrain_RR(6,true);

pros::Motor FlywheelMotor1(7,0);
pros::Motor FlywheelMotor2(8,1);
pros::Motor FlywheelMotorHood(9,0);

pros::Motor PreFlywheelMotor1(10,0);
pros::Motor PreFlywheelMotor2(11,1);



pros::Task taskSerialRead (serialRead, (void*)"", TASK_PRIORITY_DEFAULT,
            TASK_STACK_DEPTH_DEFAULT, "My Task");

            pros::Controller Controller0Base(pros::E_CONTROLLER_MASTER);
            pros::Controller Controller1Base(pros::E_CONTROLLER_PARTNER);

            PYROController Controller0(Controller0Base);
            PYROController Controller1(Controller1Base);
