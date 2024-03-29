// Copyright 2024 James Chen

#ifndef EDISTANCE_HPP
#define EDISTANCE_HPP

#include <string>

/**
 * @brief Represents the Edit Distance algorithm.
 * Edit Distance measures the similarity between two strings by calculating the minimum number
 * of operations required to transform one string into the other, where the operations can be
 * insertion, deletion, or substitution of a single character.
 */
class EDistance {
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
    EDistance(std::string geneX, std::string geneY);

    /**
     * @brief Calculates the optimal edit distance between the two gene strings. Populates the
     * internal matrix and returns the optimal distance (from the [0][0] cell of the matrix when
     * done).
     * @return The optimal edit distance between the two gene strings.
     */
    int optDistance();

    /**
     * @brief Traces the populated matrix and returns a string representing the optimal
     * alignment of the two gene strings.
     * @return A string representing the optimal alignment.
     */
    [[nodiscard]] std::string alignment() const;

 private:
    /**
     * @brief Calculates the optimal edit distance between the two gene strings using the
     * Needleman-Wunsch method.
     * @return The optimal edit distance between the two gene strings.
     */
    int poplulateMatrixNeedlemanWunsch();

    /**
     * @brief Calculates the optimal edit distance between the two gene strings using the
     * Hirschberg's algorithm.
     * @return The optimal edit distance between the two gene strings.
     */
    int populateMatrixHischbergAlgorithm();

    /**
     * @brief Traces the populated matrix and returns a string representing the optimal
     * alignment of the two gene strings. This function is used when Needleman-Wunsch method is used
     * to populate the matrix.
     * @return A string representing the optimal alignment.
     */
    [[nodiscard]] std::string alignmentNeedlemanWunsch() const;

    /**
     * @brief Prints the matrix. This function is used for debugging.
     */
    void printMatrix() const;

    /**
     * @brief The first gene string.
     */
    const std::string m_geneX;

    /**
     * @brief The second gene string.
     */
    const std::string m_geneY;

    /**
     * @brief The matrix used to trace the edit distances (Needleman-Wunsch method).
     */
    int** m_matrix;

    /**
     * @brief (Hirschberg's algorithm).
     */
    int* opt;
};

#endif
