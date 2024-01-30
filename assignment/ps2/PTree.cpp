// Copyright 2024 James Chan

#include "PTree.hpp"
#include <cmath>
#include <iostream>

#include <SFML/Graphics.hpp>

namespace PTree {

// NOLINTNEXTLINE
void pTree(sf::RenderWindow* window, const Line& mainSide, int N) {
    // Fill color pool
    static constexpr unsigned NUM_FILL_COLOR = 6;
    static const std::array<sf::Color, NUM_FILL_COLOR> FILL_COLORS{
        sf::Color::Blue,   sf::Color::Black,   sf::Color::Green,
        sf::Color::Yellow, sf::Color::Magenta, sf::Color::Cyan
    };

    // Terminate the recursion when N <= 0
    if (N <= 0) {
        return;
    }

    // Draw the square
    drawSquare(window, mainSide, FILL_COLORS[N % NUM_FILL_COLOR]);

    // Recursion
    const auto nextMainSides = getNextMainSides(mainSide);
    pTree(window, nextMainSides[0], --N);
    pTree(window, nextMainSides[1], --N);
}

void drawSquare(
    sf::RenderWindow* window, const Line& mainSide, const sf::Color& color) {
    // Find the vector between two vertices
    const sf::Vector2f vector = mainSide.A - mainSide.B;

    // Calculate the length of the side
    const float sideLength =
        std::sqrt(vector.x * vector.x + vector.y * vector.y);

    // Create a square
    sf::RectangleShape square;
    square.setSize(sf::Vector2f(sideLength, sideLength));
    square.setFillColor(color);
    square.setPosition(mainSide.A.x, mainSide.B.y - sideLength);

    window->draw(square);
}

std::array<Line, 2> getNextMainSides(const Line& mainSide) {
    return { mainSide, mainSide };
}

}  // namespace PTree
