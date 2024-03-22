#include <bitset>
#include <iostream>

template <typename T>
void printIt(T a, T b);


int main() {
    printIt(1, 2);

    return 0;
}


template <typename T>
void printIt(T a, T b) {
    T sum = a + b;
    std::cout << a << " + " << b << " = " << sum << std::endl;
}
