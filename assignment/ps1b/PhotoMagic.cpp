// Copyright 2024 James Chen
#include "PhotoMagic.hpp"
#include <string>

namespace PhotoMagic {

void transform(sf::Image& image, FibLFSR* fibLfsr) {}

SpriteTexture::SpriteTexture(const sf::Image& image) {
    texture = std::make_shared<sf::Texture>();
    texture->loadFromImage(image);
    sprite = std::make_shared<sf::Sprite>(*texture);
}

void displayImages(sf::Image& inputImage, sf::Image& outputImage) {
    static constexpr unsigned IMAGE_GAP = 50;
    static constexpr unsigned WINDOW_FPS = 60;
    static constexpr auto WINDOW_TITLE =
        "Left is the input image | Right is the output image";

    // Get the size of two images
    const auto inputImageSize = inputImage.getSize();
    const auto outputImageSize = outputImage.getSize();

    // Caluclate the window size
    const unsigned windowWidth{ inputImageSize.x + outputImageSize.x +
                                IMAGE_GAP };
    const unsigned windowHeight{ std::max(inputImageSize.y,
                                          outputImageSize.y) };
    const sf::VideoMode windowSize{ windowWidth, windowHeight };

    // Create a window
    sf::RenderWindow window(windowSize, WINDOW_TITLE);
    window.setFramerateLimit(WINDOW_FPS);
    window.clear(sf::Color::White);

    const SpriteTexture inputSpriteTexture(inputImage);
    const SpriteTexture outputSpriteTexture(outputImage);

    // Set the position for the output sprite
    const auto inputWidth = inputSpriteTexture.texture->getSize().x;
    outputSpriteTexture.sprite->setPosition(
        static_cast<float>(inputWidth) + IMAGE_GAP, 0);

    // Render and display the two images
    window.clear();
    window.draw(*inputSpriteTexture.sprite);
    window.draw(*outputSpriteTexture.sprite);
    window.display();

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }
}

}  // namespace PhotoMagic
