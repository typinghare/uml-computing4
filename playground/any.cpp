#include <algorithm>
#include <iostream>
#include <vector>


int main() {
    int a = 5, b = 10;
    auto lambda = [=, &b]() mutable {
        a += 5;
        b += 5;
        return a + b;
    };

    std::cout << lambda() << std::endl;
    std::cout << "a: " << a << ", b: " << b << std::endl;

    return 0;
}
