// Copyright 2024 James Chen

#include "CelestialBody.hpp"
#include <iostream>

CelestialBody::CelestialBody(Universe* universePtr) : m_universePtr(universePtr) {}

sf::Vector2f CelestialBody::getPosition() const {
    return { static_cast<float>(m_position.x), static_cast<float>(m_position.y) };
}

sf::Vector2f CelestialBody::getVelocity() const {
    return { static_cast<float>(m_velocity.x), static_cast<float>(m_velocity.y) };
}

double CelestialBody::getMass() const { return m_mass; }

Universe* CelestialBody::getUniverse() const { return m_universePtr; }

void CelestialBody::draw(sf::RenderTarget& target, sf::RenderStates states) const {}

std::istream& operator>>(std::istream& istream, CelestialBody& celestialBody) {
    istream >> celestialBody.m_position.x >> celestialBody.m_position.y >>
        celestialBody.m_velocity.x >> celestialBody.m_velocity.y >> celestialBody.m_mass;

    return istream;
}

std::ostream& operator<<(std::ostream& ostream, const CelestialBody& celestialBody) {
    ostream << celestialBody.m_position.x << celestialBody.m_position.y
            << celestialBody.m_velocity.x << celestialBody.m_velocity.y << celestialBody.m_mass;

    return ostream;
}
