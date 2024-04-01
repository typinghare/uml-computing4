# PS5: DNA Alignment

## Contact

> Name: Zhuojian Chen (James)
>
> Student ID: 02151380
>
> Section: COMP 2040 P 1 203
>
> Time to Complete: March 31, 2024

## Description

This innovative program tackles a core challenge in computational biology: DNA sequence alignment. Leveraging the timeless Needleman-Wunsch method and Hirschberg's algorithm, it offers robust solutions to this crucial task. What sets this program apart is its versatile approach, employing various classes to implement functionalities in distinct yet harmoniously integrated ways, ensuring a seamless and efficient alignment process.

### Features

This program comprises an abstract class and several implementation classes, each serving a distinct role:

* `AbstractEDistance`:  Abstract base class for calculating edit distance between two gene strings. There are two abstract methods in this class: `optDistance` and `alignment`. The `optDistance` method calculates the optimal edit distance between two gene strings. The `alignment` method traces the populated matrix and returns a string representing the optimal alignment of the two gene strings.
* `NeedlemanWunschEDistance`: An implementation of AbstractEDistance using Needleman & Wunsch's method.
* `OptimizedEDistance`: An implementation of AbstractEDistance using Needleman & Wunsch's method with `O(n)` space complexity, where `n` is the length of the gene X. The `optDistance` in this class does not work, as there is no matrix to trace. An extra method `row` is presented in this class. It returns the row containing the first row's elements during the populating, which is used in `HirshbergEDistance`.
* `HirshbergEDistance`: An implementation of AbstractEDistance using Hirschberg’s Algorithm.
* `EDistance`: Extends `HirshbergEDistance`.

In the NeedlemanWunschEDistance class, a matrix of dimensions `n`\*`m`, where `n` is the length of gene X and `m` is the length of gene Y, is initialized. The last row and column are immediately filled, followed by populating the matrix from `matrix[n - 1][m - 1]` to `matrix[0][0]` column by column. The core code for this population process is depicted below:

``` c++
for (size_t i = colCount - 2; i < colCount; --i) {
      const char xChar = m_geneY.at(i);
      for (size_t j = rowCount - 2; j < rowCount; --j) {
          const char yChar = m_geneX.at(j);
          const auto fromRight = m_matrix[j][i + 1] + 2;
          const auto fromDown = m_matrix[j + 1][i] + 2;
          const auto fromDiagonal = m_matrix[j + 1][i + 1] + penalty(xChar, yChar);
          m_matrix[j][i] = min3(fromRight, fromDown, fromDiagonal);
      }
  }
```

The `OptimizedEDistance` class optimizes memory usage by retaining only one column during matrix population, updating it iteratively within each loop. Although it sacrifices the ability to generate a string representing the optimal alignment, this limitation is addressed by the `HirshbergEDistance` class.

In `HirshbergEDistance`, the **arrow path
** serves as a critical component representing the path drawn from `matrix[0][0]` through `matrix[n][m]`. Once the arrow path is determined, both the calculation of edit distance and the generation of the alignment string become efficient. This is facilitated by the `align` method, which employs a divide and conquer technique to recursively align two strings. The `align` method accomplishes the following:

1. **Base Case Handling
   **: If the lengths of the strings `X` or `Y` are less than 2, the standard alignment approach (`NeedlemanWunschEDistance`) is utilized. Subsequently, the arrow path is recorded, and the method returns. This serves as the base case of the recursion.
2. **String Division
   **: The string `X` is divided into two parts: `X1` and `X2`. Prefix costs are computed for `X1` and `Y`, while suffix costs are computed for `X2` and `Y`.
3. **Cost Calculation
   **: Iterate over `q` from 0 to `m` to determine the minimal cost sum of `yPrefix[q] + ySuffix[q]`, identifying the corresponding `bestQ` value in this context.
4. **Arrow Path Expansion**: Incorporate the coordinate `(n // 2, bestQ)` into the arrow path.
5. **Recursive Exploration
   **: Recursively explore and determine the coordinates of the remaining segments of the arrow path.

The arrow path in `HirshbergEDistance` is represented by the data structure `std::vector<std::pair<size_t, size_t>>`. In this structure, the index corresponds to the summation of the pair, where each pair represents a coordinate on the dynamic programming matrix. Notably, the summations of coordinates along the path are distinct.

