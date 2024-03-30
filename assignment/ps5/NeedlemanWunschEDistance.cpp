// Copyright 2024 James Chen

#include "NeedlemanWunschEDistance.hpp"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

NeedlemanWunschEDistance::NeedlemanWunschEDistance(
    const std::string& geneX, const std::string& geneY) :
    AbstractEDistance(geneX, geneY), m_matrix(nullptr) {}

int NeedlemanWunschEDistance::optDistance() {
    // Initialize the matrix
    const size_t rowCount = m_geneX.length() + 1;
    const size_t colCount = m_geneY.length() + 1;
    m_matrix = new int*[rowCount];
    for (size_t i = 0; i < rowCount; ++i) {
        m_matrix[i] = new int[colCount]{};
    }

    // Filling the last row and last column
    auto* const lastRow = m_matrix[rowCount - 1];
    for (size_t i = colCount - 1; i < colCount; --i) {
        lastRow[i] = static_cast<int>((colCount - 1 - i)) << 1;
    }
    for (size_t i = rowCount - 1; i < rowCount; --i) {
        m_matrix[i][colCount - 1] = static_cast<int>((rowCount - 1 - i)) << 1;
    }

    // Populate the matrix column by column
    for (size_t i = colCount - 2; i < colCount; --i) {
        const char xChar = m_geneY.at(i);
        for (size_t j = rowCount - 2; j < rowCount; --j) {
            const char yChar = m_geneX.at(j);
            const auto fromRight = m_matrix[j][i + 1] + 2;
            const auto fromDown = m_matrix[j + 1][i] + 2;
            const auto fromDiagonal = m_matrix[j + 1][i + 1] + penalty(xChar, yChar);
            m_matrix[j][i] = min3(fromRight, fromDown, fromDiagonal);
        }
    }

    return m_matrix[0][0];
}

std::string NeedlemanWunschEDistance::alignment() const {
    static constexpr auto CHAR_GAP = '-';
    static constexpr auto CHAR_SPACE = ' ';

    std::stringstream stringstream;
    const size_t maxRowIndex = m_geneX.length();
    const size_t maxColIndex = m_geneY.length();
    const size_t maxIndexSum = maxRowIndex + maxColIndex;

    size_t i = 0;
    size_t j = 0;
    while (i + j < maxIndexSum) {
        const auto val = m_matrix[i][j];
        const auto xChar = i < maxRowIndex ? m_geneX.at(i) : CHAR_GAP;
        const auto yChar = j < maxColIndex ? m_geneY.at(j) : CHAR_GAP;
        if (i < maxRowIndex && val - 2 == m_matrix[i + 1][j]) {
            // From bottom
            stringstream << xChar << CHAR_SPACE << CHAR_GAP << CHAR_SPACE << 2;
            i++;
        } else if (j < maxColIndex && val - 2 == m_matrix[i][j + 1]) {
            // From right
            stringstream << CHAR_GAP << CHAR_SPACE << yChar << CHAR_SPACE << 2;
            j++;
        } else {
            // From diagonal (bottom-right)
            stringstream << xChar << CHAR_SPACE << yChar << CHAR_SPACE << penalty(xChar, yChar);
            i++;
            j++;
        }
        stringstream << std::endl;
    }

    return stringstream.str();
}

void NeedlemanWunschEDistance::printMatrix() const {
    for (size_t row = 0; row < m_geneX.length() + 1; ++row) {
        for (size_t col = 0; col < m_geneY.length() + 1; ++col) {
            std::cout << std::setw(4) << m_matrix[row][col] << " ";
        }
        std::cout << std::endl;
    }
}
