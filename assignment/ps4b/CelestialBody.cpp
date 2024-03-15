// Copyright 2024 James Chen

#include "CelestialBody.hpp"
#include <iostream>
#include <sstream>
#include <boost/algorithm/string.hpp>

#include "NBodyConstant.hpp"

namespace NB {

CelestialBody::CelestialBody(Universe* universePtr) : m_universePtr(universePtr) {}

sf::Vector2f CelestialBody::position() const {
    return {
        static_cast<float>(m_position.x),
        static_cast<float>(m_position.y),
    };
}

sf::Vector2f CelestialBody::velocity() const {
    return {
        static_cast<float>(m_velocity.x),
        static_cast<float>(m_velocity.y),
    };
}

float CelestialBody::mass() const { return static_cast<float>(m_mass); }

sf::Vector2<double> CelestialBody::positionDouble() const { return m_position; }

sf::Vector2<double> CelestialBody::velocityDouble() const { return m_velocity; }

double CelestialBody::massDouble() const { return m_mass; }

void CelestialBody::setPosition(const sf::Vector2<double> newPosition) { m_position = newPosition; }

void CelestialBody::setVelocity(const sf::Vector2<double> newVelocity) { m_velocity = newVelocity; }

void CelestialBody::loadResources() {
    // Load the image file
    m_image.first = std::make_shared<sf::Texture>();
    m_image.second = std::make_shared<sf::Sprite>();
    m_image.first->loadFromFile(ASSETS_IMAGE_DIR / m_image_filename);
    m_image.second->setTexture(*m_image.first);
}

void CelestialBody::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    const auto universeRadius = m_universePtr->radius();
    const auto universeScale = m_universePtr->scale();
    const sf::Vector2f realPosition{
        static_cast<float>((universeRadius + this->m_position.x) / universeScale),
        static_cast<float>((universeRadius - this->m_position.y) / universeScale),
    };
    m_image.second->setPosition(realPosition);

    target.draw(*m_image.second, states);
}

std::istream& operator>>(std::istream& istream, CelestialBody& celestialBody) {
    // Skip the empty lines
    while (celestialBody.m_line.empty() && !istream.eof()) {
        getline(istream, celestialBody.m_line);
    }

    // Read data
    std::stringstream stringstream(celestialBody.m_line);
    stringstream >> celestialBody.m_position.x >> celestialBody.m_position.y >>
        celestialBody.m_velocity.x >> celestialBody.m_velocity.y >> celestialBody.m_mass >>
        celestialBody.m_image_filename;

    // Throw an rumtime error if failing to read data
    if (stringstream.fail()) {
        throw std::runtime_error("Invalid input: " + celestialBody.m_line);
    }

    return istream;
}

std::ostream& operator<<(std::ostream& ostream, const CelestialBody& celestialBody) {
    // Directly output the raw line
    ostream << celestialBody.m_line;

    return ostream;
}

}  // namespace NB
