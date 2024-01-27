#include <bitset>
#include <iostream>

int main() {
    std::bitset<4> a{ "0101" };

    std::cout << a[0];

    return 0;
}
