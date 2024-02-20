// Copyright 2024 James Chen

#ifndef SOKOBANPLAYER_HPP
#define SOKOBANPLAYER_HPP

#include <SFML/Graphics.hpp>
#include "SokobanConstants.hpp"

namespace SB {

/**
 * @brief This class manages the player system in Sokoban.
 */
class SokobanPlayer : public virtual sf::Drawable {

 protected:
    /**
     * @brief Player location. Note the unit of this coordinate is tile instead of pixel.
     */
    sf::Vector2i m_playerLoc = { 0, 0 };

    /**
     * @brief Associates each direction with the corresponding player texture.
     */
    std::unordered_map<Direction, std::shared_ptr<sf::Texture>> m_playerTextureMap;

    /**
     * @brief Associates each direction with the corresponding player sprite. Player sprites vary
     * depending on the orientation.
     */
    std::unordered_map<Direction, std::shared_ptr<sf::Sprite>> m_playerSpriteMap;

    /**
     * @brief Player's current orientation. The default orientation is down.
     */
    Direction m_playerOrientation = Direction::Down;

    /**
     * @brief Creates a SokobanPlayer instance; initalizes the player texture map and the player
     * sprite map.
     */
    SokobanPlayer();

    /**
     * @brief Draws the player onto the target.
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

}  // namespace SB

#endif
