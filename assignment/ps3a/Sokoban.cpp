// Copyright 2024 James Chen
#include "Sokoban.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace SB {

Sokoban::Sokoban() :
    m_width(0), m_height(0), m_playerLoc({ 0, 0 }), player(nullptr), timeElapsedInMs(0) {
    initTileMap();
    initPlayerTextureMap();

    // The player orientates downward at the beginning
    setPlayerOrientation(Direction::Down);

    // Initailizes font
    font.loadFromFile("assets/font/digital-7.mono.ttf");
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

int Sokoban::width() const { return m_width; }

int Sokoban::height() const { return m_height; }

sf::Vector2i Sokoban::playerLoc() const { return m_playerLoc; }

// ReSharper disable once CppMemberFunctionMayBeStatic
void Sokoban::movePlayer(const Direction& direction) {}

// ReSharper disable once CppMemberFunctionMayBeStatic
bool Sokoban::isWon() { return false; }

void Sokoban::update(const int& dt) { timeElapsedInMs += dt; }

sf::Sprite* Sokoban::getTile(const sf::Vector2i& coordinate) const {
    const int index = coordinate.x + coordinate.y * m_width;
    return tiles.at(index);
}

void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Draw tiles
    for (int row = 0; row < m_height; ++row) {
        for (int col = 0; col < m_width; ++col) {
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

    // Draw the elapsed time for extra credit
    const unsigned seconds = timeElapsedInMs / 1000u;
    const unsigned minutes = seconds / 60u;
    const unsigned hours = minutes / 60u;
    const unsigned second = seconds % 60u;
    const unsigned minute = minutes % 60u;
    const std::string secondStr = (second < 10 ? "0" : "") + std::to_string(second);
    const std::string minuteStr = (minute < 10 ? "0" : "") + std::to_string(minute);
    const std::string hourStr = std::to_string(hours);
    const std::string stringToPrint = hourStr + ":" + minuteStr + ":" + secondStr;

    // Create a text and draw it on the target window
    sf::Text text;
    text.setFont(font);
    text.setString(stringToPrint);
    text.setCharacterSize(28);
    text.setFillColor(sf::Color::Black);
    text.setPosition(25, 10);
    target.draw(text);
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

    // Continue the read the following lines
    std::string line;
    getline(ifstream, line);
    for (int row = 0; row < sokoban.m_height; ++row) {
        getline(ifstream, line);
        for (int col = 0; col < sokoban.m_width; ++col) {
            const char c = line.at(col);
            const auto tile = sokoban.charToTile(c);
            if (tile == nullptr) {
                continue;
            }

            sokoban.tiles.push_back(tile);
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
        throw std::invalid_argument("File not found: " + levelFilename);
    }

    ifstream >> sokoban;
}

sf::Sprite* Sokoban::charToTile(const char& c) const {
    const auto it = tileMap.find(c);
    if (it == tileMap.end()) {
        return nullptr;
    }

    const auto texture{ it->second };
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
}

}  // namespace SB
