// Copyright 2024 James Chen

#include "AbstractEDistance.hpp"

#include <algorithm>
#include <utility>

int AbstractEDistance::penalty(const char& num1, const char& num2) { return num1 == num2 ? 0 : 1; }

int AbstractEDistance::min3(const int& a, const int& b, const int& c) {
    return a > b ? std::min(b, c) : std::min(a, c);
}

AbstractEDistance::AbstractEDistance(std::string geneX, std::string geneY) :
    m_geneX(std::move(geneX)), m_geneY(std::move(geneY)) {}

AbstractEDistance::~AbstractEDistance() = default;
