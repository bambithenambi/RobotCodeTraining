#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/Joystick.h>
#include <rev/CANSparkMax.h>

class Drive
{
private:
    frc::Joystick *controller;
    rev::CANSparkMax *leftMotor;
    rev::CANSparkMax *rightMotor;
    int throttleID, steerID;
    int throttleDZ, steerDZ;
    bool invertThrottle, invertSteering;
public:
    Drive(int trigger_id, int steering_joystick_id, int joystick_id, int throttle_dz, int steering_dz, bool invert_throttle, bool invert_steering);
    void tankDrive();
    void arcadeDrive();
    void curvatureDrive();

};

Drive::Drive(int throttle_axis_id, int steering_axis_id, int joystick_id, int throttle_dz, int steering_dz, bool invert_throttle, bool invert_steering)
{
        controller = new frc::Joystick(0);
        leftMotor = new rev::CANSparkMax(3, rev::CANSparkMax::MotorType::kBrushless);
        rightMotor = new rev::CANSparkMax(3, rev::CANSparkMax::MotorType::kBrushless);
}

void Drive::curvatureDrive()
{
    float rawXSpeed, rawZRotation, absXSpeed, absZRotation, xSpeed, zRotation;
    //get raw controller values
    rawXSpeed = -(controller->GetRawAxis(throttleID));
    rawZRotation = controller->GetRawAxis(steerID);
    
    //check if inverted
    rawXSpeed *= (invertThrottle) ? -1 : 1;
    rawZRotation *= (invertSteering) ? -1 : 1;
    
    //throttle deadzone adjustment
    const float m_t = 1/(1-throttleDZ);
	const float b_t = throttleDZ/(1-throttleDZ);
    absXSpeed = fabs(rawXSpeed);
	if (absXSpeed>throttleDZ) xSpeed = std::copysignf((m_t*absXSpeed-b_t), rawXSpeed);
	else xSpeed=0;
    
    //steering deadzone adjustment
    const float m_s = 1/(1-steerDZ);
	const float b_s = steerDZ/(1-steerDZ);
    absZRotation = fabs(rawZRotation);
	if (absZRotation>steerDZ) zRotation = std::copysignf((m_s*absZRotation-b_s), rawZRotation);
	else zRotation=0;

    
}