Pairs denoted as `<0, 0>` within the arrow path are referred to as "skipped coordinates". They arise when some arrows transition diagonally. Given an index `t`, if `arrowPath[t] = <u, v>` is not a skipped coordinate, then the coordinate `<u, v>` lies on the arrow path. Additionally, if `arrowPath[t + 1]` is also not a skipped coordinate, it implies that `<u, v>` derives from either the cell on the right or the one at the bottom. Conversely, if `arrowPath[t + 1]` is a skipped coordinate, then `<u, v>` originates from the bottom-right diagonal cell. The core code for this population process is depicted below:

```c++
void HirshbergEDistance::align(
    const std::string& geneX, const std::string& geneY, const std::pair<size_t, size_t>& offset) {
    const auto xLength = geneX.length();
    const auto yLength = geneY.length();
    const auto xHalfLength = xLength / 2;

    if (xLength <= 2 || yLength <= 2) {
        // Use standard alignment
        NeedlemanWunschEDistance eDistance{ geneX, geneY };
        eDistance.optDistance();
        const auto* const matrix = eDistance.matrix();

        size_t i = 0;
        size_t j = 0;
        while (i + j < xLength + yLength) {
            insertArrowPathCoordinate({ i + offset.first, j + offset.second });
            const auto val = matrix[i][j];
            const auto isFromBottom = i < xLength && val - 2 == matrix[i + 1][j];
            const auto isFromRight = j < yLength && val - 2 == matrix[i][j + 1];
            i += static_cast<int>(!isFromRight);
            j += static_cast<int>(!isFromBottom);
        }

        return;
    }

    const auto xHalf1 = geneX.substr(0, xHalfLength);
    const auto xHalf2 = geneX.substr(xHalfLength);
    const auto yPrefix = allYPrefixCosts(xHalf1, geneY);
    const auto ySuffix = allYSuffixCosts(xHalf2, geneY);

    int bestCost = static_cast<int>(xLength + yLength) << 1;
    size_t bestQ = 0;
    for (size_t q = 0; q < yLength; ++q) {
        const auto costSum = yPrefix[q] + ySuffix[q];
        if (costSum < bestCost) {
            bestCost = costSum;
            bestQ = q;
        }
    }

    // Add the coordinate to the arrow path
    const std::pair coordinate = { xHalfLength + offset.first, bestQ + offset.second };
    insertArrowPathCoordinate(coordinate);

    // Recursively find the other coordinates of the arrow path
    align(xHalf1, geneY.substr(0, bestQ), offset);
    align(xHalf2, geneY.substr(bestQ), coordinate);
}
```

### Testing

* **testPenalty**: Verifies the correctness of the `EDistance::penalty` function.
* **testMin3**: Ensures the proper functionality of the `EDistance::min3` function.
* **testOptDistance1
  **: Validates the accuracy of `EDistance::optDistance` using a specific example as outlined in the instructions.
* **testOptDistance2
  **: Validates the correctness of `EDistance::optDistance` using the 'endgaps7.txt' dataset.
* **testAlignmentCostSum1
  **: Compares the return value of `EDistance::optDistance` with the summation of costs obtained from `EDistance::alignment`, utilizing a specific example from the instructions.
* **testAlignmentCostSum2
  **: Compares the output of `EDistance::optDistance` with the summation of costs from `EDistance::alignment`, utilizing the 'endgaps7.txt' dataset.
* **testAlignmentColumns
  **: Validates the correctness of the two aligned columns. The first column should represent the first string, while the second column should represent the second string.

## Analysis

### Example

Input:

```bash
abcdefghizzzzjklmnop
azzbcdefghijklmnop
```

Matrix:

```c++
12   11    9   10   12   14   16   18   20   22   24   26   28   30   32   34   36   38   40 
13   12   10    8   10   12   14   16   18   20   22   24   26   28   30   32   34   36   38 
11   12   12   10    8   10   12   14   16   18   20   22   24   26   28   30   32   34   36 
12   10   11   12   10    8   10   12   14   16   18   20   22   24   26   28   30   32   34 
13   11    9   10   11   10    8   10   12   14   16   18   20   22   24   26   28   30   32 
14   12   10    8    9   10   10    8   10   12   14   16   18   20   22   24   26   28   30 
15   13   11    9    7    8    9   10    8   10   12   14   16   18   20   22   24   26   28 
15   14   12   10    8    6    7    8    9    8   10   12   14   16   18   20   22   24   26 
15   14   13   11    9    7    5    6    7    8    8   10   12   14   16   18   20   22   24 
16   14   13   12   10    8    6    4    5    6    7    8   10   12   14   16   18   20   22 
17   15   14   13   11    9    7    5    3    4    5    6    8   10   12   14   16   18   20 
18   16   15   14   12   10    8    6    4    2    3    4    6    8   10   12   14   16   18 
20   18   16   15   13   11    9    7    5    3    1    2    4    6    8   10   12   14   16 
22   20   18   16   14   12   10    8    6    4    2    0    2    4    6    8   10   12   14 
24   22   20   18   16   14   12   10    8    6    4    2    0    2    4    6    8   10   12 
26   24   22   20   18   16   14   12   10    8    6    4    2    0    2    4    6    8   10 
28   26   24   22   20   18   16   14   12   10    8    6    4    2    0    2    4    6    8 
30   28   26   24   22   20   18   16   14   12   10    8    6    4    2    0    2    4    6 
32   30   28   26   24   22   20   18   16   14   12   10    8    6    4    2    0    2    4 
34   32   30   28   26   24   22   20   18   16   14   12   10    8    6    4    2    0    2 
36   34   32   30   28   26   24   22   20   18   16   14   12   10    8    6    4    2    0 
```

