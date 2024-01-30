// Copyright 2024 James Chan

#include <cerrno>
#include <iostream>
#include <string>
#include <utility>
#include <SFML/Graphics.hpp>
#include "PTree.hpp"

// Global constants
const char* WINDOW_TITLE = "Shape";
constexpr unsigned WINDOW_FPS = 60;
constexpr int EXIT_CODE = 1;

/**
 * @brief Parses the two arguments.
 * \param LStr The L string to parse.
 * \param NStr The N string to parse.
 * @return A pair containing parsed L and N.
 */
std::pair<double, int>
parseArguments(const std::string& LStr, const std::string& NStr);

/**
 * @brief
 * @param size The size of the argument list.
 * @param arguments The command line arguments. The first argument is L, and the
 * second one is N.
 * @note L: The length of one side of the base square (double).
 * @note N: The depth of the recursion (int).
 */
int main(const int size, const char* arguments[]) {
    if (size < 2) {
        std::cout << "Not enough arguments!" << std::endl;
        return EXIT_CODE;
    }

    // I love structured binding so much
    const auto [L, N] = parseArguments(arguments[1], arguments[2]);
    std::cout << L << std::endl;
    std::cout << N << std::endl;

    // Create a window
    sf::RenderWindow window(sf::VideoMode(1080, 720), WINDOW_TITLE);
    window.setFramerateLimit(WINDOW_FPS);
    window.clear(sf::Color::White);

    // Test
    const PTree::Line baseMainSide{ { 500., 500. }, { 700., 500. } };
    PTree::pTree(&window, baseMainSide, N);

    // Display the window
    window.display();

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    return 0;
}

std::pair<double, int>
parseArguments(const std::string& LStr, const std::string& NStr) {
    std::pair<double, int> pair;

    try {
        pair.first = std::stod(LStr);
    } catch (const std::exception& _) {
        std::cerr << "L should be a double, but " << LStr << " is given";
        exit(EXIT_CODE);
    }

    try {
        pair.second = std::stoi(NStr);
    } catch (const std::exception& _) {
        std::cerr << "N should be an integer, but " << NStr << " is given";
        exit(EXIT_CODE);
    }

    return pair;
}
