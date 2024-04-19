#include <iostream>

class BaseClass {
 public:
    int dimA = 10;
    double dimB = 2.5;
};

class RealClass1 : public virtual BaseClass {
 public:
    double dimA = 7.5;
    int dimB = 15;
};

class RealClass2 : public virtual BaseClass {
 public:
    bool dimC = true;
};

class RealClass3 : public RealClass1, public RealClass2 {
 public:
    RealClass3() {
        std::cout << dimA << std::endl;
        std::cout << dimB << std::endl;
        std::cout << dimC << std::endl;  // no ambiguity
    }
};

int main() {
    const RealClass3 real_class3;
    const RealClass2 real_class2;

    std::cout << real_class2.dimA << std::endl;
    std::cout << real_class2.dimB << std::endl;

    return 0;
}
