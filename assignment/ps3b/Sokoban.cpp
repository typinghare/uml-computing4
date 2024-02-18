// Copyright 2024 James Chen

#include "Sokoban.hpp"
#include <sstream>
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

void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states) const {}

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

InvalidCoordinateException::InvalidCoordinateException(const sf::Vector2i& coordinate) noexcept {
    std::ostringstream oss;
    oss << "Invalid coordinate: (" << coordinate.x << ", " << coordinate.y << ")";
    message = oss.str();
}

const char* InvalidCoordinateException::what() const noexcept { return message.c_str(); }

}  // namespace SB
