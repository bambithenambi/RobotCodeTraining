#include <cmath>
class Drive {
    public:
        Drive(){};
        static float handleDeadzone(float raw_input, float deadzone) {
            const float m = 1/(1-deadzone);
            const float b = deadzone/(1-deadzone);
            float input = std::fabs(raw_input);
            if (input>deadzone) return std::copysignf((m*input-b), raw_input);
            else return 0;
        };

};