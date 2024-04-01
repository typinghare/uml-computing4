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
     * Constructs a HirshbergEDistance instance with two input genes.
     * @param geneX The first gene string.
     * @param geneY The second gene string.
     */
    HirshbergEDistance(const std::string& geneX, const std::string& geneY);

    /**
     * @brief Calculates the optimal edit distance between the two gene strings.
     * Populates the internal matrix and returns the optimal distance.
     * @return The optimal edit distance between the two gene strings.
     */
    int optDistance() override;

    /**
     * @brief Traces the populated matrix and returns a string representing the optimal alignment
     * of the two gene strings.
     * @return A string representing the optimal alignment.
     */
    [[nodiscard]] std::string alignment() const override;

 private:
    /**
     * @brief Returns an array containing prefix costs.
     * @param geneX The first gene string.
     * @param geneY The second gene string.
     * @return An array containing prefix costs.
     */
    static std::vector<int> allYPrefixCosts(const std::string& geneX, const std::string& geneY);

    /**
     * @brief Returns an array containing suffix costs.
     * @param geneX The first gene string.
     * @param geneY The second gene string.
     * @return An array containing suffix costs.
     */
    static std::vector<int> allYSuffixCosts(const std::string& geneX, const std::string& geneY);

    /**
     * @brief Recursively aligns the gene strings using Hirschberg's algorithm.
     * @param geneX The first gene string.
     * @param geneY The second gene string.
     * @param offset The offset of the alignment.
     */
    void align(
        const std::string& geneX,
        const std::string& geneY,
        const std::pair<size_t, size_t>& offset);

    /**
     * @brief Inserts a coordinate into the arrow path.
     * @param coordinate The coordinate to insert.
     */
    void insertArrowPathCoordinate(const std::pair<size_t, size_t>& coordinate);

    /**
     * @brief Represents the arrow path.
     */
    std::vector<std::pair<size_t, size_t>> arrowPath;
};

#endif
