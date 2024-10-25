#include <SFML/Graphics.hpp>
#include "penta.hpp"

int main() {
    auto window =
        sf::RenderWindow{ sf::VideoMode(CANVAS_SIZE, CANVAS_SIZE), "Penta" };
    window.setFramerateLimit(60);

    window.clear(sf::Color::White);
    constexpr auto center = CANVAS_SIZE / 2;
    pentaflake(window, 4, { { center, center }, 10, 0 });
    window.display();

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }

    return 0;
}