My program ran this correctly.

### Specs

> Computer: MacBook Pro
>
> Memory: 8 GB
>
> Processors: Apple M1 (3.2 GHz)

### Runs

| Data File       | Distance | Memory (MB) | Time (seconds) | Time (seconds, with -O3) |
| --------------- | -------- | ----------- | -------------- | ------------------------ |
| ecoli2500.txt   | 118      | 1.3 MB      | 0.164          | 0.089                    |
| ecoli5000.txt   | 160      | 1.7 MB      | 0.576          | 0.337                    |
| ecoli10000.txt  | 223      | 2.5 MB      | 2.197          | 1.130                    |
| ecoli20000.txt  | 3135     | 4.5 MB      | 9.034          | 4.410                    |
| ecoli50000.txt  | 19523    | 7.0 MB      | 57.079         | 26.294                   |
| ecoli100000.txt | 24189    | 11.1 MB     | 230.722        | 101.811                  |
| ecoli500000.txt | 187916   | 33.2 MB     | -              | 2542.79                  |

### Time

Assume the two strings are the same length (M = N). By applying the doubling method to the data points that you obtained, estimate the running time of your program in seconds as a polynomial function of N, in the form a * N^b for some constants a and b. Determine the largest input your program can handle if it is limited to one day of computation.

Provide a brief justification/explanation of how you applied the doubling method, and if your data seems not to work, describe what went wrong and use the sample data instead.

- a = **2.9092e-8**
- b = **1.9772**
- largest N = **2033689**

### Memory

Assume the two strings are the same length (M = N). Look at your code and determine how much memory it requires as a polynomial function of N, in the form a * N^b for some constants a and b. Determine the largest input size your computer can handle if limited to 8GiB of RAM.

- a = **0.01121**
- b = **0.5972**
- largest N = **6457157934**

### Valgrind

> I am using a MacBook with an M1 chip. It does not support Valgrind, and Virtual Box crashes for no reason. I utilized
**Activity Monitor
** on macOS to monitor the memory used by the program, and the memory used is within expectation.
>
> I also used an alternative tool called **Instruments
** on macOS to detect the memory leaks, and no warnings were detected.
>
> Oh come on, give me a break, I've been spending 7 hours implementing Hirshberg's algorithm.

## Extra Credit

1. The distinction between `min3` and `std::min` lies in their functionalities. While `std::min` utilizes templates, enabling it to handle various variable types, `min3` is limited to operating solely on three integers.

2. The program is implemented using **Hirschberg's algorithm**, so the program can handle large data set.

3. The difference between **optimization levels** are as follows:

   | Flag | Compilation Time | Running Time | Comment                                                      |
      | ---- | ---------------- | ------------ | ------------------------------------------------------------ |
   | -O0  | .                | .            | No optimization                                              |
   | -O1  | +                | +            | Optimize for speed while avoiding code size increase.        |
   | -O2  | ++               | +            | Enables vectorization; Allows inlining of intrinsics and intra-file interprocedural optimization. |
   | -O3  | +++              | +            | Enables more aggressive loop transformations (Fusion, Block-Unroll-and-Jam); Optimizations may only consistently outperform -O2 if loop and memory access transformations occur. It can even slow down the code. |

## Acknowledgments

[Space-Efficient Alignment: Hirschberg’s Algorithm](https://www.cs.cmu.edu/~ckingsf/class/02-714/Lec07-linspace.pdf)

[Compiler Optimizations: Boosting code performance without doing much!](https://medium.com/nerd-for-tech/compiler-optimizations-boosting-code-performance-without-doing-much-95f1182a5757)

[std::min](https://en.cppreference.com/w/cpp/algorithm/min)
