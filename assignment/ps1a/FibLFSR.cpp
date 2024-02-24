// Copyright 2024 James Chan
#include "FibLFSR.hpp"
#include <bitset>
#include <sstream>
#include <string>

namespace PhotoMagic {

FibLFSR::FibLFSR(const std::string& seed) {
    // Check if the seed is legal
    if (seed.length() != SEED_LENGTH) {
        const std::string message =
            "The length of seed should be " + std::to_string(SEED_LENGTH);
        throw std::invalid_argument(message);
    }
    for (const char& bit : seed) {
        if (bit != '0' && bit != '1') {
            const std::string message =
                "Each character in the seed should either be '0' or '1'";
            throw std::invalid_argument(message);
        }
    }

    // Convert the seed string into the initial LFSR
    lfsr = std::bitset<SEED_LENGTH>{ seed };
}

int FibLFSR::generate(const int k) {
    int ans = 0;
    for (int i = 0; i < k; ++i) {
        ans = (ans << 1) | step();
    }

    return ans;
}

int FibLFSR::step() {
    // Get the current most significant bit (leftmost bit)
    int ans = lfsr[SEED_LENGTH - 1];

    // Let the bit perform XOR operations with tabs
    for (const int& tabIndex : tabIndexes) {
        ans ^= lfsr[tabIndex];
    }

    // Update lfsr
    lfsr <<= 1;
    lfsr.set(0, ans);

    return ans;
}

std::string FibLFSR::getLfsrBinaryString() const { return lfsr.to_string(); }

std::ostream& operator<<(std::ostream& os, const FibLFSR& lfsr) {
    os << lfsr.getLfsrBinaryString();

    return os;
}

}  // namespace PhotoMagic
