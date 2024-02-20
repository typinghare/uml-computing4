// Copyright 2024 James Chen

#ifndef SOKOBAN_H
#define SOKOBAN_H

#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>
#include "SokobanConstants.hpp"
#include "SokobanElapsedTime.hpp"
#include "SokobanPlayer.hpp"
#include "SokobanScore.hpp"
#include "SokobanTileGrid.hpp"

namespace SB {

/**
 * @brief This class is responsible for the gameplay.
 */
class Sokoban final : public SokobanTileGrid,
                      public SokobanPlayer,
                      public SokobanElapsedTime,
                      public SokobanScore {
 public:
    /**
     * @brief Changes the player's location for one tile with the given direction.
     * @param direction The direction for the player to move.
     */
    void movePlayer(Direction direction);

    /**
     * @brief Resets the game. The game will return back to the initial form.
     */
    void reset();

    /**
     * @brief Updates the game in a game frame.
     * @param dt The delta time in microseconds between this frame and the previous frame.
     */
    void update(const int64_t& dt) override;

    /**
     * @brief Reads a map from a level file (.lvl) and loads the content to the sokoban object.
     */
    friend std::ifstream& operator>>(std::ifstream& ifstream, Sokoban& sokoban);

    /**
     * @brief Outputs a sokoban game to a level file (.lvl).
     */
    friend std::ofstream& operator<<(std::ofstream& ofstream, const Sokoban& sokoban);

 protected:
    /**
     * @brief Draws everything onto the target.
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    /**
     * @brief Returns the next location based on the current location and the orientation.
     * @param currentLoc The current location.
     * @param orientation The orientation.
     */
    [[nodiscard]] static sf::Vector2i
    getNextLoc(const sf::Vector2i& currentLoc, const Direction& orientation);

    /**
     * @brief Moves a box towards a specified direction. Note that the block at the from coordinate
     * must be a box.
     * @param fromCoordinate The initial coordinate.
     * @param direction The direction to move the box.
     * @return true if the box can be moved; false otherwise.
     */
    bool moveBox(const sf::Vector2i& fromCoordinate, const Direction& direction);
};

}  // namespace SB

#endif
