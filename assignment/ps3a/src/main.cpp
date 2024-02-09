#include "Sokoban.hpp"

int main() {
    SB::Sokoban sokoban;

    // Create a window
    sf::RenderWindow window(sf::VideoMode(100, 100), "Sokoban");
    window.setFramerateLimit(60);

    // Game loop
    sf::Clock clock;
    while (window.isOpen()) {
        const int dt = clock.restart().asMilliseconds();

        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                break;
            }
        }

        sokoban.update(dt);

        window.clear();
        window.draw(sokoban);
        window.display();
    }
}
