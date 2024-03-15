// Copyright 2024 James Chen

#ifndef UNIVERSEELAPSEDTIME_HPP
#define UNIVERSEELAPSEDTIME_HPP
#include <SFML/Graphics.hpp>

namespace NB {

class UniverseElapsedTime : virtual public sf::Drawable {
 protected:
    /**
     * @brief Constructs a UniverseElapsedTime instance.
     */
    UniverseElapsedTime();

    /**
     * @brief Applies one step; adds delta time to the elapsed time.
     * @param deltaTime The delta time in seconds.
     */
    virtual void step(double deltaTime);

    /**
     * @brief Draws the elapsed time onto the target.
     * @param target Render target to draw onto.
     * @param states Render states to use for drawing.
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    /**
     * @brief The elapsed time text font size.
     */
    static constexpr unsigned FONT_SIZE = 28;

    /**
     * @brief The x component of the  elapsed time text position.
     */
    static constexpr unsigned FONT_POSITION_X = 15;

    /**
     * @brief The y component of the  elapsed time text position.
     */
    static constexpr unsigned FONT_POSITION_Y = 10;

    /**
     * @brief The elapsed time.
     */
    double m_elapsedTime = 0.0;

    /**
     * @brief The font for the diplayed text.
     */
    sf::Font m_font;
};

}  // namespace NB

#endif
