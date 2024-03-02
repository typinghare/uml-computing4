// Copyright 2024 James Chen

#include <iostream>
#include "Universe.hpp"

/**
 * @brief Reads universe information from std::cin.
 */
void readUniverse() {
    const auto universe{ std::make_shared<Universe>() };
    std::cin >> *universe;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (int i = 0; i < universe->getNumPlanets(); ++i) {
        std::cin >> *universe->createCelestialBody();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

/**
 * @brief Starts the universe simulation.
 */
int main() {
    readUniverse();

    return 0;
}
