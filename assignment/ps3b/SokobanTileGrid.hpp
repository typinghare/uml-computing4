// Copyright 2024 James Chen

#ifndef SOKOBANTILEGRID_HPP
#define SOKOBANTILEGRID_HPP

#include <memory>
#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>
#include "SokobanConstants.hpp"

namespace SB {

/**
 * @brief This class manages the tile grid system in Sokoban. Tiles includes the unmovable things in
 * the game, inlcuding wall blocks, ground blocks, box blocks, and so on. Note the player is not
 * included in tiles.
 */
class SokobanTileGrid : public virtual sf::Drawable {
 public:
    /**
     * @brief Returns the width of the game board, which is the number of tile columns.
     */
    [[nodiscard]] int width() const;

    /**
     * @brief Returns the height of the game board, which is the number of the tile rows.
     */
    [[nodiscard]] int height() const;

    /**
     * @brief Returns the tile character at a specified coordinate.
     * @param coordinate The coordinate of the tile character to get.
     */
    [[nodiscard]] TileChar getTileChar(const sf::Vector2i& coordinate) const;

 protected:
    /**
     * @brief Creates a SokobanTileGrid instance; initalizes the tile texture map.
     */
    SokobanTileGrid();

    /**
     * @brief draws the tile grid onto the target.
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    /**
     * @brief Returns the corresponding index of a specified coordiante.
     * @param coordinate Coordinate to analyze.
     */
    [[nodiscard]] int getIndex(const sf::Vector2i& coordinate) const;

    /**
     * @brief Sets the tile character for a specified coordiante. If the tile character changes, the
     * corresponding tile in the tile grid changes synchronously.
     * @param coordinate The coordiante of the tile character to set.
     * @param tileChar The tile character to set.
     */
    void setTileChar(const sf::Vector2i& coordinate, TileChar tileChar);

    /**
     * @brief Iterates over each tile character in the grid and invokes the specified callback
     * function for each tile, providing the tile's coordinate and its associated tile character.
     * The callback function should return true to continue the traversal or false to stop it.
     * @param callback The callback function is to be invoked for each tile.
     */
    void traverseTileCharGrid(const std::function<bool(sf::Vector2i, TileChar)>& callback) const;

    /**
     * @brief Converts a character into the corresponding tile sprite.
     * @return The corresponding tile sprite; nullptr if the tile char is not supported.
     */
    [[nodiscard]] std::shared_ptr<sf::Sprite> getTile(const TileChar& tileChar) const;

    /**
     * @brief The number of tile columns.
     */
    int m_width = 0;

    /**
     * @brief The number of tile rows.
     */
    int m_height = 0;

    /**
     * @brief Associates characters with their respective tile texture. Refer to
     * `SokobanConstants.h` for additional details. This mapping is crucial for constructing the
     * sprite grid.
     */
    std::unordered_map<TileChar, std::shared_ptr<sf::Texture>> m_tileTextureMap;

    /**
     * @brief The initial tile char grid. It is unchanged until the level changes.
     */
    std::vector<TileChar> m_initialTileCharGrid;

    /**
     * @brief Represents the tile character grid, which is mapping into an one-dimentional array in
     * row-major order.
     */
    std::vector<TileChar> m_tileCharGrid;

    /**
     * @brief Represents the tile grid, which is mapping into an one-dimentional array in row-major
     * order.
     */
    std::vector<std::shared_ptr<sf::Sprite>> m_tileGrid;

 private:
    /**
     * @brief Checks if a specified coordinate is valid. A valid coordiante should be able to be
     * located in the tile char grid.
     * @param coordinate The coordinate to check.
     * @return A index corresponding to the coordinate.
     * @throws InvalidCoordinateException if the coordinate is invalid.
     */
    [[nodiscard]] int checkCoordinate(const sf::Vector2i& coordinate) const;
};

}  // namespace SB


#endif
