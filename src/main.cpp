#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#include "vex.h"

#include "init.hpp"

using namespace vex;

competition Comp;

namespace helper_functions {
  void lockingPnuematicHigh() {
    lockingPnuematics.set(true);
  }

  void lockingPnuematicLow() {
    lockingPnuematics.set(false);
  }

  void shooterEngage() {
    shooter.spin(reverse);
  }

  void shooterDisengage() {
    shooter.stop();
  }

  void pullSet0() {
    // Brain.Screen.print("yes?");
    pullup.spinToPosition(0, degrees);
  }

  void pullSet720() { 
    // Brain.Screen.print("yes?");
    pullup.spinToPosition(720, degrees);
  }

  void pullSet1440() { 
    // Brain.Screen.print("yes?");

    pullup.spinToPosition(1440, degrees);
  }
}

void controllerSetup() {
  Brain.Screen.print("Initializing controls...");

  printf("setposition to 0 deg");
  pullup.setPosition(0, degrees);

  // pnuematics
  Controller1.ButtonA.pressed(helper_functions::lockingPnuematicHigh);
  Controller1.ButtonLeft.pressed(helper_functions::lockingPnuematicLow);

  // Pull up setup
  Controller1.ButtonX.pressed(helper_functions::pullSet0);
  Controller1.ButtonY.pressed(helper_functions::pullSet720);
  Controller1.ButtonB.pressed(helper_functions::pullSet1440);

  // Shooter engage/disengage
  Controller1.ButtonR2.pressed(helper_functions::shooterEngage);
  Controller1.ButtonR2.released(helper_functions::shooterDisengage);

  // Brain.Screen.clearScreen();
}

void pre_auton() {

}

void autonomous_() {
  Drivetrain.driveFor(52, inches);
  Drivetrain.driveFor(-52, inches);
  Drivetrain.turnFor(-27.5 /* assuming that left is negative. */, degrees);
  Drivetrain.driveFor(-48, inches);
  Drivetrain.driveFor(48, inches);
}

void usercontrol() {
  controllerSetup();
  // RemoteControlCodeEnabled = true;

  shooter.setVelocity(100, percent);
  pullup.setVelocity(100, percent);
  Drivetrain.setDriveVelocity(60, percent);

  while (true) {
    wait(20, msec);
  }
}

int main() {
  Comp.autonomous(autonomous_);
  Comp.drivercontrol(usercontrol);

  pre_auton();

  while (true) {
    wait(100, msec);
  }
}