#ifndef PENTA_HPP
#define PENTA_HPP

#include <cmath>
#include <SFML/Graphics.hpp>

constexpr float RADIAN_PER_DEGREE = M_PI / 180.0;
constexpr int CANVAS_SIZE = 1080;

/**
 * @brief Represents a regular pentagon shape.
 *
 * Members:
 * - center: The 2D coordinates of the pentagon's center point.
 * - radius: The distance from the center to any vertex of the pentagon.
 * - rotation: The rotation angle (in degrees) of the pentagon, measured
 * clockwise from the positive x-axis.
 */
struct Pentagon {
    const sf::Vector2f center;
    const float radius;
    const float rotation;
};

/**
 * @brief Represents a line segment in 2D space.
 *
 * Members:
 * - a: The coordinates of the first endpoint of the segment.
 * - b: The coordinates of the second endpoint of the segment.
 */
struct Segment {
    const sf::Vector2f a;
    const sf::Vector2f b;
};

/**
 * @brief Draws a regular pentagon onto a render target.
 *
 * @param target The render target where the pentagon will be drawn.
 * @param pentagon The pentagon to draw.
 */
void drawPentagon(sf::RenderTarget& target, const Pentagon& pentagon);

void pentaflake(sf::RenderTarget& target, int n, const Pentagon& pentagon);

inline float cosDeg(const float degree) {
    return std::cos(degree * RADIAN_PER_DEGREE);
}

inline float sinDeg(const float degree) {
    return std::sin(degree * RADIAN_PER_DEGREE);
}

#endif
