# PS1: Linear Feedback Shift Register (part A)

## Contact

Name: Zhuojian Chen (James)

Section: COMP 2040 P 1 203

Time to Complete: Jan 27, 2024

## Representation Explanation

When I first did this assignment, I used `int` type to represent the register bits. However, later when I checked out a YouTube video associated with `LFSR`, and I found that `std::bitset` is a better choice as representation. Therefore, I refactored my code on Jan 27, 2024.

According to `cppreference.com`, [std::bitset](https://en.cppreference.com/w/cpp/utility/bitset) represents a fixed-size sequence of N bits. Bitwise operators are overridden in this class, and therefore it can be applied to bitwise operations as if a number.

Moreover, it provides a constructor that takes a binary string as well as a `to_string()` method to convert itself into a printable binary string. These utility functions greatly reduced the amount of code when I refactored my code.

The core code of the `FibLFSR` class is the `step()` method. With the help of `std::bitset` class, the code becomes more concise and readable:

~~~c++
// Get the current most significant bit (leftmost bit)
int ans = lfsr[SEED_LENGTH - 1];

// Let the bit perform XOR operations with tabs
for (const int& tabIndex : tabIndexes) {
    ans ^= lfsr[tabIndex];
}

// Update lfsr
lfsr <<= 1;
lfsr.set(0, ans);
~~~

## Unit Tests

A discussion of what's being tested in your two additional Boost unit tests.

> According to **_What to turn in_** section in the PDF file, it says "two additional Boost unit tests", so I just wrote two tests.

### 1

The first unit test is designed to evaluate the functionality of the overridden "<<" operator. This operator, once overridden, is responsible for outputting a string representation of the Linear Feedback Shift Register (LFSR) in a readable binary format to the specified ostream.

If the LFSR object is not modified, the output string should be equal to the seed string, therefore

~~~c++
const std::string initialLFSR = "0110110001101100";
const FibLFSR l(initialLFSR);
std::stringstream ss;
ss << l;
BOOST_REQUIRE_EQUAL(ss.str(), initialLFSR);
~~~

### 2

The second unit test further evaluates the overridden "<<" operator. In this test, the operator is used to generate an output string after nine iterations of the LFSR. The expected state of the LFSR for comparison is determined through manual calculation.

~~~c++
const std::string initialLFSR = "0110110001101100";
const std::string expectedLFSRAfterGenerate = "1101100001100110";
FibLFSR l(initialLFSR);
l.generate(9);

std::stringstream ss;
ss << l;
BOOST_REQUIRE_EQUAL(ss.str(), expectedLFSRAfterGenerate);
~~~