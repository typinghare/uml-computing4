// Copyright 2024 James Chan
#ifndef ASSIGNMENT_PS1_FIBLFSR_HPP_
#define ASSIGNMENT_PS1_FIBLFSR_HPP_

#include <iostream>
#include <string>

namespace PhotoMagic {
/**
 * \brief This class implemented Fibonacci LFSR algorithm.
 */
class FibLFSR {
    /**
     * \brief In this homework, taps are fixed 10, 12, and 13
     */
    static std::array<int, 3> taps;

 public:
    /**
     * \brief Creates LFSR with the given seed and tap.
     * \param seed The initial seed.
     */
    explicit FibLFSR(const std::string& seed);

    /**
     * \brief Simulates one step and return the new bit.
     */
    int step();

    /**
     * \brief Simulates k steps and return k-bit integer.
     * \param k The number of steps.
     */
    int generate(int k);

    /**
     * \brief Returns the dynamic seed.
     */
    [[nodiscard]] int getSeed() const;

    /**
     * \brief Returns the binary string form of seed.
     */
    [[nodiscard]] std::string getSeedBinaryString() const;

 private:
    // The length of the seed
    const size_t seed_len;

    // The initial seed;
    int init_seed;

    // The dynamic seed
    int seed;

    // The mask ([1] * seed_len)
    int mask;
};

std::ostream& operator<<(std::ostream&, const FibLFSR& lfsr);

}  // namespace PhotoMagic

#endif  // ASSIGNMENT_PS1_FIBLFSR_HPP_
