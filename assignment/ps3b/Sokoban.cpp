// Copyright 2024 James Chen

#include "Sokoban.hpp"
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include "SokobanConstants.hpp"

namespace SB {

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
    const auto nextBlock = getTileChar(nextLoc);

    // If the coordinate corresponds to a wall block or a box storage, stay on the spot
    if (nextBlock == TileChar::Wall || nextBlock == TileChar::BoxStorage) {
        return;
    }

    // If the coordinate corresponds to an box block, try to push the box to the other side
    if (nextBlock == TileChar::Box) {
        const auto canMoveBox = moveBox(nextLoc, direction);
        if (!canMoveBox) {
            return;
        }
    }

    // Update player location
    m_playerLoc = nextLoc;
}

void Sokoban::reset() {
    // Perform a shallow copy
    m_tileCharGrid = m_initialTileCharGrid;

    auto boxCount{ 0 };
    auto storageCount{ 0 };
    auto boxStorageCount{ 0 };
    traverseTileGrid([&](auto coordinate, auto tileChar) {
        m_tileGrid.push_back(getTile(tileChar));
        if (tileChar == TileChar::Player) {
            m_playerLoc = { coordinate };
        } else if (tileChar == TileChar::Box) {
            ++boxCount;
        } else if (tileChar == TileChar::Storage) {
            ++storageCount;
        } else if (tileChar == TileChar::BoxStorage) {
            ++boxStorageCount;
        }

        m_score = boxStorageCount;
        m_maxScore = std::min(storageCount, boxCount) + boxStorageCount;

        return false;
    });
}

void Sokoban::update(const int64_t& dt) {
    if (!isWon()) {
        SokobanElapsedTime::update(dt);
    }
}

std::ifstream& operator>>(std::ifstream& ifstream, Sokoban& sokoban) {
    sokoban.m_initialTileCharGrid.clear();

    // The first line consists of height and width; ignore the rest of the line
    ifstream >> sokoban.m_height >> sokoban.m_width;
    ifstream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Continue the read the following lines
    for (int row = 0; row < sokoban.m_height; ++row) {
        std::string line;
        getline(ifstream, line);
        for (int col = 0; col < sokoban.m_width; ++col) {
            sokoban.m_initialTileCharGrid.push_back(static_cast<TileChar>(line.at(col)));
        }
    }

    sokoban.reset();

    return ifstream;
}

std::ofstream& operator<<(std::ofstream& ofstream, const Sokoban& sokoban) { return ofstream; }

void Sokoban::draw(sf::RenderTarget& target, const sf::RenderStates states) const {
    SokobanTileGrid::draw(target, states);
    SokobanPlayer::draw(target, states);
    SokobanElapsedTime::draw(target, states);
    SokobanScore::draw(target, states);
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

bool Sokoban::moveBox(const sf::Vector2i& fromCoordinate, const Direction& direction) {
    const auto toCoordinate = getNextLoc(fromCoordinate, direction);
    const auto nextBlock = getTileChar(toCoordinate);

    if (nextBlock == TileChar::Empty) {
        // Swap the blocks at the initial coordiante and the destination coordinate
        setTileChar(fromCoordinate, TileChar::Empty);
        setTileChar(toCoordinate, TileChar::Box);

        return true;
    }

    if (nextBlock == TileChar::Storage) {
        // The block at the initial coordiante should become an empty block; the block at the
        // destination coordinate should become a box-storage block
        setTileChar(fromCoordinate, TileChar::Empty);
        setTileChar(toCoordinate, TileChar::BoxStorage);

        // Score increments by 1
        ++m_score;

        return true;
    }

    return false;
}

}  // namespace SB
