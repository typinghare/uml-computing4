// Copyright 2024 James Chen

#include <iostream>
#include <SFML/Graphics.hpp>
#include "NBodyConstant.hpp"
#include "Universe.hpp"

/**
 * @brief Starts the universe simulation.
 * @param argc The number of arguments.
 * @param argv The arguments vector. This program requires two arguments:
 * 1. T (double): Total time.
 * 2. Delta t (double): time quantum measured in seconds.
 */
int main(const int argc, const char* argv[]) {
    if (argc != 3) {
        std::cerr << "Not enough arguments!";
        return 1;
    }

    const double totalTime = std::stod(argv[1]);
    const double deltaTime = std::stod(argv[2]);
    double elapsedTime = 0.0;

    // Create a universe and load data and resources
    NB::Universe universe;
    std::cin >> universe;
    universe.loadResources();

    // Create a window
    const sf::VideoMode windowVideoMode{ NB::WINDOW_WIDTH, NB::WINDOW_HEIGHT };
    sf::RenderWindow window(windowVideoMode, std::string(NB::WINDOW_TITLE));
    window.setFramerateLimit(NB::WINDOW_FPS);

    bool hasPrintedFinalState = false;
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                break;
            }
        }

        if (window.isOpen()) {
            // The simulation stops when T >= t
            if (elapsedTime < totalTime) {
                universe.step(deltaTime);
            } else if (!hasPrintedFinalState) {
                std::cout << universe;
                hasPrintedFinalState = true;
            }

            window.clear(sf::Color::White);
            window.draw(universe);
            window.display();
        }

        elapsedTime += deltaTime;
    }

    return 0;
}
