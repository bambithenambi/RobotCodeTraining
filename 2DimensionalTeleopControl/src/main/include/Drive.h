#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/Joystick.h>
#include <rev/CANSparkMax.h>

class Drive
{
private:
    frc::Joystick *controller;
    rev::CANSparkMax *leftMotor;
    rev::CANSparkMax *rightMotor;
    int throttleID, steerID, quickTurnButtonID;
    float throttleDZ, steerDZ;
    int l, r; //outputs
    bool invertThrottle, invertSteering;
    const static float turnSensitivity = 1.0;
    float mQuickStopAccumulator;
public:
    Drive(int controller_id, int throttle_axis_id, int steering_axis_id, int quick_turn_button_id, float throttle_dz, float steering_dz, bool invert_throttle, bool invert_steering);
    float handleDeadzone(float input, float deadzone);
    inline float invert(float input, bool invert);
    inline float limit(float value, float limit);
    void curvatureDrive();

};

Drive::Drive(int controller_id, int throttle_axis_id, int steering_axis_id, int quick_turn_button_id, float throttle_dz, float steering_dz, bool invert_throttle, bool invert_steering)
{
        controller = new frc::Joystick(controller_id);
        leftMotor = new rev::CANSparkMax(1, rev::CANSparkMax::MotorType::kBrushless);
        rightMotor = new rev::CANSparkMax(3, rev::CANSparkMax::MotorType::kBrushless);
        throttleID = throttle_axis_id;
        steerID = steering_axis_id;
        quickTurnButtonID = quick_turn_button_id;
        throttleDZ = throttle_dz;
        steerDZ = steering_dz;
        invertThrottle = invert_throttle;
        invertSteering = invert_steering;
}
float Drive::handleDeadzone(float raw_input, float deadzone) {
    const float m = 1/(1-deadzone);
	const float b = deadzone/(1-deadzone);
    float input = fabs(raw_input);
	if (input>deadzone) return std::copysignf((m*input-b), raw_input);
	else return 0;
}
inline float Drive::invert(float input, bool invert) {
    return input *= (invert) ? -1 : 1;
}
inline float Drive::limit(float value, float limit) {
    return (fabs(value) < limit) ? value : limit * (value < 0 ? -1 : 1);
}
void Drive::curvatureDrive()
{
    float rawXSpeed, rawZRotation, xSpeed, zRotation;
    rawXSpeed = -(controller->GetRawAxis(throttleID));
    rawZRotation = controller->GetRawAxis(steerID);
    
    rawXSpeed = invert(rawXSpeed, invertThrottle);
    rawZRotation = invert(rawZRotation, invertSteering);
    xSpeed = handleDeadzone(rawXSpeed, throttleDZ);
    zRotation = handleDeadzone(rawZRotation, steerDZ);

    float overPower;
    float angularPower;

    //check for quickTurn and apply speeds
    if (controller->GetRawButton(quickTurnButtonID)) {
        if (fabs(xSpeed) < 0.2) {
            float alpha = 0.1;
            mQuickStopAccumulator = (1 - alpha) * mQuickStopAccumulator + alpha * limit(zRotation, 1.0) * 2;
        }
        overPower = 1.0;
        angularPower = zRotation;
    }
    else {
        overPower = 0.0;
        angularPower = fabs(xSpeed) * zRotation * turnSensitivity - mQuickStopAccumulator;
        if (mQuickStopAccumulator > 1) {
            mQuickStopAccumulator -= 1;
        } else if (mQuickStopAccumulator < -1) {
            mQuickStopAccumulator += 1;
        } else {
            mQuickStopAccumulator = 0.0;
        }
    }
    float rightPwm = xSpeed - angularPower;
    float leftPwm = xSpeed + angularPower;
    if (leftPwm > 1.0) {
        rightPwm -= overPower * (leftPwm - 1.0);
        leftPwm = 1.0;
    } else if (rightPwm > 1.0) {
        leftPwm -= overPower * (rightPwm - 1.0);
        rightPwm = 1.0;
    } else if (leftPwm < -1.0) {
        rightPwm += overPower * (-1.0 - leftPwm);
        leftPwm = -1.0;
    } else if (rightPwm < -1.0) {
        leftPwm += overPower * (-1.0 - rightPwm);
        rightPwm = -1.0;
    }
    //set motors
    leftMotor->Set(-leftPwm);
    rightMotor->Set(rightPwm);
}


