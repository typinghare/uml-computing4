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
    NeedlemanWunschEDistance eDistance1{ geneX, geneY };
    HirshbergEDistance eDistance2{ geneX, geneY };
    const auto editDistance1 = eDistance1.optDistance();
    const auto editDistance2 = eDistance2.optDistance();

    // Print the edit distance
    std::cout << "Edit distance: " << editDistance1 << std::endl;
    std::cout << "Edit distance: " << editDistance2 << std::endl;

    // Print the alignment data
    // std::cout << eDistance1.alignment() << std::endl;
    std::cout << eDistance2.alignment() << std::endl;

    // Print the elapsed time in seconds
    const auto elapsedTime = clock.getElapsedTime();
    std::cout << "Execution time is: " << elapsedTime.asSeconds() << " seconds" << std::endl;

    return 0;
}
