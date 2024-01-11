/*
 * All of the greatest bloat
 * 
 * :)
 */

#pragma once

#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.

#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;


// START V5 MACROS
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END V5 MACROS


// Controller
controller Controller1 = controller(primary);

// Robot configuration code.
motor leftMotorA = motor(PORT1, ratio18_1, false);
motor leftMotorB = motor(PORT2, ratio18_1, false);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);
motor rightMotorA = motor(PORT9, ratio18_1, true);
motor rightMotorB = motor(PORT10, ratio18_1, true);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);
// inertial DrivetrainInertial = inertial(PORT11);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, /*DrivetrainInertial, */319.19, 320, 40, mm, 1);

// (I'm assuming that false is normal turn direction)
motor shooter = motor(PORT12, ratio36_1, false); // Shooter
motor pullup = motor(PORT20, ratio6_1, false); // Pull up

// hydralic
digital_out lockingPnuematics  = digital_out(Brain.ThreeWirePort.F);

// Helper to make playing sounds from the V5 in VEXcode easier and
// keeps the code cleaner by making it clear what is happening.
void playVexcodeSound(const char *soundName) {
  printf("VEXPlaySound:%s\n", soundName);
  wait(5, msec);
}

// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool DrivetrainNeedsToBeStopped_Controller1 = true;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    if(RemoteControlCodeEnabled) {
        Brain.Screen.print("remote loop");
      
      // calculate the drivetrain motor velocities from the controller joystick axies
      // left = Axis3 + Axis4
      // right = Axis3 - Axis4
      int drivetrainLeftSideSpeed = Controller1.Axis3.position() + Controller1.Axis4.position();
      int drivetrainRightSideSpeed = Controller1.Axis3.position() - Controller1.Axis4.position();
      
      // check if the values are inside of the deadband range
      if (abs(drivetrainLeftSideSpeed) < 5 && abs(drivetrainRightSideSpeed) < 5) {
        // check if the motors have already been stopped
        if (DrivetrainNeedsToBeStopped_Controller1) {
          // stop the drive motors
          LeftDriveSmart.stop();
          RightDriveSmart.stop();
          // tell the code that the motors have been stopped
          DrivetrainNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the motors next time the input is in the deadband range
        DrivetrainNeedsToBeStopped_Controller1 = true;
      }
      
      // only tell the left drive motor to spin if the values are not in the deadband range
      if (DrivetrainNeedsToBeStopped_Controller1) {
        LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);
        LeftDriveSmart.spin(forward);
      }
      // only tell the right drive motor to spin if the values are not in the deadband range
      if (DrivetrainNeedsToBeStopped_Controller1) {
        RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);
        RightDriveSmart.spin(forward);
      }
    }
    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);

#pragma endregion VEXcode Generated Robot Configuration