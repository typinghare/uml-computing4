// Copyright 2024 James Chen

#include "CelestialBody.hpp"
#include <iostream>
#include <string>

#include "Common.hpp"
#include "NBodyConstant.hpp"

CelestialBody::CelestialBody(Universe* universePtr) : m_universePtr(universePtr) {}

sf::Vector2f CelestialBody::getPosition() const {
    return { static_cast<float>(m_position.x), static_cast<float>(m_position.y) };
}

sf::Vector2f CelestialBody::getVelocity() const {
    return { static_cast<float>(m_velocity.x), static_cast<float>(m_velocity.y) };
}

double CelestialBody::getMass() const { return m_mass; }

Universe* CelestialBody::getUniverse() const { return m_universePtr; }

void CelestialBody::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    const auto universeRadius = m_universePtr->getRadius();
    const auto sprite = m_image.second;
    const auto universeScale = m_universePtr->getScale();
    const sf::Vector2f realPosition{
        static_cast<float>((universeRadius + this->m_position.x) / universeScale),
        static_cast<float>((universeRadius - this->m_position.y) / universeScale),
    };
    sprite->setPosition(realPosition);

    target.draw(*sprite);
}

std::istream& operator>>(std::istream& istream, CelestialBody& celestialBody) {
    istream >> celestialBody.m_position.x >> celestialBody.m_position.y >>
        celestialBody.m_velocity.x >> celestialBody.m_velocity.y >> celestialBody.m_mass;

    // Read and load the image file
    istream >> celestialBody.m_image_filename;
    celestialBody.m_image.first = std::make_shared<sf::Texture>();
    celestialBody.m_image.second = std::make_shared<sf::Sprite>();
    celestialBody.m_image.first->loadFromFile(ASSETS_IMAGE_DIR / celestialBody.m_image_filename);
    celestialBody.m_image.second->setTexture(*celestialBody.m_image.first);

    return istream;
}

std::ostream& operator<<(std::ostream& ostream, const CelestialBody& celestialBody) {
    const auto positionX = to_standard_scientific_string(celestialBody.m_position.x);
    const auto positionY = to_standard_scientific_string(celestialBody.m_position.y);
    const auto velocityX = to_standard_scientific_string(celestialBody.m_velocity.x);
    const auto velocityY = to_standard_scientific_string(celestialBody.m_velocity.y);
    const auto mass = to_standard_scientific_string(celestialBody.m_mass);

    ostream << std::fixed << std::setprecision(2) << std::scientific << positionX << " "
            << positionY << " " << velocityX << " " << velocityY << " " << mass << " "
            << celestialBody.m_image_filename;

    return ostream;
}
