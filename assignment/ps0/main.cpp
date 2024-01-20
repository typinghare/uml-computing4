// NOLINT(legal/copyright)
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
     * \brief Creates a direction.
     * \param initOrientation The initial orientation.
     */
    explicit Direction(const Orientation initOrientation) {
        this->orientation = initOrientation;
    }

    /**
     * \brief Returns the corresponding integer.
     */
    int toInt() const { return static_cast<int>(this->orientation); }

    /**
     * \brief Returns the opposite direction.
     */
    Direction opposite() const {
        const auto orientationIndex = toInt();
        const auto OppositeOrientation =
            static_cast<Orientation>(orientationIndex ^ 1);

        return Direction(OppositeOrientation);
    }

private:
    Orientation orientation;
};

const Direction Direction::UP{Orientation::UP};
const Direction Direction::DOWN{Orientation::DOWN};
const Direction Direction::LEFT{Orientation::LEFT};
const Direction Direction::RIGHT{Orientation::RIGHT};

/**
 * \brief In game development, a sprite is a movable texture. Last semester I
 * created a 2D farming game using Python, and I try to transplant the logic to
 * here.
 * \see https://github.com/typinghare/wildtrace-farm/blob/main/src/world/character.py
 */
class ControllableSprite final : public sf::Sprite {
    /**
     * \brief To simplify the logic, the sprite moves at a constant speed.
     */
    constexpr static float SPEED{0.5};

public:
    /**
     * \brief Creates a sprite.
     * \param filepath The filepath of the texture file.
     */
    explicit ControllableSprite(const std::string&filepath) {
        const std::filesystem::path absolutePath =
            std::filesystem::absolute(filepath);
        std::cout << "Loading texture file: " << absolutePath << std::endl;

        if (!texture.loadFromFile(filepath)) {
            throw new std::invalid_argument("Fail to load the texture.");
        }

        this->setTexture(texture);
        this->setPosition(0, 0);
    }

    /**
     * \brief Enables a specific dierction
     * \param direction The direction to enable.
     */
    void enableDirection(const Direction&direction) {
        // Set the key state to true
        this->keyState[direction.toInt()] = true;

        // Set the opposite movement state to true if its key state is true
        const auto opposite = direction.opposite();
        if (!this->keyState[opposite.toInt()]) {
            this->movementState[direction.toInt()] = true;
        }
    }

    /**
     * \brief Disables a specific direction.
     * \param direction The direction to disable.
     */
    void disableDirection(const Direction&direction) {
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
     * \brief Updates the position of this sprite.
     * \param dt Delta time in milliseconds.
     */
    void update(const int&dt) {
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

        const float ds = 1 / sqrt(x * x + y * y);
        const auto position = this->getPosition();
        this->setPosition(position.x + x * ds * dt, position.y + y * ds * dt);
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

    // Create a sprite

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
                if (event.key.code == sf::Keyboard::W) {
                    sprite.enableDirection(Direction::UP);
                } else if (event.key.code == sf::Keyboard::A) {
                    sprite.enableDirection(Direction::LEFT);
                } else if (event.key.code == sf::Keyboard::S) {
                    sprite.enableDirection(Direction::DOWN);
                } else if (event.key.code == sf::Keyboard::D) {
                    sprite.enableDirection(Direction::RIGHT);
                }
            }

            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::W) {
                    sprite.disableDirection(Direction::UP);
                } else if (event.key.code == sf::Keyboard::A) {
                    sprite.disableDirection(Direction::LEFT);
                } else if (event.key.code == sf::Keyboard::S) {
                    sprite.disableDirection(Direction::DOWN);
                } else if (event.key.code == sf::Keyboard::D) {
                    sprite.disableDirection(Direction::RIGHT);
                }
            }
        }

        // Clear the window before rendering
        window.clear();

        // Update sprite and draw the sprite onto the window
        sprite.update(dt);
        window.draw(sprite);

        // display the new frame
        window.display();
    }
}
