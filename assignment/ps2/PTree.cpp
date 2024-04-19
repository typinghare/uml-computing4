// Copyright 2024 James Chan

#include "PTree.hpp"
#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>

namespace PTree {

void pTree(sf::RenderWindow* window, const Square& square, const float& deltaAlpha, int N) {
    // Fill colors pool
    static constexpr unsigned NUM_FILL_COLOR = 7;
    static const std::array<sf::Color, NUM_FILL_COLOR> FILL_COLORS{
        sf::Color(255, 0, 0), sf::Color(255, 127, 0), sf::Color(255, 255, 0), sf::Color(0, 255, 0),
        sf::Color(0, 0, 255), sf::Color(75, 0, 130),  sf::Color(148, 0, 211),
    };

    // Terminate the recursion when N <= 0
    if (N <= 0) {
        return;
    }

    // Draw the square
    drawSquare(window, square, FILL_COLORS[N % NUM_FILL_COLOR]);

    // Recursion
    if (N > 1) {
        --N;
        const auto nextSquares = getNextSquares(square, deltaAlpha);
        pTree(window, nextSquares[0], deltaAlpha, N);
        pTree(window, nextSquares[1], deltaAlpha, N);
    }
}

void drawSquare(sf::RenderWindow* window, const Square& square, const sf::Color& color) {
    // Create a square shape
    sf::RectangleShape squareShape;
    squareShape.setPosition(square.tlVertex.x, square.tlVertex.y);
    squareShape.setSize(sf::Vector2f(square.sideLength, square.sideLength));
    squareShape.setRotation(-square.alpha);
    squareShape.setFillColor(color);
    squareShape.setOutlineThickness(1);
    squareShape.setOutlineColor(sf::Color::Black);

    // Draw the square shape onto the screen
    window->draw(squareShape);
}

std::array<Square, 2> getNextSquares(const Square& square, const float& deltaAlpha) {
    // Beta in degrees
    const auto beta = square.alpha + deltaAlpha;
    const auto sinBeta = sinDeg(beta);
    const auto cosBeta = cosDeg(beta);

    // Find the next two sides
    const auto leftSideLength = square.sideLength * cosDeg(deltaAlpha);
    const auto rightSideLength = square.sideLength * sinDeg(deltaAlpha);

    // Tranformers
    const sf::Vector2f tlLeftVec{ -sinBeta, -cosBeta };
    const sf::Vector2f trVec{ cosBeta - sinBeta, -sinBeta - cosBeta };
    const sf::Vector2f trRightVec{ +cosBeta, -sinBeta };

    // Vertices
    const sf::Vector2f leftTlVertex = square.tlVertex + leftSideLength * tlLeftVec;
    const sf::Vector2f leftTrVertex = square.tlVertex + leftSideLength * trVec;
    const sf::Vector2f rightTlVertex = square.trVertex + rightSideLength * trVec;
    const sf::Vector2f rightTrVertex = square.trVertex + rightSideLength * trRightVec;

    // Create the next two squares
    const Square leftSquare{ leftTlVertex, leftTrVertex, leftSideLength, beta };
    const Square rightSquare{ rightTlVertex, rightTrVertex, rightSideLength, beta - 90 };

    return { leftSquare, rightSquare };
}

inline float degreeToRadian(const float& degree) {
    static constexpr float C = M_PI / 180;
    return C * degree;
}

inline float sinDeg(const float& degree) { return std::sin(degreeToRadian(degree)); }

inline float cosDeg(const float& degree) { return std::cos(degreeToRadian(degree)); }

}  // namespace PTree
