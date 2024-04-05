// ReSharper disable CppDeclaratorNeverUsed
#include <algorithm>
#include <iostream>
#include <vector>

long decode2(long x, long y, const long z) {
    y -= z;
    x *= y;

    std::cout << ((y << 63) >> 63) << std::endl;
    std::cout << x << std::endl;
    return 0;
}


int main() {
    // int a1 = 1;
    // // int& b1 = 1; // does not work
    // int&& c1 = 1;
    //
    // const int a2 = 1;
    // const int& b2 = 1;  // it works
    // const int&& c2 = 1;
    //
    // int& b3 = a1;
    // // int&& c3 = a1;
    //
    // // const int&& b4 = a1;    // does not work, a1 is lvalue
    // const int&& c4 = a1 + 1;   // it works, a1 + 1 is a rvalue
    // // const int&& c5 = c2;    // does not work, c2 is lvalue

    // int* a = new int;
    // delete a;
    // delete a;
    // std::cout << a;

    // constexpr double x = 4.8420e+11;
    // constexpr double y = -1.5420e+11;
    //
    // constexpr double G = 6.67e-11;
    // constexpr double SunMass = 1.9890e+30;
    // const double Radius = std::sqrt(std::pow(x, 2) + std::pow(y, 2));
    //
    // const double vy = 1.2397e+04;
    //
    // const double velocity = std::sqrt(G * SunMass / Radius);
    // std::cout << velocity << std::endl;
    // std::cout << "vx: " << std::sqrt(std::pow(velocity, 2) - std::pow(vy, 2)) << std::endl;

    // constexpr auto Flag = not true;
    // std::cout << Flag << std::endl;

    std::cout << decode2(3, 7, 0) << std::endl;

    return 0;
}
