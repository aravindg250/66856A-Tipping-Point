#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor fork = motor(PORT16, ratio18_1, true);
motor liftMotorA = motor(PORT1, ratio18_1, true);
motor liftMotorB = motor(PORT2, ratio18_1, false);
motor_group lift = motor_group(liftMotorA, liftMotorB);
digital_out clamp = digital_out(Brain.ThreeWirePort.A);
digital_out hook = digital_out(Brain.ThreeWirePort.B);
motor leftDriveMotorA = motor(PORT19, ratio18_1, false);
motor leftDriveMotorB = motor(PORT21, ratio18_1, false);
motor_group leftDrive = motor_group(leftDriveMotorA, leftDriveMotorB);
motor rightDriveMotorA = motor(PORT15, ratio18_1, true);
motor rightDriveMotorB = motor(PORT14, ratio18_1, true);
motor_group rightDrive = motor_group(rightDriveMotorA, rightDriveMotorB);
digital_in encode = digital_in(Brain.ThreeWirePort.C);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}