#include "../include/serial.hpp"
#include "../include/api.h"
#include "../include/robot.hpp"
#include "../include/pros/apix.h"

/*
 * FILE DESCRIPTION
 * serial.cpp defines the functions related to the
 * robot's serial communications with the Raspberry Pi
 */

double HEADING_RAW = 0;
double HEADING_ADJUSTED = 0;
double ax = 0;
double ay = 0;
double az = 0;

int lastID = -1;
//
double lastUpdateTime = pros::millis();
double msSinceLastUpdate = -1;

FILE * serialPort = NULL;


//Initialize serial comms with the Pi
void serialInit()
{
  pros::c::serctl( SERCTL_DEACTIVATE, (void*)0x6E6973 );
  pros::c::serctl( SERCTL_DEACTIVATE, (void*)0x74756f73);
  pros::c::serctl( SERCTL_DISABLE_COBS, NULL );
}

void serialRead(void* a)
{
  char serialCharArray [100] = {0};

  //pros::lcd::print(1, "Before fopen");

  serialPort = NULL;
  int startMillis = pros::millis();
  do{
  serialPort = fopen("/ser/sin", "r" );	// Opens serialPort Filestream as serial read
} while(serialPort == NULL || pros::millis() - startMillis > 1000); // FIXME
  //pros::lcd::print(2, "After fopen");

  if (serialPort == NULL)             	// Could not open serial stream
  {
    pros::lcd::print(0, "ERROR: SERIAL PORT NOT OPENED (READ)");
  }
	else
  {
    //pros::lcd::print(3, "Serial Stream Opened");

    fgets(serialCharArray, 100, serialPort);

    fflush(serialPort);
    pros::delay(10); //FIXME

  	fclose (serialPort);
  }


	//Check if it is at start of packet (255254)
	if(		 serialCharArray[0] == '1'
			&& serialCharArray[1] == '2'
			&& serialCharArray[2] == '8'
			&& serialCharArray[3] == '1'
			&& serialCharArray[4] == '2'
			&& serialCharArray[5] == '7')
	{
		char headtemp[7] = {serialCharArray[6], serialCharArray[7], serialCharArray[8], serialCharArray[9], serialCharArray[10], serialCharArray[11], serialCharArray[12]};
		HEADING_RAW = std::stof( headtemp );
		char axtemp[7] = {serialCharArray[13], serialCharArray[14], serialCharArray[15], serialCharArray[16], serialCharArray[17], serialCharArray[18], serialCharArray[19]};
		ax = std::stof( axtemp );
    char aytemp[7] = {serialCharArray[20], serialCharArray[21], serialCharArray[22], serialCharArray[23], serialCharArray[24], serialCharArray[25], serialCharArray[26]};
    ay = std::stof( aytemp );
    char aztemp[7] = {serialCharArray[27], serialCharArray[28], serialCharArray[29], serialCharArray[30], serialCharArray[31], serialCharArray[32], serialCharArray[33]};
    az = std::stof( aztemp );
    int IDTemp[2] = {serialCharArray[34], serialCharArray[35]};
    /*
    std::string str = "";
    for (int i = 0; i < 2; i++)
    {
  		str += std::to_string(IDTemp[i]);
  	}*/

    int IDTempRes = IDTemp[1];// = std::stoi(str);

    if(IDTempRes != floor(lastID%10))
    {
      lastID = IDTempRes;
      lastUpdateTime = pros::millis();
    }

    if(HEADING_RAW > 180)
      HEADING_ADJUSTED = HEADING_RAW - 360;
    else
      HEADING_ADJUSTED = HEADING_RAW;
	}

	//pros::lcd::print(4, "Serial heading: %f", heading);	// Write new data to screen
	//pros::lcd::print(5, "Serial ax: %f", ax);	// Write new data to screen
  msSinceLastUpdate = pros::millis() - lastUpdateTime;
}

void serialWrite(void* a) // TODO: Does not work yet
{
  char serialCharArray [] = {"RESET\0"};

  serialPort = fopen("/ser/sin", "w" );	// Opens serialPort Filestream as serial read

  if (serialPort == NULL)             	// Could not open serial stream
  {
    pros::lcd::print(6, "ERROR: SERIAL PORT NOT OPENED (WRITE)");
  }
	else
  {
    //pros::lcd::print(6, "Serial Stream Opened");
    //pros::lcd::print(6, serialCharArray);
    fputs(serialCharArray, serialPort);
    //fprintf(serialPort, "RESET\n");
    //printf("Should have sent: RESET\ n");
  }
	fflush(serialPort);

  pros::delay(20);

	fclose (serialPort);
}

void serialClose(FILE * serialPort)  //Obsolete with tasks
{
  fclose (serialPort);
}
