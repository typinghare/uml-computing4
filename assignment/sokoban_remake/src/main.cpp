#include <fstream>
#include <SFML/Window.hpp>
#include "Sokoban.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Invalid number of arguments." << std::endl;
        return EXIT_FAILURE;
    }

    // Create a Sokoban game and read the level file
    auto sokoban = SB::Sokoban();
    auto inputStream = std::ifstream(argv[1]);
    inputStream >> sokoban;

    // Output the map
    std::cout << sokoban << std::endl;

    auto windowVideoMode =
        sf::VideoMode{ sokoban.width() * SB::TILE_SIZE, sokoban.height() * SB::TILE_SIZE };
    auto window = sf::RenderWindow(windowVideoMode, "Sokoban Remake");
    window.setFramerateLimit(60);

    // Game loop
    while (window.isOpen()) {
        auto event = sf::Event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::W) {
                    sokoban.movePlayer(SB::Direction::Up);
                } else if (event.key.code == sf::Keyboard::S) {
                    sokoban.movePlayer(SB::Direction::Down);
                } else if (event.key.code == sf::Keyboard::A) {
                    sokoban.movePlayer(SB::Direction::Left);
                } else if (event.key.code == sf::Keyboard::D) {
                    sokoban.movePlayer(SB::Direction::Right);
                } else if (event.key.code == sf::Keyboard::R) {
                    // Reset the game
                    sokoban.reset();
                }
            }
        }

        window.clear(sf::Color::White);
        window.draw(sokoban);
        window.display();
    }

    return 0;
}
