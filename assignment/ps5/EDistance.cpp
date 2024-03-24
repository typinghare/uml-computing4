// Copyright 2024 James Chen

#include "EDistance.hpp"
#include <cmath>
#include "Constant.hpp"

int EDistance::penalty(const char& a, const char& b) { return a == b ? 0 : 1; }

int EDistance::penalty(const Nucleobase& a, const Nucleobase& b) {
    return penalty(static_cast<char>(a), static_cast<char>(b));
}

int EDistance::min3(const int& a, const int& b, const int& c) {
    return a > b ? std::min(b, c) : std::min(a, c);
}

EDistance::EDistance(const std::string& geneX, const std::string& geneY) {}

int EDistance::optDistance() { return 0; }

std::string EDistance::alignment() const { return ""; }
