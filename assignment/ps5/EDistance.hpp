// Copyright 2024 James Chen

#ifndef EDISTANCE_HPP
#define EDISTANCE_HPP

#include <string>
#include "AbstractEDistance.hpp"

/**
 * @brief An implementation of AbstractEDistance using Hirschberg’s Algorithm.
 */
class EDistance final : AbstractEDistance {
 public:
    /**
     * @brief Calculates the penalty for aligning characters 'a' and 'b'.
     * @param num1 The first character.
     * @param num2 The second character.
     * @return The penalty value, which is 0 if the characters are identical, and 1 otherwise.
     */
    static int penalty(const char& num1, const char& num2);

    /**
     * @brief Returns the minimum of three integer values.
     * @param a The first integer.
     * @param b The second integer.
     * @param c The third integer.
     * @return The minimum value among the three integers.
     */
    static int min3(const int& a, const int& b, const int& c);

    /**
     * Constructs an EDistance instance with two input genes.
     * @param geneX The first gene string.
     * @param geneY The second gene string.
     */
    EDistance(const std::string& geneX, const std::string& geneY);

    /**
     * @brief Calculates the optimal edit distance between the two gene strings. Populates the
     * internal matrix and returns the optimal distance (from the [0][0] cell of the matrix when
     * done).
     * @return The optimal edit distance between the two gene strings.
     */
    int optDistance() override;

    /**
     * @brief Traces the populated matrix and returns a string representing the optimal
     * alignment of the two gene strings.
     * @return A string representing the optimal alignment.
     */
    [[nodiscard]] std::string alignment() const override;
};

#endif
