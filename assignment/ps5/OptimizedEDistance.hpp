// Copyright 2024 James Chen

#ifndef OPTIMIZEDEDISTANCE_H
#define OPTIMIZEDEDISTANCE_H

#include <string>
#include <vector>
#include "AbstractEDistance.hpp"

/**
 * @brief An implementation of AbstractEDistance using Needleman & Wunsch's method with O(n)
 * space complexity, where n is the length of the gene X.
 */
class OptimizedEDistance final : AbstractEDistance {
 public:
    /**
     * Constructs an NeedlemanWunschEDistance instance with two input genes.
     * @param geneX The first gene string.
     * @param geneY The second gene string.
     */
    OptimizedEDistance(const std::string& geneX, const std::string& geneY);

    /**
     * @brief Calculates the optimal edit distance between the two gene strings.
     * @return The optimal edit distance between the two gene strings.
     */
    int optDistance() override;

    /**
     * @brief Since no matrix is maintained, backtracking the alignment path is not feasible,
     *        hence this method is not implemented.
     * @throws std::exception Always throws an exception.
     */
    [[nodiscard]] std::string alignment() const override;

    /**
     * @brief Returns the row array containing the first row's elements during the populating.
     */
    [[nodiscard]] std::vector<int> row() const;

 private:
    /**
     * @brief The column vector used for populating the virtual matrix.
     */
    std::vector<int> m_column;

    /**
     * @brief The row vector containing the first row's elements during the populating.
     */
    std::vector<int> m_row;
};

#endif
