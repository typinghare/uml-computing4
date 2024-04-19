// Copyright 2024 James Chen

#include <string>
#include "PhotoMagic.hpp"

/**
 * @brief Takes three arguments: an input picture filename, an output picture
 * filename, and a binary password (the initial LFSR seed). It should display
 * the transformed picture on the screen. Note that since I implement a function
 * that can convert a alphanumeric string into a seed string, the third arugment
 * can be a alphanumeric password.
 * @param size The size of the argument list.
 * @param arguments The command line arguments.
 */
int main(const int size, const char* arguments[]) {
    if (size < 4) {
        std::cout << "Not enough arguments!" << std::endl;

        return -1;
    }

    const std::string inputFilename{ arguments[1] };
    const std::string outputFilename{ arguments[2] };
    const std::string seed{ PhotoMagic::convertPasswordToSeed(arguments[3]) };

    // Create images
    sf::Image originalImage;
    sf::Image processedImage;
    if (!originalImage.loadFromFile(inputFilename)) {
        return -1;
    }
    if (!processedImage.loadFromFile(inputFilename)) {
        return -1;
    }

    // Create a FibLFSR instance with the initial seed
    PhotoMagic::FibLFSR fibLfsr{ seed };

    // Transform the image using the FibLFSR object
    transform(processedImage, &fibLfsr);

    // Output the photo to the hard disk (output filename)
    if (processedImage.saveToFile(outputFilename)) {
        std::cout << "Successfully output file to: " << outputFilename
                  << std::endl;
    } else {
        std::cout << "Fail to output file to: " << outputFilename << std::endl;
    }

    // Display the original image and the processed image using SFML
    PhotoMagic::displayImages(originalImage, processedImage);

    return 0;
}
