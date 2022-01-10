#include "sensorFunctions.h"
#include "vex.h"

using namespace vex;

double convertToTick (double inch)
{
  return inch/(4*3.1415936);
}


