// Copyright 2024 James Chan
#include "FibLFSR.hpp"
#include <sstream>
#include <string>

namespace PhotoMagic {
std::array<int, 3> FibLFSR::tabIndexes = {10, 12, 13};

FibLFSR::FibLFSR(const std::string& seed) : len(seed.length()), lfsr(0) {
    // Convert the seed string into the initial LFSR
    for (const char& bit : seed) {
        lfsr = lfsr << 1 | bit - '0';
    }

    // Initialize the mask
    mask = 0;
    for (int i = 0; i < len; ++i) {
        mask = (mask << 1) | 1;
    }
}

int FibLFSR::generate(const int k) {
    int ans = 0;
    for (int i = 0; i < k; ++i) {
        ans = (ans << 1) | step();
    }

    return ans;
}

int FibLFSR::step() {
    int ans = lfsr >> (len - 1);
    for (const int& pos : tabIndexes) {
        ans ^= (lfsr >> pos) & 1;
    }

    lfsr = (lfsr << 1 | ans) & this->mask;

    return ans;
}

int FibLFSR::getLfsr() const { return lfsr; }

std::string FibLFSR::getLfsrBinaryString() const {
    std::stringstream ss;
    for (int i = static_cast<int>(len - 1); i >= 0; --i) {
        ss << (lfsr >> i & 1 ? '1' : '0');
    }

    return ss.str();
}

std::ostream& operator<<(std::ostream& os, const FibLFSR& lfsr) {
    os << lfsr.getLfsrBinaryString();

    return os;
}

}  // namespace PhotoMagic
