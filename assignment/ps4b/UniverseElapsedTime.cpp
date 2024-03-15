// Copyright 2024 James Chen

#include "UniverseElapsedTime.hpp"
#include <string>
#include "NBodyConstant.hpp"

namespace NB {

UniverseElapsedTime::UniverseElapsedTime() { m_font.loadFromFile(FONT_DIGITAL7); }

void UniverseElapsedTime::step(const double deltaTime) { m_elapsedTime += deltaTime; }

void UniverseElapsedTime::draw(sf::RenderTarget& target, const sf::RenderStates states) const {
    const auto seconds = static_cast<unsigned>(m_elapsedTime);
    const std::string stringToPrint = std::to_string(seconds) + " seconds";

    sf::Text text;
    text.setFont(m_font);
    text.setString(stringToPrint);
    text.setCharacterSize(FONT_SIZE);
    text.setFillColor(sf::Color::White);
    text.setPosition(FONT_POSITION_X, FONT_POSITION_Y);
    target.draw(text);
}

}  // namespace NB
