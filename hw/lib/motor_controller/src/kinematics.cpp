
#include "motor_controller/kinematics.hpp"

namespace IK{
    /// @brief Inverse kinematics calculation
    /// @param x The x coordinate
    /// @param y The y coordinate
    /// @return The calculated joint angles in 0.01 degrees
    Angles inverse_kinematics(double x, double y) {
        Angles angles;
        const double R = std::hypot(x, y);
        const double l1 = acos(std::fma(L2,L2,R*R - L1*L1) / (2 * L2 * R)); //radian
        const double l2 = acos(std::fma(L1,L1,R*R - L2*L2) / (2 * L1 * R)); //radian

        const double theta1_rad = l2 + asin(y/R); // radians
        const double theta2_rad = (-(-1.5707963268 + l1 + acos(y/R)) - theta1_rad); // radians, constant is 90 degrees

        //Now convert both to 0.01 degrees
        //Note .theta1/2 are in 'int' not 'double' beware of conversion errors
        angles.theta1 = (180/M_PI)*100*theta1_rad;
        angles.theta2 = -(180/M_PI)*100*theta2_rad;

        #ifdef DEBUG
        std::cout << "R: " << R << std::endl;
        std::cout << "r: " << (180/M_PI)*r << std::endl;
        std::cout << "l1: " << (180/M_PI)*l1 << std::endl;
        std::cout << "l2: " << (180/M_PI)*l2 << std::endl;
        #endif 
        Serial.print("Theta1: ");
        Serial.print(angles.theta1);
        Serial.print(", Theta2: ");
        Serial.println(angles.theta2); 
        return angles;
    }
}

    // int test (){
    //     double x, y;
    //     Serial.print("Enter x and y coordinates: ");
    //     std::cin >> x >> y;
    //     IK::inverse_kinematics(x, y);
    //     return 0;
    // }

// }
// int main(){
//     IK::test();
//     return 0;   
// }



