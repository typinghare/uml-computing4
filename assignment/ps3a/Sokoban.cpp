// Copyright 2024 James Chen
#include "Sokoban.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace SB {

Sokoban::Sokoban() : m_width(0), m_height(0), m_playerLoc({ 0, 0 }), player(nullptr) {
    initTileMap();
    initPlayerTextureMap();
    setPlayerOrientation(Direction::Down);
}

Sokoban::~Sokoban() {
    // Delete tiles in tiles vector
    for (const auto& tile : tiles) {
        delete tile;
    }
    tiles.clear();

    // Delete player textures
    for (auto& [name, playerTexture] : playerTextureMap) {
        delete playerTexture;
    }
    playerTextureMap.clear();

    // Delete player sprite
    delete player;
}

unsigned Sokoban::width() const { return m_width; }

unsigned Sokoban::height() const { return m_height; }

sf::Vector2u Sokoban::playerLoc() const { return m_playerLoc; }

void Sokoban::movePlayer(const Direction& direction) {}

bool Sokoban::isWon() { return false; }

void Sokoban::update(const int& dt) { std::cout << dt << std::endl; }

sf::Sprite* Sokoban::getTile(const sf::Vector2u& coordinate) const {
    return this->tiles[coordinate.x + coordinate.y * m_width];
}

void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Draw tiles
    for (unsigned row = 0; row < m_width; ++row) {
        for (unsigned col = 0; col < m_height; ++col) {
            const auto tile = getTile({ col, row });
            if (tile == nullptr)
                continue;

            auto position = sf::Vector2f{ static_cast<float>(col * TILE_WIDTH),
                                          static_cast<float>(row * TILE_HEIGHT) };
            tile->setPosition(position);
            target.draw(*tile);
        }
    }

    // Draw the player
    player->setPosition({
        static_cast<float>(m_playerLoc.x * TILE_WIDTH),
        static_cast<float>(m_playerLoc.y * TILE_HEIGHT),
    });
    target.draw(*player);
}

std::ifstream& operator>>(std::ifstream& ifstream, Sokoban& sokoban) {
    // Clear all tiles
    for (auto& tile : sokoban.tiles) {
        delete tile;
        tile = nullptr;
    }
    sokoban.tiles.clear();

    // The first line consists of height and width
    ifstream >> sokoban.m_height >> sokoban.m_width;
    std::string line;
    getline(ifstream, line);  // Skip the first line

    for (unsigned row = 0; row < sokoban.m_width; ++row) {
        getline(ifstream, line);
        for (unsigned col = 0; col < sokoban.m_height; ++col) {
            const char c = line[col];
            sokoban.tiles.push_back(sokoban.charToTile(c));
            if (c == TILE_CHAR_PLYAER) {
                sokoban.m_playerLoc = { col, row };
            }
        }
    }

    return ifstream;
}

std::ofstream& operator<<(std::ofstream& ofstream, const Sokoban& sokoban) { return ofstream; }

void loadLevel(Sokoban& sokoban, const std::string& levelFilename) {
    std::ifstream ifstream{ levelFilename };
    if (!ifstream.is_open()) {
        throw std::exception();
    }

    ifstream >> sokoban;
}

sf::Sprite* Sokoban::charToTile(const char& c) const {
    const auto texture{ tileMap.at(c) };
    const auto sprite{ new sf::Sprite };
    sprite->setTexture(*texture);

    return sprite;
}

void Sokoban::initTileMap() {
    const auto groundTexture{ new sf::Texture };
    const auto groundStorageTexture{ new sf::Texture };
    const auto crateTexture{ new sf::Texture };
    const auto wallTexture{ new sf::Texture };

    groundTexture->loadFromFile(TILE_GROUND_01_FILENAME);
    groundStorageTexture->loadFromFile(TILE_GROUND_04_FILENAME);
    crateTexture->loadFromFile(TILE_CRATE_03_FILENAME);
    wallTexture->loadFromFile(TILE_BLOCK_06_FILENAME);

    tileMap[TILE_CHAR_PLYAER] = groundTexture;
    tileMap[TILE_CHAR_EMPTY] = groundTexture;
    tileMap[TILE_CHAR_WALL] = wallTexture;
    tileMap[TILE_CHAR_BOX] = crateTexture;
    tileMap[TILE_CHAR_STORAGE] = groundStorageTexture;
    tileMap[TILE_CHAR_BOX_STORAGE] = crateTexture;
}

void Sokoban::initPlayerTextureMap() {
    const auto playerUpTexture{ new sf::Texture };
    const auto playerRightTexture{ new sf::Texture };
    const auto playerDownTexture{ new sf::Texture };
    const auto playerLeftTexture{ new sf::Texture };

    playerUpTexture->loadFromFile(TILE_PLAYER_08_FILENAME);
    playerRightTexture->loadFromFile(TILE_PLAYER_17_FILENAME);
    playerDownTexture->loadFromFile(TILE_PLAYER_05_FILENAME);
    playerLeftTexture->loadFromFile(TILE_PLAYER_20_FILENAME);

    playerTextureMap[Direction::Up] = playerUpTexture;
    playerTextureMap[Direction::Right] = playerRightTexture;
    playerTextureMap[Direction::Down] = playerDownTexture;
    playerTextureMap[Direction::Left] = playerLeftTexture;
}

void Sokoban::setPlayerOrientation(const Direction& direction) {
    delete player;

    const auto texture{ playerTextureMap.at(direction) };
    const auto sprite{ new sf::Sprite };
    sprite->setTexture(*texture);

    player = sprite;
    player = sprite;
}

}  // namespace SB
