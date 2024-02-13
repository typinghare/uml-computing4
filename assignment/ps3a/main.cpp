// Copyright 2024 James Chen
#include <fstream>
#include <iostream>

#include "Sokoban.hpp"

int main(const int size, const char* arguments[]) {
    if (size < 2) {
        std::cout << "Too few arguments!" << std::endl;
        return 1;
    }

    std::string level = arguments[1];
    SB::Sokoban sokoban;
    loadLevel(sokoban, level);

    // Create a window
    const auto windowWidth = sokoban.width() * SB::TILE_WIDTH;
    const auto windowHeight = sokoban.height() * SB::TILE_HEIGHT;
    const auto videoMode = sf::VideoMode(windowWidth, windowHeight);
    sf::RenderWindow window(videoMode, SB::GAME_NAME);
    window.setFramerateLimit(60);

    // Game loop
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                break;
            }
        }

        if (window.isOpen()) {
            window.clear();
            window.draw(sokoban);
            window.display();
        }
    }
}
