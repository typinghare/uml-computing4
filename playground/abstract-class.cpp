#include <iostream>
#include <memory>
#include <vector>

// Abstract class
class Transportation {
 public:
    Transportation() = default;
    virtual ~Transportation() = default;

    virtual void accelerate(float dv) = 0;
};

class Car final : public Transportation {
 public:
    void accelerate(float dv) override { std::cout << "Car accelerates!" << std::endl; };
};

class Sailboat final : public Transportation {
 public:
    void accelerate(float dv) override { std::cout << "Sailboat accelerates!" << std::endl; };
};

int main() {
    std::vector<std::unique_ptr<Transportation>> transportationVector;
    transportationVector.push_back(std::make_unique<Car>());
    transportationVector.push_back(std::make_unique<Sailboat>());
    transportationVector.at(0)->accelerate(0);
    transportationVector.at(1)->accelerate(1);

    std::vector<Transportation*> transportations;
    transportations.push_back(new Car());
    transportations.push_back(new Sailboat());
    transportationVector.at(0)->accelerate(0);
    transportationVector.at(1)->accelerate(1);

    for (const auto& transportation: transportations) {
        delete transportation;
    }
}
