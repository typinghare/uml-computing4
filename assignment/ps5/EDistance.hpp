// Copyright 2024 James Chen

#ifndef EDISTANCE_HPP
#define EDISTANCE_HPP

#include <string>

#include "Constant.hpp"

/**
 * @brief Represents "Edit Distance".
 */
class EDistance {
 public:
    /**
     * @brief Calculates the penalty for aligning characters a and b.
     * @param a The first character.
     * @param b The second character.
     * @return The penalty value, which is either 0 or 1.
     */
    static int penalty(const char& a, const char& b);

    /**
     * @brief Calculates the penalty for aligning nucleobases a and b.
     * @param a The first character.
     * @param b The second character.
     * @return The penalty value, which is either 0 or 1.
     */
    static int penalty(const Nucleobase& a, const Nucleobase& b);

    /**
     * @brief Returns the minimum of three integer values.
     * @param a The first integer.
     * @param b The second integer.
     * @param c The third integer.
     * @return The minimum value among the three integers.
     */
    static int min3(const int& a, const int& b, const int& c);

    /**
     * Constructs a EDistance instance.
     * @param geneX
     * @param geneY
     */
    EDistance(const std::string& geneX, const std::string& geneY);

    /**
     * @brief Populates the matrix based on having the two strings, and returns the optimal
     * distance (from the [0][0] cell of the matrix when done).
     */
    int optDistance();

    /**
     * @brief Traces the matrix and returns a string that can be printed to display the actual
     * alignment. In general, this will be a multi-line string.
     */
    [[nodiscard]] std::string alignment() const;
};

#endif
