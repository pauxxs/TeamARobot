# Thomass robot

The robot for team a comp 1/11/24


auto for back
```cpp
int main() {
  Drivetrain.setDriveVelocity(150, percent);
  Drivetrain.driveFor(43, inches);
  Drivetrain.setDriveVelocity(100, percent);
  Drivetrain.driveFor(-20, inches);
  wait(.5, seconds);
  Drivetrain.turnFor(right, -60, degrees);
  Drivetrain.driveFor(-10, inches);
  wait(.5, seconds);
  Drivetrain.driveFor(13, inches);
  wait(.5, seconds);
  Drivetrain.turnFor(-50, degrees);
  Drivetrain.driveFor(27, inches);
  Drivetrain.turnFor(10, degrees);
  Drivetrain.driveFor(forward, 40, inches);
}
}
```