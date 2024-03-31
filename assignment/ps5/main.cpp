// Copyright 2024 James Chen

#include <iostream>
#include <SFML/System.hpp>
#include "EDistance.hpp"
#include "NeedlemanWunschEDistance.hpp"
#include "OptimizedEDistance.hpp"

/**
 * @brief Finds the edit distance of two genes.
 */
int main() {
    const sf::Clock clock;

    // Read the two genes and find the edit distance
    std::string geneX;
    std::string geneY;
    std::cin >> geneX >> geneY;
    EDistance eDistance{ geneX, geneY };
    const auto editDistance = eDistance.optDistance();

    // Print the edit distance and alignment data
    std::cout << "Edit distance: " << editDistance << std::endl;
    std::cout << eDistance.alignment() << std::endl;

    // Print the elapsed time in seconds
    const auto elapsedTime = clock.getElapsedTime();
    std::cout << "Execution time is: " << elapsedTime.asSeconds() << " seconds" << std::endl;

    return 0;
}
