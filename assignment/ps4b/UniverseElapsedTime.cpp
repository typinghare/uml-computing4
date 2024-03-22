// Copyright 2024 James Chen

#include "UniverseElapsedTime.hpp"
#include <string>
#include "NBodyConstant.hpp"

namespace NB {

UniverseElapsedTime::UniverseElapsedTime() { m_font.loadFromFile(FONT_DIGITAL7); }

void UniverseElapsedTime::step(const double deltaTime) { m_elapsedTime += deltaTime; }

void UniverseElapsedTime::draw(sf::RenderTarget& target, const sf::RenderStates states) const {
    const auto seconds = static_cast<unsigned>(m_elapsedTime);
    const auto days = (seconds / SEONCDS_IN_DAY) % 365;
    const auto years = seconds / SEONCDS_IN_YEAR;
    const auto secondsStr = std::to_string(seconds);
    const auto daysStr = std::to_string(days);
    const auto yearsStr = std::to_string(years);
    std::string stringToPrint;

    if (seconds >= SEONCDS_IN_YEAR) {
        stringToPrint = yearsStr + " years " + daysStr + " days";
    } else if (seconds >= SEONCDS_IN_DAY) {
        stringToPrint = daysStr + " days";
    } else {
        stringToPrint = secondsStr + " seconds";
    }

    sf::Text text;
    text.setFont(m_font);
    text.setString(stringToPrint);
    text.setCharacterSize(FONT_SIZE);
    text.setFillColor(sf::Color::White);
    text.setPosition(FONT_POSITION_X, FONT_POSITION_Y);
    target.draw(text);
}

}  // namespace NB
