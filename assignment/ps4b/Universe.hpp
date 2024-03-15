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
#include "UniverseElapsedTime.hpp"

namespace NB {

class CelestialBody;

class Universe final : public UniverseElapsedTime {
 public:
    /**
     * Constructs a Universe.
     */
    Universe();

    /**
     * @brief Constructs a Universe from a file.
     * @param filename The filename to load Universe data from.
     */
    explicit Universe(const std::string& filename);

    /**
     * @brief Loads resources necessary for the Universe (background image and music).
     */
    void loadResources();

    /**
     * @brief Returns the number of planets in this Universe.
     * @return Number of planets.
     */
    [[nodiscard]] int numPlanets() const;

    /**
     * @brief Returns the radius of this Universe.
     * @return Radius of the Universe.
     */
    [[nodiscard]] double radius() const;

    /**
     * @brief Returns the scale of the Universe.
     * @return Scale of the Universe.
     */
    [[nodiscard]] double scale() const;

    /**
     * Simulates one step.
     * @param deltaTime Delta time in seconds.
     */
    void step(double deltaTime) override;

    /**
     * @brief Reads the number of planets and the radius of this Universe from input stream.
     * @param istream Input stream to read from.
     * @param universe Universe object to store the data.
     * @return Reference to the input stream.
     */
    friend std::istream& operator>>(std::istream& istream, Universe& universe);

    /**
     * @brief Writes the number of planets and the radius of this Universe to output stream.
     * @param ostream Output stream to write to.
     * @param universe Universe object to retrieve the data from.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& ostream, const Universe& universe);

    /**
     * @brief Accesses the CelestialBody at the specified index.
     * @param index Index of the CelestialBody to access.
     * @return Reference to the CelestialBody.
     */
    CelestialBody& operator[](const std::size_t& index) const;

 protected:
    /**
     * @brief Draws the Universe onto the target.
     * @param target Render target to draw onto.
     * @param states Render states to use for drawing.
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    /**
     * @brief Creates a matrix, in which each element is a double vector.
     */
    std::vector<std::vector<sf::Vector2<double>>> createMatrix() const;

    /**
     * @brief Number of planets in this Universe.
     */
    int m_numPlanets = 0;

    /**
     * @brief Radius of this Universe.
     */
    double m_radius = 0.0;

    /**
     * @brief Ratio of the Universe diameter to the width of the window.
     */
    double m_scale = 1.0;

    /**
     * @brief Vector of CelestialBodies in this Universe.
     */
    std::vector<std::shared_ptr<CelestialBody>> m_celestialBodyVector;

    /**
     * @brief Background image of this Universe.
     */
    std::pair<std::shared_ptr<sf::Texture>, std::shared_ptr<sf::Sprite>> m_backgroundImage;

    /**
     * @brief Background music of this Universe.
     */
    std::pair<std::shared_ptr<sf::SoundBuffer>, std::shared_ptr<sf::Sound>> m_backgroundMusic;
};

}  // namespace NB

#endif
