// Copyright 2024 James Chen

#include "OptimizedEDistance.hpp"

OptimizedEDistance::OptimizedEDistance(const std::string& geneX, const std::string& geneY) :
    AbstractEDistance(geneX, geneY) {
    m_column.resize(geneX.length() + 1, 0);
    m_row.resize(geneY.length() + 1, 0);
}

int OptimizedEDistance::optDistance() {
    // Initialize column
    const size_t rowCount = m_geneX.length() + 1;
    const size_t colCount = m_geneY.length() + 1;
    for (size_t i = rowCount - 1; i < rowCount; --i) {
        m_column[i] = static_cast<int>((rowCount - 1 - i)) << 1;
    }

    m_row[colCount - 1] = m_column[0];

    // Update the column as if populating the matrix using Needlman-Wusch method
    for (size_t i = colCount - 2; i < colCount; --i) {
        const char xChar = m_geneY.at(i);
        int reservedDiagnoal = m_column[rowCount - 1];
        m_column[rowCount - 1] += 2;
        for (size_t j = rowCount - 2; j < rowCount; --j) {
            const char yChar = m_geneX.at(j);
            const auto fromRight = m_column[j] + 2;
            const auto fromDown = m_column[j + 1] + 2;
            const auto fromDiagonal = reservedDiagnoal + penalty(xChar, yChar);
            reservedDiagnoal = m_column[j];
            m_column[j] = min3(fromRight, fromDown, fromDiagonal);
        }

        // Record the last row element
        m_row[i] = m_column[0];
    }

    return m_column[0];
}

std::string OptimizedEDistance::alignment() const { throw std::exception(); }

std::vector<int> OptimizedEDistance::row() const { return m_row; }
