#include "shared.hpp"

float heading = -1;
float ax = 0;
float ay = 0;
float az = 0;


//Initialize serial comms with Pi
inline void serialInit()
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
    pros::lcd::print(6, "Serial Stream Opened");
    std::string oldstring = mystring;
    fgets (mystring , 100, serialPort);
		if (mystring != oldstring ) 									// If incomming data is new:
    {
      pros::lcd::print(0, "Serial String: %s", mystring);	// Write new data to screen
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
	}

	float abc = std::stof( mystring );
	pros::lcd::print(4, "Serial heading: %f", heading);	// Write new data to screen
	pros::lcd::print(5, "Serial ax: %f", ax);	// Write new data to screen

  pros::delay(20);

	fclose (serialPort);
}

void serialClose(FILE * serialPort)  //Obsolete with tasks
{
  fclose (serialPort);
}
