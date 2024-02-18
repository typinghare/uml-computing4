// Copyright 2024 James Chen

#include "Sokoban.hpp"
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include "InvalidCoordinateException.hpp"
#include "SokobanConstants.hpp"

namespace SB {

Sokoban::Sokoban() {
    initTileTextureMap();
    initPlayerSpriteMap();

    font.loadFromFile("assets/font/digital-7.mono.ttf");
}

int Sokoban::height() const { return m_height; }

int Sokoban::width() const { return m_width; }

sf::Vector2i Sokoban::playerLoc() const { return m_playerLoc; }

void Sokoban::movePlayer(const Direction direction) {
    // Change the player's orientation
    playerOrientation = direction;

    // Find the coordinate of the block to move to
    const auto nextLoc = getNextLoc(m_playerLoc, direction);

    // If the coordinate is out of the map, stay on the spot
    if (nextLoc.x < 0 || nextLoc.x >= m_width || nextLoc.y < 0 || nextLoc.y >= m_height) {
        return;
    }

    // Get the texture of the next block
    const auto nextBlockTexture = getBlockTexture(nextLoc);

    // If the coordinate corresponds to a wall block, stay on the spot
    if (nextBlockTexture == tileTextureMap.at(TILE_CHAR_WALL).get()) {
        return;
    }

    // If the coordinate corresponds to an box block, push the box to the other side
    const auto boxTexture = tileTextureMap.at(TILE_CHAR_BOX).get();
    if (nextBlockTexture == boxTexture) {
        const auto canMoveBox = moveBox(nextLoc, direction);
        if (!canMoveBox) {
            return;
        }
    }

    // Update player location
    m_playerLoc = nextLoc;
}

void Sokoban::update(const int64_t& dt) { timeElapsedInMicroseconds += dt; }

std::ifstream& operator>>(std::ifstream& ifstream, Sokoban& sokoban) {
    // Clear all tiles in the tile grid
    sokoban.tileGrid.clear();

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
            if (const auto tile = sokoban.charToTile(c)) {
                sokoban.tileGrid.push_back(tile);
                if (c == TILE_CHAR_PLYAER) {
                    sokoban.m_playerLoc = { col, row };
                }
            }
        }
    }

    return ifstream;
}

std::ofstream& operator<<(std::ofstream& ofstream, const Sokoban& sokoban) { return ofstream; }

void Sokoban::drawTiles(sf::RenderTarget& target) const {
    traverseTileGrid([&](auto coordinate, auto tile) {
        const sf::Vector2i position = { coordinate.x * TILE_WIDTH, coordinate.y * TILE_HEIGHT };
        const sf::Vector2f positionFloat(position);
        tile->setPosition(positionFloat);
        target.draw(*tile);

        return false;
    });
}
void Sokoban::drawPlayer(sf::RenderTarget& target) const {
    const auto player = playerSpriteMap.at(playerOrientation);
    player->setPosition({
        static_cast<float>(m_playerLoc.x * TILE_WIDTH),
        static_cast<float>(m_playerLoc.y * TILE_HEIGHT),
    });
    target.draw(*player);
}

void Sokoban::drawElapsedTime(sf::RenderTarget& target) const {
    const unsigned seconds = timeElapsedInMicroseconds / 1000000u;
    const unsigned minutes = seconds / 60u;
    const unsigned hours = minutes / 60u;
    const unsigned second = seconds % 60u;
    const unsigned minute = minutes % 60u;
    const std::string secondStr = (second < 10 ? "0" : "") + std::to_string(second);
    const std::string minuteStr = (minute < 10 ? "0" : "") + std::to_string(minute);
    const std::string hourStr = std::to_string(hours);
    const std::string stringToPrint = hourStr + ":" + minuteStr + ":" + secondStr;

    sf::Text text;
    text.setFont(font);
    text.setString(stringToPrint);
    text.setCharacterSize(28);
    text.setFillColor(sf::Color::Black);
    text.setPosition(15, 10);
    target.draw(text);
}

void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    drawTiles(target);
    drawPlayer(target);
    drawElapsedTime(target);
}

