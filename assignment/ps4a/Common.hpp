// Copyright 2024 James Chen

#ifndef COMMON_HPP
#define COMMON_HPP

#include <string>

namespace NB {

/**
 * Converts a double number into a string in the scientific form.
 * @param number The number to convert.
 * @return a string in the form of "x.yye?zz", where x is the integer part, yy is the fraction part,
 * ? is negative sign, and zz is the exponent.
 */
std::string to_standard_scientific_string(const double& number);

}  // namespace NB

#endif
