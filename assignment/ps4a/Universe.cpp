// Copyright 2024 James Chen

#include "Universe.hpp"
#include <fstream>
#include <iostream>
#include "CelestialBody.hpp"

void Universe::draw(sf::RenderTarget& target, sf::RenderStates states) const {}

Universe::Universe() = default;

Universe::Universe(const std::string& filename) {
    std::fstream fstream{ filename };

    // Check if the file opened successfully
    if (!fstream.is_open()) {
        throw new std::invalid_argument("Cannot open: " + filename);
    }

    // The first line is the number of planets and the radius of the universe
    fstream >> *this;
    fstream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (int i = 0; i < m_numPlanets; ++i) {
        fstream >> *createCelestialBody();
        fstream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::shared_ptr<CelestialBody> Universe::createCelestialBody() {
    auto celestialBody = std::make_shared<CelestialBody>(this);
    celestialBodyVector.push_back(celestialBody);

    return celestialBody;
}

int Universe::getNumPlanets() const { return m_numPlanets; }

double Universe::getRadius() const { return m_radius; }

std::istream& operator>>(std::istream& istream, Universe& universe) {
    istream >> universe.m_numPlanets >> universe.m_radius;

    return istream;
}

std::ostream& operator<<(std::ostream& ostream, const Universe& universe) {
    ostream << universe.m_numPlanets << universe.m_radius;

    return ostream;
}

CelestialBody& Universe::operator[](const std::size_t& index) const {
    return *celestialBodyVector.at(index);
}
