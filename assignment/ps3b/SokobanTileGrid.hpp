// Copyright 2024 James Chen

#ifndef SOKOBANTILEGRID_HPP
#define SOKOBANTILEGRID_HPP

#include <unordered_map>
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
     * @brief Iterates over each tile in the grid and invokes the specified callback function
     * for each tile, providing the tile's coordinate and its associated sprite. The callback
     * function should return true to continue the traversal or false to stop it.
     * @param callback The callback function to be invoked for each tile.
     */
    void traverseTileGrid(
        const std::function<bool(sf::Vector2i, std::shared_ptr<sf::Sprite>)>& callback) const;

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
     * @brief Represents the tile character grid, which is mapping into an one-dimentional array in
     * row-major order.
     */
    std::vector<TileChar> m_tileCharGrid;

    /**
     * @brief Represents the tile grid, which is mapping into an one-dimentional array in row-major
     * order.
     */
    std::vector<std::shared_ptr<sf::Sprite>> m_tileGrid;
};

}  // namespace SB


#endif
