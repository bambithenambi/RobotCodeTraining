// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#include "Drive.h"


void Robot::RobotInit() {
  
}
void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {
  /*
  const float dz = 0.15;
  const float m = 1/(1-dz);
	const float b = dz/(1-dz);
  float rawXSpeed, rawZRotation;
  float xSpeed, zRotation;
  rawXSpeed = -(stick->GetRawAxis(trigger_id));
  rawZRotation = stick->GetRawAxis(steering_joystick_id);
  */


}

void Robot::DisabledInit() {}
void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
