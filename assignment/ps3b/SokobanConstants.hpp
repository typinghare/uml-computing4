#ifndef SOKOBANCONSTANTS_H
#define SOKOBANCONSTANTS_H

#include <string>

/**
 * @brief Sokoban game constants. Include but not limit to the following:
 * 1. The name of the game
 * 2. The size of each tiles
 * 3. Tilesets' filenames
 * 4.
 */
namespace SB {

// The name of the game
inline const char* GAME_NAME = "Sokoban";

// The height and width of each tile
inline constexpr unsigned TILE_HEIGHT = 64;
inline constexpr unsigned TILE_WIDTH = 64;

// Tile characters. In the level (.lvl) files, each character corresponds to a specific texture of
// has particular meaning to the corresponding position.
// '@' - The initial position of the player.
// '.' - An empty space, which the player can move through.
// '#' - A wall, which blocks movement.
// 'A' - A box, which can be paused by the player.
// 'a' - A storage location, where the player is trying to push a box.
// '1' - A box that is already in a storage location.
inline constexpr char TILE_CHAR_PLYAER = '@';
inline constexpr char TILE_CHAR_EMPTY = '.';
inline constexpr char TILE_CHAR_WALL = '#';
inline constexpr char TILE_CHAR_BOX = 'A';
inline constexpr char TILE_CHAR_STORAGE = 'a';
inline constexpr char TILE_CHAR_BOX_STORAGE = '1';

// Assets directory
inline const std::string ASSETS_DIR = "./assets/";

// Tileset directory
inline const std::string TILESET_DIR = ASSETS_DIR + "tileset/";

// Tiles filename
inline const std::string TILE_ENVIRONMENT_03_FILENAME = TILESET_DIR + "environment_03.png";
inline const std::string TILE_BLOCK_06_FILENAME = TILESET_DIR + "block_06.png";
inline const std::string TILE_CRATE_03_FILENAME = TILESET_DIR + "crate_03.png";
inline const std::string TILE_GROUND_01_FILENAME = TILESET_DIR + "ground_01.png";
inline const std::string TILE_GROUND_04_FILENAME = TILESET_DIR + "ground_04.png";
inline const std::string TILE_PLAYER_05_FILENAME = TILESET_DIR + "player_05.png";
inline const std::string TILE_PLAYER_08_FILENAME = TILESET_DIR + "player_08.png";
inline const std::string TILE_PLAYER_17_FILENAME = TILESET_DIR + "player_17.png";
inline const std::string TILE_PLAYER_20_FILENAME = TILESET_DIR + "player_20.png";

/**
 * @brief Enumerates four cardinal directions: Up, Down, Left, and Right. This enumeration follows
 * the naming convention used in SFML.
 */
enum class Direction { Up, Down, Left, Right };

}  // namespace SB

#endif
