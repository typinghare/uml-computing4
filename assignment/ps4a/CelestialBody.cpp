// Copyright 2024 James Chen

#include "CelestialBody.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <boost/algorithm/string.hpp>
#include "Common.hpp"
#include "NBodyConstant.hpp"

namespace NB {

CelestialBody::CelestialBody(Universe* universePtr) : m_universePtr(universePtr) {}

sf::Vector2f CelestialBody::position() const {
    return { static_cast<float>(m_position.x), static_cast<float>(m_position.y) };
}

sf::Vector2f CelestialBody::velocity() const {
    return { static_cast<float>(m_velocity.x), static_cast<float>(m_velocity.y) };
}

float CelestialBody::mass() const { return static_cast<float>(m_mass); }

void CelestialBody::loadResource() {
    // Load the image file
    m_image.first = std::make_shared<sf::Texture>();
    m_image.second = std::make_shared<sf::Sprite>();
    m_image.first->loadFromFile(ASSETS_IMAGE_DIR / m_image_filename);
    m_image.second->setTexture(*m_image.first);
}

Universe* CelestialBody::universe() const { return m_universePtr; }

void CelestialBody::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    const auto universeRadius = m_universePtr->radius();
    const auto sprite = m_image.second;
    const auto universeScale = m_universePtr->scale();
    const sf::Vector2f realPosition{
        static_cast<float>((universeRadius + this->m_position.x) / universeScale),
        static_cast<float>((universeRadius - this->m_position.y) / universeScale),
    };
    sprite->setPosition(realPosition);

    target.draw(*sprite);
}

std::istream& operator>>(std::istream& istream, CelestialBody& celestialBody) {
    std::string line;

    // Skip blank lines
    while (line.empty() && !istream.eof()) {
        getline(istream, line);
        boost::trim(line);
    }

    std::stringstream stringstream(line);
    stringstream >> celestialBody.m_position.x >> celestialBody.m_position.y >>
        celestialBody.m_velocity.x >> celestialBody.m_velocity.y >> celestialBody.m_mass >>
        celestialBody.m_image_filename;

    if (stringstream.fail()) {
        throw std::runtime_error("Invalid input: " + line);
    }

    return istream;
}

std::ostream& operator<<(std::ostream& ostream, const CelestialBody& celestialBody) {
    const auto position = celestialBody.position();
    const auto velocity = celestialBody.velocity();
    ostream << position.x << " " << position.y << " " << velocity.x << " " << velocity.y << " "
            << celestialBody.mass() << " " << celestialBody.m_image_filename;

    return ostream;
}

}  // namespace NB
