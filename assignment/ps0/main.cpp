// Copyright 2024 James Chen
#include <cmath>
#include <filesystem>
#include <iostream>

#include <SFML/Graphics.hpp>

// Global constants
constexpr int WINDOW_WIDTH = 1080;
constexpr int WINDOW_HEIGHT = 720;
constexpr int WINDOW_FPS = 60;
constexpr char WINDOW_TITLE[] = "First Experience with SFML";
constexpr char SPRITE_FILEPATH[] = "sprite.png";

class Direction {
    enum class Orientation { UP, DOWN, LEFT, RIGHT };

 public:
    static const Direction UP;
    static const Direction DOWN;
    static const Direction LEFT;
    static const Direction RIGHT;
    constexpr static int ORIENTAION_COUNT = 4;

    /**
     * @brief Creates a direction.
     * @param initOrientation The initial orientation.
     */
    explicit Direction(const Orientation initOrientation) {
        this->orientation = initOrientation;
    }

    /**
     * @brief Returns the corresponding integer.
     */
    [[nodiscard]] int toInt() const {
        return static_cast<int>(this->orientation);
    }

    /**
     * @brief Returns the opposite direction.
     */
    [[nodiscard]] Direction opposite() const {
        const auto orientationIndex = toInt();
        return Direction(static_cast<Orientation>(orientationIndex ^ 1));
    }

 private:
    Orientation orientation;
};

const Direction Direction::UP{Orientation::UP};
const Direction Direction::DOWN{Orientation::DOWN};
const Direction Direction::LEFT{Orientation::LEFT};
const Direction Direction::RIGHT{Orientation::RIGHT};

/**
 * @brief In game development, a sprite is a movable texture. Last semester I
 * created a 2D farming game using Python, and I try to transplant the logic to
 * here.
 * \see
 * https://github.com/typinghare/wildtrace-farm/blob/main/src/world/character.py
 */
class ControllableSprite final : public sf::Sprite {
    /**
     * @brief To simplify the logic, the sprite moves at a constant speed.
     */
    constexpr static float SPEED{0.5};

 public:
    /**
     * @brief Creates a sprite.
     * @param filepath The filepath of the texture file.
     */
    explicit ControllableSprite(const std::string& filepath) : sf::Sprite() {
        const std::filesystem::path absolutePath =
            std::filesystem::absolute(filepath);
        std::cout << "Loading texture file: " << absolutePath << std::endl;

        if (!texture.loadFromFile(filepath)) {
            throw std::invalid_argument("Failed to load the texture.");
        }

        this->setTexture(texture);
        this->setPosition(sf::Vector2f(0.0f, 0.0f));
    }

    /**
     * @brief Enables a specific dierction
     * @param direction The direction to enable.
     */
    void enableDirection(const Direction& direction) {
        // Set the key state to true
        this->keyState[direction.toInt()] = true;

        // Set the opposite movement state to true if its key state is true
        const auto opposite = direction.opposite();
        if (!this->keyState[opposite.toInt()]) {
            this->movementState[direction.toInt()] = true;
        }
    }

    /**
     * @brief Disables a specific direction.
     * @param direction The direction to disable.
     */
    void disableDirection(const Direction& direction) {
        // Set the key state and movement state to false
        this->keyState[direction.toInt()] = false;
        this->movementState[direction.toInt()] = false;

        // Set the opposite movement state to true if its key state is true
        const auto opposite = direction.opposite();
        if (this->keyState[opposite.toInt()]) {
            this->movementState[opposite.toInt()] = true;
        }
    }

    /**
     * @brief Updates the position of this sprite.
     * @param dt Delta time in milliseconds.
     */
    void update(const int& dt) {
        int x = 0, y = 0;

        if (movementState[Direction::UP.toInt()])
            y = -1;
        if (movementState[Direction::DOWN.toInt()])
            y = 1;
        if (movementState[Direction::LEFT.toInt()])
            x = -1;
        if (movementState[Direction::RIGHT.toInt()])
            x = 1;

        if (x == 0 && y == 0)
            return;

        const float ds = 1.0f / static_cast<float>(sqrt(x * x + y * y));
        auto position = this->getPosition();
        position.x += static_cast<float>(x) * ds * static_cast<float>(dt);
        position.y += static_cast<float>(y) * ds * static_cast<float>(dt);
        this->setPosition(position);
    }

 private:
    sf::Texture texture;
    std::array<bool, Direction::ORIENTAION_COUNT> keyState{};
    std::array<bool, Direction::ORIENTAION_COUNT> movementState{};
};

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                            WINDOW_TITLE);
    window.setFramerateLimit(WINDOW_FPS);

    // Create a circle and a sprite
    constexpr int CIRCLE_RADIUS = 100.f;
    sf::CircleShape circleShape(CIRCLE_RADIUS);
    circleShape.setFillColor(sf::Color::Green);
    circleShape.setPosition(
        sf::Vector2f(static_cast<float>(WINDOW_WIDTH) / 2.0f - CIRCLE_RADIUS,
                     static_cast<float>(WINDOW_HEIGHT) / 2.0f - CIRCLE_RADIUS));
    ControllableSprite sprite(SPRITE_FILEPATH);

    // Game loop
    sf::Clock clock;
    while (window.isOpen()) {
        const int dt = clock.restart().asMilliseconds();

        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                break;
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Key::W) {
                    sprite.enableDirection(Direction::UP);
                } else if (event.key.code == sf::Keyboard::Key::A) {
                    sprite.enableDirection(Direction::LEFT);
                } else if (event.key.code == sf::Keyboard::Key::S) {
                    sprite.enableDirection(Direction::DOWN);
                } else if (event.key.code == sf::Keyboard::Key::D) {
                    sprite.enableDirection(Direction::RIGHT);
                }
            }

            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Key::W) {
                    sprite.disableDirection(Direction::UP);
                } else if (event.key.code == sf::Keyboard::Key::A) {
                    sprite.disableDirection(Direction::LEFT);
                } else if (event.key.code == sf::Keyboard::Key::S) {
                    sprite.disableDirection(Direction::DOWN);
                } else if (event.key.code == sf::Keyboard::Key::D) {
                    sprite.disableDirection(Direction::RIGHT);
                }
            }
        }

        // Clear the window before rendering
        window.clear();

        // Draw the circle
        window.draw(circleShape);

        // Update sprite and draw the sprite onto the window
        sprite.update(dt);
        window.draw(sprite);

        // display the new frame
        window.display();
    }
}
