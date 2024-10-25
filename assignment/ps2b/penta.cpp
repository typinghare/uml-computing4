#include "penta.hpp"

const auto COS_36_DEGREE = cosDeg(36);

void drawPentagon(sf::RenderTarget& target, const Pentagon& pentagon) {
    const auto [center, radius, rotation] = pentagon;
    sf::CircleShape pentagonShape{ radius, 5 };
    pentagonShape.setPosition(center);
    pentagonShape.setOrigin(radius, radius);
    pentagonShape.setRotation(rotation);

    // Color control
    const auto redComponent = static_cast<unsigned char>(
        (CANVAS_SIZE - center.x) / CANVAS_SIZE * 255);
    const auto greenComponent = static_cast<unsigned char>(
        (CANVAS_SIZE - center.y) / CANVAS_SIZE * 255);
    pentagonShape.setFillColor(sf::Color(redComponent, greenComponent, 255));

    target.draw(pentagonShape);
}

float getBlockDistance(const float distance, const int n) {
    static const float coefficient = 2 * COS_36_DEGREE + 1;
    return n == 1 ? distance : getBlockDistance(distance, n - 1) * coefficient;
}

void pentaflake(
    sf::RenderTarget& target, const int n, const Pentagon& pentagon) {
    if (n == 0) {
        return drawPentagon(target, pentagon);
    }

    // Draw the center block
    pentaflake(target, n - 1, pentagon);

    // Draw the adjacent five blocks
    const auto [center, radius, rotation] = pentagon;
    const float distance = getBlockDistance(2 * radius * COS_36_DEGREE, n);
    for (int i = 0; i < 5; ++i) {
        const auto deg = rotation + static_cast<float>(72 * i + 36 * n);
        const auto newCenter =
            center + distance * sf::Vector2f{ sinDeg(deg), -cosDeg(deg) };
        const auto newPentagon = Pentagon{ newCenter, radius, rotation + 180 };
        pentaflake(target, n - 1, newPentagon);
    }
}
