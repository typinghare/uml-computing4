
// Copyright 2024 James Chen
#include <iostream>
#include "Sokoban.hpp"

/**
 * @brief Starts a Sokoban game.
 * @param size The size of the argument list.
 * @param arguments The command line arguments. This game requires one argument, which is the
 * filename of the level file to load.
 */
int main(const int size, const char* arguments[]) {
    // Check arguments
    if (size < 2) {
        std::cout << "Too few arguments! Require the filename of the level file." << std::endl;
        return 1;
    }

    const std::string level = arguments[1];
}