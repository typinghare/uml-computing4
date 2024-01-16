#include <iostream>

int main() {
    constexpr int num = 1;
    const int* p = &num;
    std::cout << *p;

    return 0;
}
