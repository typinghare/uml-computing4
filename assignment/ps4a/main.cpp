// Copyright 2024 James Chen

#include <iostream>
#include "NBodyConstant.hpp"
#include "Universe.hpp"

/**
 * @brief Reads universe information from std::cin.
 */
void readUniverse(NB::Universe& universe) {
    std::cin >> universe;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (int i = 0; i < universe.numPlanets(); ++i) {
        std::cin >> *universe.createCelestialBody();
    }
}

/**
 * @brief Starts the universe simulation.
 */
int main() {
    NB::Universe universe{ "assets/data/planets.txt" };

    // readUniverse(universe);

    for (int i = 0; i < universe.numPlanets(); ++i) {
        const auto celestialBody = universe[i];
        std::cout << celestialBody.position().x << " ";
        std::cout << celestialBody.position().y << " ";
        std::cout << celestialBody.velocity().x << " ";
        std::cout << celestialBody.velocity().y << " ";
        std::cout << celestialBody.mass() << std::endl;
    }

    const sf::VideoMode windowVideoMode{ NB::WINDOW_WIDTH, NB::WINDOW_HEIGHT };
    sf::RenderWindow window(windowVideoMode, std::string(NB::WINDOW_TITLE));
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
