// Copyright 2024 James Chan

#include <cerrno>
#include <iostream>
#include <string>
#include <utility>
#include <SFML/Graphics.hpp>
#include "PTree.hpp"

// Global constants
const char* WINDOW_TITLE = "Pythagoras Tree";
const char* ICON_FILENAME = "./assets/icon.png";
constexpr unsigned WINDOW_FPS = 60;
constexpr int EXIT_CODE = 1;
constexpr int DEFAULT_ANGLE = 45;

/**
 * @brief Parses the two or three arguments.
 * @param LStr The L string to parse.
 * @param NStr The N string to parse.
 * @param AStr (optional) The A string to parse.
 * @return A typle containing parsed L and N.
 */
std::tuple<float, int, float>
parseArguments(const std::string& LStr, const std::string& NStr, const std::string& AStr);

/**
 * @brief
 * @param size The size of the argument list.
 * @param arguments The command line arguments. The first argument is L, and the
 * second one is N. I added
 * @note L: The length of one side of the base square (double).
 * @note N: The depth of the recursion (int).
 * @note A: The angle alpha. (double).
 */
int main(const int size, const char* arguments[]) {
    // Checks the arguments
    if (size < 3 || size > 4) {
        std::cout << "Invalid number of arguments!" << std::endl;
        std::cout << "[argument list]" << std::endl
                  << "(1) L: The length of one side of the base square. (double)" << std::endl
                  << "(2) N: The depth of the recursion. (int)" << std::endl
                  << "(3) A: The angle alpha. (double)" << std::endl;

        return EXIT_CODE;
    }

    // Get L, N, and A
    const auto tuple{ parseArguments(arguments[1], arguments[2], size == 4 ? arguments[3] : "0") };
    const auto L{ std::get<0>(tuple) };
    const auto N{ std::get<1>(tuple) };
    const auto A{ std::get<2>(tuple) };

    // Create a window
    const unsigned windowWidth{ static_cast<unsigned>(L) * 4 + std::min(N, 9) * 80 };
    const unsigned windowHeight{ windowWidth * 10 / 16 };
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), WINDOW_TITLE);
    window.setFramerateLimit(WINDOW_FPS);
    window.clear(sf::Color::White);

    // Load the icon (extra feature)
    sf::Image icon;
    if (icon.loadFromFile(ICON_FILENAME)) {
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }

    // Determine the coordinates of top-left corner and right-left corner
    const float leftX{ (static_cast<float>(windowWidth) - L) / 2 - (A - 45) * 5 };
    const float rightX{ (static_cast<float>(windowWidth) + L) / 2 - (A - 45) * 5 };
    const float y{ static_cast<float>(windowHeight) * 0.7f };
    const sf::Vector2f baseSquareTlVertex{ leftX, y };
    const sf::Vector2f baseSquareTrVertex{ rightX, y };

    // Call pTree()
    const PTree::Square baseSquare{ baseSquareTlVertex, baseSquareTrVertex, L, 0 };
    pTree(&window, baseSquare, A, N);

    // Display the window
    window.display();

    // Game loop
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    return 0;
}

std::tuple<float, int, float>
parseArguments(const std::string& LStr, const std::string& NStr, const std::string& AStr) {
    float L, A;
    int N;

    try {
        L = static_cast<float>(std::stod(LStr));
    } catch (const std::exception& _) {
        std::cerr << "L should be a double, but " << LStr << " is given";
        exit(EXIT_CODE);
    }

    try {
        N = std::stoi(NStr);
    } catch (const std::exception& _) {
        std::cerr << "N should be an integer, but " << NStr << " is given";
        exit(EXIT_CODE);
    }

    try {
        A = static_cast<float>(std::stod(AStr));
        if (A == 0) {
            A = DEFAULT_ANGLE;
        }
    } catch (const std::exception& _) {
        std::cerr << "A should be a double, but " << LStr << " is given";
        exit(EXIT_CODE);
    }

    return std::make_tuple(L, N, A);
}
