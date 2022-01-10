/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// fork                 motor         16              
// lift                 motor_group   1, 2            
// clamp                digital_out   A               
// hook                 digital_out   B               
// leftDrive            motor_group   19, 21          
// rightDrive           motor_group   15, 14          
// encode               digital_in    C               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "sensorFunctions.h"
#include "driveTrainFunctions.h"
#include "controls.h"
#include "autonomous.h"
using namespace vex;





float leftSide, rightSide;
double volts = 10;
// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following functionvdlvidhviejrnvierverioiiogergrgververvfrom this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

//Autonomous Settingss
double desiredValue = 0;
int desiredTurnValue = 0;

bool enableDrivePID = true;

//Settings
double kP = 0.08; // increase kp means to go faster, higher speed
double kI = 0.00; // it give you extra push
double kD = 0.7; //increase to slow down

double turnkP = 0.01;
double turnkI = 0.0001;
double turnkD = 0.001;

int error; //SensorValue - DesiredValue : Position Value
int prevError = 0; //Postion 20ms ago
int derivative;
int totalError = 0; //totalError = totalError + error

int turnError; //SensorValue - DesiredValue : Position Value
int turnPrevError = 0; //Postion 20ms ago
int turnDerivative;
int turnTotalError = 0; //totalError = totalError + error

bool resetDriveSensors = false;

int drivePID()
{
  while(enableDrivePID)
  {

    if(resetDriveSensors)
    {
      resetDriveSensors = false;

      leftDrive.setPosition(0, rotationUnits::deg);
      rightDrive.setPosition(0, rotationUnits::deg);
    }

    //get position of motors
    int leftMotorPosition = leftDrive.position(degrees);
    int rightMotorPosition = rightDrive.position(degrees);
   
   
    //
    //Lateral Movement
    //

    //get average of two motors
    int averagePosition = (leftMotorPosition + rightMotorPosition)/2;
    
    
    //Potential
    error = averagePosition - desiredValue;

    //Derivative
    derivative = error - prevError;


    //Integral
    totalError += error;

    double lateralMotorPower = (error * kP + derivative * kD + totalError * kI);

    ///////////////////////////////////////////////////////////////////////////////
    //Turning Movement PID
    //////////////////////////////////////////////////////////////////////////////
    //get average of two motors
    int turnDifference = (leftMotorPosition - rightMotorPosition);
    
    
    //Potential
    turnError = turnDifference - desiredTurnValue;

    //Derivative
    turnDerivative = turnError - turnPrevError;


    //Integral
    turnTotalError += turnError;

    double turnMotorPower = (turnError * turnkP + turnDerivative * turnkD);





    leftDrive.spin(reverse, lateralMotorPower + turnMotorPower, voltageUnits::volt);
    rightDrive.spin(reverse, lateralMotorPower - turnMotorPower, voltageUnits::volt);
    prevError = error;
    turnPrevError = turnError;
    vex::task::sleep(20);
  }
  return 1;
}
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  vex::task drivingStuff(drivePID);
  
  resetDriveSensors = true;
  //  desiredValue = int2deg(10);
  // desiredTurnValue = int2deg(30);


  desiredValue = int2deg(55);

  vex::task::sleep(1300);
  clamp.set(true);
  vex::task::sleep(400);
  // lift.rotateFor(fwd, 1000, msec, 75, velocityUnits::rpm);
  // lift.stop(brakeType::hold);

  // vex::task::sleep(4000);

  resetDriveSensors = true;
  // desiredTurnValue = 0;

desiredValue = int2deg(-45);
  // clamp.set(false);
  // resetDriveSensors = true;
  // desiredValue = int2deg(50);
  // vex::task::sleep(1800);
  // clamp.set(true);
  // vex::task::sleep(1000);
  // //lift.rotateFor(fwd, 1000, msec, 75, velocityUnits::rpm);
  // vex::task::sleep(500);
  // resetDriveSensors = true;
  // desiredValue = int2deg(-10);

  
vex::task::sleep(500);

  

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    double speed = 1;
    enableDrivePID = false;

    leftDrive.spin(directionType::fwd, (Controller1.Axis3.value() + Controller1.Axis1.value())/2, velocityUnits::pct); //(Axis3+Axis4)/2;
    rightDrive.spin(directionType::fwd, (Controller1.Axis3.value() - Controller1.Axis1.value())/2, velocityUnits::pct);//(Axis3-Axis4)/2;

    //--------------------------------------------------------
    //-----------------TANK DRIVE-----------------------------
    // leftSide = Controller1.Axis3.value();
    // rightSide = Controller1.Axis2.value();
    // leftDrive.spin(fwd, leftSide/(1.75), percentUnits::pct);
    // rightDrive.spin(fwd, rightSide/(1.75), percentUnits::pct);
    //--------------------------------------------------------
   

    forkLift();
    fourBar();
    barClamp();
    underClaw();
    // intakes();


    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
