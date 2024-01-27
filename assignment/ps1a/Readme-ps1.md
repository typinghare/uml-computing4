# PS1: Linear Feedback Shift Register (part A)

## Contact

Name: Zhuojian Chen (James)

Section: COMP 2040 P 1 203

Time to Complete: Jan 23, 2024

## Representation Explanation

In the `FibLFSR` class, the register bits are represented using an integer (`int lfsr`). This choice was driven by the efficiency and simplicity that an integer type offers for bitwise operations. The `lfsr` stores the current state of the LFSR. Each bit of this integer corresponds to a bit in the LFSR.

When I was reading the instructions, I was not sure whether the length of the seed is unchanged 16. If so, I will use `short` instead of `int`, since performing left shift operation to a short `lfsr` removes the most significant bit of it. However, if the length of the given seed is less than 16, a problem may arise: the `lfsr` variable does not store the real `lfsr` value, as the leftmost several bits are "garbage bits", which should be all zeros.

To fix the problem, I introduced two member variables in `FibLFSR`: `seed_len` and `mask`, where `seed_len` is the length of the seed string, which is also the bits of LFSR, and `mask` is an integer that the rightmost n bits are one, where `n = len`. Whenever a `step()` method is called, a left shift operation is performed on the `lfsr`, it will be performed a bitwise AND operation with `mask`, so that the left irrelevant bits are eliminated.

The core code for the `LFSR` is the following snippet from the `step()` method:

```c++
// Get the current most significant bit (leftmost bit)
int ans = lfsr >> (len - 1);

// Let the bit perform XOR operations with tabs
for (const int& tabIndex : tabIndexes) {
    ans ^= (lfsr >> tabIndex) & 1;
}
```

## Unit Tests

A discussion of what's being tested in your two additional Boost unit tests.

