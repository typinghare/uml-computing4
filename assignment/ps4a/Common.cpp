// Copyright 2024 James Chen

#include "Common.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace NB {

std::string to_standard_scientific_string(const double& number) {
    std::ostringstream stream;
    stream << std::scientific << std::setprecision(2) << number;
    std::string result = stream.str();

    // Check if the exponent part contains a '+' sign
    // Remove the "+" if found
    // const size_t pos = result.find('e');
    // if (pos != std::string::npos && result[pos + 1] == '+') {
    //     result.erase(pos + 1, 1);
    // }

    return result;
}

}  // namespace NB
