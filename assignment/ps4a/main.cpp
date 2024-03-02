// Copyright 2024 James Chen

#include <iostream>
#include "NBodyConstant.hpp"
#include "Universe.hpp"

/**
 * @brief Reads universe information from std::cin.
 */
void readUniverse(Universe& universe) {
    std::cin >> universe;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (int i = 0; i < universe.getNumPlanets(); ++i) {
        std::cin >> *universe.createCelestialBody();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

/**
 * @brief Starts the universe simulation.
 */
int main() {
    Universe universe;
    readUniverse(universe);

    const sf::VideoMode windowVideoMode{ WINDOW_WIDTH, WINDOW_HEIGHT };
    sf::RenderWindow window(windowVideoMode, std::string(WINDOW_TITLE));
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                break;
            }
        }

        if (window.isOpen()) {
            window.clear(sf::Color::White);
            window.draw(universe);
            window.display();
        }
    }

    return 0;
}
