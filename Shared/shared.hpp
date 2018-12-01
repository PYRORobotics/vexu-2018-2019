#include "../Robot_Mini/include/api.h"
#include "../Robot_Mini/include/pros/apix.h"

extern float heading;
extern float ax;
extern float ay;
extern float az;

extern FILE * serialPort;

extern void serialInit();
extern void serialRead(void* a);
extern void serialClose(FILE * serialPort);
