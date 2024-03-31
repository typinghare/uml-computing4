// Copyright 2024 James Chen

#ifndef HIRSHBERGEDISTANCE_H
#define HIRSHBERGEDISTANCE_H

#include <string>
#include <utility>
#include <vector>
#include "AbstractEDistance.hpp"

/**
 * @brief An implementation of AbstractEDistance using Hirschberg’s Algorithm.
 */
class HirshbergEDistance : public AbstractEDistance {
 public:
    /**
     * Constructs an HirshbergEDistance instance with two input genes.
     * @param geneX The first gene string.
     * @param geneY The second gene string.
     */
    HirshbergEDistance(const std::string& geneX, const std::string& geneY);

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

 private:
    /**
     * @brief Returns an array.
     * @param geneX
     * @param geneY
     */
    static std::vector<int> allYPrefixCosts(const std::string& geneX, const std::string& geneY);

    /**
     * @brief Returns an array.
     * @param geneX
     * @param geneY
     */
    static std::vector<int> allYSuffixCosts(const std::string& geneX, const std::string& geneY);

    /**
     *
     * @param geneX
     * @param geneY
     * @param offset
     */
    void align(
        const std::string& geneX,
        const std::string& geneY,
        const std::pair<size_t, size_t>& offset);

    /**
     * Inserts a coordiante into the arrow path.
     * @param coordinate The coordinate to insert.
     */
    void insertArrowPathCoordinate(const std::pair<size_t, size_t>& coordinate);

    /**
     * @brief Arrow path.
     */
    std::vector<std::pair<size_t, size_t>> arrowPath;
};

#endif
