// Copyright 2024 James Chan
#include "FibLFSR.hpp"
#include <sstream>
#include <string>

namespace PhotoMagic {
std::array<int, 3> FibLFSR::taps = {10, 12, 13};

FibLFSR::FibLFSR(const std::string& seed) : seed_len(seed.length()) {
    // Convert the seed string to an integer (member property)
    this->seed = 0;
    for (const char& bit : seed) {
        this->seed = this->seed << 1 | bit - '0';
    }

    // Save the initial seed
    this->init_seed = this->seed;

    // Initialize the mask
    this->mask = 0;
    for (int i = 0; i < seed_len; ++i) {
        this->mask = (this->mask << 1) | 1;
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
    int ans = seed >> (seed_len - 1);
    for (const int& pos : taps) {
        ans ^= (seed >> pos) & 1;
    }

    seed = (seed << 1 | ans) & this->mask;

    return ans;
}

int FibLFSR::getSeed() const { return seed; }

std::string FibLFSR::getSeedBinaryString() const {
    std::stringstream ss;
    for (int i = static_cast<int>(seed_len - 1); i >= 0; --i) {
        ss << (seed >> i & 1 ? '1' : '0');
    }

    return ss.str();
}

}  // namespace PhotoMagic
