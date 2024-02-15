#include <iostream>

// 4 bytes
class Base {
 public:
    int iMem = 0;
    char charArray[];

    Base() : charArray("What") {}

    void foo() {
    }
};

// class ABase : virtual public Base {};
//
// class BBase : virtual public Base {
//     int iMem = 0;
// };
//
// class CBase : public ABase, public BBase {
//     int iMem = 0;
// };

int main() {
    std::cout << sizeof(Base) << std::endl;
    // std::cout << sizeof(ABase) << std::endl;
    // std::cout << sizeof(BBase) << std::endl;
    // std::cout << sizeof(CBase) << std::endl;

    const Base base;
    std::cout << base.charArray << std::endl;
}