void Sokoban::initTileTextureMap() {
    const auto groundTexture{ std::make_shared<sf::Texture>() };
    const auto groundStorageTexture{ std::make_shared<sf::Texture>() };
    const auto crateTexture{ std::make_shared<sf::Texture>() };
    const auto wallTexture{ std::make_shared<sf::Texture>() };
    groundTexture->loadFromFile(TILE_GROUND_01_FILENAME);
    groundStorageTexture->loadFromFile(TILE_GROUND_04_FILENAME);
    crateTexture->loadFromFile(TILE_CRATE_03_FILENAME);
    wallTexture->loadFromFile(TILE_BLOCK_06_FILENAME);

    tileTextureMap[TILE_CHAR_PLYAER] = { groundTexture };
    tileTextureMap[TILE_CHAR_EMPTY] = { groundTexture };
    tileTextureMap[TILE_CHAR_WALL] = { wallTexture };
    tileTextureMap[TILE_CHAR_BOX] = { crateTexture };
    tileTextureMap[TILE_CHAR_STORAGE] = { groundStorageTexture };
    tileTextureMap[TILE_CHAR_BOX_STORAGE] = { crateTexture };
}

void Sokoban::initPlayerSpriteMap() {
    const auto playerUpTexture{ std::make_shared<sf::Texture>() };
    const auto playerRightTexture{ std::make_shared<sf::Texture>() };
    const auto playerDownTexture{ std::make_shared<sf::Texture>() };
    const auto playerLeftTexture{ std::make_shared<sf::Texture>() };
    playerUpTexture->loadFromFile(TILE_PLAYER_08_FILENAME);
    playerRightTexture->loadFromFile(TILE_PLAYER_17_FILENAME);
    playerDownTexture->loadFromFile(TILE_PLAYER_05_FILENAME);
    playerLeftTexture->loadFromFile(TILE_PLAYER_20_FILENAME);

    playerTextureMap[Direction::Up] = { playerUpTexture };
    playerTextureMap[Direction::Right] = { playerRightTexture };
    playerTextureMap[Direction::Down] = { playerDownTexture };
    playerTextureMap[Direction::Left] = { playerLeftTexture };

    const auto playerUpSprite{ std::make_shared<sf::Sprite>() };
    const auto playerRightSprite{ std::make_shared<sf::Sprite>() };
    const auto playerDownSprite{ std::make_shared<sf::Sprite>() };
    const auto playerLeftSprite{ std::make_shared<sf::Sprite>() };
    playerUpSprite->setTexture(*playerUpTexture);
    playerRightSprite->setTexture(*playerRightTexture);
    playerDownSprite->setTexture(*playerDownTexture);
    playerLeftSprite->setTexture(*playerLeftTexture);

    playerSpriteMap[Direction::Up] = playerUpSprite;
    playerSpriteMap[Direction::Right] = playerRightSprite;
    playerSpriteMap[Direction::Down] = playerDownSprite;
    playerSpriteMap[Direction::Left] = playerLeftSprite;
}

std::shared_ptr<sf::Sprite> Sokoban::getTile(const sf::Vector2i& coordinate) const {
    const int index = coordinate.x + coordinate.y * m_width;
    if (index < 0 || index >= tileGrid.size()) {
        throw InvalidCoordinateException(coordinate);
    }

    return tileGrid.at(index);
}

void Sokoban::setTile(const sf::Vector2i& coordinate, const std::shared_ptr<sf::Sprite>& tile) {
    const int index = coordinate.x + coordinate.y * m_width;
    if (index < 0 || index >= tileGrid.size()) {
        throw InvalidCoordinateException(coordinate);
    }

    tileGrid[index] = tile;
}

std::shared_ptr<sf::Sprite> Sokoban::charToTile(const char& c) const {
    const auto it = tileTextureMap.find(c);
    if (it == tileTextureMap.end()) {
        return nullptr;
    }

    const auto sprite{ std::make_shared<sf::Sprite>() };
    sprite->setTexture(*it->second);

    return sprite;
}

void Sokoban::traverseTileGrid(
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
    const auto boxNextLoc = getNextLoc(fromCoordinate, direction);
    const auto boxNextBlockTexture = getBlockTexture(boxNextLoc);

    // If the box should not be pushed on the current side, the player should stay on the spot
    if (boxNextBlockTexture != tileTextureMap.at(TILE_CHAR_EMPTY).get()) {
        return false;
    }

    // Move it: the block at the from coordiante becomes an empty block, and the block at the to
    // coordinate becomes a box block
    const auto boxTile = getTile(fromCoordinate);
    const auto emptyTile = getTile(boxNextLoc);
    setTile(fromCoordinate, emptyTile);
    setTile(boxNextLoc, boxTile);

    return true;
}

}  // namespace SB
