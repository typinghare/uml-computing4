#ifndef SOKOBAN_H
#define SOKOBAN_H

#include <SFML/Graphics.hpp>

namespace SB {

class Sokoban final : public sf::Drawable {
 public:
    /**
     * @brief A direction enumeration including four directions. The naming convention keeps with
     * SFML's.
     */
    enum class Direction { Up, Down, Left, Right };

    /**
     * @brief Creates a Sokoban object.
     */
    Sokoban();

    /**
     * @brief Returns the width of the game board.
     */
    int width() const;

    /**
     * @brief Returns the height of the game board.
     */
    int height() const;

    /**
     * @brief Returns the players' current position; (0, 0) represents the upper-left cell in the
     * upper-left corner.
     */
    sf::Vector2f playerLoc() const;

    /**
     * @brief Changes the player's location with the given direction.
     * @param direction The direction for the player to move.
     */
    void movePlayer(const Direction& direction);

    /**
     * @brief Returns whether the player has won.
     */
    bool isWon();

    void update(int dt);

 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    int m_width;
    int m_height;
    sf::Sprite player;
    sf::Sprite blocks;
};

}  // namespace SB

#endif
