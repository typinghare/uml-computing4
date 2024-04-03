// Copyright 2024 James Chen

#ifndef RANDWRITTEN_H
#define RANDWRITTEN_H

#include <array>
#include <string>
#include <unordered_map>
#include "FrequencyStore.hpp"

/**
 * @brief A class for generating text using a Markov model. This class provides functionalities to
 * create and utilize a Markov model of order k from a given text, allowing the generation of new
 * text based on the learned patterns.
 */
class RandWriter {
 public:
    /**
     * @brief Constructs a RandWriter object with a Markov model of order k. Creates a Markov model
     * of order k from the provided text. The order k represents the number of preceding characters
     * considered for predicting the next character.
     * @param text The text used to create the Markov model.
     * @param k The order of the Markov model.
     */
    RandWriter(const std::string& text, size_t k);

    /**
     * @brief Returns the order of the Markov model.
     * @return The order of the Markov model.
     */
    [[nodiscard]] size_t orderK() const;

    /**
     * @brief Returns the number of occurrences of a specific k-gram in the text.
     * @param kgram The k-gram to search for.
     * @return The frequency of the k-gram in the text.
     * @throw std::invalid_argument If the length of kgram is not equal to the order of the Markov
     * model.
     */
    [[nodiscard]] int freq(const std::string& kgram) const;

    /**
     * @brief Returns the number of times a character follows a specific k-gram
     * in the text.
     * @param kgram The k-gram preceding the character.
     * @param c The character to check for.
     * @return The frequency of character c following the k-gram.
     * @throw std::invalid_argument If the length of kgram is not equal to the order of the Markov
     * model.
     */
    [[nodiscard]] int freq(const std::string& kgram, char c) const;

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
    [[nodiscard]] std::string generate(const std::string& kgram, size_t L) const;

 private:
    /**
     * @brief Checks if a k-gram is of length k, which is the order of the Markov model.
     * @param kgram The k-gram to check.
     */
    void checkKgram(const std::string& kgram) const;

    /**
     * @brief Returns a random character followed by a specified k-gram .
     * @param kgram The k-gram.
     * @return a random character followed by a specified k-gram.
     */
    [[nodiscard]] char kRand(const std::string& kgram) const;

    /**
     * Returns a random number between 1 (included) and the given total frequency (excluded).
     * @param totalFreq The total frequency of all characters.
     * @return A random number between 1 (included) and the given total frequency (excluded).
     */
    [[nodiscard]] static int getRandomNumber(int totalFreq);

    /**
     * @brief The order of the Markov model.
     */
    size_t m_orderK;

    /**
     * @brief Mapping from character to the index in the symbol table.
     */
    std::unordered_map<char, int> m_charMap;

    /**
     * @brief Mapping from k-grams to frequency store.
     */
    std::unordered_map<std::string, FrequencyStore> m_symbolTable;
};

#endif
