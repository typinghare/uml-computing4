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
     * @brief Constructs a CelestialBody instance.
     */
    CelestialBody();

    /**
     * @brief Constructs a CelestialBody instance within a specified Universe.
     * @param universePtr Pointer to the Universe this CelestialBody belongs to.
     */
    explicit CelestialBody(Universe* universePtr);

    /**
     * @brief Retrieves the Universe this CelestialBody belongs to.
     * @return Pointer to the Universe.
     */
    [[nodiscard]] Universe* universe() const;

    /**
     * @brief Retrieves the position vector of this CelestialBody.
     * @return Position vector as sf::Vector2f.
     */
    [[nodiscard]] sf::Vector2f position() const;

    /**
     * @brief Retrieves the velocity vector of this CelestialBody.
     * @return Velocity vector as sf::Vector2f.
     */
    [[nodiscard]] sf::Vector2f velocity() const;

    /**
     * @brief Retrieves the mass of this CelestialBody.
     * @return Mass of the CelestialBody.
     */
    [[nodiscard]] float mass() const;

    /**
     * @brief Retrieves the position vector of this CelestialBody.
     * @return Position vector as sf::Vector2<double>.
     */
    [[nodiscard]] sf::Vector2<double> positionDouble() const;

    /**
     * @brief Retrieves the velocity vector of this CelestialBody.
     * @return Velocity vector as sf::Vector2<double>.
     */
    [[nodiscard]] sf::Vector2<double> velocityDouble() const;

    /**
     * @brief Retrieves the mass of this CelestialBody.
     * @return Mass of the CelestialBody.
     */
    [[nodiscard]] double massDouble() const;

    /**
     * @brief Sets the new position for this CelestialBody.
     */
    void position(sf::Vector2<double> newPosition);

    /**
     * @brief Sets the new velocity for this CelestialBody.
     */
    void velocity(sf::Vector2<double> newVelocity);

    /**
     * @brief Loads the resource (image) associated with this CelestialBody.
     */
    void loadResources();

 protected:
    /**
     * @brief Draws this CelestialBody onto a given render target.
     * @param target The render target to draw onto.
     * @param states The render states to use for drawing.
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    /**
     * @brief Pointer to the Universe this CelestialBody belongs to.
     */
    Universe* m_universePtr;

    /**
     * @brief The center coordinate of this CelestialBody.
     */
    sf::Vector2<double> m_position;

    /**
     * @brief The velocity vector of this CelestialBody.
     */
    sf::Vector2<double> m_velocity;

    /**
     * @brief The mass of this CelestialBody.
     */
    double m_mass = 0.0;

    /**
     * @brief The filename of the associated image.
     */
    std::string m_image_filename;

    /**
     * @brief Pair containing shared pointers to the texture and sprite of this CelestialBody.
     */
    std::pair<std::shared_ptr<sf::Texture>, std::shared_ptr<sf::Sprite>> m_image;

    /**
     * @brief Reads data from a std::istream into the CelestialBody.
     */
    friend std::istream& operator>>(std::istream& istream, CelestialBody& celestialBody);

    /**
     * @brief Writes data from the CelestialBody to a std::ostream.
     */
    friend std::ostream& operator<<(std::ostream& ostream, const CelestialBody& celestialBody);
};

}  // namespace NB

#endif
