
#include <iostream>
class Base {
    int iMem = 0;
};

class ABase : virtual public Base {
    int iMem = 0;
};

class BBase : virtual public Base {
    int iMem = 0;
};

class CBase : public ABase, public BBase {
    int iMem = 0;
};

int main() {
    std::cout << sizeof(Base) << std::endl;
    std::cout << sizeof(ABase) << std::endl;
    std::cout << sizeof(BBase) << std::endl;
    std::cout << sizeof(CBase) << std::endl;
}
