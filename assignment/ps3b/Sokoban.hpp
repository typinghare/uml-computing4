// Copyright 2024 James Chen

#ifndef SOKOBAN_H
#define SOKOBAN_H

#include <functional>
#include <SFML/Graphics.hpp>
#include "SokobanConstants.hpp"

namespace SB {

class Sokoban final : public sf::Drawable {
 public:
    /**
     * @brief Creates a Sokoban game object.
     */
    Sokoban();

    /**
     * @brief Returns the width of the game board, which is the number of tile columns.
     */
    [[nodiscard]] int width() const;

    /**
     * @brief Returns the height of the game board, which is the number of the tile rows.
     */
    [[nodiscard]] int height() const;

    /**
     * @brief Returns the players' current position; (0, 0) represents the upper-left cell in the
     * upper-left corner.
     */
    [[nodiscard]] sf::Vector2i playerLoc() const;

    /**
     * @brief Changes the player's location for one tile with the given direction.
     * @param direction The direction for the player to move.
     */
    void movePlayer(Direction direction);

    /**
     * @brief Reads a map from a level file (.lvl) and loads the content to the sokoban object.
     */
    friend std::ifstream& operator>>(std::ifstream& ifstream, Sokoban& sokoban);

    /**
     * @brief Outputs a sokoban game to a level file (.lvl).
     */
    friend std::ofstream& operator<<(std::ofstream& ofstream, const Sokoban& sokoban);

 protected:
    /**
     * @brief Draws the.
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    /**
     * @brief The number of tile columns.
     */
    int m_width = 0;

    /**
     * @brief The number of tile rows.
     */
    int m_height = 0;

    /**
     * @brief Player location. Note the unit of this coordinate is tile instead of pixel.
     */
    sf::Vector2i m_playerLoc = { 0, 0 };

    /**
     * @brief Associates characters with their respective tile texture. Refer to
     * `SokobanConstants.h` for additional details. This mapping is crucial for constructing the
     * sprite grid.
     */
    std::unordered_map<char, std::shared_ptr<sf::Texture>> tileTextureMap;

    /**
     * @brief Associates each direction with the corresponding player sprite. Player sprites vary
     * depending on the orientation.
     */
    std::unordered_map<Direction, std::shared_ptr<sf::Sprite>> playerSpriteMap;

    /**
     * @brief Represents the tile grid, which is mapping into a one-dimentional array in row-major
     * order.
     */
    std::vector<std::shared_ptr<sf::Sprite>> tileGrid;

    /**
     * @brief Player's current orientation.
     */
    Direction playerOrientation = Direction::Down;

    /**
     * @brief The time elasped in milliseconds.
     */
    unsigned timeElapsedInMs = 0;

    /**
     * @brief The font for the diplayed text.
     */
    sf::Font font;

    /**
     * @brief Initializes the tile texture map.
     */
    void initTileTextureMap();

    /**
     * @brief Initializes the player sprite map.
     */
    void initPlayerSpriteMap();

    /**
     * @brief Returns the tile of a specific coordinate.
     * @param coordinate The coordinate of the tile to get.
     */
    [[nodiscard]] std::shared_ptr<sf::Sprite> getTile(const sf::Vector2i& coordinate) const;

    /**
     * @brief Converts a character into the corresponding sprite.
     */
    [[nodiscard]] std::shared_ptr<sf::Sprite> charToTile(const char& c) const;

    /**
     * @brief Iterates over each tile in the grid and invokes the specified callback function
     * for each tile, providing the tile's coordinate and its associated sprite. The callback
     * function should return true to continue the traversal or false to stop it.
     * @param callback The callback function to be invoked for each tile.
     */
    void traverseTileGrid(
        const std::function<bool(sf::Vector2i, std::shared_ptr<sf::Sprite>)>& callback) const;
};

}  // namespace SB

#endif
