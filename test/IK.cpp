#include <iostream>
#include <cmath>
const double L1 = 17.5; //mm
const double L2 = 15.0; //mm


struct Angles{
    double theta1;
    double theta2;
};



Angles inverse_kinematics(double x, double y) {
    Angles angles;
    const double R = sqrt(x*x + y*y); //cm
    std::cout << "R: " << R << std::endl;
    const double r = acos((L1*L1 + L2*L2 - R*R) / (2 * L1 * L2)); //degrees
    std::cout << "r: " << (180/M_PI)*r << std::endl;
    const double l1 = acos((L2*L2 + R*R - L1*L1) / (2 * L2 * R)); //degrees
    std::cout << "l1: " << (180/M_PI)*l1 << std::endl;
    const double l2 = acos((L1*L1 + R*R - L2*L2) / (2 * L1 * R)); //degrees
    std::cout << "l2: " << (180/M_PI)*l2 << std::endl;
    angles.theta1 = (l2+asin(y/R));//degrees
    angles.theta2 = -(-1.5708+l1+acos(y/R));//degrees
    std::cout << "Theta1: " << (180/M_PI)*angles.theta1 << ", Theta2: " << (180/M_PI)*angles.theta2 << std::endl;
    return angles;
}
int main (){
    double x, y;
    std::cout << "Enter x and y coordinates: ";
    std::cin >> x >> y;
    Angles angles = inverse_kinematics(x, y);
    return 0;
}
