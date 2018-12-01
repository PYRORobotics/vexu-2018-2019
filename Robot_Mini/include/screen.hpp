#include "api.h"


extern int process;
extern double distTraveled;
extern bool velIsLocked;
extern int setVel;
extern bool runAuto;

extern void mainCenter();
extern void toFlywheel();
extern void selectedFlywheel();
extern void toDrivetrain();
extern void selectedDrivetrain();
extern void toAuto();
extern void selectedAuto();

extern void printSerial();

class Screen
{
  private:

  public:
    Screen()
    {
      process = 0;
    }
    void write();
};
