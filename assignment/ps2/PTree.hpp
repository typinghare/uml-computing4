// Copyright 2024 James Chan

#ifndef PTREE_H
#define PTREE_H

#include <SFML/Graphics.hpp>

namespace PTree {

/**
 * @brief A line consiting of two coordinates, which are represented by vectors.
 */
struct Line {
    sf::Vector2f A;
    sf::Vector2f B;
};

/**
 * @brief Draws a Pythagoras tree recursively.
 * @param window The window to draw onto.
 * @param mainSide The main side of the square to draw.
 * @param N A recursive variable. The function stops recurse when N equals to 1.
 * Every recursion takes 1 from N.
 */
void pTree(sf::RenderWindow* window, const Line& mainSide, int N);

/**
 * @brief Draws a square based on the main side.
 * @param window The window to draw onto.
 * @param mainSide The main side of the square to draw.
 * @param color The fill color of the square.
 * @return The next two main sides.
 */
void drawSquare(
    sf::RenderWindow* window, const Line& mainSide, const sf::Color& color);

/**
 * @brief Get the next two main sides.
 * @param mainSide The current main side.
 */
std::array<Line, 2> getNextMainSides(const Line& mainSide);

}  // namespace PTree

#endif
