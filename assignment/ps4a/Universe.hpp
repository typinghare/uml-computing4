// Copyright 2024 James Chen

#ifndef UNIVERSE_HPP
#define UNIVERSE_HPP

#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "CelestialBody.hpp"

namespace NB {

class CelestialBody;

class Universe final : public sf::Drawable {
 public:
    /**
     * @brief Creates a universe.
     */
    Universe();

    /**
     * @brief Creates a universe from a file.
     * @param filename The name of the file.
     */
    explicit Universe(const std::string& filename);

    /**
     * @brief Creates and returns a celestial body.
     */
    std::shared_ptr<CelestialBody> createCelestialBody();

    /**
     * @brief Returns the numer of planets in this universe.
     */
    [[nodiscard]] int numPlanets() const;

    /**
     * @brief Returns the radius of this universe.
     */
    [[nodiscard]] double radius() const;

    /**
     * @brief Gets the scale of the universe.
     */
    [[nodiscard]] double scale() const;

    /**
     * Prints the number of planets and the radius of this universe.
     */
    friend std::istream& operator>>(std::istream& istream, Universe& universe);

    /**
     * Prints the number of planets and the radius of this universe.
     */
    friend std::ostream& operator<<(std::ostream& ostream, const Universe& universe);

    /**
     * Returns the celestial body at specified index.
     * @param index The index of the celestial body to retrieve.
     */
    CelestialBody& operator[](const std::size_t& index) const;

 protected:
    /**
     * Draws the universe onto the target.
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    /**
     * @brief The number of planets.
     */
    int m_numPlanets = 0;

    /**
     * @brief The radius of this universe.
     */
    double m_radius = 0.0;

    /**
     * @brief The ratio of the universe diameter to the width of the window.
     */
    double m_scale = 1.0;

    /**
     * @brief A vector of celestial bodies in this universe.
     */
    std::vector<std::shared_ptr<CelestialBody>> m_celestialBodyVector;

    /**
     * @brief The background image.
     */
    std::pair<std::shared_ptr<sf::Texture>, std::shared_ptr<sf::Sprite>> m_backgroundImage;

    /**
     * @brief The background music.
     */
    std::pair<std::shared_ptr<sf::SoundBuffer>, std::shared_ptr<sf::Sound>> m_backgroundMusic;
};

}  // namespace NB

#endif
