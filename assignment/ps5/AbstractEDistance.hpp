// Copyright 2024 James Chen

#ifndef ABSTRACTEDISTANCE_HPP
#define ABSTRACTEDISTANCE_HPP

#include <string>

/**
 * @brief Abstract base class for calculating edit distance between two gene strings. Subclasses
 * should populate an internal matrix to compute the edit distance efficiently. The gene strings to
 * be compared are provided during construction.
 */
class AbstractEDistance {
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
     * @brief Calculates the optimal edit distance between two gene strings.
     * Populates the internal matrix and returns the optimal distance (from the [0][0] cell
     * of the matrix when done).
     * @return The optimal edit distance between the two gene strings.
     */
    virtual int optDistance() = 0;

    /**
     * @brief Traces the populated matrix and returns a string representing the optimal
     * alignment of the two gene strings.
     * @return A string representing the optimal alignment.
     */
    [[nodiscard]] virtual std::string alignment() const = 0;

    /**
     * @brief Destructor for AbstractEDistance.
     */
    virtual ~AbstractEDistance();

 protected:
    /**
     * @brief Constructs an AbstractEDistance instance with two input genes.
     * @param geneX The first gene string.
     * @param geneY The second gene string.
     */
    AbstractEDistance(std::string geneX, std::string geneY);

    /**
     * @brief The first gene string.
     */
    const std::string m_geneX;

    /**
     * @brief The second gene string.
     */
    const std::string m_geneY;
};

#endif
