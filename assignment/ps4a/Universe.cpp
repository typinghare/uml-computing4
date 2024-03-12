// Copyright 2024 James Chen

#include "Universe.hpp"
#include <fstream>
#include <iostream>
#include <limits>
#include "CelestialBody.hpp"
#include "Common.hpp"
#include "NBodyConstant.hpp"

namespace NB {

Universe::Universe() = default;

Universe::Universe(const std::string& filename) : Universe() {
    std::fstream fstream{ filename };

    // Check if the file is opened successfully
    if (!fstream.is_open()) {
        throw std::invalid_argument("Cannot open: " + filename);
    }

    fstream >> *this;
}

void Universe::loadResources() {
    // Load the background image
    m_backgroundImage.first = { std::make_shared<sf::Texture>() };
    m_backgroundImage.second = { std::make_shared<sf::Sprite>() };
    m_backgroundImage.first->loadFromFile(IMAGE_BACKGRROUND);
    m_backgroundImage.second->setTexture(*m_backgroundImage.first);

    // Rescale the background image so that the image fits the window
    const auto backgroundTexture = m_backgroundImage.first;
    const auto backgroundSprite = m_backgroundImage.second;
    const auto textureSize = backgroundTexture->getSize();
    backgroundSprite->setScale(
        static_cast<float>(WINDOW_WIDTH) / textureSize.x,
        static_cast<float>(WINDOW_HEIGHT) / textureSize.y);

    // Load and play the background music
    const auto soundBuffer{ std::make_shared<sf::SoundBuffer>() };
    const auto sound{ std::make_shared<sf::Sound>() };
    if (soundBuffer->loadFromFile(SOUND_2001)) {
        sound->setBuffer(*soundBuffer);
        m_backgroundMusic.first = soundBuffer;
        m_backgroundMusic.second = sound;

        sound->play();
    }

    // Load celestial bodies' images
    for (auto const& celestialBody : m_celestialBodyVector) {
        celestialBody->loadResource();
    }
}

int Universe::numPlanets() const { return m_numPlanets; }

double Universe::radius() const { return m_radius; }

double Universe::scale() const { return m_scale; }

std::istream& operator>>(std::istream& istream, Universe& universe) {
    istream >> universe.m_numPlanets >> universe.m_radius;

    // Set the scale (1.1x larger, as some planets' trajectories are ecllipses)
    universe.m_scale = universe.m_radius * 2.0 / WINDOW_WIDTH * 1.1;

    if (istream.fail()) {
        throw std::runtime_error("Invalid input");
    }

    istream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Celestial bodies
    for (int i = 0; i < universe.m_numPlanets; ++i) {
        auto celestialBody = std::make_shared<CelestialBody>(&universe);
        universe.m_celestialBodyVector.push_back(celestialBody);
        istream >> *celestialBody;
    }

    return istream;
}

std::ostream& operator<<(std::ostream& ostream, const Universe& universe) {
    const auto radius = to_standard_scientific_string(universe.m_radius);
    ostream << universe.m_numPlanets << std::endl << radius << std::endl;

    // Output celestial bodies
    const auto numPlanets = static_cast<size_t>(universe.m_numPlanets);
    for (size_t i = 0; i < universe.m_celestialBodyVector.size(); ++i) {
        const auto celestialBody = universe.m_celestialBodyVector[i];
        ostream << *universe.m_celestialBodyVector[i];
        if (i != numPlanets - 1) {
            ostream << std::endl;
        }
    }

    return ostream;
}

CelestialBody& Universe::operator[](const std::size_t& index) const {
    return *m_celestialBodyVector.at(index);
}

void Universe::draw(sf::RenderTarget& target, const sf::RenderStates states) const {
    // Set the background for the target
    target.draw(*m_backgroundImage.second);

    auto drawCelestialBody = [&](const std::shared_ptr<CelestialBody>& celestialBody) {
        celestialBody->draw(target, states);
    };

    std::for_each(m_celestialBodyVector.cbegin(), m_celestialBodyVector.cend(), drawCelestialBody);
}

}  // namespace NB
