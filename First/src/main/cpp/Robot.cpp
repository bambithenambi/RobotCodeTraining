// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

void Robot::RobotInit() {
	myStick = new frc::Joystick(0);
	myRightMotor = new rev::CANSparkMax(3, rev::CANSparkMaxLowLevel::MotorType::kBrushless);
	myLeftMotor = new rev::CANSparkMax(1, rev::CANSparkMaxLowLevel::MotorType::kBrushless);
	int dz = 0.1;
  	double m = 1/(1-dz);
	double b = dz/(1-dz);
}
void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {
	
}
void Robot::TeleopPeriodic() {
	myLeftMotor->Set(myStick->GetRawAxis(1));
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

// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.



/**
 * This sample program shows how to control a motor using a joystick. In the
 * operator control part of the program, the joystick is read and the value is
 * written to the motor.
 *
 * Joystick analog values range from -1 to 1 and speed controller inputs as
 * range from -1 to 1 making it easy to work together.
 */
