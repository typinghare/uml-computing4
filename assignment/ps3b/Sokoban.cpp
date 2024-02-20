// Copyright 2024 James Chen

#include "Sokoban.hpp"
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include "SokobanConstants.hpp"

namespace SB {

sf::Vector2i Sokoban::playerLoc() const { return m_playerLoc; }

void Sokoban::movePlayer(const Direction direction) {
    // Change the player's orientation
    m_playerOrientation = direction;

    // Find the coordinate of the block to move to
    const auto nextLoc = getNextLoc(m_playerLoc, direction);

    // If the coordinate is out of the map, stay on the spot
    if (nextLoc.x < 0 || nextLoc.x >= m_width || nextLoc.y < 0 || nextLoc.y >= m_height) {
        return;
    }

    // Get the texture of the next block
    const auto nextBlockTexture = getBlockTexture(nextLoc);

    // If the coordinate corresponds to a wall block, stay on the spot
    if (nextBlockTexture == m_tileTextureMap.at(TileChar::Wall).get()) {
        return;
    }

    // If the coordinate corresponds to an box block, push the box to the other side
    const auto boxTexture = m_tileTextureMap.at(TileChar::Box).get();
    if (nextBlockTexture == boxTexture) {
        const auto canMoveBox = moveBox(nextLoc, direction);
        if (!canMoveBox) {
            return;
        }
    }

    // Update player location
    m_playerLoc = nextLoc;
}

void Sokoban::reset() { m_tileGrid.clear(); }

void Sokoban::update(const int64_t& dt) {
    if (!isWon()) {
        SokobanElapsedTime::update(dt);
    }
}

std::ifstream& operator>>(std::ifstream& ifstream, Sokoban& sokoban) {
    // Clear all tiles in the tile grid
    sokoban.m_tileGrid.clear();

    // The first line consists of height and width
    ifstream >> sokoban.m_height >> sokoban.m_width;

    // Ignore the rest of the line
    ifstream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Continue the read the following lines
    for (int row = 0; row < sokoban.m_height; ++row) {
        std::string line;
        getline(ifstream, line);
        for (int col = 0; col < sokoban.m_width; ++col) {
            const char c = line.at(col);
            if (const auto tile = sokoban.tileCharToTile(static_cast<TileChar>(c))) {
                sokoban.m_tileGrid.push_back(tile);
                if (c == TILE_CHAR_PLYAER) {
                    sokoban.m_playerLoc = { col, row };
                }
            }
        }
    }

    return ifstream;
}

std::ofstream& operator<<(std::ofstream& ofstream, const Sokoban& sokoban) { return ofstream; }

void Sokoban::draw(sf::RenderTarget& target, const sf::RenderStates states) const {
    SokobanTileGrid::draw(target, states);
    SokobanPlayer::draw(target, states);
    SokobanElapsedTime::draw(target, states);
    SokobanScore::draw(target, states);
}

std::shared_ptr<sf::Sprite> Sokoban::tileCharToTile(const TileChar& tileChar) const {
    const auto it = m_tileTextureMap.find(tileChar);
    if (it == m_tileTextureMap.end()) {
        return nullptr;
    }

    const auto sprite{ std::make_shared<sf::Sprite>() };
    sprite->setTexture(*it->second);

    return sprite;
}

sf::Vector2i Sokoban::getNextLoc(const sf::Vector2i& currentLoc, const Direction& orientation) {
    sf::Vector2i nextLoc(currentLoc);
    switch (orientation) {
        case Direction::Up:
            --nextLoc.y;
            break;
        case Direction::Down:
            ++nextLoc.y;
            break;
        case Direction::Left:
            --nextLoc.x;
            break;
        case Direction::Right:
            ++nextLoc.x;
            break;
    }

    return nextLoc;
}

const sf::Texture* Sokoban::getBlockTexture(const sf::Vector2i& coordinate) const {
    return getTile(coordinate)->getTexture();
}

bool Sokoban::moveBox(const sf::Vector2i& fromCoordinate, const Direction& direction) {
    const auto toCoordinate = getNextLoc(fromCoordinate, direction);
    const auto boxNextBlockTexture = getBlockTexture(toCoordinate);

    if (boxNextBlockTexture == m_tileTextureMap.at(TileChar::Empty).get()) {
        // Swap the blocks at the initial coordiante and the destination coordinate
        const auto boxTile = getTile(fromCoordinate);
        const auto emptyTile = getTile(toCoordinate);
        setTile(fromCoordinate, emptyTile);
        setTile(toCoordinate, boxTile);

        return true;
    }

    if (boxNextBlockTexture == m_tileTextureMap.at(TileChar::Storage).get()) {
        // The block at the initial coordiante should become an empty block
        const auto emptyTile{ std::make_shared<sf::Sprite>() };
        emptyTile->setTexture(*m_tileTextureMap.at(TileChar::Empty));
        setTile(fromCoordinate, emptyTile);

        // The block at the destination coordinate should become a box-storge block
        const auto boxStorageTile{ std::make_shared<sf::Sprite>() };
        boxStorageTile->setTexture(*m_tileTextureMap.at(TileChar::BoxStorage));
        setTile(toCoordinate, boxStorageTile);

        return true;
    }

    return false;
}

}  // namespace SB
