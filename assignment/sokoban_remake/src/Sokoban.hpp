#ifndef SOKOBAN_HPP
#define SOKOBAN_HPP

#include <iostream>
#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>

namespace SB {

constexpr unsigned TILE_SIZE = 64;

inline std::string ASSETS_DIR = "../assets/";
inline std::string TILESET_DIR = ASSETS_DIR + "tileset/";
inline std::string FONT_DIR = ASSETS_DIR + "font/";

enum class Direction : int { Up, Down, Left, Right };

enum class TileChar : char {
    Player = '@',
    EmptySpace = '.',
    Wall = '#',
    Box = 'A',
    Storage = 'a',
    BoxStorage = '1'
};

class Sokoban final : public sf::Drawable {
 public:
    Sokoban();

    ~Sokoban() override = default;

    [[nodiscard]] unsigned width() const { return size_.x; }

    [[nodiscard]] unsigned height() const { return size_.y; }

    [[nodiscard]] sf::Vector2u playerLoc() const { return player_loc_; }

    void movePlayer(Direction dir);

    [[nodiscard]] bool isWon() const;

    // Reset the game; the map and the player's location will be rolled back to the initial state
    void reset();

    friend std::ostream& operator<<(std::ostream& os, const Sokoban& sokoban);

    friend std::istream& operator>>(std::istream& is, Sokoban& sokoban);

 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    TileChar& tileAt(const sf::Vector2u& coord) { return map_[coord.x][coord.y]; }

    [[nodiscard]] TileChar tileAtConst(const sf::Vector2u& coord) const {
        return map_.at(coord.x).at(coord.y);
    }

    // Calculates the next coordinate by a coordinate and a direction.
    [[nodiscard]] static sf::Vector2u nextCoord(const sf::Vector2u& coord, Direction dir);

    // Check if a box can be moved along a specified direction
    // If the box cannot be moved, then return its current coordinate
    // If the box can be moved, then return its next coordinate
    [[nodiscard]] std::pair<bool, sf::Vector2u>
    testBoxNextCoord(const sf::Vector2u& boxCoord, Direction dir) const;

    // Move a box from one coordinate to another coordinate
    void moveBox(const sf::Vector2u& boxCoord, const sf::Vector2u& boxNextCoord);

 private:
    // The size of the map
    sf::Vector2u size_{};

    // Initial map
    std::vector<std::vector<TileChar>> initial_map_{};

    // Initial player location
    sf::Vector2u initial_player_loc_{};

    // Initial number of boxes that are placed in storages
    int initial_num_boxes_storage{ 0 };

    // Represents the map, where each character represents a corresponding tile
    std::vector<std::vector<TileChar>> map_{};

    // Mapping from tile characters to corresponding tile texture
    std::unordered_map<TileChar, sf::Texture> tile_textures_{};

    // Mapping from directions to corresponding player texture
    std::unordered_map<Direction, sf::Texture> player_textures_{};

    // Player's current location
    sf::Vector2u player_loc_{};

    // Player's current orientation
    Direction player_dir_{ Direction::Down };

    // The number of storages
    int num_storages{ 0 };

    // The number of boxes
    int num_boxes{ 0 };

    // The number of boxes that are placed in storages
    int num_boxes_storage{ 0 };

    sf::Font text_font_{};
};

}  // namespace SB

#endif
