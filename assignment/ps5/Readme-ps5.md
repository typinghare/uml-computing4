# PS5: DNA Alignment

## Contact

> Name: Zhuojian Chen (James)
>
> Student ID: 02151380
>
> Section: COMP 2040 P 1 203
>
> Time to Complete: March 12, 2024

## Description

Explain what the project does

### Features

Explain how you did the actual alignment including the data structures used.

### Testing

Describe what the unit tests you wrote check for and why you picked them.

## Analysis

### Example

Do one additional test case by hand. It should be constructed in such a way that you know the correct output before running your program on it, and it should be a "corner case" that helps check if your program handles all special situations correctly.

Please list:

- a copy of the test case input
- the expected test case output
- whether your program ran correctly on it or not
- optionally, any other remarks

### Specs

Your Computer
Memory: 8 GB
Processors: Apple M1 (3.2 GHz)

### Runs

Fill in the table with the results of running your code on both your and your partner's computers.

| data file       | distance | memory (mb) | time (seconds) | partner time |
|-----------------|----------|-------------|----------------|--------------|
| ecoli2500.txt   |          |             |                |              |
| ecoli5000.txt   |          |             |                |              |
| ecoli10000.txt  |          |             |                |              |
| ecoli20000.txt  |          |             |                |              |
| ecoli50000.txt  |          |             |                |              |
| ecoli100000.txt |          |             |                |              |

Here is an example from another computer for some of the files.

| data file      | distance | time (s) |
|----------------|----------|----------|
| ecoli2500.txt  | 118      | 0.171    |
| ecoli5000.txt  | 160      | 0.529    |
| ecoli7000.txt  | 194      | 0.990    |
| ecoli10000.txt | 223      | 1.972    |
| ecoli20000.txt | 3135     | 7.730    |

### Time

Assume the two strings are the same length (M = N). By applying the doubling method to the data points that you obtained, estimate the running time of youu program in seconds as a polynomial function of N, in the form a * N^b for some constants a and b. Determine the largest input your program can handle if it is limited to one day of computation.

Provide a brief justification/explanation of how you applied the doubling method, and if you data seems not to work, describe what went wrong and use the sample data instead.

- a =
- b =
- largest N =

### Memory

Assume the two strings are the same length (M = N). Look at your code and determine how much memory it requires as a polynomial function of N, in the form a * N^b for some constants a and b. Determine the largest input size your computer can handle if limited to 8GiB of RAM.

- a =
- b =
- largest N =

### Valgrind

Run valgrind and list any errors you see. Identify whether the memory usage reported by valgrind almost matches the calculations in the previous section.

## Pair Programming

If you worked with a partner, do you have any remarks on the pair programming method? E.g., how many times did you switch, what are the tradeoffs of driving vs. navigating, etc.?

## Extra Credit

Anything special you did. This is required to earn bonus points.

## Acknowledgements

[Space-Efficient Alignment: Hirschberg’s Algorithm](https://www.cs.cmu.edu/~ckingsf/class/02-714/Lec07-linspace.pdf)

