// Copyright 2024 James Chen

#include <iostream>
#include <fstream>
#include "Sokoban.hpp"

/**
 * @brief Starts a Sokoban game.
 * @param size The size of the argument list.
 * @param arguments The command line arguments. This game requires one argument, which is the
 * filename of the level file to load.
 */
int main(const int size, const char* arguments[]) {
    // Check arguments
    if (size < 2) {
        std::cout << "Too few arguments! Require the filename of the level file." << std::endl;
        return 1;
    }

    const std::string levelFilename = arguments[1];
    SB::Sokoban sokoban;

    std::ifstream ifstream{ levelFilename };
    if (!ifstream.is_open()) {
        throw std::invalid_argument("File not found: " + levelFilename);
    }
    ifstream >> sokoban;

    // Create a window
    const auto windowWidth = sokoban.width() * SB::TILE_WIDTH;
    const auto windowHeight = sokoban.height() * SB::TILE_HEIGHT;
    const auto videoMode = sf::VideoMode(windowWidth, windowHeight);
    sf::RenderWindow window(videoMode, SB::GAME_NAME);
    window.setFramerateLimit(60);

    // Game loop
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                break;
            }
        }

        sokoban.update(clock.restart().asMilliseconds());

        if (window.isOpen()) {
            window.clear();
            window.draw(sokoban);
            window.display();
        }
    }
}
