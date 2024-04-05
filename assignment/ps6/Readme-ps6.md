# PS6: RandWriter

## Contact
> Name: Zhuojian Chen (James)
>
> Student ID: 02151380
>
> Section: COMP 2040 P 1 203
>
> Time to Complete: March 31, 2024


## Description
This program serves as a random text generator utilizing the Markov model. It operates by accepting two parameters: the order "k" and the desired length of the generated text. Additionally, it necessitates training data input. The program then proceeds to construct a Markov model based on this training data, subsequently producing text of the specified length.

### Features

First of all, I've significantly revamped this project through an aggressive refactor. The key enhancement lies in the creation of the `SymbolTable`, a template class designed to accommodate two distinct generics. This essential component functions as a repository for k-grams (also refers to as "symbol") along with their associated subsequent characters (also refers to as "token") and frequencies. By implementing the class as a template, I've ensured its versatility, enabling it to be utilized seamlessly by both `RandWriter` and `WordWriter`.

```c++
// In RandWriter
SymbolTable<std::string, char> symbol_table_;

// In WordWriter
SymbolTable<std::string, std::string> symbol_table_;
```

Secondly, I leveraged `<random>` library to generate pesudo-random indexes between 1 and `totalFreq`:

```c++
int RandWriter::getRandomNumber(const int totalFreq) {
    static std::random_device randomDevice;
    static std::mt19937 gen(randomDevice());

    if (totalFreq <= 0) {
        return 0;
    }

    std::uniform_int_distribution distribution(1, totalFreq);
    return distribution(gen);
}

```

With this useful function, `kRand()` can be easily implemented:

```c++
char RandWriter::kRand(const std::string& kgram) {
    const auto totalFrequency = symbol_table_.frequencyOf(kgram);
    const auto randomIndex = getRandomNumber(totalFrequency);
    const auto frequencyTable = symbol_table_.frequencyMapOf(kgram);

    int cumulative_frequency = 0;
    for (const auto& [c, frequency] : frequencyTable) {
        cumulative_frequency += frequency;
        if (cumulative_frequency >= randomIndex) {
            return c;
        }
    }

    return '\0';
}
```

There weren't interesting things happen during the development. I spent a lot of time creating a novel structure to store the frequencies but ended up finding it useless. That wasn't interesting.

### Testing

* `testFreq1`: Checks if `RandWriter::freq(const std::string&)` works correctly.
* `testFreq2`: Checks if `RandWriter::freq(const std::string&, char)` works correctly.
* `testFreq3`: Checks if `RandWriter::freq(const std::string&)` works correctly. It should return 0 if the provided k-gram is not presented in the text.
* `testFre4`:  Checks if `RandWriter::freq(const std::string&, char)` works correctly. It should return 0 if the provided k-gram is not presented in the text or the frequency of a character is 0.
* `testWrongKgram1`: Checks if `RandWriter::freq(const std::string&)` throws an exception when the provided k-gram does not appear in the original text.
* `testWrongKgram2`: Checks if `RandWriter::freq(const std::string&, char)` throws an exception when the provided k-gram does not appear in the original text.
* `testOrderKFail`: Checks if `RandWriter` constructor throws an exception when the provided `k` is greater than the length of the text.
* `testKRand` Checks if `RandWriter::kRand()` works correctly. If a character x is the only successor of a k-gram y in the text, then this function shuold always return x when y is given.
* `testGenerate`: Checks if `RandWriter::generate()` works correctly: (1) The length of the generated text should be equal to the given length, and (2) the first k characters should be equal to the first k-gram.
* `testKRandDistribution`:  Checks if `RandWriter::kRand()` follows a correct distribution. The `input-17.txt` is used to test, the probability of `g` after k-gram `ga` is 0.8. Iteratively call `kRand()` 10000 times, and check if the actual probability of the appearance of `g` is close to 0.8 (tolerance is 10%).

### Lambda

In `SymbolTable` defines a `traverse` function:

```c++
/**
 * Traverses through the symbol table, invoking provided callbacks for symbol and token
 * information.
 * @param symbolCallback A callback function accepting a symbol and its total frequency;
 * @param tokenCallback A callback function accepting a token and its frequency;
 */
void traverse(
    std::function<void(S, int)> symbolCallback,
    std::function<void(T, int)> tokenCallback
) const;
```

This function is extremely useful when printing the whole symbol table:

```c++
// This can be found in `RandWriter.cpp`, line 64
std::ostream& operator<<(std::ostream& os, const RandWriter& randWriter) {
    static const std::string INDENT = "--- ";

    randWriter.symbol_table_.traverse(
        [&](auto kgram, auto totalFreq) { os << kgram << ": " << totalFreq << std::endl; },
        [&](auto c, auto freq) { os << INDENT << c << ": " << freq << std::endl; });

    return os;
}
```

The output of an example symbol table is as follows:

```bash
aa: 2
--- a: 1
--- g: 1
gg: 3
--- g: 1
--- a: 1
--- c: 1
cg: 1
--- a: 1
gc: 1
--- g: 1
ag: 5
--- g: 2
--- a: 3
ga: 5
--- g: 4
--- a: 1
```

### Extra Credit
1. I implemented `WordWriter` based on `SymbolTable`. You can run the following command to test it:

   ```bash
   # Use romeo.txt
   make run-word-romeo
   
   # Use tomsawyer.txt
   make run-word-tomsawyer
   
   # I didn't submit the text files, so make sure you copy and paste the them to the root directory before you test
   ```

## Acknowledgements
[Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)

[std::unordered_map](https://cplusplus.com/reference/unordered_map/unordered_map/)

