#include "api.h"

extern double HEADING_RAW;
extern double HEADING_ADJUSTED;
extern double HEADING_FROM_CAMERA;
extern double ax;
extern double ay;
extern double az;
extern double lastUpdateTime;
extern double msSinceLastUpdate;
extern int lastID;
extern double IMU_YAW;

extern FILE * serialPort;

extern void serialInit();
extern void serialRead(void* a);
extern void serialWrite(void* a);
extern void serialClose(FILE * serialPort);
