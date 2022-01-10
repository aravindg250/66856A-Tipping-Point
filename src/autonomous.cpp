#include "sensorFunctions.h"
#include "driveTrainFunctions.h"
#include "controls.h"
#include "vex.h"

using namespace vex;

const float WHEEL_DIAMETER = 4.125;
const float WHEEL_CIRCUMFERENCE = WHEEL_DIAMETER * 3.1415926535;



double int2deg(double dist) {
  return (dist/WHEEL_CIRCUMFERENCE)*360;
}

void driveForward( int inches, int vel ) {
    leftDrive.setVelocity(vel, percentUnits::pct);
    rightDrive.setVelocity(vel, percentUnits::pct);
    leftDrive.spinFor(fwd, int2deg(inches), rotationUnits::deg, false);
    rightDrive.spinFor(fwd, int2deg(inches), rotationUnits::deg);
    clamp.set(true);
    leftDrive.stop(brakeType::hold);
    rightDrive.stop(brakeType::hold);
}