// Copyright 2024 James Chen

#ifndef SOKOBAN_H
#define SOKOBAN_H

#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>
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
     * @brief Updates the game in a game frame.
     * @param dt The delta time in microseconds between this frame and the previous frame.
     */
    void update(const int64_t& dt);

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
     * @brief Draws the tiles onto the render target.
     */
    void drawTiles(sf::RenderTarget& target) const;

    /**
     * @brief Draws the player onto the render target.
     */
    void drawPlayer(sf::RenderTarget& target) const;

    /**
     * @brief Drwas the elapsed time text onto the render target.
     */
    void drawElapsedTime(sf::RenderTarget& target) const;

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
     * @brief Associates each direction with the corresponding player texture.
     */
    std::unordered_map<Direction, std::shared_ptr<sf::Texture>> playerTextureMap;

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
     * @brief Player's current orientation. The default orientation is down.
     */
    Direction playerOrientation = Direction::Down;

    /**
     * @brief The time elasped in microseconds.
     */
    int64_t timeElapsedInMicroseconds = 0;

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
     * @brief Returns the tile at a specified coordinate.
     * @param coordinate The coordinate of the tile to get.
     */
    [[nodiscard]] std::shared_ptr<sf::Sprite> getTile(const sf::Vector2i& coordinate) const;

    /**
     * @brief Sets the tile at a specified coordiante.
     * @param coordinate The coordiante of the tile to set.
     * @param tile The tile to set.
     */
    void setTile(const sf::Vector2i& coordinate, const std::shared_ptr<sf::Sprite>& tile);

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

    /**
     * @brief Returns the next location based on the current location and the orientation.
     * @param currentLoc The current location.
     * @param orientation The orientation.
     */
    [[nodiscard]] static sf::Vector2i
    getNextLoc(const sf::Vector2i& currentLoc, const Direction& orientation);

    /**
     * @brief Returns the tile texture at the block of specified coordiante.
     * @param coordinate The coordinate of the block.
     */
    [[nodiscard]] const sf::Texture* getBlockTexture(const sf::Vector2i& coordinate) const;

    /**
     * @brief Moves a box towards a specified direction. Note that the block at the from coordinate
     * must be a box.
     * @param fromCoordinate The initial coordinate.
     * @param direction The direction to move the box.
     * @return true if the box can be moved; false otherwise.
     */
    bool moveBox(const sf::Vector2i& fromCoordinate, const Direction& direction);
};

}  // namespace SB

#endif
