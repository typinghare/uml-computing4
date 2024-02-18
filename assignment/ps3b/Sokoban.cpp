// Copyright 2024 James Chen

#include "Sokoban.hpp"
#include <fstream>
#include "InvalidCoordinateException.hpp"
#include "SokobanConstants.hpp"

namespace SB {

Sokoban::Sokoban() {
    initTileTextureMap();
    initPlayerSpriteMap();
}

int Sokoban::height() const { return m_height; }

int Sokoban::width() const { return m_width; }

sf::Vector2i Sokoban::playerLoc() const { return m_playerLoc; }

void Sokoban::movePlayer(const Direction direction) {
    // Change player's orientation
    playerOrientation = direction;

    // Find the coordinate of the tile to move to
    sf::Vector2i nextLoc(m_playerLoc);
    switch (direction) {
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

    // If the coordinate is out of the map, don't move
    if (nextLoc.x < 0 || nextLoc.x >= m_width || nextLoc.y < 0 || nextLoc.y >= m_height) {
        return;
    }

    // If the coordinate is a block, don't move
}

std::ifstream& operator>>(std::ifstream& ifstream, Sokoban& sokoban) {
    // Clear all tiles
    sokoban.tileTextureMap.clear();

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

void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Draw tiles
    traverseTileGrid([&](auto coordinate, auto tile) {
        const sf::Vector2i position = { coordinate.x * TILE_WIDTH, coordinate.y * TILE_HEIGHT };
        const sf::Vector2f positionFloat(position);
        tile->setPosition(positionFloat);
        target.draw(*tile);

        return true;
    });

    // Draw the player
    const auto player = playerSpriteMap.at(playerOrientation);
    player->setPosition({
        static_cast<float>(m_playerLoc.x * TILE_WIDTH),
        static_cast<float>(m_playerLoc.y * TILE_HEIGHT),
    });
    target.draw(*player);
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

    const auto playerUpSprite{ std::make_shared<sf::Sprite>() };
    const auto playerRightSprite{ std::make_shared<sf::Sprite>() };
    const auto playerDownSprite{ std::make_shared<sf::Sprite>() };
    const auto playerLeftSprite{ std::make_shared<sf::Sprite>() };
    playerUpSprite->setTexture(*playerUpTexture);
    playerRightSprite->setTexture(*playerRightTexture);
    playerDownSprite->setTexture(*playerDownTexture);
    playerLeftSprite->setTexture(*playerLeftTexture);

    playerSpriteMap[Direction::Up] = { playerUpSprite };
    playerSpriteMap[Direction::Right] = { playerRightSprite };
    playerSpriteMap[Direction::Down] = { playerDownSprite };
    playerSpriteMap[Direction::Left] = { playerLeftSprite };
}

std::shared_ptr<sf::Sprite> Sokoban::getTile(const sf::Vector2i& coordinate) const {
    const int index = coordinate.x + coordinate.y * m_width;
    if (index < 0 || index >= tileGrid.size()) {
        throw new InvalidCoordinateException(coordinate);
    }

    return tileGrid.at(index);
}

std::shared_ptr<sf::Sprite> Sokoban::charToTile(const char& c) const {
    const auto it = tileTextureMap.find(c);
    if (it == tileTextureMap.end()) {
        return nullptr;
    }

    const auto sprite{ std::shared_ptr<sf::Sprite>() };
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

}  // namespace SB
