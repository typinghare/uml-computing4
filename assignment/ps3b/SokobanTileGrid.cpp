// Copyright 2024 James Chen

#include "SokobanTileGrid.hpp"
#include <SFML/Graphics.hpp>
#include "InvalidCoordinateException.hpp"

namespace SB {

SokobanTileGrid::SokobanTileGrid() {
    const auto boxStorageTexture{ std::make_shared<sf::Texture>() };
    const auto groundTexture{ std::make_shared<sf::Texture>() };
    const auto groundStorageTexture{ std::make_shared<sf::Texture>() };
    const auto crateTexture{ std::make_shared<sf::Texture>() };
    const auto wallTexture{ std::make_shared<sf::Texture>() };
    boxStorageTexture->loadFromFile(TILE_ENVIRONMENT_03_FILENAME);
    groundTexture->loadFromFile(TILE_GROUND_01_FILENAME);
    groundStorageTexture->loadFromFile(TILE_GROUND_04_FILENAME);
    crateTexture->loadFromFile(TILE_CRATE_03_FILENAME);
    wallTexture->loadFromFile(TILE_BLOCK_06_FILENAME);

    m_tileTextureMap[TileChar::Player] = { groundTexture };
    m_tileTextureMap[TileChar::Empty] = { groundTexture };
    m_tileTextureMap[TileChar::Wall] = { wallTexture };
    m_tileTextureMap[TileChar::Box] = { crateTexture };
    m_tileTextureMap[TileChar::Storage] = { groundStorageTexture };
    m_tileTextureMap[TileChar::BoxStorage] = { boxStorageTexture };
}

void SokobanTileGrid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    traverseTileGrid([&](auto coordinate, auto tile) {
        const sf::Vector2i position = { coordinate.x * TILE_WIDTH, coordinate.y * TILE_HEIGHT };
        const sf::Vector2f positionFloat(position);
        tile->setPosition(positionFloat);
        target.draw(*tile);

        return false;
    });
}

int SokobanTileGrid::height() const { return m_height; }

int SokobanTileGrid::width() const { return m_width; }

std::shared_ptr<sf::Sprite> SokobanTileGrid::getTile(const sf::Vector2i& coordinate) const {
    const int index = coordinate.x + coordinate.y * m_width;
    if (index < 0 || index >= m_tileGrid.size()) {
        throw InvalidCoordinateException(coordinate);
    }

    return m_tileGrid.at(index);
}

void SokobanTileGrid::setTile(
    const sf::Vector2i& coordinate, const std::shared_ptr<sf::Sprite>& tile) {
    const int index = coordinate.x + coordinate.y * m_width;
    if (index < 0 || index >= m_tileGrid.size()) {
        throw InvalidCoordinateException(coordinate);
    }

    m_tileGrid[index] = nullptr;
    m_tileGrid[index] = tile;
}

void SokobanTileGrid::traverseTileGrid(
    const std::function<bool(sf::Vector2i, std::shared_ptr<sf::Sprite>)>& callback) const {
    auto stopIteration = false;
    for (int row = 0; !stopIteration && row < m_height; ++row) {
        for (int col = 0; !stopIteration && col < m_width; ++col) {
            if (const auto tile = getTile({ col, row })) {
                stopIteration = callback({ col, row }, tile);
            }
        }
    }
}

}  // namespace SB
