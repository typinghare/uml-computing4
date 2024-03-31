// Copyright 2024 James Chen

#ifndef EDISTANCE_HPP
#define EDISTANCE_HPP

#include <string>
#include "HirshbergEDistance.hpp"

/**
 * @brief An implementation of AbstractEDistance using Hirschberg’s Algorithm.
 */
class EDistance final : public HirshbergEDistance {
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
};

#endif
