// Copyright 2024 James Chen
#include "EDistance.hpp"
#include <string>
#include "AbstractEDistance.hpp"

int EDistance::penalty(const char& num1, const char& num2) {
    return AbstractEDistance::penalty(num1, num2);
}

int EDistance::min3(const int& a, const int& b, const int& c) {
    return AbstractEDistance::min3(a, b, c);
}

EDistance::EDistance(const std::string& geneX, const std::string& geneY) :
    HirshbergEDistance(geneX, geneY) {}
