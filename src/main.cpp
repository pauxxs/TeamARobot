#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#include "vex.h"

#include "init.hpp"

using namespace vex;

competition Comp;

void controllerSetup() {
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
}

void pre_auton() {
  shooter.setPosition(0, degrees);
  pullup.setVelocity(100, percent);
}

void autonomous() {
  Drivetrain.driveFor(52, inches);
  Drivetrain.driveFor(-52, inches);
  Drivetrain.turnFor(27.5 /* assuming that left is negative. */, degrees);
  Drivetrain.driveFor(-48, inches);
  Drivetrain.driveFor(48, inches);
}

void usercontrol() {
  controllerSetup();

  while (true) {
    wait(20, msec);
  }
}

int main() {
  Comp.autonomous(autonomous);
  Comp.drivercontrol(usercontrol);

  pre_auton();

  while (true) {
    wait(100, msec);
  }
}
