// Copyright 2024 James Chen

#ifndef UNIVERSE_HPP
#define UNIVERSE_HPP

#include <memory>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "CelestialBody.hpp"

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
    [[nodiscard]] int getNumPlanets() const;

    /**
     * @brief Returns the radius of this universe.
     */
    [[nodiscard]] double getRadius() const;

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
     * @brief A vector of celestial bodies in this universe.
     */
    std::vector<std::shared_ptr<CelestialBody>> celestialBodyVector;
};

#endif
