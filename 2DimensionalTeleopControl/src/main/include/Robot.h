// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include "Drive.h"
#include <frc/TimedRobot.h>
#define throttle_axis_id 3
#define steering_axis_id 0
#define quick_turn_button_id 1


class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;

  void AutonomousInit() override;
  void AutonomousPeriodic() override;

  void TeleopInit() override;
  void TeleopPeriodic() override;

  void DisabledInit() override;
  void DisabledPeriodic() override;

  void TestInit() override;
  void TestPeriodic() override;

  Drive drive = Drive(0, throttle_axis_id, steering_axis_id, quick_turn_button_id, 0.05, 0.1, true, false);
};
