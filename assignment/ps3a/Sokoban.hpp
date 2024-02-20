// Copyright 2024 James Chen
#ifndef SOKOBAN_H
#define SOKOBAN_H

#include <string>
#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>

/**
 * @brief Sokoban namespace.
 */
namespace SB {

// The name of the game
inline const char* GAME_NAME = "Sokoban";

// The size of each tile
inline constexpr int TILE_HEIGHT = 64;
inline constexpr int TILE_WIDTH = 64;

// Tileset directory
inline const std::string TILESET_DIR = "assets/tileset/";

// Tiles filename
inline const std::string TILE_BLOCK_06_FILENAME = TILESET_DIR + "block_06.png";
inline const std::string TILE_CRATE_03_FILENAME = TILESET_DIR + "crate_03.png";
inline const std::string TILE_ENVIRONMENT_03_FILENAME = TILESET_DIR + "environment_03.png";
inline const std::string TILE_GROUND_01_FILENAME = TILESET_DIR + "ground_01.png";
inline const std::string TILE_GROUND_04_FILENAME = TILESET_DIR + "ground_04.png";
inline const std::string TILE_PLAYER_05_FILENAME = TILESET_DIR + "player_05.png";
inline const std::string TILE_PLAYER_08_FILENAME = TILESET_DIR + "player_08.png";
inline const std::string TILE_PLAYER_17_FILENAME = TILESET_DIR + "player_17.png";
inline const std::string TILE_PLAYER_20_FILENAME = TILESET_DIR + "player_20.png";

// Tile characters
inline constexpr char TILE_CHAR_PLYAER = '@';
inline constexpr char TILE_CHAR_EMPTY = '.';
inline constexpr char TILE_CHAR_WALL = '#';
inline constexpr char TILE_CHAR_BOX = 'A';
inline constexpr char TILE_CHAR_STORAGE = 'a';
inline constexpr char TILE_CHAR_BOX_STORAGE = '1';

/**
 * @brief A direction enumeration including four directions. The naming convention keeps with
 * SFML's.
 */
enum class Direction { Up, Down, Left, Right };

class Sokoban final : public sf::Drawable {
 public:
    /**
     * @brief Creates a Sokoban object.
     */
    Sokoban();

    /**
     * @brief Deletes textures and tiles.
     */
    ~Sokoban() override;

    /**
     * @brief Returns the width of the game board.
     */
    [[nodiscard]] int width() const;

    /**
     * @brief Returns the height of the game board.
     */
    [[nodiscard]] int height() const;

    /**
     * @brief Returns the players' current position; (0, 0) represents the upper-left cell in the
     * upper-left corner.
     */
    [[nodiscard]] sf::Vector2i playerLoc() const;

    /**
     * @brief Changes the player's location with the given direction.
     * @param direction The direction for the player to move.
     */
    void movePlayer(const Direction& direction);

    /**
     * @brief Returns whether the player has won the game.
     */
    bool isWon();

    /**
     * @brief Updates the game.
     */
    void update(const int& dt);

    /**
     * @brief Reads a map from a level file (.lvl) and loads the content to the sokoban object.
     */
    friend std::ifstream& operator>>(std::ifstream& ifstream, Sokoban& sokoban);

    /**
     * @brief Outputs a sokoban game to a level file (.lvl).
     */
    friend std::ofstream& operator<<(std::ofstream& ofstream, const Sokoban& sokoban);

 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    int m_width;
    int m_height;
    sf::Vector2i m_playerLoc;
    std::unordered_map<char, sf::Texture*> tileMap;
    std::unordered_map<Direction, sf::Texture*> playerTextureMap;
    sf::Sprite* player;
    std::vector<sf::Sprite*> tiles;
    unsigned timeElapsedInMs;
    sf::Font m_font;

    /**
     * @brief Returns the tile of a specific coordinate.
     * @param coordinate
     */
    [[nodiscard]] sf::Sprite* getTile(const sf::Vector2i& coordinate) const;

    /**
     * @brief Converts a character to the corresponding sprite.
     */
    [[nodiscard]] sf::Sprite* charToTile(const char& c) const;

    /**
     * @brief Initializes the tile map.
     */
    void initTileMap();

    /**
     * @brief Initializes the player texture map.
     */
    void initPlayerTextureMap();

    /**
     * @brief Sets the player's orientation.
     * @param direction The direction the player orientente.
     */
    void setPlayerOrientation(const Direction& direction);
};

/**
 * @brief Loads a level from a level file.
 * @param sokoban
 * @param levelFilename
 */
void loadLevel(Sokoban& sokoban, const std::string& levelFilename);

}  // namespace SB

#endif
