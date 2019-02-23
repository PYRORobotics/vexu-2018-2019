#include "../include/api.h"
#include "../include/controller.hpp"

/*
 * FILE DESCRIPTION
 * controller.cpp defines the functions and implements the TODO PYROController
 * Class and objects.
 */

using namespace pros;

/* Master Controller */
Controller Controller0(E_CONTROLLER_MASTER);
/* Partner Controller */
Controller Controller1(E_CONTROLLER_PARTNER);

/* Controller Value Array for printing values*/
std::string contValues[16];

void controllerPrintValues(int num)
{
  pros::lcd::print(0, "[%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s] [%s|%s|%s|%s]",
                      contValues[0],contValues[1],contValues[2],contValues[3],
                      contValues[4],contValues[5],contValues[6],contValues[7],
                      contValues[8],contValues[9],contValues[10],contValues[11],
                      contValues[12],contValues[13],contValues[14],contValues[15]);
}
