// Copyright 2024 James Chen

#include "Universe.hpp"
#include <fstream>
#include <iostream>
#include <limits>
#include <numeric>
#include <sstream>
#include <SFML/Audio.hpp>
#include "NBodyConstant.hpp"

/**
 * Converts a double number into a string in the scientific form.
 * @param number The number to convert.
 * @return a string in the form of "x.yye?zz", where x is the integer part, yy is the fraction part,
 * ? is negative sign (optional), and zz is the exponent.
 */
std::string to_standard_scientific_string(const double& number) {
    std::ostringstream stream;
    stream << std::scientific << std::setprecision(2) << number;

    return stream.str();
}

template <typename T>
T magnitude_vector2(const sf::Vector2<T>& vector2) {
    return static_cast<T>(std::sqrt(vector2.x * vector2.x + vector2.y * vector2.y));
}

template <typename T>
sf::Vector2<T> normalize_vector2(const sf::Vector2<T>& vector2) {
    T magnitude = magnitude_vector2(vector2);
    if (magnitude == 0) {
        throw std::invalid_argument("Cannot normalize a zero vector!");
    }

    return { vector2.x / magnitude, vector2.y / magnitude };
}

namespace NB {

Universe::Universe() = default;

Universe::Universe(const std::string& filename) {
    std::ifstream ifstream{ filename };

    // Check if the file is opened successfully
    if (!ifstream.is_open()) {
        throw std::invalid_argument("Cannot open: " + filename);
    }

    ifstream >> *this;
}

int Universe::numPlanets() const { return m_numPlanets; }

double Universe::radius() const { return m_radius; }

double Universe::scale() const { return m_scale; }

void Universe::step(const double deltaTime) {
    // Calculate the unit vector pointing from one planet to another
    // unitVector[i][j] stores the unit vector from planet i to planet j
    auto unitVectorMatrix = createMatrix();
    for (int i = 0; i < m_numPlanets; ++i) {
        const auto firstPlanet = m_celestialBodyVector[i];
        for (int j = i + 1; j < m_numPlanets; ++j) {
            const auto secondPlanet = m_celestialBodyVector[j];
            const auto firstToSecondUnitVector =
                normalize_vector2((secondPlanet->positionDouble() - firstPlanet->positionDouble()));
            unitVectorMatrix[i][j] = firstToSecondUnitVector;
            unitVectorMatrix[j][i] = { -firstToSecondUnitVector.x, -firstToSecondUnitVector.y };
        }
    }

    // Cacluate the net forces between celestial bodies
    // netForceMatrix[i][j] stores the gravity from planet i to planet j
    // summation of netForceMatrix[i] is the gravity exerted on planet i
    auto netForceMatrix = createMatrix();
    for (int i = 0; i < m_numPlanets; ++i) {
        const auto firstPlanet = m_celestialBodyVector[i];
        for (int j = i + 1; j < m_numPlanets; ++j) {
            const auto secondPlanet = m_celestialBodyVector[j];
            const auto distance =
                magnitude_vector2(firstPlanet->positionDouble() - secondPlanet->positionDouble());
            const auto gravityMagnitude = GravitationalConstant * firstPlanet->massDouble() *
                                          secondPlanet->massDouble() / (distance * distance);

            netForceMatrix[i][j] = unitVectorMatrix[i][j] * gravityMagnitude;
            netForceMatrix[j][i] = unitVectorMatrix[j][i] * gravityMagnitude;
        }
    }

    // Calculate the acceleration
    // accelerationVector[i] stores the acceleration of planet i
    std::vector<sf::Vector2<double>> accelerationVector;
    accelerationVector.reserve(m_numPlanets);
    for (int i = 0; i < m_numPlanets; ++i) {
        // Find the resultant of planet i
        const auto& netForces = netForceMatrix[i];
        sf::Vector2 resultant{ 0.0, 0.0 };
        for (int j = 0; j < m_numPlanets; ++j) {
            resultant = resultant + netForces[j];
        }

        const auto planet = m_celestialBodyVector[i];
        const auto accelerationX = resultant.x / planet->massDouble();
        const auto accelerationY = resultant.y / planet->massDouble();

        accelerationVector.emplace_back(
            isnan(accelerationX) ? 0 : accelerationX, isnan(accelerationY) ? 0 : accelerationY);
    }

    // Calculate the new velocity of each planet
    for (int i = 0; i < m_numPlanets; ++i) {
        const auto planet = m_celestialBodyVector[i];
        const auto velocity = planet->velocityDouble();
        const auto acceleration = accelerationVector[i];

        planet->setVelocity(
            { velocity.x + acceleration.x * deltaTime, velocity.y + acceleration.y * deltaTime });
    }

    // Calculate the new position of each planet
    for (int i = 0; i < m_numPlanets; ++i) {
        const auto planet = m_celestialBodyVector[i];
        const auto position = planet->positionDouble();
        const auto velocity = planet->velocityDouble();

        planet->setPosition(
            { position.x + velocity.x * deltaTime, position.y + velocity.y * deltaTime });
    }

    // Update the elapsed time
    UniverseElapsedTime::step(deltaTime);
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
        static_cast<float>(WINDOW_WIDTH) / static_cast<float>(textureSize.x),
        static_cast<float>(WINDOW_HEIGHT) / static_cast<float>(textureSize.y));

    // Load and play the background music
    const auto soundBuffer{ std::make_shared<sf::SoundBuffer>() };
    const auto sound{ std::make_shared<sf::Sound>() };
    if (soundBuffer->loadFromFile(SOUND_BACKGROUND_MUSIC)) {
        sound->setBuffer(*soundBuffer);
        m_backgroundMusic.first = soundBuffer;
        m_backgroundMusic.second = sound;
        sound->setLoop(true);
        sound->play();
    }

    // Load celestial bodies' resources
    for (auto const& celestialBody : m_celestialBodyVector) {
        celestialBody->loadResources();
    }
}

void Universe::draw(sf::RenderTarget& target, const sf::RenderStates states) const {
    target.draw(*m_backgroundImage.second, states);

    auto drawCelestialBody = [&](const std::shared_ptr<CelestialBody>& celestialBody) {
        target.draw(*celestialBody, states);
    };

    std::for_each(m_celestialBodyVector.cbegin(), m_celestialBodyVector.cend(), drawCelestialBody);

    // Draw the elapsed time
    UniverseElapsedTime::draw(target, states);
}

std::vector<std::vector<sf::Vector2<double>>> Universe::createMatrix() const {
    std::vector<std::vector<sf::Vector2<double>>> matrix;
    matrix.reserve(m_numPlanets);
    for (int i = 0; i < m_numPlanets; ++i) {
        matrix.push_back(std::vector<sf::Vector2<double>>(m_numPlanets, { 0.0, 0.0 }));
    }

    return matrix;
}

std::istream& operator>>(std::istream& istream, Universe& universe) {
    istream >> universe.m_numPlanets >> universe.m_radius;

    // Set the scale (1.1x larger, as some planets' trajectories are ecllipses)
    universe.m_scale = universe.m_radius / DOUBLE_HALF / WINDOW_WIDTH * SCALE_FACTOR;

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

}  // namespace NB
