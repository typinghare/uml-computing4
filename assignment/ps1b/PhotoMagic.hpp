// Copyright 2024 James Chen
#ifndef PHOTOMAGIC_H
#define PHOTOMAGIC_H

#include <algorithm>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "FibLFSR.hpp"

namespace PhotoMagic {

class FibLFSR;

/**
 * @brief Transforms image using FibLFSR. For each pixel (x, y) in row-major
 * order, extra the red, green, and blue components of the color (each component
 * is an integer between 0 and 255). Then XOR the red component with a newly
 * generated 8-bit integer. Do the same for the green (using another new 8-bit
 * integer), and finally the blue. Create a new color using the result of the
 * XOR operations, and set the pixel in the new picture to that color.
 * @param image The image to transform.
 * @param fibLfsr The FibLFSR object to use.
 */
void transform(sf::Image& image, FibLFSR* fibLfsr);

/**
 * @brief Converts an alphanumeric password to a LFSR initial seed.
 * @param password The alphanumeric password to convert.
 */
std::string convertPasswordToSeed(const std::string& password);

/**
 * @brief A struct containing two shared pointers: texture and sprite.
 */
struct SpriteTexture {
    std::shared_ptr<sf::Texture> texture;
    std::shared_ptr<sf::Sprite> sprite;

    /**
     * @brief Creates a SpriteTexture struct with an image.
     * @param image The image to use.
     */
    explicit SpriteTexture(const sf::Image& image);
};

/**
 * @brief Displays two images with SFML.
 * @param inputImage The input (original) image to display.
 * @param outputImage The output (processed) image to display.
 */
void displayImages(sf::Image& inputImage, sf::Image& outputImage);

}  // namespace PhotoMagic

#endif
