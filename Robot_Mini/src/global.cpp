#include "../include/global.hpp"
#include "../include/ports.hpp"
#include "../include/api.h"
#include "../include/robot.hpp"
#include "../include/pros/apix.h"

int autoSelection;



float heading = -1;
float ax = 0;
float ay = 0;
float az = 0;

FILE * serialPort = NULL;


//Initialize serial comms with Pi
void serialInit()
{
  serctl( SERCTL_DEACTIVATE, (void*)0x6E6973 );
  serctl( SERCTL_DEACTIVATE, (void*)0x74756f73);
  serctl( SERCTL_DISABLE_COBS, NULL );
}

void serialRead(void* a) // read/write enum?
{
  char mystring [100] = {0};

  serialPort = fopen("/ser/sin", "r" );	// Opens serialPort Filestream as serial read

  if (serialPort == NULL)             	// Could not open serial stream
  {
    pros::lcd::print(6, "ERROR");
  }
	else
  {
    //pros::lcd::print(6, "Serial Stream Opened");
    std::string oldstring = mystring;
    fgets (mystring , 100, serialPort);
		if (mystring != oldstring ) 									// If incomming data is new:
    {
      //pros::lcd::print(0, "Serial String: %s", mystring);	// Write new data to screen
		}
  }
	fflush(serialPort);

	//Check if it is at start of packet (255254)
	if(		 mystring[0] == '1'
			&& mystring[1] == '2'
			&& mystring[2] == '8'
			&& mystring[3] == '1'
			&& mystring[4] == '2'
			&& mystring[5] == '7')
	{
		char headtemp[7] = {mystring[6], mystring[7], mystring[8], mystring[9], mystring[10], mystring[11], mystring[12]};
		heading = std::stof( headtemp );
		char axtemp[7] = {mystring[13], mystring[14], mystring[15], mystring[16], mystring[17], mystring[18], mystring[19]};
		ax = std::stof( axtemp );
    char aytemp[7] = {mystring[20], mystring[21], mystring[22], mystring[23], mystring[24], mystring[25], mystring[26]};
    ay = std::stof( aytemp );
    char aztemp[7] = {mystring[27], mystring[28], mystring[29], mystring[30], mystring[31], mystring[32], mystring[33]};
    az = std::stof( aztemp );
	}

	float abc = std::stof( mystring );
	//pros::lcd::print(4, "Serial heading: %f", heading);	// Write new data to screen
	//pros::lcd::print(5, "Serial ax: %f", ax);	// Write new data to screen

  pros::delay(20);

	fclose (serialPort);
}

void serialClose(FILE * serialPort)  //Obsolete with tasks
{
  fclose (serialPort);
}
