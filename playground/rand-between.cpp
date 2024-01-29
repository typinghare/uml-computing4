#include <iostream>
#include <random>

/**
 * @brief Generates an integer number between two numbers.
 */
int randBetween(const int min, const int max) {
    static std::random_device SEED;
    static std::ranlux48 engine(SEED());
    std::uniform_int_distribution distribution(min, max);
    return distribution(engine);
}

int main() {
    std::cout << randBetween(0, 100);
    return 0;
}
