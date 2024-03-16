// Copyright 2024 James Chen

#ifndef CELESTIALBODY_HPP
#define CELESTIALBODY_HPP

#include <memory>
#include <string>
#include <utility>
#include <SFML/Graphics.hpp>
#include "Universe.hpp"

namespace NB {

class Universe;

class CelestialBody final : public sf::Drawable {
 public:
    /**
     * @brief Creates a CelestialBody instance.
     * @param universePtr The universe this celesitial body is in.
     */
    explicit CelestialBody(Universe* universePtr);

    /**
     * @brief Returns the universe this celesitial body is in.
     */
    [[nodiscard]] Universe* universe() const;

    /**
     * @brief Returns the position of this celestial body.
     */
    [[nodiscard]] sf::Vector2f position() const;

    /**
     * @brief Returns the velocity of this celestial body.
     */
    [[nodiscard]] sf::Vector2f velocity() const;

    /**
     * @brief Returns the mass of this celestial body.
     */
    [[nodiscard]] float mass() const;

    /**
     * @brief Loads resource (image).
     */
    void loadResource();

    /**
     * Draws this celestial body onto the target.
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    /**
     * @brief The universe this celesitial body is in.
     */
    Universe* m_universePtr;

    /**
     * @brief The center coordiante of this celestial body.
     */
    sf::Vector2<double> m_position;

    /**
     * @brief The velocity of this celestial body.
     */
    sf::Vector2<double> m_velocity;

    /**
     * @brief The mass of this celestial body.
     */
    double m_mass = 0.0;

    /**
     * @brief The filename of the image.
     */
    std::string m_image_filename;

    /**
     * @brief The image (Sprite and corresponding texture) of this celestial body.
     */
    std::pair<std::shared_ptr<sf::Texture>, std::shared_ptr<sf::Sprite>> m_image;

    /**
     * @brief Reads data from the std::istream to the celestial body.
     */
    friend std::istream& operator>>(std::istream& istream, CelestialBody& celestialBody);

    /**
     * @brief Writes data from the celesitial body to the std::ostream.
     */
    friend std::ostream& operator<<(std::ostream& ostream, const CelestialBody& celestialBody);
};

}  // namespace NB

#endif
