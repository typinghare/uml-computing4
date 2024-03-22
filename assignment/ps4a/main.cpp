// Copyright 2024 James Chen

#include <iostream>
#include "NBodyConstant.hpp"
#include "Universe.hpp"

/**
 * @brief Starts the universe simulation.
 */
int main() {
    NB::Universe universe;
    std::cin >> universe;
    universe.loadResources();

    std::cout << universe;

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
