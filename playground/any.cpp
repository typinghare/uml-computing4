#include <bitset>
#include <iostream>

// Function to print the binary representation of a float
void printFloatBinary(float f) {
    // Interpret the float as an integer
    const auto* const intPtr = reinterpret_cast<int*>(&f);

    // Get the integer value
    int integerValue = *intPtr;

    // Convert the integer value to binary string
    std::bitset<sizeof(float) * 8> binary(integerValue);

    // Print the binary string
    std::cout << binary << std::endl;
}

int main() {
    float floatValue = 1 / 0.F;
    float b2 =  floatValue;

    std::cout << "Binary representation of " << b2 << ":\n";
    printFloatBinary(b2);

    return 0;
}
