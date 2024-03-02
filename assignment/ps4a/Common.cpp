// Copyright 2024 James Chen

#include "Common.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

std::string to_standard_scientific_string(const double& number) {
    std::ostringstream stream;
    stream << std::scientific << std::setprecision(2) << number;

    return stream.str();
}
