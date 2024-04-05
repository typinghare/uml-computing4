// Copyright 2024 James Chen

#ifndef WORDWRITER_HPP
#define WORDWRITER_HPP

#include <string>
#include <vector>
#include "SymbolTable.hpp"

class WordWriter {
 public:
    /**
     * @brief Constructs a RandWriter object with a Markov model of order k. Creates a Markov model
     * of order k from the provided text. The order k represents the number of preceding characters
     * considered for predicting the next character.
     * @param text The text used to create the Markov model.
     * @param k The order of the Markov model.
     */
    WordWriter(const std::string& text, size_t k);

    /**
     * @brief Generates a string of specified length using the Markov chain. Generates a string of
     * length L characters by simulating a trajectory through the Markov chain learned from the
     * input text. The initial k characters of the generated string are provided as the argument
     * kgram.
     * @param kgram The initial k characters of the generated string.
     * @param L The length of the generated string.
     * @return The generated string.
     * @throw std::invalid_argument If the length of kgram is not equal to the order of the Markov
     * model.
     */
    std::string generate(const std::vector<std::string>& kgram, size_t L) const;

    /**
     * @brief Returns a random character followed by a specified k-gram .
     * @param kgram The k-gram.
     * @return a random character followed by a specified k-gram.
     */
    std::string kRand(const std::vector<std::string>& kgram) const;

    /**
     * @brief Overloading of "<<" for this class. Outputs the symbol table, including kgrams, k+1
     * grams and their frequencies.
     */
    friend std::ostream& operator<<(std::ostream& os, const WordWriter& wordWriter);

 private:
    /**
     * Returns a random number between 1 (included) and the given total frequency (excluded).
     * @param totalFreq The total frequency of all characters.
     * @return A random number between 1 (included) and the given total frequency (excluded).
     */
    [[nodiscard]] static int getRandomNumber(int totalFreq);

    /**
     * @brief The order of the Markov model.
     */
    size_t order_k_;

    SymbolTable<std::string, std::string> symbol_table_;
};

#endif
