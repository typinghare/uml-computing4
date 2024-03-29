// Copyright 2024 James Chen

#include "EDistance.hpp"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <utility>

int EDistance::penalty(const char& num1, const char& num2) { return num1 == num2 ? 0 : 1; }

int EDistance::min3(const int& a, const int& b, const int& c) {
    return a > b ? std::min(b, c) : std::min(a, c);
}

EDistance::EDistance(std::string geneX, std::string geneY) :
    m_geneX(std::move(geneX)), m_geneY(std::move(geneY)), m_matrix(nullptr), opt(nullptr) {}

int EDistance::optDistance() { return poplulateMatrixNeedlemanWunsch(); }

std::string EDistance::alignment() const { return alignmentNeedlemanWunsch(); }

int EDistance::poplulateMatrixNeedlemanWunsch() {
    // Initialize the matrix
    const size_t rowCount = m_geneX.length() + 1;
    const size_t colCount = m_geneY.length() + 1;
    m_matrix = new int*[rowCount];
    for (int i = 0; i < rowCount; ++i) {
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

int EDistance::populateMatrixHischbergAlgorithm() {
    // Intialize the optimal array
    opt = new int[m_geneX.length() + 1];

    return 0;
}

std::string EDistance::alignmentNeedlemanWunsch() const {
    static constexpr auto GAP_CHAR = '-';
    std::stringstream stringstream;
    const size_t rowCount = m_geneX.length() + 1;
    const size_t colCount = m_geneY.length() + 1;

    size_t i = 0;
    size_t j = 0;
    while (i < rowCount - 1 && j < colCount - 1) {
        const auto val = m_matrix[i][j];
        const auto xChar = m_geneX.at(i);
        const auto yChar = m_geneY.at(j);
        if (val - 2 == m_matrix[i + 1][j]) {
            // From bottom
            stringstream << xChar << " " << GAP_CHAR << " " << 2;
            i++;
        } else if (val - 2 == m_matrix[i][j + 1]) {
            // From right
            stringstream << GAP_CHAR << " " << yChar << " " << 2;
            j++;
        } else {
            // From diagonal (bottom-right)
            stringstream << xChar << " " << yChar << " " << penalty(xChar, yChar);
            i++;
            j++;
        }
        stringstream << std::endl;
    }

    return stringstream.str();
}

void EDistance::printMatrix() const {
    for (size_t row = 0; row < m_geneX.length() + 1; ++row) {
        for (size_t col = 0; col < m_geneY.length() + 1; ++col) {
            std::cout << std::setw(4) << m_matrix[row][col] << " ";
        }
        std::cout << std::endl;
    }
}
