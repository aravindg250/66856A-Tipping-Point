#include "sensorFunctions.h"
#include "driveTrainFunctions.h"
#include "controls.h"
#include "vex.h"

using namespace vex;


void forkLift()
{
  if(Controller1.ButtonL1.pressing())
  {
    fork.setVelocity(150, velocityUnits::rpm);
    fork.spin(reverse);
  }
  else if(Controller1.ButtonL2.pressing())
  {
    fork.setVelocity(150, velocityUnits::rpm);
    fork.spin(fwd);                                                                 
  }
  else
  {
    fork.stop(brakeType::hold);
  }
}
void fourBar()
{
  if(Controller1.ButtonR2.pressing())
  {
    
    lift.spin(directionType::rev, 75, velocityUnits::pct);
  }
  else if(Controller1.ButtonR1.pressing())
  {
    lift.spin(directionType::fwd, 350, velocityUnits::pct);                                                                 
  }
  else
  { 
    lift.stop(brakeType::hold);
  }
}
void barClamp()
{
  if(Controller1.ButtonA.pressing())
  {
    clamp.set(true);
  }
  else if(Controller1.ButtonX.pressing())
  {
    clamp.set(false);
  }
}
void underClaw()
{
  if(Controller1.ButtonUp.pressing())
  {
    hook.set(true);
  }
  else if(Controller1.ButtonLeft.pressing())
  {
    hook.set(false);
  }
}

void intakes()
{
  if(Controller1.ButtonY.pressing())
  {
    
    intake.spin(directionType::rev, 60, velocityUnits::pct);
  }
  else if(Controller1.ButtonB.pressing())
  {
    intake.spin(directionType::fwd, 350, velocityUnits::pct);                                                                 
  }
  else
  {
    intake.stop(brakeType::hold);
  }
}