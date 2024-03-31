// Copyright 2024 James Chen

#ifndef NEEDLEMANWUNSCHEDISTANCE_HPP
#define NEEDLEMANWUNSCHEDISTANCE_HPP

#include <string>
#include "AbstractEDistance.hpp"

/**
 * @brief An implementation of AbstractEDistance using Needleman & Wunsch's method.
 */
class NeedlemanWunschEDistance final : AbstractEDistance {
 public:
    /**
     * Constructs an NeedlemanWunschEDistance instance with two input genes.
     * @param geneX The first gene string.
     * @param geneY The second gene string.
     */
    NeedlemanWunschEDistance(const std::string& geneX, const std::string& geneY);

    /**
     * @brief Destructor for AbstractEDistance.
     */
    ~NeedlemanWunschEDistance() override;

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

    /**
     * @brief Return the matrix used to trace the edit distances.
     */
    [[nodiscard]] int** matrix() const;

 private:
    /**
     * @brief Prints the matrix. This function is used for debugging.
     */
    void printMatrix() const;

    /**
     * @brief The matrix used to trace the edit distances.
     */
    int** m_matrix;
};

#endif
