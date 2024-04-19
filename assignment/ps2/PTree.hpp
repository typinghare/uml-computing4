// Copyright 2024 James Chan

#ifndef PTREE_H
#define PTREE_H

#include <SFML/Graphics.hpp>

namespace PTree {

/**
 * @brief A square can be unambiguously determined by one vertext, the length of
 * four sides, and the angle between the significant side and the horizontal
 * axis (X axis). For the sake of symmetry, top-left and top-right are stored.
 */
struct Square {
    /**
     * @brief The top-left vertex.
     */
    sf::Vector2f tlVertex;

    /**
     * @brief The top-right vertex.
     */
    sf::Vector2f trVertex;

    /**
     * @brief The length of the side.
     */
    float sideLength{ 0 };

    /**
     * @brief The angle in degrees between the significant side and the
     * horizontal axis.
     */
    float alpha{ 0 };
};

/**
 * @brief Draws a Pythagoras tree recursively.
 * @param window The window to draw onto.
 * @param square The initial square to draw.
 * @param deltaAlpha The difference in alpha.
 * @param N A recursive variable. The function stops recurse when N equals to 1.
 * Every recursion takes 1 from N.
 */
void pTree(sf::RenderWindow* window, const Square& square, const float& deltaAlpha, int N);

/**
 * @brief Draws a square.
 * @param window The window to draw onto.
 * @param square THe square to draw.
 * @param color The fill color of the square.
 */
void drawSquare(sf::RenderWindow* window, const Square& square, const sf::Color& color);

/**
 * @brief Returns the next two squares.
 * @param square The current square.
 * @param deltaAlpha The difference in alpha.
 */
std::array<Square, 2> getNextSquares(const Square& square, const float& deltaAlpha);

/**
 * @brief Converts a degree into radian.
 * @param degree The degree to convert.
 */
inline float degreeToRadian(const float& degree);

/**
 * @brief Finds the sine value of a degree.
 */
inline float sinDeg(const float& degree);

/**
 * @brief Finds the consine value of a degree.
 */
inline float cosDeg(const float& degree);

}  // namespace PTree

#endif
