#include "api.h"

extern int autoSelection;

extern pros::Task taskSerialRead();



extern float heading;
extern float ax;
extern float ay;
extern float az;

extern FILE * serialPort;

extern void serialInit();
extern void serialRead(void* a);
extern void serialClose(FILE * serialPort);
