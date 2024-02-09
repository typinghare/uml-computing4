#include "Sokoban.hpp"

namespace SB {

Sokoban::Sokoban() : m_width(0), m_height(0) {}

int Sokoban::width() const { return m_width; }

int Sokoban::height() const { return m_height; }

sf::Vector2f Sokoban::playerLoc() const { return player.getPosition(); }

void Sokoban::movePlayer(const Direction& direction) {}

bool Sokoban::isWon() { return false; }

void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states) const {}



}  // namespace SB
