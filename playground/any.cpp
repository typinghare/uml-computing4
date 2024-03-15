// ReSharper disable CppDeclaratorNeverUsed
#include <algorithm>
#include <iostream>
#include <vector>


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

    int* a = new int;
    delete a;
    delete a;
    std::cout << a;

    return 0;
}
